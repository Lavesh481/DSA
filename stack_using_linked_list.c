#include <stdio.h>
#include <stdlib.h>


struct Node{
    int data;
    struct Node *next;

};



void init(struct Node *ptr){

     struct Node *top;
     top=(struct Node *)malloc(sizeof(struct Node));
     top=ptr;




}

isEmpty(struct Node *ptr){

    if(ptr==NULL){
        return 1;
    }

    return 0;
    
}

isFull(){
    struct Node *n;
    n=(struct Node *)malloc(sizeof(struct Node));
    if(n==NULL){
        return 1;
    }

    return 0;
}



int main(){


    
    struct Node *head;
    struct Node *second;
    struct Node *third;
    struct Node *fourth;

    head=(struct Node *)malloc(sizeof(struct Node));
    second=(struct Node *)malloc(sizeof(struct Node));
    third=(struct Node *)malloc(sizeof(struct Node));
    fourth=(struct Node *)malloc(sizeof(struct Node));

    head->data=10;
    head->next=second;
    second->data=20;
    second->next=third;
    third->data=30;
    third->next=fourth;
    fourth->data=40;
    fourth->next=NULL;
}