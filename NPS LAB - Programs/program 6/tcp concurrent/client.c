#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

main()
{
	int socketfd;
	char buff[1024];
	struct sockaddr_in serverAddr;
	socklen_t socketLength;
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == -1)
	{
		printf("Soket failed");
		return 0;
	}
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(6005);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int connStatus = connect(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(connStatus == -1)
	{
		printf("Connect failed");
		return 0;
	}
	printf("Enter a message : ");
	scanf("%s", buff);
	write(socketfd, buff, sizeof(buff));
	read(socketfd, buff, 1024);
	printf("%s", buff);
	fflush(stdout);
	sleep(30);
	close(socketfd);
}

