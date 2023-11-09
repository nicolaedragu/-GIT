#include <stdio.h>
#include <stdlib.h>

#define NR_NODURI 4
#define INF 99999

void printSolution(int dist[][NR_NODURI])
{
    printf(
        "The following matrix shows the shortest distances"
        " between every pair of vertices \n");
    for (int i = 0; i < NR_NODURI; i++)
    {
        for (int j = 0; j < NR_NODURI; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

void floyd_warshall(int mat[][NR_NODURI])
{
    int i, j, k;

    for (k = 0; k < NR_NODURI; k++)
    {
        for (i = 0; i < NR_NODURI; i++)
        {
            for (j = 0; j < NR_NODURI; j++)
            {

                if (mat[i][k] + mat[k][j] < mat[i][j])
                    mat[i][j] = mat[i][k] + mat[k][j];
            }
        }
    }
    printSolution(mat);
}

// driver's code
int main()
{
    /* Let us create the following weighted graph
            10
       (0)------->(3)
        |         /|\
      5 |          |
        |          | 1
       \|/         |
       (1)------->(2)
            3           */
    int graph[NR_NODURI][NR_NODURI] = {{0, 5, INF, 10},
                                       {INF, 0, 3, INF},
                                       {INF, INF, 0, 1},
                                       {INF, INF, INF, 0}};

    // Function call
    floyd_warshall(graph);
    return 0;
}