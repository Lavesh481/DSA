#include <stdio.h>
#include <stdlib.h>


struct queue {
    int size;
    int f;
    int r;
    int *arr;

}q;



int isempty(struct queue *q){
    if(q->f==q->r){
        return 1;

    }
    return 0;

}


int main(){
    q.size=5;
    q.f=-1;
    q.r=-1;
    q.arr=(int*)malloc(q.size*sizeof(int));
    

}