#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

 
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

 
int countTotal(struct Node* root) {
    if (root == NULL)
        return 0;

    return 1 + countTotal(root->left) + countTotal(root->right);
}

 
int countLeaf(struct Node* root) {
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeaf(root->left) + countLeaf(root->right);
}

 
int countInternal(struct Node* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;

    return 1 + countInternal(root->left) + countInternal(root->right);
}

int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Total Nodes: %d\n", countTotal(root));
    printf("Leaf Nodes: %d\n", countLeaf(root));
    printf("Internal Nodes: %d\n", countInternal(root));

    return 0;
}