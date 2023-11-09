#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

void insereazaUltim(struct Node **head_ref, int valuare)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = valuare;
    new_node->next = NULL;
    if (*head_ref == NULL)
    {
        new_node->prev = NULL;
        *head_ref = new_node;
    }
    else
    {
        struct Node *last_node = *head_ref;
        while (last_node->next != NULL)
        {
            last_node = last_node->next;
        }
        last_node->next = new_node;
        new_node->prev = last_node;
    }
}

void print_list(struct Node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}

void free_list(struct Node **head_ref)
{
    struct Node *current_node = *head_ref;
    while (current_node != NULL)
    {
        struct Node *temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
    *head_ref = NULL;
}

int main()
{
    int n;
    printf("Introduceți numărul de valori: ");
    scanf("%d", &n);

    int *valori;
    valori=(int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
        printf("Introduceți valoarea: ");
        scanf("%d", &valori[i]);
    }

    struct Node *multiplii[n];
    for (int i = n - 1; i >= 0; i--)
    {
        multiplii[i] = NULL;
        for (int j = 1; j <= n; j++)
        {
            int multiplu = valori[i] * j;
            if (multiplu > valori[i] * n)
                break;
            insereazaUltim(&multiplii[i], multiplu);
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        struct Node *current_node = multiplii[i];
        int max_multiplu = current_node->data;
        while (current_node != NULL)
        {
            if (current_node->data > max_multiplu)
            {
                max_multiplu = current_node->data;
            }
            current_node = current_node->next;
        }
        printf("Cel mai mare multiplu pentru %d este: %d\n", valori[i], max_multiplu);
        free_list(&multiplii[i]);
    }

    return 0;
}
