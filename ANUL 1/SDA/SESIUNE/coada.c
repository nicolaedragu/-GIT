#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Coada
{
    int primul, ultimul, dimensiune;
    unsigned capacitate;
    int *tablou;
};

struct Coada *creazaCoada(unsigned capacitate)
{
    struct Coada *coada = (struct Coada *)malloc(sizeof(struct Coada));
    coada->capacitate = capacitate;
    coada->primul = coada->dimensiune = 0;
    coada->ultimul = capacitate - 1;
    coada->tablou = (int *)malloc(coada->capacitate * sizeof(int));
    return coada;
}

int estePlina(struct Coada *coada)
{
    return (coada->dimensiune == coada->capacitate);
}

int esteGoala(struct Coada *coada)
{
    return (coada->dimensiune == 0);
}

void enqueue(struct Coada *coada, int element)
{
    if (estePlina(coada))
        return;
    coada->ultimul = (coada->ultimul + 1) % coada->capacitate;
    coada->tablou[coada->ultimul] = element;
    coada->dimensiune = coada->dimensiune + 1;
    printf("%d pus in coada\n", element);
}

int dequeue(struct Coada *coada)
{
    if (esteGoala(coada))
        return INT_MIN;
    int element = coada->tablou[coada->primul];
    coada->primul = (coada->primul + 1) % coada->capacitate;
    coada->dimensiune = coada->dimensiune - 1;
    return element;
}

int primul(struct Coada *coada)
{
    if (esteGoala(coada))
        return INT_MIN;
    return coada->tablou[coada->primul];
}

int ultimul(struct Coada *coada)
{
    if (esteGoala(coada))
        return INT_MIN;
    return coada->tablou[coada->ultimul];
}

int extrageMinim(struct Coada *coada)
{
    if (esteGoala(coada))
        return INT_MIN;

    int minim = coada->tablou[coada->primul];
    for (int i = 1; i < coada->dimensiune; i++)
    {
        int element = coada->tablou[(coada->primul + i) % coada->capacitate];
        if (element < minim)
            minim = element;
    }

    return minim;
}

int main()
{
    struct Coada *coada = creazaCoada(1000);
    enqueue(coada, 10);
    enqueue(coada, 20);
    enqueue(coada, 30);
    enqueue(coada, 40);
    printf("%d indepartat din coada\n\n", dequeue(coada));
    printf("Primul element este %d\n", primul(coada));
    printf("Ultimul element este %d\n", ultimul(coada));
    return 0;
}