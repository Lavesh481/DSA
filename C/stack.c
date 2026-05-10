#include <stdio.h>
#include <stdlib.h>

struct stack{
    int size;
    int top;
    int *arr;

}S;


int isFull(){
    if(S.top==S.size-1){
         
        return 1;
    }
    else{
        return 0;

    }
}

int isEmpty(){
    if(S.top==-1){
        return 1;
    }
    else{
        return 0;
    }
}

void push(int value){
    if(isFull()){
        printf("Stak is overflow\n");

    }
    else{
        S.top++;
        S.arr[S.top]=value;
    }
}

int pop(){
    if(isEmpty()){
        printf("Stack is underflow\n");

    }
    else{
        int value=S.arr[S.top];
        S.top--;
        printf("Popped:%d\n",value);
        return value;
         
    }

}

 

void display(){
    if(isEmpty()){
        printf("stack is underflow\n");
    }
    printf("Stack elements:\n");
    for(int i=0;i<=S.top;i++){
        printf("Elements: %d\n",S.arr[i]);
    }
}

int main(){
    S.size=6;
    S.top=-1;
     S.arr=(int*)malloc(S.size*sizeof(int));
    push(10); 
    display();
     


    
}