#include <stdio.h>
#include <stdlib.h>

int sumaprodus(int v[], int n, int *suma, int *produs, int s, int d)
{
    int m,i;
    m=(s+d)/2;
    if (m<d)
    {
        for (i=m+1;i<=d;i++)
        {
            *suma=(*suma)+v[i];
            *produs=(*produs)*v[i];
        }
        sumaprodus(v,n,&*suma,&*produs,0,m);   
    }
    else
        {
            *suma=(*suma)+v[m];
            *produs=(*produs)*v[m];
            return 0;
        }
}

int main()
{
    int *v, n, i, suma=0,*s,*p,produs=1;
    scanf("%d ", &n);
    v = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    s=&suma;
    p=&produs;
    sumaprodus(v,n,s,p,0,n);

    printf("suma: %d\nprodusul: %d",suma,produs);

    return 0;
}
