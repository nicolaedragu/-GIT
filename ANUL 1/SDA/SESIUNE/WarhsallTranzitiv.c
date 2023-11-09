#include <stdio.h>
#include <stdlib.h>

#define NR 4

void printSolution(int dist[][NR])
{
    printf("Following matrix is transitive");
    printf("closure of the given graph\n");
    for (int i = 0; i < NR; i++)
    {
        for (int j = 0; j < NR; j++)
        {
            /* because "i==j means same vertex"
             and we can reach same vertex
             from same vertex. So, we print 1....
             and we have not considered this in
             Floyd Warshall Algo. so we need to
             make this true by ourself
             while printing transitive closure.*/
            if (i == j)
                printf("1 ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

void floyd_warshall_transitiv(int mat[][NR])
{
    int transit[NR][NR], i, j, k;

    for (i = 0; i < NR; i++)
        for (j = 0; j < NR; j++)
            transit[i][j] = mat[i][j];

    for (k = 0; k < NR; k++)
        for (i = 0; i < NR; i++)
            for (j = 0; j < NR; j++)
                transit[i][j] = transit[i][j] ||
                                (transit[i][k] && transit[k][j]);
    printSolution(transit);
}

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
    int graph[NR][NR] = {{1, 1, 0, 1},
                       {0, 1, 1, 0},
                       {0, 0, 1, 1},
                       {0, 0, 0, 1}};

    // Print the solution
    floyd_warshall_transitiv(graph);
    return 0;
}