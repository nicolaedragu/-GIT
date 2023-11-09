/*
Determinati nivelul nodului k.
Faceti suma tuturor nodurilor de pe 
fiecare nivel.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct nod
{
    int valoare;
    int nivel;
    struct nod *stanga, *dreapta;
} nod;

nod *creazaNod(int item)
{
    nod *temp = (nod *)malloc(sizeof(nod));
    temp->valoare = item;
    temp->stanga = temp->dreapta = NULL;
    return temp;
}

nod *adaugaNod(nod *nod, int valoare)
{
    if (nod == NULL)
        return creazaNod(valoare);
    if (valoare < nod->valoare)
        nod->stanga = adaugaNod(nod->stanga, valoare);
    else
        nod->dreapta = adaugaNod(nod->dreapta, valoare);

    return nod;
}

void gasireNivel(int *nivel, nod *radacina, int caut)
{
    *nivel = *nivel + 1;
    if (radacina->valoare == caut)
        return;
    else
    {
        if (radacina->valoare > caut)
            gasireNivel(nivel, radacina->stanga, caut);
        if (radacina->valoare < caut)
            gasireNivel(nivel, radacina->dreapta, caut);
    }
}

int main()
{
    nod *radacina = NULL;
    int k, i, n;
    // printf ("nr noduri = ");
    scanf("%d", &k);
    for (i = 0; i < k; i++)
    {
        scanf ("%d", &n);
        radacina = adaugaNod(radacina, n);
    }
    
    printf ("Cautam nodul ");
    scanf ("%d", &k);
    int nivel = -1;
    gasireNivel(&nivel, radacina, k);
    printf ("Nodul %d - nivelul %d\n", k, nivel);
    return 0;
}