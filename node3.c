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

int isFullBinaryTree(struct Node* root) {
    if (root == NULL)
        return 1;

    // Leaf node
    if (root->left == NULL && root->right == NULL)
        return 1;

    // Both children present
    if (root->left && root->right)
        return isFullBinaryTree(root->left) &&
               isFullBinaryTree(root->right);

    return 0;
}

int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);

    if (isFullBinaryTree(root))
        printf("Tree is Full Binary Tree\n");
    else
        printf("Tree is NOT Full Binary Tree\n");

    return 0;
}