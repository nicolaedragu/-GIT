#include <stdio.h>
#include <stdlib.h>

int inversari(int v[], int *inv, int s, int d)
{
    int m = (s + d) / 2;
    
    if (v[s] > v[d])
    {
        int aux;
        aux=v[s];
        v[s]=v[d];
        v[d]=aux;
        *inv += 1;
    }
    
    inversari(v, inv, s+1, d);
    return inv;
}

int main()
{
    int i,*v,n;
    scanf ("%d",&n);
    v=(int*)malloc(n*sizeof(int));
    for (i=0;i<n;i++)
        scanf ("%d",&v[i]);
    int inv1,inv2;
    inv1=inversari(v,0,0,n/2);
    inv2=inversari(v,0,n/2,n);
    printf ("Numarul de inversari=%d\n",inv1+inv2);
}