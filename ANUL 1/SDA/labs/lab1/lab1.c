#include <stdio.h>
#include <stdlib.h>

int search(int v[], int s, int d)
{
    int i, maxx=0;
    for (i = s; i < d; i++)
        if (v[i] > maxx)
            maxx = v[i];
    return maxx;
}

int cautare(int *v, int start, int end)
{
    int mid, max1, max2;
    mid = (start + end) / 2;
    max1 = search(v, start, mid);
    max2 = search(v, mid + 1, end);
    
    if (max2 > max1)
        return max2;
    else
        return max1;
}

int main()
{
    int n, i, val_max, *v;
    scanf("%d", &n);
    v=(int *)malloc(n*sizeof(int));
    
    for (i = 0; i < n; i++)
        scanf("%d",&v[i]);
 
    val_max = cautare(v, 0, n);

    printf("max = %d", val_max);
    
    return 0;
}
