#include<stdio.h>

int main()
{
//sender
int data[100], redundant[100], sent[100];
int i;
printf("Enter the 4 data bits : ");
for(i=3;i>=0;i--)
{
scanf("%d", &data[i]);
}
redundant[0] = (data[0]+data[1]+data[3])%2;
redundant[1] = (data[0]+data[2]+data[3])%2;
redundant[2] = (data[1]+data[2]+data[3])%2;
sent[0] = (redundant[0]+redundant[1]+redundant[2]+data[0]+data[1]+data[2]+data[3])%2;
sent[1] = redundant[0];
sent[2] = redundant[1];
sent[3] = data[0];
sent[4] = redundant[2];
sent[5] = data[1];
sent[6] = data[2];
sent[7] = data[3];
for(i=0;i<8;i++){
printf(" %d",sent[i]);
}
printf("\n");
//receiver
int rcvd[100];
printf("Enter the 8 bits received : ");
for(i=0;i<=7;i++)
{
scanf("%d", &rcvd[i]);
}
int datar[100], redundantr[100], syndrome[100];
datar[0] = rcvd[3];
datar[1] = rcvd[5];
datar[2] = rcvd[6];
datar[3] = rcvd[7];
redundantr[0] = rcvd[1];
redundantr[1] = rcvd[2];
redundantr[2] = rcvd[4];
printf("Redundant : %d %d %d\nData received : %d %d %d %d", redundantr[0], redundantr[1], redundantr[2], datar[0], datar[1], datar[2], datar[3]);
syndrome[0] = (redundantr[0]+datar[0]+datar[1]+datar[3])%2;
syndrome[1] = (redundantr[1]+datar[0]+datar[2]+datar[3])%2;
syndrome[2] = (redundantr[2]+datar[1]+datar[2]+datar[3])%2;
printf("Syndrome bits : %d %d %d\n", syndrome[0], syndrome[1], syndrome[2]);

if(syndrome[0]==0 && syndrome[1]==0 && syndrome[2]==0)
{
	printf("packet is Error free");
}
else if(syndrome[0]==0 && syndrome[1]==0 && syndrome[2]==1)
{
	printf("Error in Bit 4");
	rcvd[4] = (rcvd[4]==1)?0:1;
}
else if(syndrome[0]==0 && syndrome[1]==1 && syndrome[2]==0)
{
	printf("Error in Bit 2");
	rcvd[2] = (rcvd[2]==1)?0:1;
}
else if(syndrome[0]==0 && syndrome[1]==1 && syndrome[2]==1)
{
	printf("Error in Bit 6");
	rcvd[6] = (rcvd[6]==1)?0:1;
}
else if(syndrome[0]==1 && syndrome[1]==0 && syndrome[2]==0)
{
	printf("Error in Bit 1");
	rcvd[1] = (rcvd[1]==1)?0:1;
}
else if(syndrome[0]==1 && syndrome[1]==0 && syndrome[2]==1)
{
	printf("Error in Bit 5");
	rcvd[5] = (rcvd[5]==1)?0:1;
}
else if(syndrome[0]==1 && syndrome[1]==1 && syndrome[2]==0)
{
	printf("Error in Bit 3");
	rcvd[3] = (rcvd[3]==1)?0:1;
}
else if(syndrome[0]==1 && syndrome[1]==1 && syndrome[2]==1)
{
	printf("Error in Bit 7");
	rcvd[7] = (rcvd[7]==1)?0:1;
}
printf("Received data : ");
for(i=0;i<8;i++)
printf("%d\t", rcvd[i]);
}
