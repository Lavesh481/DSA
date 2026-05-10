#include <stdio.h>
#include <stdlib.h>

struct stack{
    int size;
    int top;
    int *arr;

}S;


int isEmpty(){
    if(S.top==-1){
        return 1;
    }

    else{
        return 0;
    }
}

int isFull(){
    if(S.top==S.size-1){
        return 1;
    }
    else {
        return 0;
    }
}

void push(int value){
    if(isFull()){
        printf("Stack is overflow\n");
         
    }

    else{
        S.top++;
        S.arr[S.top]=value;
         
    }



}
int peek(){
    if(S.top==-1){
        printf("Stack is underflow\n");
        return -1;
    }

    else{
        printf("Top Element is:%d\n",S.arr[S.top]);
        return S.arr[S.top];
    }
}


int pop(){
    if(isEmpty()){
        printf("Stack is underflow\n");


    }

    else{
        int value=S.arr[S.top];
        S.top--;
        printf("Popped %d from Stack\n",value);
        return value;
    }
}


void display(){
    if(S.top==-1){
        printf("stack is underflow\n");

    }

    
        for(int i=0;i<=S.top;i++){
            printf("Element:%d\n",S.arr[i]);
    
    }
}






int main(){
    S.size=5;
    S.top=-1;
    S.arr=(int *)malloc(S.size*sizeof(int));
    push(10);
    push(20);
    display();
    peek();
    pop();
    display();
    peek();

}