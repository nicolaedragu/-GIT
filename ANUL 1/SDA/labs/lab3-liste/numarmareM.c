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

void insereazaPrimulElem(elem **cap,int valoare)
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
        insereazaUltim(valoare,cap,ultim);
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

int mare(elem *cap,int m,int n)
{
    int k=0;
    while (cap!=NULL)
    {
        if (cap->numar>m)
            {
                k++;
                if (k==n)
                    return cap->numar;
            }
        cap=cap->urm;
    }
    return cap->numar;
}

int main()
{
    int n,m;
    printf ("m este: ");
    scanf ("%d",&m);
    printf ("n este: ");
    scanf ("%d",&n);
    creeaza_listaInlantuita(&cap,&ultim);
    printf("Lista inlantuita contine elementele:\n");
    printeaza_listaInlantuita(cap);
    
    printf ("Elementul al %d-lea mai mare decat %d este: %d\n",n,m,mare(cap,m,n));

    return 0;
}