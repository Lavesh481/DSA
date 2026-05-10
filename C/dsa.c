#include <stdio.h>
int main(){
    int arr[7]={1,2,3,4,5,6,7};
    int n=7;
    int d=3;
 
    int temp[3]= {1,2,3};
    int i;
    
    for(i=d;i<n;i++){
        arr[i-d]=arr[i];

    }

    for(int i=n-d;i<n;i++){
        arr[i]=temp[i-(n-d)];
    }
    
    for(int i=0;i<n;i++){
        printf("%d\n",arr[i]);
        

    }

    return 0;
}