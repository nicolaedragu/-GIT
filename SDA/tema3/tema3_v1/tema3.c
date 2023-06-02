/* DRAGU Nicolae - 314CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int index;
    char obiectiv[20];
    struct Node *urm;
    int *distante;
} Node;

typedef struct Graph
{
    int numar_noduri;
    int numar_muchii;
    Node **noduri;
    char **obiective;
    int obiective_index;
} Graph;

Graph *creareGraph(int n, int m)
{
    int i;
    Graph *harta = (Graph *)malloc(sizeof(Graph));
    harta->numar_noduri = n;
    harta->numar_muchii = m;

    harta->noduri = (Node **)malloc(n * sizeof(Node *));
    harta->obiective = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; i++)
    {
        harta->noduri[i] = (Node *)malloc(sizeof(Node));
        harta->noduri[i]->index = i;
        harta->noduri[i]->urm = NULL;
        harta->obiective[i] = (char *)malloc(20 * sizeof(char));
    }
    harta->obiective_index = 0;

    return harta;
}

void actualizareNode(Node **locatie, int index, char obiectiv[20], Node *next)
{
    strcpy((*locatie)->obiectiv, obiectiv);
    (*locatie)->index = index;
    (*locatie)->urm = next;
}

Node *creareNode(int nr_noduri)
{
    int i;
    Node *locatie = (Node *)malloc(sizeof(Node));
    locatie->distante = (int *)malloc(nr_noduri * sizeof(int));
    for (i = 0; i < nr_noduri; i++)
        locatie->distante[i] = 0;
    return locatie;
}

void Muchie(Graph *harta, char obiectiv1[20], char obiectiv2[20], int distanta)
{
    int i, index1 = -1, index2 = -1;
    for (i = 0; i < harta->obiective_index; i++)
    {
        if (strcmp(harta->obiective[i], obiectiv1) == 0)
            index1 = i;
        if (strcmp(harta->obiective[i], obiectiv2) == 0)
            index2 = i;
    }
    if (index1 == -1)
    {
        strcpy(harta->obiective[harta->obiective_index], obiectiv1);
        index1 = harta->obiective_index;
        harta->obiective_index++;
    }
    if (index2 == -1)
    {
        strcpy(harta->obiective[harta->obiective_index], obiectiv2);
        index2 = harta->obiective_index;
        harta->obiective_index++;
    }
    actualizareNode(&(harta->noduri[index2]), index2, obiectiv2, harta->noduri[index1]);
    harta->noduri[index2]->distante[index1] = distanta;
    actualizareNode(&(harta->noduri[index1]), index1, obiectiv1, harta->noduri[index1]);
    harta->noduri[index1]->distante[index2] = distanta;
}

void citesteHarta(Graph **harta, FILE *f)
{
    char obiectiv1[20];
    char obiectiv2[20];
    int distanta, i;

    // initializare distante cu 0
    for (i = 0; i < (*harta)->numar_noduri; i++)
        (*harta)->noduri[i] = creareNode((*harta)->numar_noduri);

    for (i = 0; i < (*harta)->numar_muchii; i++)
    {
        fscanf(f, "%s", obiectiv1);
        fscanf(f, "%s", obiectiv2);
        fscanf(f, "%d", &distanta);
        Muchie((*harta), obiectiv1, obiectiv2, distanta);
    }
}

int *determinareVecini(Node *nod, int numar_noduri, int *capat)
{
    int i, k;
    int *vecini;
    k = 0;
    for (i = 0; i < numar_noduri; i++)
        if (nod->distante[i] != 0)
            k++;
    vecini = (int *)malloc(k * sizeof(int));
    k = 0;
    for (i = 0; i < numar_noduri; i++)
        if (nod->distante[i] != 0)
            vecini[k++] = i;
    *capat = k;
    return vecini;
}

void dfs(Graph *harta, int i, int *trecut, int *vecini, int capat, int *contor)
{
    int j;
    trecut[i] = 1;
    vecini = determinareVecini(harta->noduri[i], harta->numar_noduri, &capat);
    for (j = 0; j < capat; j++)
    {
        if (trecut[vecini[j]] == 0)
        {
            *contor = *contor + 1;
            dfs(harta, vecini[j], trecut, vecini, capat, contor);
        }
    }
}

int *determinareStPoints(Graph *harta, int zone, int *contori)
{
    int *starting_points = (int *)malloc(zone * sizeof(int));
    int i, *trecut, k = 0, *vecini, capat, contor = 0;
    trecut = (int *)calloc(harta->numar_noduri, sizeof(int));
    for (i = 0; i < harta->numar_noduri; i++)
    {
        vecini = determinareVecini(harta->noduri[i], harta->numar_noduri, &capat);
        if (trecut[i] == 0)
        {
            dfs(harta, i, trecut, vecini, capat, &contor);
            contori[k] = contor;
            starting_points[k++] = i;
            contor = 0;
        }
        free(vecini);
    }

    free(trecut);
    return starting_points;
}

int determinareZone(Graph *harta)
{
    int i, *trecut, k = 0, *vecini, capat, contor = 0;
    trecut = (int *)calloc(harta->numar_noduri, sizeof(int));
    for (i = 0; i < harta->numar_noduri; i++)
    {
        vecini = determinareVecini(harta->noduri[i], harta->numar_noduri, &capat);
        if (trecut[i] == 0)
        {
            dfs(harta, i, trecut, vecini, capat, &contor);
            k++;
            contor = 0;
        }
        free(vecini);
    }

    free(trecut);
    return k;
}
// -----------------------
void gasireMinimDFS(Graph *harta, int i, int *trecut, int *vecini, int capat, int *drum)
{
    int j, copie_indice, copie_distanta;
    trecut[i] = 1;
    vecini = determinareVecini(harta->noduri[i], harta->numar_noduri, &capat);
    copie_distanta = 99999;
    copie_indice = -1;
    for (j = 0; j < capat; j++)
        if (trecut[vecini[j]] == 0)
            if (harta->noduri[i]->distante[vecini[j]] < copie_distanta)
            {
                copie_distanta = harta->noduri[i]->distante[vecini[j]];
                copie_indice = vecini[j];
            }
    if (copie_indice == -1)
        return;

    *drum += copie_distanta;
    gasireMinimDFS(harta, copie_indice, trecut, vecini, capat, drum);
}

int gasire_vecin_minim(Graph *harta, int *distante, int *trecut)
{
    int min = 99999, min_index, i;
    for (i = 0; i < harta->numar_noduri; i++)
        if ((trecut[i] == 0) && (distante[i] < min))
        {
            min = distante[i];
            min_index = i;
        }
    return min_index;
}

void afisareArbore(int arbore[], Graph *harta)
{
    int i;
    printf("Muchia \tDistanta\n");
    for (i = 1; i < harta->numar_noduri; i++)
        printf("%d - %d \t%d \n", arbore[i], i, harta->noduri[i]->distante[arbore[i]]);
}

int adunareDistante(int arbore[], Graph *harta, int *trecut, FILE *g)
{
    int i, d = 0;
    for (i = 0; i < harta->numar_noduri; i++)
        if (trecut[i])
            d += harta->noduri[i]->distante[arbore[i]];

    // printf("drum = %d\n", d);
    // fprintf(g, "%d\n", d);
    return d;
}

int PRIMS(Graph *harta, int lungime_sa, int starting_point, FILE *g)
{
    int nr_noduri, drum;
    nr_noduri = harta->numar_noduri;
    int *arbore_minim = (int *)malloc(nr_noduri * sizeof(int));
    int *trecut = (int *)calloc(nr_noduri, sizeof(int));
    int *distante = (int *)malloc(nr_noduri * sizeof(int));

    int i, next;
    for (i = 0; i < nr_noduri; i++)
        distante[i] = 99999;

    distante[starting_point] = 0;      // distanta de la un nod la el insisi = 0
    arbore_minim[starting_point] = -1; // Radacina
    int capat = 0, *vecini, v;

    for (i = 0; i < lungime_sa; i++)
    {
        next = gasire_vecin_minim(harta, distante, trecut);
        trecut[next] = 1;
        capat = 0;
        vecini = determinareVecini(harta->noduri[next], nr_noduri, &capat);

        for (v = 0; v < capat; v++)
            if ((trecut[vecini[v]] == 0) &&
                (harta->noduri[next]->distante[vecini[v]] < distante[vecini[v]]))
            {
                arbore_minim[vecini[v]] = next;
                distante[vecini[v]] = harta->noduri[next]->distante[vecini[v]];
            }
        free(vecini);
    }
    // afisareArbore(arbore_minim, harta);
    // printf("%d")
    drum = adunareDistante(arbore_minim, harta, trecut, g);
    free(arbore_minim);
    free(distante);
    return drum;
}

void determinareDrum(Graph *harta, int *drum)
{
    int i, k = 0, *trecut, *vecini, capat;
    trecut = (int *)calloc(harta->numar_noduri, sizeof(int));
    for (i = 0; i < harta->numar_noduri; i++)
    {
        vecini = determinareVecini(harta->noduri[i], harta->numar_noduri, &capat);
        if (trecut[i] == 0)
        {
            gasireMinimDFS(harta, i, trecut, vecini, capat, &drum[k]);
            k++;
        }
        free(vecini);
    }

    free(trecut);
}
// -----------------------

/* --------------------------------------------------------- //
int *dijkstra(Graph *harta, int sursa)
{
    int i, j, minim, u;
    int numar_noduri = harta->numar_noduri;
    int *distante = (int *)malloc(numar_noduri * sizeof(int));
    int *vizitat = (int *)calloc(numar_noduri, sizeof(int));
    for (i = 0; i < numar_noduri; i++)
        distante[i] = 9999;

    distante[sursa] = 0;
    // Gasirea drumului cel mai scurt pentru toate nodurile
    for (i = 0; i < numar_noduri - 1; i++)
    {
        minim = 99999;
        // Selectarea nodului cu distanta minima care nu a fost vizitat
        for (j = 0; j < numar_noduri; j++)
            if (vizitat[j] == 0 && distante[j] <= minim)
            {
                minim = distante[j];
                u = j;
            }
        vizitat[u] = 1;
        // Actualizarea distantei pentru toti vecinii nodului selectat
        for (j = 0; j < numar_noduri; j++)
            if (vizitat[j] == 0 && harta->noduri[u]->distante[j] != 0 && distante[u] != 99999 && distante[u] + harta->noduri[u]->distante[j] < distante[j])
                distante[j] = distante[u] + harta->noduri[u]->distante[j];
    }

    free(vizitat);
    return distante;
}
// --------------------------------------------------------- */

void cerinta1(Graph *harta, FILE *f, FILE *g)
{
    citesteHarta(&harta, f);
    int i, j, aux, k, *starting_points, *contori;
    k = determinareZone(harta);
    contori = (int *)malloc(k * sizeof(int));
    starting_points = determinareStPoints(harta, k, contori);

    fprintf(g, "%d\n", k);
    // printf("%d\n", k);

    // int *trecut = (int *)calloc(harta->numar_noduri, sizeof(int));
    int *drumuri = (int *)malloc(k * sizeof(int));
    for (i = 0; i < k; i++)
        drumuri[i] = PRIMS(harta, contori[i], starting_points[i], g);

    // sortarea vectorului *drumuri
    for (i = 0; i < k - 1; i++)
        for (j = i + 1; j < k; j++)
            if (drumuri[j] < drumuri[i])
            {
                aux = drumuri[j];
                drumuri[j] = drumuri[i];
                drumuri[i] = aux;
            }
    for (i = 0; i < k; i++)
    {
        printf("(%d) -> %d\n", i + 1, drumuri[i]);
        fprintf(g, "%d\n", drumuri[i]);
    }
}

// void cerinta2(Graph *harta, FILE *f, FILE *g)
// {
//     citesteHarta(&harta, f);
//    int sursa, destinatie;
//     fscanf(f, "%d", &sursa);
//     fscanf(f, "%d", &destinatie);
//     int *distante = d
//     int distanta = distante[destinatie];
//     fprintf(g,"%d\n", distanta);
//     free(distante);
// }

int main(int argc, char **argv)
{
    FILE *f = fopen("tema3.in", "r");
    FILE *g = fopen("tema3.out", "w");
    // N = nr. noduri
    // M =  nr. muchii
    int N, M;
    char cerinta[1];
    strcpy(cerinta, argv[1]);
    fscanf(f, "%d", &N);
    fscanf(f, "%d", &M);
    Graph *harta = creareGraph(N, M);

    if (strcmp(cerinta, "1") == 0)
        cerinta1(harta, f, g);
    else if (strcmp(cerinta, "2") == 0)
        printf("2\n");
    // cerinta2

    fclose(f);
    fclose(g);
    return 0;
}