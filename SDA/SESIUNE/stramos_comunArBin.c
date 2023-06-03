#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *stanga;
    struct Node *dreapta;
};

struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->stanga = newNode->dreapta = NULL;
    return newNode;
}

struct Node *insert(struct Node *node, int value)
{
    if (node == NULL)
        return createNode(value);

    if (value < node->value)
        node->stanga = insert(node->stanga, value);
    else if (value > node->value)
        node->dreapta = insert(node->dreapta, value);

    return node;
}

struct Node *findLowestCommonAncestor(struct Node *root, int nodeA, int nodeB)
{
    if (root == NULL)
        return NULL;

    if (nodeA < root->value && nodeB < root->value)
        return findLowestCommonAncestor(root->stanga, nodeA, nodeB);
    else if (nodeA > root->value && nodeB > root->value)
        return findLowestCommonAncestor(root->dreapta, nodeA, nodeB);

    return root;
}

int main()
{
    struct Node *root = NULL;
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 2);
    insert(root, 7);
    insert(root, 12);
    insert(root, 20);
    insert(root, 25);

    int nodeA = 12;
    int nodeB = 20;
    struct Node *lowestCommonAncestor = findLowestCommonAncestor(root, nodeA, nodeB);

    printf("Lowest Common Ancestor of %d and %d is %d\n", nodeA, nodeB, lowestCommonAncestor->value);

    return 0;
}
