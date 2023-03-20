#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void execute_cmd(int sockfd){
    char buf[5000];
    while(1){
        scanf("%[^\n]s", buf);
        write(sockfd, buf, sizeof(buf));
        read(sockfd, buf, sizeof(buf));
        printf("Returned from server: %s\n", buf);
        getchar();
    }
}

int main(int argc, char const *argv[]){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    struct in_addr ip_addr;
    ip_addr.s_addr = inet_addr("127.0.0.1");
    //ip_addr.s_addr = htonl(0x7f000001);
    addr.sin_addr = ip_addr;
    addr.sin_port = htons(16002);
    connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
    execute_cmd(sockfd);
    close(sockfd);
}
