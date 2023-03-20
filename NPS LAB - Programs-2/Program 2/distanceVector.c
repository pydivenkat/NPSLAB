#include<stdio.h>
#include<stdlib.h>
#define INF 999
int G[100][100], n, selected[100], P[100], d[100];
int getMinDistAndNotSelectedNode()
{
	int i, min = INF, node;
	for(i=0;i<n;i++)
	{
		if(!selected[i] && min>d[i])
		{
			min = d[i];
			node = i;
		}
	}
	return node;
}
void display(int source)
{
	printf("For Source %d:\n", source);
	int i, j;
	for(i=0;i<n;i++)
	{
	j = i;
	if(j!=source){
	while(j!=source)
	{
		printf("%d->", j);
		j = P[j];
	}
	printf("%d\tdist : %d\n", j, d[i]);
	}
	}
}
void distanceVectorCalc(int source)
{
	int i, minNode, j, count =0;
	for(i=0;i<n;i++)
	{
		d[i] = INF;
		P[i] = -1;
	}
	d[source] = 0;
	for(j=1;j<=n-1;j++){
	minNode = getMinDistAndNotSelectedNode();
	selected[minNode] = 1;
	for(i=0;i<n;i++)
	{
		if(!selected[i] && d[i]>d[minNode]+G[minNode][i])
		{
			d[i] = d[minNode] + G[minNode][i];
			P[i] = minNode;
			count++;
		}
	}}
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	if(d[j]>d[i]+G[i][j])
	{
		printf("Negative edge");
		//return 0;
	}
		display(source);
}
int main()
{
	int i, j;
	printf("Enter the no. of routers : ");
	scanf("%d", &n);
	printf("Enter the adjacency matrix : ");
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	scanf("%d", &G[i][j]);
	i =0;
	for(i=0;i<n;i++)
	{
		distanceVectorCalc(i);
		for(j=0;j<n;j++){
		selected[j] = 0;}
	}
}
