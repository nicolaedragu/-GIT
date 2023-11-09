#include <stdio.h>
#include <stdlib.h>

int g[10][10] = {0}, afisat[10], grad_intern[10], n, count = 0;

int main()
{
    printf("enter the value of n\n");
    scanf("%d", &n);
    int i, j, k;

    printf("enter the matrix\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    for (i = 0; i < n; i++)
    {
        afisat[i] = 0;
        grad_intern[i] = 0;
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            grad_intern[i] = grad_intern[i] + g[j][i];

    printf ("greade\n");
    for (i = 0; i < n; i++)
        printf("nodul %d, grad intern = %d\n", i, grad_intern[i]);

    for (count = 0; count < n; count++)
        for (k = 0; k < n; k++)
        {
            if ((grad_intern[k] == 0) && (afisat[k] == 0))
            {
                afisat[k] = 1;
                printf("%d ", k);
            }

            for (j = 0; j < n; j++)
            {
                if (g[j][k] == 1 && afisat[k] == 0)
                {
                    grad_intern[k]--;
                }
            }
        }
    printf("\n");
    return 0;
}