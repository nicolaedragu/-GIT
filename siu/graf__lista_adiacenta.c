#include <stdio.h>
#include <stdlib.h>

// Structura pentru un nod al listei de adiacență
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// Structura pentru lista de adiacență
typedef struct {
    Node** adjList;
    int numNodes;
} Graph;

// Funcție pentru crearea unui nou nod
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Funcție pentru crearea unui graf cu un anumit număr de noduri
Graph* createGraph(int numNodes) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = numNodes;

    // Alocare memorie pentru lista de adiacență
    graph->adjList = (Node**)malloc(numNodes * sizeof(Node*));

    // Inițializare lista de adiacență cu NULL
    for (int i = 0; i < numNodes; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

// Funcție pentru adăugarea unei muchii în graf
void addEdge(Graph* graph, int src, int dest) {
    // Adăugare muchie de la src la dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Adăugare muchie de la dest la src (pentru graf neorientat)
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Funcție pentru afișarea grafului
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numNodes; i++) {
        Node* currentNode = graph->adjList[i];
        printf("Nodul %d: ", i);
        while (currentNode) {
            printf("%d -> ", currentNode->dest);
            currentNode = currentNode->next;
        }
        printf("NULL\n");
    }
}

// Funcție pentru eliberarea memoriei alocate pentru graful cu lista de adiacență
void freeGraph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->numNodes; i++) {
            Node* currentNode = graph->adjList[i];
            while (currentNode) {
                Node* temp = currentNode;
                currentNode = currentNode->next;
                free(temp);
            }
        }
        free(graph->adjList);
        free(graph);
    }
}

int main() {
    int numNodes = 5;
    Graph* graph = createGraph(numNodes);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printGraph(graph);

    freeGraph(graph);

    return 0;
}
