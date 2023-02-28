#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

main()
{char  buf[1024];
ssize_t s;
 int sockfd= socket(AF_INET,SOCK_STREAM,0);
 if(sockfd==-1)
 {
  printf("\n Socket error!");
  return 0;
 }
 struct sockaddr_in sockad,serad;
 sockad.sin_family=AF_INET;
 sockad.sin_port=htons(16003);
 sockad.sin_addr.s_addr=inet_addr("127.0.0.1");
 int confd=connect(sockfd,(struct sockaddr*)&sockad,sizeof(sockad));
 printf("\n Enter name of the file : ");
 scanf("%s",buf);
 write(sockfd,buf,sizeof(buf));
 do{
 s = read(sockfd,buf,5);
 if(s==0)
 break;
 printf("%s", buf);
  for(int i=0;i<5;i++)
 buf[i] = '\0';
 }while(s!=0);
 printf("\n Server sent ");
 close(sockfd);
 }
