#include <stdio.h>
#include <string.h>

int main(){

    printf("Name-Lavesh kumar  ");
    printf("Roll no -25/A03/059\n");
    char S[20];
    printf("Enter a string\n");
    scanf("%s",&S);
    int n;
    n=strlen(S);
     
    
    

    for(int i=0;S[i]!=0;i++){

    if(S[i]==S[n-1-i]){
                                                             
        return
        printf("String is palindrome\n");
        
    }

    else{
        return
        printf("String is not palindrome\n");
         
    }
 }

    return 0;
}