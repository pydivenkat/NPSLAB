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
	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socketfd == -1)
	{
		printf("Soket failed");
		return 0;
	}
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(6003);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	printf("Enter a message : ");
	scanf("%s", buff);
	socketLength = sizeof(serverAddr);
	sendto(socketfd, buff, sizeof(buff), 0, (struct sockaddr*)&serverAddr, socketLength);
	memset(buff, 0, sizeof(buff));
	memset(&serverAddr, 0, sizeof(serverAddr));
	recvfrom(socketfd, buff, sizeof(buff), 0, (struct sockaddr*)&serverAddr, &socketLength);
	printf("%s", buff);
	close(socketfd);
}

