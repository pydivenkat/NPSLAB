#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<fcntl.h>

main()
{
int socketfd, connectfd, s, fd;
ssize_t readSize;
char buff[1024];
struct sockaddr_in serverAddr, clientAddr;
socklen_t socketLength;
socketfd = socket(AF_INET, SOCK_STREAM, 0);
if(socketfd == -1)
{
printf("Soket failed");
return 0;
}
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(16003);
serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
int bindStatus = bind(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
if(bindStatus==-1)
{
printf("Bind failed");
return 0;
}
int listenStatus = listen(socketfd, 5);
if(listenStatus == -1)
{
printf("Listen failed");
return 0;
}
char path[100];
for(;;)
{
strcpy(path,"");
socketLength = sizeof(clientAddr);
connectfd = accept(socketfd, (struct sockaddr*)&clientAddr, &socketLength);
s = read(connectfd, buff, 1024);
//printf("%s\n", buff);
//printf("%d", strlen(buff));
strcat(path,buff);
strcat(path, ".txt");
printf("File requested : %s\n", path);
fd = open(path, O_RDONLY);
if(fd == -1)
{
	printf("Open failed");
	close(connectfd);
	return 0;
}
fflush(stdout);
do{
		readSize = read(fd, buff, 5);
		if(readSize==0)
		break;
		write(connectfd, buff, readSize);
		printf("%s->%ld\n", buff, readSize);
		 for(int i=0;i<5;i++)
 buff[i] = '\0';
}while(readSize!=0);
close(fd);
close(connectfd);
}
close(socketfd);
}
