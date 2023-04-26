#include <stdio.h>
#include <stdlib.h>

int n;
void dfs(int node, int adj[][n], int visited[]);
int isEulerian(int adj[][n]);
int isHamiltonian(int adj[][n]);

int main()
{
    printf("numarul de noduri este: ");
    scanf("%d", &n);
    int adj[n][n];  // matricea de adiacență a grafului
    int visited[n]; // vectorul de vizitare a nodurilor

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }

    // cod pentru inițializarea matricei de adiacență și a vectorului de vizitare a nodurilor

    dfs(0, adj, visited);

    int isConex = 1;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            isConex = 0;
            break;
        }
    }

    int isEuler = isEulerian(adj);
    int isHam = isHamiltonian(adj);

    return 0;
}

void dfs(int node, int adj[][n], int visited[])
{
    visited[node] = 1;
    for (int i = 0; i < n; i++)
    {
        if (adj[node][i] && !visited[i])
        {
            dfs(i, adj, visited);
        }
    }
}

int isEulerian(int adj[][n])
{
    // cod pentru verificarea dacă graficul este eulerian
}

int isHamiltonian(int adj[][n])
{
    int count, i, j;
    for (i = 0; i < n; i++)
    {
        count = 0;
        for (j = 0; j < n; j++)
        {
            if (adj[i][j])
            {
                count++;
            }
        }
        if (count < (n / 2))
        {
            return 0;
        }
    }

    int visited[n];
    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    visited[0] = 1;
    int pos = 0, next;
    for (i = 0; i < n - 1; i++)
    {
        next = -1;
        for (j = 0; j < n; j++)
        {
            if (adj[pos][j] && !visited[j])
            {
                if (next == -1)
                {
                    next = j;
                }
                else
                {
                    if (countConnections(next, adj, visited) > countConnections(j, adj, visited))
                    {
                        next = j;
                    }
                }
            }
        }
        if (next == -1)
        {
            return 0;
        }
        visited[next] = 1;
        pos = next;
    }
    return 1;
}

int countConnections(int node, int adj[][n], int visited[])
{
    int count = 0, i;
    for (i = 0; i < n; i++)
    {
        if (adj[node][i] && !visited[i])
        {
            count++;
        }
    }
    return count;
}