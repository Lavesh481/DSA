#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Function to create a new node with the given value
Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory error\n");
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// Function to insert a new node at the front of the linked list
void insert_front(Node** head, int value) {
    Node* new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    new_node->next = *head;
    *head = new_node;
}

// Function to print the values in the linked list
void print_list(Node** head) {
    while (*head != NULL) {
        printf("%d -> ", *head->value);
        *head = *head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;

    // Insert some values into the linked list
    insert_front(&head, 1);
    insert_front(&head, 2);
    insert_front(&head, 3);

    // Print the values in the linked list
    print_list(&head);

    return 0;
}