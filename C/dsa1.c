#include <stdio.h>
#include <stdlib.h>
struct node {
int data;
struct node *next;
};
struct node* search(struct node* start, int x)
{
struct node *temp = start;
while (temp != NULL)
{
if (temp->data == x)
return temp;
temp = temp->next;
}
return NULL;
}
int main()
{

printf("Name-Lavesh Kumar Roll No -25/A03?059\n");
struct node *head = NULL, *temp, *newnode;
int n, x;
printf("Enter number of nodes: ");
scanf("%d", &n);
for (int i = 0; i < n; i++)
{
newnode = (struct node*)malloc(sizeof(struct node));
printf("Enter data: ");
scanf("%d", &newnode->data);
newnode->next = NULL;
if (head == NULL)
{
head = temp = newnode;
}
else
{
temp->next = newnode;
temp = newnode;
}
}
printf("Enter element to search: ");
scanf("%d", &x);
temp = search(head, x);
if (temp != NULL)
printf("Element %d found in linked list\n", temp->data);
else
printf("Element not found in linked list\n");
return 0;
}
