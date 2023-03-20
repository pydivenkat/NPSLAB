#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

int main(int arg,char* argv[])
{char  buf[1024];
 int sockfd= socket(AF_INET,SOCK_STREAM,0);
 if(sockfd==-1)
 {
  printf("\n Socket error!");
  return 0;
 }
 struct sockaddr_in sockad,serad;
 sockad.sin_family=AF_INET;
 sockad.sin_port=htons(5554);
 sockad.sin_addr.s_addr=inet_addr("127.0.0.1");
 int confd=connect(sockfd,(struct sockaddr*)&sockad,sizeof(sockad));
 printf("\n Enter message : ");
 scanf("%s",buf);
 
 write(sockfd,buf,strlen(buf));
 read(sockfd,buf,1024);
 close(sockfd);
 return 0;
 }
