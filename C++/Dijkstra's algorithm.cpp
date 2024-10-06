#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

void dijkstra(int graph[10][10], int n, int start, int dist[])
{
    int visited[10] = {0};

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = INF, min_index;

        for (int v = 0; v < n; v++)
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }

        int u = min_index;
        visited[u] = 1;

        for (int v = 0; v < n; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
}

int main()
{
    FILE *inputFile, *outputFile;
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int n;
    fscanf(inputFile, "%d", &n);

    int graph[10][10];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(inputFile, "%d", &graph[i][j]);

    int start;
    fscanf(inputFile, "%d", &start);

    int dist[10];
    dijkstra(graph, n, start, dist);

    fprintf(outputFile, "Shortest distances from node %d:\n", start);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF)
            fprintf(outputFile, "%d -> %d: No path\n", start, i);
        else
            fprintf(outputFile, "%d -> %d: %d\n", start, i, dist[i]);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Dijkstra's algorithm completed. Check output.txt for results.\n");
    return 0;
}
