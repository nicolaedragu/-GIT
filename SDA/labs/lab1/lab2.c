#include <stdio.h>

int radacina(int n,int s,int d)

{
    int m;
    if(s==d-1) return s;
    m=(s+d)/2;
    if(m*m<=n) return radacina(n,m,d);
    return radacina(n,s,m);
}

int main()

{   
    int n,rezultat;
    scanf("%d", &n);
    rezultat=radacina(n,1,n+1);
    printf("Radacina naturala este %d \n", rezultat);

    return 0;

}