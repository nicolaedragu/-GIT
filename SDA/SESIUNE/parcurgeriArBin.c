#include <stdio.h>

typedef struct Nod
{
    int valoare;
    struct Nod *stanga, *dreapta;
} Nod;

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