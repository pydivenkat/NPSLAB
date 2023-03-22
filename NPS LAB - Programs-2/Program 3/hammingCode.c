#include<stdio.h>

int main()
{
    int data[8], recv[8], c, c0, c1, c2;
    printf("Enter the data bits\n");
    scanf("%d", &data[3]);
    scanf("%d", &data[5]);
    scanf("%d", &data[6]);
    scanf("%d", &data[7]);

    data[1] = (data[3]+data[5]+data[7])%2;
    data[2] = (data[3]+data[6]+data[7])%2;
    data[4] = (data[5]+data[6]+data[7])%2;

    printf("The data is: ");
    for(int i=1;i<8;i++)
    {
        printf("%d", data[i]);
    }
    printf("\n Enter the received data: ");
    for(int i=1;i<8;i++)
    {
        scanf("%d", &recv[i]);
    }
    c0 = (recv[1]+recv[3]+recv[5]+recv[7])%2;
    c1 = (recv[2]+recv[3]+recv[6]+recv[7])%2;
    c2 = (recv[4]+recv[5]+recv[6]+recv[7])%2;
    c = c2*4+c1*2+c0*1;
    if(c==0)
    {
        printf("No error");
        return 0;
    }
    printf("Error detected at position %d\n", c);
    recv[c] = recv[c]^1;
    printf("The corrected data is ");
    for(int i=1;i<8;i++)
    {
        printf("%d", recv[i]);
    }
}
