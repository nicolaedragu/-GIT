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

void insereazaUltim(int valoare, elem **cap, elem **ultim)
{
    elem *temp_elem, *inainte_elem;
    temp_elem = malloc(sizeof(elem));
    temp_elem->numar = valoare;
    // temp_elem->urm = NULL;
    // temp_elem->ant = NULL;
    if (*cap == NULL)
    {
        *cap = temp_elem;
        (*cap)->ant = NULL;
        *ultim = temp_elem;
        (*ultim)->urm = NULL;
    }
    else
    {
        // (*ultim)->ant = inainte_elem;
        (*ultim)->urm = temp_elem;
        temp_elem->ant = (*ultim);
        *ultim = temp_elem;
        (*ultim)->urm = NULL;
    }
}

void insereazaPrimulElem(elem **cap, int valoare)
{
    elem *temp_elem = (elem *)malloc(sizeof(elem));
    temp_elem->numar = valoare;
    temp_elem->urm = *cap;
    *cap = temp_elem;
}

void creeaza_listaInlantuita(elem **cap, elem **ultim)
{
    int valoare;
    while (1)
    {
        printf("Introduceti numar de introdus(-1 pentru a iesi)\n");
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

int minim(elem *cap)
{
    int min = 10000;
    while (cap != NULL)
    {
        if (min > cap->numar)
            min = cap->numar;
        cap = cap->urm;
    }
    return min;
}

void stergere_nod(int valoare)
{
    elem *p, *p_vechi;
    if (cap == NULL)
        return;
    if ((cap == ultim) && cap->numar == valoare)
    {
        cap = NULL;
        ultim = NULL;
        return;
    }
    p = cap;
    while (p != NULL)
        if (p->numar == valoare)
        {
            p_vechi = p;
            p->urm->ant = p->ant;
            p->ant->urm = p->urm;
            free(p_vechi);
            return;
        }
        else
            p=p->urm;
    /*   PENTRU CAZURI SPECIALE
    if (p==cap)
    {
        stergere_prim();
        return;
    }
    if (p==ultim)
    {
        stergere_ultim();
        return;
    }
    */
}


void stergere_negativ(elem *cap)
{
    elem *p,*p_vechi;
    int x;
    // p=(elem*)malloc(sizeof(elem));
    if (cap == NULL)
        return;
    p=cap;
    x=p->urm->urm->numar;
    // printf("p este\n");
    // printeaza_listaInlantuita(p);
    
    while (p != NULL)
    {
        if (x < 0)
        {
            p_vechi=p;
            p->urm->ant = p->ant;
            p->ant->urm = p->urm;
            free(p_vechi);
            // p=p->urm;
        }
        else{
        p = p->urm;
        printf ("ELSE ");
        }
    }
    
    printf ("\n");
    
}

int main()
{
    creeaza_listaInlantuita(&cap, &ultim);
    printf("Lista inlantuita contine elementele: ");
    printeaza_listaInlantuita(cap);

    stergere_negativ(cap);
    printf("Lista pozitiva:\n");
    printeaza_listaInlantuita(cap);
    // printf ("Elementul minim este: %d\n",minim(cap));
    return 0;
}