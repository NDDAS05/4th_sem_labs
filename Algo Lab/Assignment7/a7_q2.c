#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define V 10
#define INF 999999
#define NEG_INF -999999

int minDistance(int dist[], bool sptSet[]) {
    int min = INF, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[V][V], int src, int trueDist[V]) {
    int dist[V];     
    bool sptSet[V];  
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = false;
    }

    dist[src] = 0;

    printf("--- Tracing Dijkstra's Algorithm Execution ---\n");

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        
        if (u == -1 || dist[u] == INF) break;

        sptSet[u] = true;
        printf("Finalizing Vertex %d with distance %d\n", u, dist[u]);

        for (int v = 0; v < V; v++) {

            if (!sptSet[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                printf("  -> Updating distance of Vertex %d to %d (via %d)\n", v, dist[v], u);
            }
            else if (sptSet[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                printf("  -> [!] Found shorter path to Vertex %d (new dist: %d) via %d, "
                       "BUT it is already finalized. Ignoring.\n", v, dist[u] + graph[u][v], u);
            }
        }
    }

    printf("\nFinal Computed Distances from Source (%d)\n", src);
    printf("  %-6s | %-17s | %-25s\n", "Vertex", "Dijkstra (Greedy)", "Actual True Dist (Bellman)");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < V; i++) {
        char dStr[25], tStr[40];
        
        if (dist[i] == INF) sprintf(dStr, "INFINITY");
        else sprintf(dStr, "%d", dist[i]);

        if (trueDist[i] == INF) sprintf(tStr, "INFINITY");
        else if (trueDist[i] == NEG_INF) sprintf(tStr, "-INFINITY (Negative Cycle)");
        else sprintf(tStr, "%d", trueDist[i]);

        printf("  %-6d | %-17s | %-25s\n", i, dStr, tStr);
    }
}

void addEdge(int graph[V][V], int u, int v, int weight) {
    if (u >= 0 && u < V && v >= 0 && v < V) {
        graph[u][v] = weight;
    }
}

void bellmanFord(int graph[V][V], int src, int trueDist[V]) {
    for(int i = 0; i < V; i++) trueDist[i] = INF;
    trueDist[src] = 0;
    
    for(int k = 0; k < V - 1; k++) {
        for(int u = 0; u < V; u++) {
            for(int v = 0; v < V; v++) {
                if(graph[u][v] != INF && trueDist[u] != INF && trueDist[u] + graph[u][v] < trueDist[v]) {
                    trueDist[v] = trueDist[u] + graph[u][v];
                }
            }
        }
    }
    
    for(int k = 0; k < V - 1; k++) {
        for(int u = 0; u < V; u++) {
            for(int v = 0; v < V; v++) {
                if(graph[u][v] != INF && trueDist[u] != INF) {
                    if (trueDist[u] == NEG_INF || trueDist[u] + graph[u][v] < trueDist[v]) {
                        trueDist[v] = NEG_INF;
                    }
                }
            }
        }
    }
}

void generateRandomGraph(int graph[V][V], int *c1, int *c2, int *c3) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            if(i != j && (rand() % 100) < 30) {
                graph[i][j] = (rand() % 20) + 1;
            }
        }
    }

    *c1 = (rand() % 9) + 1;
    *c2 = (rand() % 9) + 1; while(*c2 == *c1) *c2 = (rand() % 9) + 1;
    *c3 = (rand() % 9) + 1; while(*c3 == *c1 || *c3 == *c2) *c3 = (rand() % 9) + 1;

    graph[0][*c1] = (rand() % 10) + 1; 

    int w1 = (rand() % 10) + 1;
    int w2 = (rand() % 10) + 1;
    int w3 = -(w1 + w2 + (rand() % 5) + 1); 

    graph[*c1][*c2] = w1;
    graph[*c2][*c3] = w2;
    graph[*c3][*c1] = w3;
}

int main() {
    srand(time(NULL));

    int graph[V][V];
    int c1, c2, c3;
    int trueDist[V];

    printf("Generating random graph with a guaranteed negative cycle...\n");
    generateRandomGraph(graph, &c1, &c2, &c3);

    printf("\nRandomly Generated Edges\n");
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(graph[i][j] != 0 && graph[i][j] != INF){
                printf("Edge: %d -> %d \t Weight: %d\n", i, j, graph[i][j]);
            }
        }
    }
    printf("--------------------------------\n\n");

    printf("Computing Actual True Distances using Bellman-Ford...\n\n");
    bellmanFord(graph, 0, trueDist);

    printf("Executing Dijkstra's Algorithm starting from Vertex 0...\n\n");
    dijkstra(graph, 0, trueDist);

    printf("\nAnalysis of Failure\n");
    printf("1. We injected a random negative cycle into the graph: %d -> %d -> %d -> %d\n", c1, c2, c3, c1);
    printf("2. The weights of this cycle sum to a negative value.\n");
    printf("3. Dijkstra's greedy algorithm finalizes vertices once it picks them.\n");
    printf("4. While tracing the execution, `[!]` logs will be printed. This is when the algorithm finds a shorter path back to nodes %d, %d, or %d via the negative cycle, but ignores it because they are already marked 'finalized'.\n", c1, c2, c3);
    printf("5. Because of this, Dijkstra returns completely incorrect static values for any nodes connected to the cycle, missing the fact that their true distance is actually -INFINITY.\n");

    return 0;
}