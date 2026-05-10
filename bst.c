#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node* prev = NULL;

struct node* createNode(int data){
    struct node *n; 
    n = (struct node *) malloc(sizeof(struct node)); 
        n->data = data; 
        n->left = NULL;
    n->right = NULL; 
    return n;
}

 
int isBST(struct node* root) {
    
    if (root != NULL) {
        
        if (!isBST(root->left))
            return 0;

        if (prev != NULL && root->data <= prev->data)
            return 0;

        prev = root;

        return isBST(root->right);
    }
    
    return 1;
}

int main() {

    struct node* root =createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(2);
    root->left->right = createNode(8);

    if (isBST(root))
        printf("The tree is a Binary Search Tree");
    else
        printf("The tree is NOT a Binary Search Tree");

    return 0;
}