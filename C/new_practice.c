#include <stdio.h>
#include <math.h>
int main(){
	int a,b,x;
	printf("Enter base : \n");
	scanf("%d",&a);
	printf("Enter power: \n");
    scanf("%d",&b);
	x=pow(a,b);
	printf("%d",x);
	
	return 0;
}
