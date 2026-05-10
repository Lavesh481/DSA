#include <stdio.h>




void merge(int A[],int B[],int C[],int m,int n){

    int i,j,k;
    i=j=k=0;
    while(i<m&&j<n){
        if(A[i]<B[j]){
            C[k]=A[i];
            i++,k++;

        }
        else{
            C[k]=B[j];
            k++;j++;
        }
    }


    while(i<m){
        C[k]=A[i];
        k++,i++;
    }
    

    while(j<n){
        C[k]=B[j];
        k++,j++;
    }
}
int main(){
    int Arr1[]={2,1,3};
    int Arr2[]={5,6,4};
    int Arr3[6];
    merge(Arr1,Arr2,Arr3,3,3);
    for(int i=0;i<6;i++){
        printf("%d"  ,Arr3[i]);
    }
    return 0;
}