#include <stdio.h>

typedef struct Nod
{
    int valoare;
    struct Nod *stanga, *dreapta;
} Nod;

typedef struct Graph
{
    int numar_noduri;
    Nod *noduri;
} Graph;

// parcurgere preordine
void preordine(Nod *radacina)
{
    if (radacina != NULL)
    {
        printf("%d ", radacina->valoare);
        inordine(radacina->stanga);
        inordine(radacina->dreapta);
    }
}

// parcurgere inordine - BFS
void inordine(Nod *radacina)
{
    if (radacina != NULL)
    {
        inordine(radacina->stanga);
        printf("%d ", radacina->valoare);
        inordine(radacina->dreapta);
    }
}

// parcurgere postordine
void postordine(Nod *radacina)
{
    if (radacina != NULL)
    {
        inordine(radacina->stanga);
        inordine(radacina->dreapta);
        printf("%d ", radacina->valoare);
    }
}

void DFS(Graph *harta, int i, int *trecut, int *vecini, int capat, int *contor)
{
    int j;
    trecut[i] = 1;
    vecini = determinareVecini(harta->noduri[i], harta->numar_noduri, &capat);
    for (j = 0; j < capat; j++)
    {
        if (trecut[vecini[j]] == 0)
        {
            *contor = *contor + 1;
            // apelare recursiv
            DFS(harta, vecini[j], trecut, vecini, capat, contor);
        }
    }
}

// BFS
typedef struct
{
    Nod *inceput;
    Nod *sfarsit;
} Coada;

Coada *creareCoada()
{
    Coada *coada = (Coada *)malloc(sizeof(Coada));
    coada->inceput = NULL;
    coada->sfarsit = NULL;
    return coada;
}

void adaugaInCoada(Coada *coada, int valoare)
{
    Nod *nodNou = (Nod *)malloc(sizeof(Nod));
    nodNou->valoare = valoare;
    nodNou->urmator = NULL;

    if (coada->inceput == NULL)
    {
        coada->inceput = nodNou;
        coada->sfarsit = nodNou;
    }
    else
    {
        coada->sfarsit->urmator = nodNou;
        coada->sfarsit = nodNou;
    }
}

int extrageDinCoada(Coada *coada)
{
    if (coada->inceput == NULL)
    {
        return -1; // Coada este goală
    }

    Nod *nodExtras = coada->inceput;
    int valoareExtrasa = nodExtras->valoare;

    coada->inceput = coada->inceput->urmator;
    free(nodExtras);

    if (coada->inceput == NULL)
    {
        coada->sfarsit = NULL;
    }

    return valoareExtrasa;
}

int coadaGoala(Coada *coada)
{
    return coada->inceput == NULL;
}

void BFS(Graph *graf, int *trecut, int ic)
{
    Coada *coada = creareCoada();

    trecut[ic] = 1;
    adaugaInCoada(coada, ic);

    while (!coadaGoala(coada))
    {
        int nodCurent = extrageDinCoada(coada);
        printf("%d ", nodCurent);

        for (int i = 0; i < graf->numar_noduri; i++)
        {
            if (graf->noduri[nodCurent]->distante[i] && !trecut[i])
            {
                trecut[i] = 1;
                adaugaInCoada(coada, i);
            }
        }
    }

    free(coada);
}