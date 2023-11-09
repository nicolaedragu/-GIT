#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

void insert(Node **head, Node **tail, int valoare)
{
    Node *temp;
    temp = (Node *)malloc(sizeof(Node));
    temp->data = valoare;
    temp->next = NULL;
    if (*head == NULL)
    {
        temp->prev = NULL;
        *head = temp;
        *tail = temp;
    }
    else
    {
        temp->prev = *tail;
        (*tail)->next = temp;
        *tail = (*tail)->next;
    }
}

void create(Node **head, Node **tail)
{
    int valoare;
    while (1)
    {
        printf("introduceti valoarea: (-1 pentru a iesi)\n");
        scanf("%d", &valoare);
        if (valoare == -1)
            break;
        insert(head, tail, valoare);
    }
}

void print(Node *node)
{
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    puts("");
}

void print_invers(Node *tail)
{
    while (tail)
    {
        printf("%d ", tail->data);
        tail = tail->prev;
    }
    puts("");
}

void parcurgere(Node *head, Node *tail, int k, int contor)
{
    contor = 0;
    int gasit = 0;
    while (contor != k && gasit == 0)
    {
        if (head)
            contor++;
        else
        {
            printf("eroare\n");
            gasit = 1;
        }
        if (contor == k)
        {
            printf("al %d-lea element = %d\n", k, head->data);
            gasit = 1;
        }
        if (gasit == 0)
        {
            if (tail)
                contor++;
            else
            {
                printf("eroare\n");
                gasit = 1;
            }
        }
        if (contor == k && gasit == 0)
        {
            printf("al %d-lea element = %d\n", k, tail->data);
            gasit = 1;
        }
        head = head->next;
        tail = tail->prev;
    }
}

int main()
{
    int k, contor = 0;
    printf("K = \n");
    scanf("%d", &k);
    Node *head = NULL;
    Node *tail = NULL;
    create(&head, &tail);
    print(head);
    // print_invers(tail);
    parcurgere(head, tail, k, contor);

    return 0;
}