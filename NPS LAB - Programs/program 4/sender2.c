#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<time.h>
#define BROADCASTPORT 9999
#define BROADCASTADDR "10.0.2.255"
int main()
{
	int socketfd, ret;
	struct sockaddr_in broadcastAddr;
	char buff[] = "HELLLO WORLD";
	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socketfd==-1)
	{
		printf("Socket failed");
		return 0;
	}
	int val = 1;
	ret = setsockopt(socketfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val));
	if(ret==-1)
	{
		printf("Setsockopt failed");
		return 0;
	}
	broadcastAddr.sin_family = AF_INET;
	broadcastAddr.sin_port = htons(9999);
	ret = inet_pton(AF_INET, BROADCASTADDR, &broadcastAddr.sin_addr);
	if(ret==1)
	{
		printf("inet_pton successful");
	}
	else
	{
		printf("inet_pton error");
		return 0;
	}
	for(;;)
	{
		sendto(socketfd, buff, sizeof(buff), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr));
		printf("Message has been sent");
		fflush(stdout);
	}
}
