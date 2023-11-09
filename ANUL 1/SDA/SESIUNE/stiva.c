#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Stiva
{
    int sus;
    unsigned capacitate;
    int *tablou;
};

struct Stiva *creazaStiva(unsigned capacitate)
{
    struct Stiva *stiva = (struct Stiva *)malloc(sizeof(struct Stiva));
    stiva->capacitate = capacitate;
    stiva->sus = -1;
    stiva->tablou = (int *)malloc(stiva->capacitate * sizeof(int));
    return stiva;
}

int estePlina(struct Stiva *stiva)
{
    return stiva->sus == stiva->capacitate - 1;
}

int esteGoala(struct Stiva *stiva)
{
    return stiva->sus == -1;
}

void push(struct Stiva *stiva, int element)
{
    if (estePlina(stiva))
        return;
    stiva->tablou[++stiva->sus] = element;
    printf("%d adaugat in stiva\n", element);
}

int pop(struct Stiva *stiva)
{
    if (esteGoala(stiva))
        return INT_MIN;
    return stiva->tablou[stiva->sus--];
}

int peek(struct Stiva *stiva)
{
    if (esteGoala(stiva))
        return INT_MIN;
    return stiva->tablou[stiva->sus];
}

int main()
{
    struct Stiva *stiva = creazaStiva(100);
    push(stiva, 10);
    push(stiva, 20);
    push(stiva, 30);
    printf("%d scos din stiva\n", pop(stiva));
    printf("%d este varful stivei\n", peek(stiva));
    return 0;
}