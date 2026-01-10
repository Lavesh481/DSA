#include <stdio.h>
int main(){
    char name[6] = "Lavesh";
    for(int i = 0 ; i<1;i++){
        printf("%c\n",name[i]);
        
    }
    for(int i = 0 ; i<2;i++){
        printf("%c  ",name[i]);
    }
    printf("\n");
    for(int i = 0 ; i<3;i++){
        printf("%c  " , name[i]);
    }
    printf("\n");
    for(int i = 0 ; i<4;i++){
        printf("%c  ",name[i]);
    }
    printf("\n");
    for(int i = 0 ;i<3;i++){
        printf("%c  ",name[i]);
    }printf("\n");
    for(int i = 0 ; i<2;i++){
        printf("%c  ",name[i]);
    }printf("\n");
    

    return 0;
}