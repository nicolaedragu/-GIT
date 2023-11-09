#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listaInlantuita
{
    int numar;
    struct listaInlantuita *urm;
} elem;

elem *cap = NULL;
elem *ultim = NULL;

void insereazaUltim(int val)
{
    elem *temp_elem;
    temp_elem = malloc(sizeof(elem));
    temp_elem->numar = val;
    temp_elem->urm = NULL;
    if (cap == NULL)
    {
        cap = temp_elem;
        ultim = temp_elem;
    }
    else
    {
        ultim->urm = temp_elem;
        ultim = temp_elem;
    }
}

void creeaza_listaInlantuita()
{
    int val;
    while (1)
    {
        printf("Introduceti numar de introdus | -1 pentru a iesi\n");
        scanf("%d", &val);
        if (val == -1)
            break;
        insereazaUltim(val);
    }
}

void printeaza_listaInlantuita()
{
    printf("\nLista contine numerele:\n");
    elem *lista;
    lista = cap;
    while (lista != NULL)
    {
        printf("%d ", lista->numar);
        lista = lista->urm;
    }
    puts("");
}

int gaseste_mijloc()
{
    elem *primul = cap;
    elem *doilea = cap;
    while (doilea->urm != NULL)
    {
        doilea = doilea->urm->urm;
        if (doilea == NULL)
            break;
        primul = primul->urm;
    }
    printf("Elementul din mijloc al listei este: %d\n", primul->numar);
}

int main(void)
{
    creeaza_listaInlantuita();
    printeaza_listaInlantuita();

    gaseste_mijloc();
    return 0;
}