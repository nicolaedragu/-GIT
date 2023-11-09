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

void creeaza_listaInlantuita(elem **cap, elem **ultim)
{
    int a, b, c, s = 0, primacitire = 0, ok = 0;
    while (1)
    {
        // printf("Introduceti numar: \n");
        if (primacitire == 0)
        {
            scanf("%d", &a);
            insereazaUltim(a, cap, ultim);
        }
        else if (primacitire == 1)
        {
            scanf("%d", &b);
            insereazaUltim(b, cap, ultim);
        }
        else if (primacitire >= 2)
        {
            ok = 1;
            scanf("%d", &c);
            s = a + b;
            if (c != s) 
                insereazaUltim(c, cap, ultim);
        }
        if ((c == s) && (ok == 1))
            break;
        if (primacitire >= 2)
        {
            a = b;
            b = c;
        }
        primacitire++;
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

void printeaza_invers(elem *ultim)
{
    while (1)
    {
        printf("%d ", ultim->numar);
        if (ultim->ant != NULL)
            ultim = ultim->ant;
        else
            break;
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
            p = p->urm;
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
    elem *p, *p_vechi;
    int x;
    if (cap == NULL)
        return;
    p = cap;
    x = p->urm->urm->numar;

    while (p != NULL)
    {
        if (x < 0)
        {
            p_vechi = p;
            p->urm->ant = p->ant;
            p->ant->urm = p->urm;
            free(p_vechi);
            // p=p->urm;
        }
        else
        {
            p = p->urm;
            printf("ELSE ");
        }
    }

    printf("\n");
}

int main()
{
    printf("Introduceti lista:\n");
    creeaza_listaInlantuita(&cap, &ultim);
    printf("Lista inlantuita contine elementele: ");
    printeaza_invers(ultim);

    return 0;
}