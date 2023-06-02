#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listaInlantuita
{
    int numar;
    struct listaInlantuita *urm;
    struct listaInlantuita *ant;
} elem;

elem *cap = NULL;
elem *ultim = NULL;

void insereazaPrimulElem(elem **cap, int valoare)
{
    elem *temp_elem = (elem *)malloc(sizeof(elem));
    temp_elem->numar = valoare;
    temp_elem->urm = *cap;
    *cap = temp_elem;
}

void insereazaUltim(int valoare, elem **cap, elem **ultim)
{
    elem *temp_elem, *inainte_elem;
    temp_elem = (elem *)malloc(sizeof(elem));
    temp_elem->numar = valoare;
    temp_elem->urm = NULL;
    temp_elem->ant = NULL;
    if (*cap == NULL)
    {
        *cap = temp_elem;
        (*cap)->ant = NULL;
        *ultim = temp_elem;
        (*ultim)->urm = NULL;
    }
    else
    {
        (*ultim)->ant = inainte_elem;
        (*ultim)->urm = temp_elem;
        temp_elem->ant = (*ultim);
        *ultim = temp_elem;
        (*ultim)->urm = NULL;
    }
}

void creeaza_listaInlantuita(elem **cap, elem **ultim)
{
    int valoare;
    while (1)
    {
        scanf("%d", &valoare);
        if (valoare == -1)
            break;
        insereazaUltim(valoare, cap, ultim);
    }
}

void printeaza_listaInlantuita(elem *cap)
{
    while (cap != NULL)
    {
        printf("%d ", cap->numar);
        cap = cap->urm;
    }
    puts("");
}

int calc_lungime(elem *cap)
{
    int l = 0;
    while (cap != NULL)
    {
        l++;
        cap = cap->urm;
    }
    return l;
}

void cauta(elem *copie, elem **cap, elem **ultim, int i)
{
    if ((*cap)->numar == i)
        return;
    else
    {
        copie = *cap;
        while ((copie)->numar != i)
        {
            copie = (copie)->urm;
        }
    }
}

int cautare_copac(elem **cap, elem **ultim, int i)
{
    elem *primul = (elem *)malloc(sizeof(elem));
    elem *aldoilea = (elem *)malloc(sizeof(elem));
    primul = *cap;
    while (primul != (*ultim)->ant)
    {
        aldoilea = primul->urm;
        while (aldoilea != *ultim)
        {
            if (primul->numar > aldoilea->numar)
            {
                int aux = primul->numar;
                primul->numar = aldoilea->numar;
                aldoilea->numar = aux;
            }
            aldoilea = aldoilea->urm;
        }
        primul = primul->urm;
    }
    
    primul = *cap;
    int k = 0;
    elem copie;
    //  (elem *)malloc(sizeof(elem));
    cauta(&copie, &cap, &ultim, i);
    // aldoilea = primul->urm;
    while (primul != *ultim)
    {
        if (primul == &copie)
        {
            while (*cap != primul)
            {
                k++;
                *cap = (*cap)->urm; 
            }
            break;
        }
        primul = primul->urm; 
    }
    return k;
}

int main()
{
    int i,k;
    printf("numarul de ordine: ");
    scanf("%d", &i);
    printf("Introduceti inaltimea copacilor (-1 pentru a iesi):\n");
    creeaza_listaInlantuita(&cap, &ultim);
    printf("Lista inlantuita contine elementele: ");
    printeaza_listaInlantuita(cap);

    k = cautare_copac(&cap, &ultim, i);
    printf("Lista sortata: ");
    printeaza_listaInlantuita(cap);
    printf ("K = %d\n",k);

    return 0;
}