#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};


void linked_list_traversal(struct Node *ptr){

    while(ptr!=NULL){
        printf("Element: %d\n",ptr->data);
        ptr=ptr->next;
    }





}


void insertAtbeginning(struct Node **head,int data){
    
    struct Node *ptr;
    ptr=(struct Node *)malloc(sizeof(struct Node));
    ptr->data=0;
    ptr->next=*head;
    *head=ptr;


     
    

}

void insertAtend(struct Node **head,int value){

    struct Node *new_node;
    new_node=(struct Node *)malloc(sizeof(struct Node));
    new_node->data=60;
    new_node->next=NULL;
    
    
     
    
    if(*head==NULL){
        *head=new_node;

    }

    struct Node *last=*head;
    while(last->next!=NULL){
        last=last->next;

    }

    last->next=new_node;



}


int main(){

    
    struct Node *head;
    struct Node *second;
    struct Node *third;
    struct Node *fourth;
    struct Node *fifth;
    
    
   
    head=(struct Node *)malloc(sizeof(struct Node));
    second=(struct Node *)malloc(sizeof(struct Node));
    third=(struct Node *)malloc(sizeof(struct Node));
    fourth=(struct Node *)malloc(sizeof(struct Node));
    fifth=(struct Node *)malloc(sizeof(struct Node));


    
    
    
    head->data=10;
    head->next=second;
    second->data=20;
    second->next=third;
    third->data=30;
    third->next=fourth;
    fourth->data=40;
    fourth->next=fifth;
    fifth->data=50;
    fifth->next=NULL;
    insertAtbeginning(&head,0);
    insertAtend(&head,60);
    linked_list_traversal(head);

}
