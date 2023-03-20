#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>

main()
{
	int socketfd;
	char buff[1024];
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t socketLength;
	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socketfd == -1)
	{
		printf("Soket failed");
		return 0;
	}
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(6003);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int bindStatus = bind(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(bindStatus==-1)
	{
		printf("Bind failed");
		return 0;
	}
	for(;;)
	{
		socketLength = sizeof(clientAddr);
		recvfrom(socketfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientAddr, &socketLength);
		printf("Server read :  %s", buff);
		fflush(stdout);
		sendto(socketfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientAddr, socketLength);
	}
	close(socketfd);
}
