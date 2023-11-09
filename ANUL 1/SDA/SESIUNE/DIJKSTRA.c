#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_key(int distante[], int vizitat[], int nr_noduri)
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < nr_noduri; v++)
        if (vizitat[v] == 0 && distante[v] <= min)
        {
            min = distante[v];
            min_index = v;
        }
    return min_index;
}

void DIJKSTRA(Graph *graf, int sursa)
{
    int i, v, contor, next, nr_noduri = graf->numar_noduri;
    int *trecut = (int *)calloc(nr_noduri, sizeof(int));
    int *distante = (int *)malloc(nr_noduri * sizeof(int));

    for (i = 0; i < nr_noduri; i++)
        distante[i] = INT_MAX;

    trecut[sursa] = 1;
    distante[sursa] = 0;

    for (contor = 0; contor < nr_noduri - 1; contor++)
    {
        next = min_key(distante, trecut, nr_noduri);
        trecut[next] = 1;

        for (v = 0; v < nr_noduri; v++)
            if (graf->noduri[next]->distante[v] && trecut[v] == 0 &&
                distante[next] != INT_MAX &&
                distante[next] + graf->noduri[next]->distante[v] < distante[v])
            {
                distante[v] = distante[next] + graf->noduri[next]->distante[v];
            }
    }

    // in distante[] avem toate distantele de la nodul SURSA la oricare alt nod
}