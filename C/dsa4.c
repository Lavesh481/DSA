#include <stdio.h>
#include <string.h>

int main(){

    printf("Name-Lavesh kumar  ");
    printf("Roll no -25/A03/059\n");  
    char S[20];
    printf("Enter a string\n");
    scanf("%s",&S);
    int count;
    for(int i=0;S[i]!=0;i++){
        count++;
     }

    printf("%d\n",count);
    return 0;
}