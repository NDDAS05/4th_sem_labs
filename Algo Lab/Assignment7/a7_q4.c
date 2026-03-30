#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (!graph) {
        printf("Error: Memory allocation failed for Graph.\n");
        exit(EXIT_FAILURE);
    }
    
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));
    
    if (!graph->edge && E > 0) {
        printf("Error: Memory allocation failed for Edges.\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    
    return graph;
}

void printDistances(int dist[], int n, int source) {
    printf("\nVertex\t\tDistance from Source (%d)\n", source);
    printf("----------------------------------------\n");
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INT_MAX) {
            printf("%d\t\tInfinity\n", i);
        } else {
            printf("%d\t\t%d\n", i, dist[i]);
        }
    }
}

void BellmanFord(struct Graph* graph, int source) {
    int V = graph->V;
    int E = graph->E;
    int *dist = (int *)malloc(V * sizeof(int));

    if (!dist) {
        printf("Error: Memory allocation failed for distance array.\n");
        return;
    }

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[source] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int j = 0; j < E; j++) {
        int u = graph->edge[j].src;
        int v = graph->edge[j].dest;
        int weight = graph->edge[j].weight;
        
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("\n[!] Bellman-Ford Algorithm detected a NEGATIVE WEIGHT CYCLE in the graph.\n");
            printf("[!] Shortest path values cannot be guaranteed because distance can decrease indefinitely.\n");
            free(dist);
            return;
        }
    }

    printf("\n[Success] No negative weight cycle detected.\n");
    printDistances(dist, V, source);
    
    free(dist);
}

int main() {
    int V, E, source;

    printf("Bellman-Ford Algorithm Implementation\n\n");
    
    printf("Enter the number of vertices in the graph: ");
    if(scanf("%d", &V) != 1 || V <= 0) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter the number of edges in the graph: ");
    if(scanf("%d", &E) != 1 || E < 0) {
        printf("Invalid number of edges.\n");
        return 1;
    }

    struct Graph* graph = createGraph(V, E);

    srand(time(NULL));

    printf("\nGenerating Random Edges\n");
    for (int i = 0; i < E; i++) {
        graph->edge[i].src = rand() % V;
        
        int dest = rand() % V;
        while (V > 1 && dest == graph->edge[i].src) {
            dest = rand() % V;
        }
        graph->edge[i].dest = dest;
        
        graph->edge[i].weight = (rand() % 21) - 5;
        
        printf("Edge %d: Source %d -> Destination %d, Weight: %d\n", 
               i + 1, graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    }

    printf("\nEnter the starting source vertex (0 to %d): ", V - 1);
    if(scanf("%d", &source) != 1 || source < 0 || source >= V) {
        printf("Error: Source vertex out of bounds or invalid input.\n");
        free(graph->edge);
        free(graph);
        return 1;
    }

    BellmanFord(graph, source);

    free(graph->edge);
    free(graph);

    return 0;
}