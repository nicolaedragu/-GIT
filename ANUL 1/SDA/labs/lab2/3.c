#include <stdio.h>
#include <stdlib.h>

float cautare(float n,float start,float final,float e)
{
    if (start==final-1)
        return start;
    float mid=(start+final)/2.;
    float modul;
    modul=n-mid*mid*mid;
    if (modul<0)
        modul=modul*(-1);
        
    if (modul<e)    
        return mid;
    else
    {   
        if (mid*mid*mid>n)
            final=mid;
        else
            if (mid*mid*mid<n)
                start=mid;
        cautare(n,start,final,e);
    }
}

int main()
{
    float n,e=0.000001,start=0, final,r;
    scanf ("%f",&n);
    final=n;
    r=cautare(n,start,final,e);
    
    printf ("Radacina cubica a numarului %f este: %f\n",n,r);

}