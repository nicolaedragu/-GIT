/*
arbore de expresie.
Găsiți valoarea expresiei.
*/
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char data;
    struct Node *stanga;
    struct Node *dreapta;
};

struct Node *createNode(char data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->stanga = newNode->dreapta = NULL;
    return newNode;
}

int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 1;
    return 0;
}

int evaluateExpression(struct Node *root)
{
    if (root == NULL)
        return 0;

    if (root->stanga == NULL && root->dreapta == NULL)
        return root->data - '0';

    int stangaValue = evaluateExpression(root->stanga);
    int dreaptaValue = evaluateExpression(root->dreapta);

    if (isOperator(root->data))
    {
        if (root->data == '+')
            return stangaValue + dreaptaValue;
        else if (root->data == '-')
            return stangaValue - dreaptaValue;
        else if (root->data == '*')
            return stangaValue * dreaptaValue;
        else if (root->data == '/')
            return stangaValue / dreaptaValue;
    }

    return 0;
}

int main()
{
    struct Node *root = createNode('+');
    root->stanga = createNode('*');
    root->stanga->stanga = createNode('5');
    root->stanga->dreapta = createNode('4');
    root->dreapta = createNode('-');
    root->dreapta->stanga = createNode('7');
    root->dreapta->dreapta = createNode('2');

    int result = evaluateExpression(root);
    printf("Rezultatul expresiei este: %d\n", result);

    return 0;
}
