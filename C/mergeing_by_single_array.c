#include <stdio.h>



void merge_by_single_array(int Arr1[],int Arr2[],int low,int mid,int high){

    int i,j,k;
    i=low;
    j=mid+1;
    k=low;
    while(i<=mid&&j<high){
        if(Arr1[i]<Arr1[j]){
            Arr2[k]=Arr1[i];
            k++,i++;

        }

        else{
            Arr2[k]=Arr1[j];
            k++,j++;

        }
    }


    while(i<=mid){
        Arr2[k]=Arr1[i];
        i++,k++;

    }

    while(j<=high){
        Arr2[k]=Arr1[j];
        k++,j++;
    }


    for(int i=0;i<5;i++){
         Arr1[i]=Arr2[j];

    }
}
int main(){

    int A[5]={7,15,2,8,10};
    int B[5];
    merge_by_single_array( A,B,0, 1, 4);




    for(int i=0;i<5;i++){
        printf("%d  ",B[i]);
    }

    
    
    return 0;

}