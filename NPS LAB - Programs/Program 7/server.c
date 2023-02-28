#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_cmd(int clientsockfd){
    char buf[100];
    read(clientsockfd, buf, 100);
    FILE *fp;
    char path[1035], output[5000], newline='\n';
    fp = popen(buf, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    memset(output, '\0', sizeof(output));
    while (fgets(path, sizeof(path), fp)!=NULL) {
        strcat(output, path);
        strcat(output, "\n");
        memset(path, '\0', sizeof(path));
    }
    write(clientsockfd, output, sizeof(output));
    pclose(fp);
}

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    struct in_addr ip_addr;
    ip_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_addr = ip_addr;
    addr.sin_port = htons(16002);
    if((bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr)))<0)
    {
    	printf("Bind failed!");
    	return -1;
    }
    listen(sockfd, 10);
    struct sockaddr_in clientaddr;
    pid_t pid;
    while(1){
    socklen_t clientsocklen = sizeof(clientaddr);
        int clientsockfd = accept(sockfd, (struct sockaddr*)&clientaddr, &clientsocklen);
         pid = fork();
        if(pid==0){
            close(sockfd);
            execute_cmd(clientsockfd);
            close(clientsockfd);
            break;
        }
        else
            close(clientsockfd);
    }
}
