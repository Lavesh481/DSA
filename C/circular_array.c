#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5

typedef struct {

    int arr[CAPACITY];
    int front;
    int rear; 
    int size;
    
}CircularQueue;


void intit(CircularQueue *q){
    q->front=0;
    q->rear=-1;
    q->size=0;
}

int isFull(CircularQueue *q){
    return q->size==CAPACITY;

}

int isEmpty(CircularQueue *q){
    return q->size==0;
}



int enqueue(CircularQueue *q,int value){
    if(isFull(q)) {
        printf("Array is Overflow\n");
    }

    q->rear=(q->rear+1)%CAPACITY;
    q->arr[q->rear]=value;
    q->size++;


}

int dequeue(CircularQueue *q){

     if(isEmpty(q)){
        printf("Array is overflow\n");
     }

    int removed=q->arr[q->front];
    q->front=(q->front+1)%CAPACITY;
    q->size--;
}


int display(CircularQueue *q){

    if(isEmpty(q)){
        printf("Array is underflow\n");
    }

    for(int i=0;i<q->size;i++){
        printf("Queue:  %d\n",q->arr[(q->front+i)%CAPACITY]);
    }

}








int main(){

    CircularQueue q;

    enqueue(&q,10);
    enqueue(&q,20);
    enqueue(&q,30);

    display(&q);
    enqueue(&q,40);
    enqueue(&q,50);
    
}