#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct List
{
    int vertex;
    struct List *next;
} List;

typedef struct Graph
{
    int n;
    List **adj;
} Graph;

Graph *createGraph(int n)
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->n = n;
    g->adj = (List **)malloc(n * sizeof(List *));
    for (int i = 0; i < n; i++)
    {
        g->adj[i] = NULL;
    }
    return g;
}

void addEdge(Graph *g, int u, int v)
{
    List *node1 = (List *)malloc(sizeof(List));
    node1->vertex = v;
    node1->next = g->adj[u];
    g->adj[u] = node1;

    List *node2 = (List *)malloc(sizeof(List));
    node2->vertex = u;
    node2->next = g->adj[v];
    g->adj[v] = node2;
}

void print(Graph *g)
{
    printf("Graph:\n");
    for (int i = 0; i < g->n; i++)
    {
        printf("%d: ", i);
        List *node = g->adj[i];
        while (node != NULL)
        {
            printf("%d ", node->vertex);
            node = node->next;
        }
        printf("\n");
    }
}

void print_close_friends(Graph *g, int u, int N)
{
    printf("Prietenii apropiati ai %d (grad <= %d):\n", u, N);

    // căutăm toți prietenii cu gradul de prietenie <= N
    int queue[g->n];
    int front = 0, rear = 0;
    bool visited[g->n];
    int degrees[g->n];
    for (int i = 0; i < g->n; i++)
    {
        visited[i] = false;
        degrees[i] = -1;
    }
    visited[u] = true;
    degrees[u] = 0;
    queue[rear++] = u;
    while (front < rear && degrees[queue[front]] < N)
    {
        int v = queue[front++];
        List *node = g->adj[v];
        while (node != NULL)
        {
            int w = node->vertex;
            if (!visited[w])
            {
                visited[w] = true;
                degrees[w] = degrees[v] + 1;
                queue[rear++] = w;
            }
            node = node->next;
        }
    }

    // afișăm toți prietenii cu gradul de prietenie <= N
    for (int i = 0; i < g->n; i++)
    {
        if (visited[i] && i != u && degrees[i] <= N)
        {
            printf("%d (degree %d)\n", i, degrees[i]);
        }
    }
}

void print_friends_of_friends(Graph *g, int u, int N)
{
    printf("Friends of friends of %d (degree <= %d):\n", u, N);
    // determinăm mulțimea tuturor prietenilor
    bool visited[g->n];
    for (int i = 0; i < g->n; i++)
    {
        visited[i] = false;
    }
    visited[u] = true;
    List *node = g->adj[u];
    while (node != NULL)
    {
        visited[node->vertex] = true;
        node = node->next;
    }

    // căutăm toți prietenii prietenilor cu gradul de prietenie <= N
    int queue[g->n];
    int front = 0, rear = 0;
    int degrees[g->n];
    for (int i = 0; i < g->n; i++)
    {
        degrees[i] = -1;
    }
    node = g->adj[u];
    while (node != NULL)
    {
        int v = node->vertex;
        List *neighbor = g->adj[v];
        while (neighbor != NULL)
        {
            int w = neighbor->vertex;
            if (!visited[w])
            {
                visited[w] = true;
                degrees[w] = 2;
                queue[rear++] = w;
            }
            neighbor = neighbor->next;
        }
        node = node->next;
    }
    while (front < rear && degrees[queue[front]] < N)
    {
        int v = queue[front++];
        List *node = g->adj[v];
        while (node != NULL)
        {
            int w = node->vertex;
            if (!visited[w])
            {
                visited[w] = true;
                degrees[w] = degrees[v] + 1;
                queue[rear++] = w;
            }
            node = node->next;
        }
    }

    // afișăm toți prietenii prietenilor cu gradul de prietenie <= N
    for (int i = 0; i < g->n; i++)
    {
        if (visited[i] && i != u && degrees[i] <= N)
        {
            printf("%d (degree %d)\n", i, degrees[i]);
        }
    }
}

int main()
{
    int n = 6;
    Graph *g = createGraph(n);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 3, 4);
    addEdge(g, 3, 5);
    addEdge(g, 4, 5);

    print(g);

    int u = 0;
    int N = 2;
    print_close_friends(g, u, N);
    print_friends_of_friends(g, u, N);

    return 0;
}