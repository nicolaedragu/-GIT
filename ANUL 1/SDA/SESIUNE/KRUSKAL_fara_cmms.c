#include <stdio.h>
#include <stdlib.h>

int cmp(const void* p1, const void* p2)
{
    const int(*a)[3] = p1;
    const int(*b)[3] = p2;
    
    return (*a)[2] - (*b)[2];
}

int findParent(int parent[], int v)
{
    if (parent[v] == v)
        return v;
    
    return parent[v] = findParent(parent, parent[v]);
}

void unionKruskal(int parent[], int rank[], int v1, int v2, int n)
{
    v1 = findParent(parent, v1);
    v2 = findParent(parent, v2);
    
    if (rank[v1] < rank[v2])
    {
        parent[v1] = v2;
    }
    else
    if (rank[v1] > rank[v2])
    {
        parent[v2] = v1;
    }
    else
    {
        parent[v2] = v1;
        rank[v1]++;
    }
}

void kruskal(int graf[][], int n)
{
    int parent[n], rank[n];
    
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
    
    qsort(graf, n, sizeof(graf[0]), cmp);
    int cost_min = 0, v1, v2, wt;
    
    for (i = 0; i < n; i++)
    {
        v1 = findParent(parent, graf[i][0]);
        v2 = findParent(parent, graf[i][1]);
        wt = graf[i][2];
        
        if (v1 != v2)
        {
            unionKruskal(parent, rank, v1, v2, n);
            cost_min += wt;
        }
    }
    // in cost_min avem costul arborelui minim
}

int main()
{
    int n = 3;
    int graf[][];
    kruskal(graf, n);
}