#include <stdio.h>
#include <stdlib.h>

struct Nod
{
    int valoare;
    struct Nod *stanga;
    struct Nod *dreapta;
};

struct Nod *creazaNod(int item)
{
    struct Nod *temp = (struct Nod *)malloc(sizeof(struct Nod));
    temp->valoare = item;
    temp->stanga = temp->dreapta = NULL;
    return temp;
}

struct Nod *adaugaNod(struct Nod *nod, int valoare)
{
    if (nod == NULL)
        return creazaNod(valoare);
    if (valoare < nod->valoare)
        nod->stanga = adaugaNod(nod->stanga, valoare);
    else
        nod->dreapta = adaugaNod(nod->dreapta, valoare);

    return nod;
}

void maxime(struct Nod *radacina, int *maxStanga, int *maxDreapta)
{
    if (radacina == NULL)
        return;

    maxime(radacina->stanga, maxStanga, maxDreapta);
    maxime(radacina->dreapta, maxStanga, maxDreapta);

    // Actualizați valorile maxime pentru subarborele stâng și drept ale rădăcinii
    if ((radacina->stanga != NULL) && (radacina->stanga->valoare > *maxStanga))
        *maxStanga = radacina->stanga->valoare;
    if (radacina->dreapta != NULL && radacina->dreapta->valoare > *maxDreapta)
        *maxDreapta = radacina->dreapta->valoare;
}

int main()
{
    struct Nod *radacina = (struct Nod *)malloc(sizeof(struct Nod));
    int maxStanga = -1;
    int maxDreapta = -1;

    int i, n, k;
    printf("Introdu numarul de noduri: ");
    scanf("%d", &k);
    for (i = 0; i < k; i++)
    {
        scanf("%d", &n);
        radacina = adaugaNod(radacina, n);
    }

    maxime(radacina, &maxStanga, &maxDreapta);

    printf("Stanga: %d\n", maxStanga);
    printf("Draepta: %d\n", maxDreapta);
}