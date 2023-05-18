/* DRAGU Nicolae - 314CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int numar_noduri;
    int **mat_ad;
    
} Graph;

void alocareMatAd(int ***mat, int nr_nod)
{
    int i;
    *mat = (int **)malloc(nr_nod * sizeof(int*));
    for (i = 0; i < nr_nod; i++)
        (*mat)[i] = (int *)malloc(nr_nod * sizeof(int));
}

Graph *creareGraph(int numar_noduri)
{
    int i, j;
    Graph *harta = (Graph *)malloc(sizeof(Graph));
    harta->numar_noduri = numar_noduri;
    
    alocareMatAd(&(harta->mat_ad), harta->numar_noduri);
    // Initialize the adjacency matrix
    for (i = 0; i < numar_noduri; i++)
    {
        for (j = 0; j < numar_noduri; j++)
        {
            harta->mat_ad[i][j] = 0;
        }
    }
    return harta;
}

void creareMatrix(Graph **graf, int noduri, int muchii, FILE *f)
{
    char obiectiv1[20];
    char obiectiv2[20];
    int lungime, i, k1 = 0, k2 = 1;
    for (i = 0; i < muchii; i++)
    {
        fscanf(f, "%s", obiectiv1);
        fscanf(f, "%s", obiectiv2);
        fscanf(f, "%d", &lungime);
        // printf ("%s %s %d\n", obiectiv1, obiectiv2, lungime);
        // (*graf)->mat_ad[][] = 1
    }
    
}

int main()
{
    FILE *f = fopen("tema3.in", "r");
    int n, m;
    fscanf(f, "%d", &n);
    fscanf(f, "%d", &m);
    Graph *harta = creareGraph(n);
    creareMatrix(&harta, n, m, f);
    
}