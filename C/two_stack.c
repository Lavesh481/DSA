#include <stdio.h>
#include <stdlib.h>

struct stacki1{
    int size;
    int top;
    int *arr;

}S1;

struct stack2{
    int size;
    int top;
    int *arr;

}S2;








int isEmpty1(){
    if(S1.top==-1){
        return 1;
    }

    else{
        return 0;
    }
}

int isFull1(){
    if(S1.top==S1.size-1){
        return 1;
    }
    else {
        return 0;
    }
}

void push1(int value){
    if(isFull1()){
        printf("Stack is overflow\n");
         
    }

    else{
        S1.top++;
        S1.arr[S1.top]=value;
         
    }



}
int peek1(){
    if(S1.top==-1){
        printf("Stack is underflow\n");
        return -1;
    }

    else{
        printf("Top Element is:%d\n",S1.arr[S1.top]);
        return S1.arr[S1.top];
    }
}


int pop1(){
    if(isEmpty1()){
        printf("Stack is underflow\n");


    }

    else{
        int value=S1.arr[S1.top];
        S1.top--;
        printf("Popped %d from Stack\n",value);
        return value;
    }
}


void display1(){
    if(S1.top==-1){
        printf("stack is underflow\n");

    }

    
        for(int i=0;i<=S1.top;i++){
            printf("Element:%d\n",S1.arr[i]);
    
    }
     
}



int isEmpty2(){
    if(S2.top==-1){
        return 1;
    }

    else{
        return 0;
    }
}

int isFull2(){
    if(S2.top==S2.size-1){
        return 1;
    }
    else {
        return 0;
    }
}

void push2(int value){
    if(isFull2()){
        printf("Stack is overflow\n");
         
    }

    else{
        S2.top++;
        S2.arr[S2.top]=value;
         
    }



}
int peek2(){
    if(S2.top==-1){
        printf("Stack is underflow\n");
        return -1;
    }

    else{
        printf("Top Element is:%d\n",S2.arr[S2.top]);
        return S2.arr[S2.top];
    }
}


int pop2(){
    if(isEmpty2()){
        printf("Stack is underflow\n");


    }

    else{
        int value=S1.arr[S1.top];
        S2.top--;
        printf("Popped %d from Stack\n",value);
        return value;
    }
}


void display2(){
    if(S2.top==-1){
        printf("stack is underflow\n");

    }

    
        for(int i=0;i<=S2.top;i++){
            printf("Element2:%d\n",S2.arr[i]);
             
    
    }
}






int main(){
    S1.size=5;
    S1.top=-1;
    S1.arr=(int *)malloc(S1.size*sizeof(int));
    push1(10);
    push1(20);
    display1();
    peek1();
    pop1();
    display1();
    printf("\n \n");
    S2.size=5;
    S2.top=-1;
    S2.arr=(int *)malloc(S2.size*sizeof(int));
    push2(20);
    push2(30);
    display2();
    peek2();
    pop2();
    display2();

    
     

}