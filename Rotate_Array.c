#include <stdio.h>
int main(){
    int n;
    printf("Enter size of array:\n");
    scanf("%d",&n);
    int arr[n];
    int temp;
    for(int i=0;i<n;i++){
        printf("enter array element\n");

        scanf("%d",&arr[i]);
    }
        
    temp=arr[4];

    for(int i=4;i>=0;i--){

        arr[i]=arr[i-1];

    }
    arr[0]=temp;

    for(int i=0;i<n;i++){

        printf("%d",arr[i]);

    }

    return 0;

}


