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

void insereazaUltim(int valoare, elem **cap, elem **ultim)
{
    elem *temp_elem;
    temp_elem = malloc(sizeof(elem));
    temp_elem->numar = valoare;
    temp_elem->urm = NULL;
    if (*cap == NULL)
    {
        *cap = temp_elem;
        *ultim = temp_elem;
    }
    else
    {
        (*ultim)->urm = temp_elem;
        *ultim = temp_elem;
    }
}

void creeaza_listaInlantuita(elem **cap, elem **ultim)
{
    int valoare;
    while (1)
    {
        printf("Introduceti numar de introdus | -1 pentru a iesi\n");
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

void par_impar(elem *cap, elem **cap_par, elem **cap_impar, elem **ultim_par, elem **ultim_impar)
{
    int i;
    for (i = -1; cap != NULL; i++)
    {
        if (!(i % 2))
            insereazaUltim(cap->numar, cap_par, ultim_par);
        else
            insereazaUltim(cap->numar, cap_impar, ultim_impar);

        cap = cap->urm;
    }
}

int main()
{
    int cheie, valoare;
    creeaza_listaInlantuita(&cap, &ultim);
    printf("Lista inlantuita contine elementele:\n");
    printeaza_listaInlantuita(cap);

    elem *cap_par = NULL, *cap_impar = NULL, *ultim_impar = NULL, *ultim_par = NULL;
    par_impar(cap, &cap_par, &cap_impar, &ultim_par, &ultim_impar);
    printf("Elementele de pe pozitiile pare sunt:\n");
    printeaza_listaInlantuita(cap_par);
    printf("Elementele de pe pozitiile impare sunt:\n");
    printeaza_listaInlantuita(cap_impar);

    return 0;
}