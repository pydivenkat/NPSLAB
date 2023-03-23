#include<sys/types.h> 
#include<sys/socket.h> 
#include<sys/stat.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<fcntl.h> 
#include<arpa/inet.h> 
#include<netinet/in.h> 


void str_cli(FILE *fp,int sockfd)
{ 
    int bufs=1024,cont; 
    char *buff = malloc(bufs); 
    while((fgets(buff,bufs,fp)!=NULL))
    {
        send(sockfd,buff,bufs,0); 
        if((cont = recv(sockfd,buff,bufs,0)) >=0)
        { 
            printf("Server replied :"); 
            fputs(buff,stdout); 
        }
    }
    printf("str cli\n"); 
    printf("\nEOF\n"); 
}


int main()
{ 
    int create_socket,ret; 
    struct sockaddr_in address; 
    if((create_socket = socket(AF_INET,SOCK_STREAM,0)) >0) 
        printf("Socket created\n"); 
    else 
        printf("Socket creation error"); 
    address.sin_family = AF_INET; 
    address.sin_port = htons(15002); 
    address.sin_addr.s_addr=inet_addr("127.0.0.1");
    if( (ret=connect(create_socket,(struct sockaddr *) &address,sizeof(address))) ==  0) 
        printf("Connected\n"); 
    else 
        printf("Error in connect"); 
    str_cli(stdin,create_socket); 
    return 0; 
} 
