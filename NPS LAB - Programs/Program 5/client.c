#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
void str_echo(FILE *fp,int sockfd)
{
	int n=1024,cont;
	char *buf=malloc(n);
	while(fgets(buf,n,fp)!=NULL)
	{
		//printf("\nEnter the string:\n");
		//scanf("%s",buf);
		send(sockfd,buf,n,0);
	
	//	printf("%s",buf);
		while((n=recv(sockfd,buf,n,0))<0);
			fputs(buf,stdout);
	}
	printf("\nEOF\n");
}
int main(int argc,char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;
	printf("%s\n",argv[1]);
	if(sockfd=socket(AF_INET,SOCK_STREAM,0))
		printf("\nSocket created\n");
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(15001);
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	
	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	str_echo(stdin,sockfd);
	close(sockfd);
}
