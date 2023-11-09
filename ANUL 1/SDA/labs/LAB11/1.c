#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int hash(char *iban)
{
    int i, aux, h = 0;
    for (i = 0; i < strlen(iban); i++)
    {
        aux += iban[i] % 10;
        if (aux > 10)
            aux = aux / 10;
    }
    h = floor(exp(aux));
    return h;
}

int main()
{
    char *s = "RO12 RNCB 4432 5655 9631";
    int h = hash(s);
    printf ("%d\n", h);
}