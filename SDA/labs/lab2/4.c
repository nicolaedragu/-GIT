#include <stdio.h>
#include <stdlib.h>

int functie(int v[10], int start, int end, int dif)
{
    if (start >= end)
        return 0;
    int mid = start + (end - start) / 2;
    if (v[mid] - v[mid - 1] != dif)
        return (v[mid - 1] + dif);
    else if (v[mid] == v[0] + mid * dif)
        return functie(v, mid + 1, end, dif);
    else
        return functie(v, start, mid - 1, dif);
}

int main()
{
    int *v, n, prog;
    scanf("%d", &n);
    v = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    prog = (v[n - 1] - v[0]) / n;

    printf("Numarul lipsa e: %d\n", functie(v, 0, n - 1, prog));
}