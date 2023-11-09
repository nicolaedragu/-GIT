#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_key(int distante[], int vizitat[], int nr_noduri)
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < nr_noduri; v++)
        if (vizitat[v] == 0 && distante[v] < min)
        {
            min = distante[v];
            min_index = v;
        }
    return min_index;
}

void PRIMS(Graph *graf)
{
    int nr_noduri;
    nr_noduri = graf->numar_noduri;
    int *parinti = (int *)malloc(nr_noduri * sizeof(int));
    int *distante = (int *)malloc(nr_noduri * sizeof(int));
    int *trecut = (int *)calloc(nr_noduri, sizeof(int));
    
    int i, contor, next;
    for (i = 0; i < nr_noduri; i++)
        distante[i] = INT_MAX;

    distante[0] = 0;    // distanta de la un nod la el insisi = 0
    parinti[0] = -1;
    
    for (contor = 0; contor < nr_noduri - 1; contor++)
    {
        next = min_key(distante, trecut, nr_noduri);
        trecut[next] = 1;

        for (int v = 0; v < nr_noduri; v++)
            if (graf->noduri[next]->distante[v] && trecut[v] == 0 && graf->noduri[next]->distante[v] < distante[v])
            {
                parinti[v] = next;
                distante[v] = graf->noduri[next]->distante[v];
            }
    }

    // in parinti[] avem subarborele minim
}