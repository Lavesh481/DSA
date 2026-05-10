#include <stdio.h>
#include <string.h>

int main(){
    int arr[]={4,6,2,5,7,9,1,3};
    int size=strlen(arr);
    int low;
    int high;
    int pivot=arr[low];
    int left;
    int right;
    int temp;
    for(int i=0;i<size;i++){
        if(arr[i]>=pivot){
            left=arr[i];

        }

        for(int j=size;j>0;j--){
            if(arr[j]<=pivot){
                right=arr[j];
            }
        }

        temp=right;
        right=left;
        left=temp;


    }
    
    for(int i=0;i<n;i++){
        printf("%d\n",arr[i]);
    }
    return 0;

}