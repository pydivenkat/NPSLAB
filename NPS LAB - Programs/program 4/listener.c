#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define MULTIPORT 9999
#define MULTIADDR "225.0.0.37"
int main()
{
	int socketfd, ret;
	u_int status = 1;
	char buff[1024];
	struct sockaddr_in listenerAddr, senderAddr;
	struct ip_mreq joinDetails;
	socklen_t senderAddrLen;
	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socketfd==-1)
	{
		printf("Socket failed");
		return 0;
	}
	ret = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &status, sizeof(status));
	if(ret==-1)
	{
		printf("setsockopt Resuse failed");
		return 0;
	}
	listenerAddr.sin_family = AF_INET;
	listenerAddr.sin_port = htons(MULTIPORT);
	listenerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(socketfd, (struct sockaddr*)&listenerAddr, sizeof(listenerAddr));
	if(ret==-1)
	{
		printf("Bind failed");
		return 0;
	}
	joinDetails.imr_multiaddr.s_addr = inet_addr(MULTIADDR);
	joinDetails.imr_interface.s_addr = htonl(INADDR_ANY);
	ret = setsockopt(socketfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &joinDetails, sizeof(joinDetails));
	if(ret==-1)
	{
		printf("Membership could not be added");
		return 0;
	}
	for(;;)
	{
		senderAddrLen = sizeof(senderAddr);
		recvfrom(socketfd, buff, sizeof(buff), 0,(struct sockaddr*)&senderAddr, &senderAddrLen);
		puts(buff);
	}
}
