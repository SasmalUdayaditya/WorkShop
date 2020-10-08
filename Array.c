#include<stdio.h>
void main()
{
	int a[50],i,n,search;
	printf("Enter numbers of array: ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("a[%d]: ",i);
		scanf("%d", &a[i]);
	}
	printf("Enter a number to search:");
	scanf("%d", &search);
	for(i=0;i<=n;i++)
	{
		if(search==a[i])
		{
			printf("Number is found at location a[%d]",i);
			break;
		}
		if(i==n)
		{
			printf("Entered number is not found.");
			break;
		}
	}
	
}