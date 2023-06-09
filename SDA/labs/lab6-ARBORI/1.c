#include <stdio.h>
#include <stdlib.h>

struct nod
{
    int valoare;
    struct nod *stanga, *dreapta;
};
typedef struct nod nod;

nod *creazaNod(int item)
{
    nod *temp = (nod *)malloc(sizeof(nod));
    temp->valoare = item;
    temp->stanga = temp->dreapta = NULL;
    return temp;
}

// parcurgere inordine
void inordine(nod *radacina)
{
    if (radacina != NULL)
    {
        inordine(radacina->stanga);
        printf("%d ", radacina->valoare);
        inordine(radacina->dreapta);
    }
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

nod *nodCuValoareMinima(nod *node)
{
    nod *curent = node;
    while (curent && curent->stanga != NULL)
        curent = curent->stanga;
    return curent;
}

nod *stergeNod(nod *radacina, int valoare)
{
    if (radacina == NULL)
        return radacina;
    if (valoare < radacina->valoare)
        radacina->stanga = stergeNod(radacina->stanga, valoare);
    else if (valoare > radacina->valoare)
        radacina->dreapta = stergeNod(radacina->dreapta, valoare);
    // daca radacina are valoarea pe care o cautam
    else
    {
        if (radacina->stanga == NULL)
        {
            nod *temp = radacina->dreapta;
            free(radacina);
            return temp;
        }
        else if (radacina->dreapta == NULL)
        {
            nod *temp = radacina->stanga;
            free(radacina);
            return temp;
        }
        // nod cu copil in partea stanga, cat si la dreapta. Gaseste elementul din subarborele drept care are cea mai mica valoare
        nod *temp = nodCuValoareMinima(radacina->dreapta);
        radacina->valoare = temp->valoare;
        radacina->dreapta = stergeNod(radacina->dreapta, temp->valoare);
    }
    return radacina;
}

int prim(int x)
{
    int ok = 1;
    if (x < 2)
        return 0;
    if (x == 2)
        return 1;
    int d;
    for (d = 2; d * d <= x; d++)
        if (x % d == 0)
            ok = 0;
    return ok;
}

int parcurgere(nod *radacina)
{
    if (radacina == NULL)
        return 0;
    int k = 0;
    if (prim(radacina->valoare))
        k++;
    k += parcurgere(radacina->stanga) + parcurgere(radacina->dreapta);
    return k;
}

int main()
{ /* Consideram urmatorul arbore binar cu 7 noduri
    5
   / \
  3   7
 / \  / \
2  4  6  8
*/
    nod *radacina = NULL;
    int i, n, k;
    printf("Introdu numarul de noduri: ");
    scanf("%d", &k);
    for (i = 0; i < k; i++)
    {
        scanf("%d", &n);
        radacina = adaugaNod(radacina, n);
    }
    // printf("Arborele parcurs in ordine: \n");
    // inordine(radacina);
    int dreapta = 0;
    // nod *rezerva = (nod *)malloc(sizeof(nod));
    nod *copie = (nod *)malloc(sizeof(nod));
    copie = radacina->dreapta;
    for (i = 0; i < k; i++)
    {
        int c = 0;
        c = parcurgere(radacina);
        printf("Pentru nodul %d, nr prime: %d\n", radacina->valoare, c);
        
        // if ((radacina->stanga->stanga == NULL) && (radacina->stanga->dreapta == NULL))
            // rezerva = radacina->dreapta;
        if (radacina->stanga)
            radacina = radacina->stanga;
        else 
            radacina = radacina->dreapta;
        if (dreapta == 1)
        {
            radacina = radacina->dreapta;
        }
        if (radacina == NULL)
        {
            radacina = copie;
            dreapta = 1;
        }
    }
        return 0;
}