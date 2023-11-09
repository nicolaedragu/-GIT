/*
Să se determine valorile maxime din
subarborii stâng și drept ai rădăcinii.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Nod
{
    int valoare;
    struct Nod *stanga;
    struct Nod *dreapta;
};

struct Nod *creareNod(int valoare)
{
    struct Nod *temp = (struct Nod *)malloc(sizeof(struct Nod));
    temp->valoare = valoare;
    temp->stanga = NULL;
    temp->dreapta = NULL;
    return temp;
}

struct Nod *adaugaNod(struct Nod *nod, int valoare)
{
    if (nod == NULL)
        return creareNod(valoare);
    if (valoare < nod->valoare)
        nod->stanga = adaugaNod(nod->stanga, valoare);
    else if (valoare > nod->valoare)
        nod->dreapta = adaugaNod(nod->dreapta, valoare);
    return nod;
}

void maxime(struct Nod *radacina, int *maxStanga)
{
    if (radacina == NULL)
        return;
    
    if (radacina->valoare > *maxStanga)
        *maxStanga = radacina->valoare;
    
    maxime(radacina->stanga, maxStanga);
    maxime(radacina->dreapta, maxStanga);
}

int main()
{
    struct Nod *radacina = NULL;
    int k, n;
    printf("nr noduri: ");
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &n);
        radacina = adaugaNod(radacina, n);
    }

    int max = -1;
    maxime(radacina->stanga, &max);
    printf("Maximul pe stanga: %d\n", max);
    
    max = -1;
    maxime(radacina->dreapta, &max);

    printf("Maximul pe dreapta: %d\n", max);
    return 0;
}