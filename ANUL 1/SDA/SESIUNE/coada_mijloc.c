#include <stdio.h>
#include <stdlib.h>

struct Coada
{
    int primul, ultimul, dimensiune;
    unsigned capacitate;
    int *tablou;
};

void scoateMijloc(struct Coada *coada)
{
    if (coada->dimensiune == 0)
    {
        printf("Coada este goala. Nu se poate scoate elementul din mijloc.\n");
        return;
    }

    int mijloc = (coada->dimensiune - 1) / 2;
    int index = (coada->primul + mijloc) % coada->capacitate;
    int element = coada->tablou[index];

    // Mutam elementele din dreapta mijlocului spre stanga, pentru a umple golul
    for (int i = index; i < coada->ultimul; i = (i + 1) % coada->capacitate)
    {
        int nextIndex = (i + 1) % coada->capacitate;
        coada->tablou[i] = coada->tablou[nextIndex];
    }

    coada->ultimul = (coada->ultimul - 1 + coada->capacitate) % coada->capacitate;
    coada->dimensiune--;

    printf("Elementul din mijloc (%d) a fost scos din coada.\n", element);
}

int main()
{
    struct Coada coada;
    coada.primul = 0;
    coada.ultimul = -1;
    coada.dimensiune = 0;
    coada.capacitate = 10;
    coada.tablou = (int *)malloc(coada.capacitate * sizeof(int));

    // Adaugam elemente de test in coada
    for (int i = 1; i <= 5; i++)
    {
        coada.ultimul = (coada.ultimul + 1) % coada.capacitate;
        coada.tablou[coada.ultimul] = i;
        coada.dimensiune++;
    }

    // Afisam coada initiala
    printf("Coada initiala: ");
    for (int i = 0; i < coada.dimensiune; i++)
    {
        int index = (coada.primul + i) % coada.capacitate;
        printf("%d ", coada.tablou[index]);
    }
    printf("\n");

    // Scoatem elementul din mijloc
    scoateMijloc(&coada);

    // Afisam coada dupa scoaterea elementului din mijloc
    printf("Coada dupa scoaterea elementului din mijloc: ");
    for (int i = 0; i < coada.dimensiune; i++)
    {
        int index = (coada.primul + i) % coada.capacitate;
        printf("%d ", coada.tablou[index]);
    }
    printf("\n");

    free(coada.tablou);
    return 0;
}
