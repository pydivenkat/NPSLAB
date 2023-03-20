#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#define MULTIPORT 9999
#define MULTIADDR "225.0.0.37"
int main()
{
	int socketfd;
	struct sockaddr_in multicastAddr;
	char buff[] = "HELLLO WORLD";
	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socketfd==-1)
	{
		printf("Socket failed");
		return 0;
	}
	
	multicastAddr.sin_family = AF_INET;
	multicastAddr.sin_port = htons(MULTIPORT);
	multicastAddr.sin_addr.s_addr = inet_addr(MULTIADDR);
	
	for(;;)
	{
		sendto(socketfd, buff, sizeof(buff), 0, (struct sockaddr*)&multicastAddr, sizeof(multicastAddr));
		printf("Message has been sent");
		sleep(30);
	}
}