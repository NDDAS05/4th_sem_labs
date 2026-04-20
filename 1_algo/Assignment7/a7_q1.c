#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#define V 10
#define INF INT_MAX
#define ITERATIONS 100000


const char* locations[V] = {
    "Hospital", "School", "Market", "Fire Station", "Police Station",
    "City Mall", "Central Park", "Library", "Bus Stand", "Train Station"
};


struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode *head;
};

struct GraphList {
    int numVertices;
    struct AdjList* array;
};


typedef struct {
    int dist[V];      
    int minHeap[V];   
    int pos[V];       
    int size;         
} MinHeap;


void initMinHeap(MinHeap* h) {
    h->size = V;
    for (int i = 0; i < V; ++i) {
        h->dist[i] = INF;
        h->minHeap[i] = i;
        h->pos[i] = i;
    }
}

void swapMinHeapNode(MinHeap* h, int i, int j) {
    int temp = h->minHeap[i];
    h->minHeap[i] = h->minHeap[j];
    h->minHeap[j] = temp;

    
    h->pos[h->minHeap[i]] = i;
    h->pos[h->minHeap[j]] = j;
}

void minHeapify(MinHeap* h, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < h->size && h->dist[h->minHeap[left]] < h->dist[h->minHeap[smallest]])
        smallest = left;

    if (right < h->size && h->dist[h->minHeap[right]] < h->dist[h->minHeap[smallest]])
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(h, idx, smallest);
        minHeapify(h, smallest);
    }
}


bool isEmpty(MinHeap* h) {
    return h->size == 0;
}


int extractMin(MinHeap* h) {
    if (isEmpty(h)) return -1;

    int root = h->minHeap[0];
    int lastNode = h->minHeap[h->size - 1];

    h->minHeap[0] = lastNode;
    h->pos[root] = -1; 
    h->pos[lastNode] = 0;
    
    h->size--;
    minHeapify(h, 0);

    return root;
}

void decreaseKey(MinHeap* h, int v, int new_dist) {
    h->dist[v] = new_dist;
    int i = h->pos[v];

    while (i && h->dist[h->minHeap[i]] < h->dist[h->minHeap[(i - 1) / 2]]) {
        swapMinHeapNode(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

bool isInMinHeap(MinHeap* h, int v) {
    return h->pos[v] < h->size && h->pos[v] != -1;
}


struct GraphList* createGraphList(int vertices) {
    struct GraphList* graph = (struct GraphList*)malloc(sizeof(struct GraphList));
    graph->numVertices = vertices;
    graph->array = (struct AdjList*)malloc(vertices * sizeof(struct AdjList));
    for (int i = 0; i < vertices; ++i)
        graph->array[i].head = NULL;
    return graph;
}

struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdgeList(struct GraphList* graph, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void freeGraphList(struct GraphList* graph) {
    if (!graph) return;
    for (int i = 0; i < graph->numVertices; i++) {
        struct AdjListNode* curr = graph->array[i].head;
        while (curr != NULL) {
            struct AdjListNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

void addEdgeMatrix(int matrix[V][V], int src, int dest, int weight) {
    matrix[src][dest] = weight;
}

void initMatrix(int matrix[V][V]) {
    for(int i=0; i<V; i++)
        for(int j=0; j<V; j++)
            matrix[i][j] = 0;
}


void printArr(int dist[], int n, int src) {
    printf("\nShortest Paths from Source: [%d] %s\n", src, locations[src]);
    printf("--------------------------------------------------\n");
    printf("%-5s | %-15s | %s\n", "ID", "Location", "Distance from Source");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF)
            printf("%-5d | %-15s | %s\n", i, locations[i], "Unreachable");
        else
            printf("%-5d | %-15s | %d units\n", i, locations[i], dist[i]);
    }
    printf("--------------------------------------------------\n");
}

void dijkstraList(struct GraphList* graph, int src, bool printOutput) {
    MinHeap h;
    initMinHeap(&h);

    decreaseKey(&h, src, 0);

    while (!isEmpty(&h)) {
        int u = extractMin(&h);

        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            if (isInMinHeap(&h, v) && h.dist[u] != INF && pCrawl->weight + h.dist[u] < h.dist[v]) {
                decreaseKey(&h, v, h.dist[u] + pCrawl->weight);
            }
            pCrawl = pCrawl->next;
        }
    }

    if (printOutput) {
        printf("\n[Results using Adjacency List]");
        printArr(h.dist, V, src);
    }
}


void dijkstraMatrix(int matrix[V][V], int src, bool printOutput) {
    MinHeap h;
    initMinHeap(&h);

    decreaseKey(&h, src, 0);

    while (!isEmpty(&h)) {
        int u = extractMin(&h);

        for (int v = 0; v < V; v++) {
            if (matrix[u][v] > 0) {
                if (isInMinHeap(&h, v) && h.dist[u] != INF && matrix[u][v] + h.dist[u] < h.dist[v]) {
                    decreaseKey(&h, v, h.dist[u] + matrix[u][v]);
                }
            }
        }
    }

    if (printOutput) {
        printf("\n[Results using Adjacency Matrix]");
        printArr(h.dist, V, src);
    }
}



void generateRandomGraph(struct GraphList* listGraph, int matrix[V][V], int numEdges) {
    int edgesAdded = 0;
    int maxAttempts = numEdges * 100; 
    int attempts = 0;
    
    while(edgesAdded < numEdges && attempts < maxAttempts) {
        int u = rand() % V;
        int v = rand() % V;
        int w = (rand() % 50) + 1; 


        if (u != v && matrix[u][v] == 0) {
            addEdgeMatrix(matrix, u, v, w);
            addEdgeList(listGraph, u, v, w);
            edgesAdded++;
        }
        attempts++;
    }
}

void evaluatePerformance() {
    printf("\nPerformance Evaluation (%d Iterations)\n", ITERATIONS);
    printf("--------------------------------------------\n");
    
    struct GraphList* sparseList = createGraphList(V);
    int sparseMatrix[V][V];
    initMatrix(sparseMatrix);
    
    generateRandomGraph(sparseList, sparseMatrix, 15);

    clock_t start, end;
    double timeListSparse, timeMatrixSparse;

    start = clock();
    for(int i=0; i<ITERATIONS; i++) dijkstraList(sparseList, 0, false);
    end = clock();
    timeListSparse = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for(int i=0; i<ITERATIONS; i++) dijkstraMatrix(sparseMatrix, 0, false);
    end = clock();
    timeMatrixSparse = ((double)(end - start)) / CLOCKS_PER_SEC;

    struct GraphList* denseList = createGraphList(V);
    int denseMatrix[V][V];
    initMatrix(denseMatrix);
    generateRandomGraph(denseList, denseMatrix, 70);

    double timeListDense, timeMatrixDense;

    start = clock();
    for(int i=0; i<ITERATIONS; i++) dijkstraList(denseList, 0, false);
    end = clock();
    timeListDense = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for(int i=0; i<ITERATIONS; i++) dijkstraMatrix(denseMatrix, 0, false);
    end = clock();
    timeMatrixDense = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n[Sparse Graph Analysis (~15 edges)]\n");
    printf("Execution time (Adj List)   : %f seconds\n", timeListSparse);
    printf("Execution time (Adj Matrix) : %f seconds\n", timeMatrixSparse);

    printf("\n[Dense Graph Analysis (~70 edges)]\n");
    printf("Execution time (Adj List)   : %f seconds\n", timeListDense);
    printf("Execution time (Adj Matrix) : %f seconds\n", timeMatrixDense);
    
    printf("\nConclusion: Adjacency List usually outperforms on Sparse graphs.\n");
    printf("Adjacency Matrix may catch up or slightly outperform on Dense graphs due to constant cache lookups compared to pointer chasing.\n");
    
    freeGraphList(sparseList);
    freeGraphList(denseList);
}



void printLocations() {
    printf("\n--- City Locations ---\n");
    for (int i = 0; i < V; i++) {
        printf("%d: %s\n", i, locations[i]);
    }
}

int main() {
    srand(time(NULL));

    struct GraphList* graphList = createGraphList(V);
    int graphMatrix[V][V];
    initMatrix(graphMatrix);

    int choice;
    while (1) {
        printf("Choose an option\n\n");

        printf("1. View Locations\n");
        printf("2. Add a Road (Edge)\n");
        printf("3. Find Shortest Path (using Adjacency List)\n");
        printf("4. Find Shortest Path (using Adjacency Matrix)\n");
        printf("5. Run Performance Evaluation (Sparse vs Dense)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            printLocations();
        } 
        else if (choice == 2) {
            int u, v, w;
            printLocations();
            printf("\nEnter Source Location ID (0-9): ");
            scanf("%d", &u);
            printf("Enter Destination Location ID (0-9): ");
            scanf("%d", &v);
            printf("Enter Travel Cost / Distance (> 0): ");
            scanf("%d", &w);

            if (u >= 0 && u < V && v >= 0 && v < V && w > 0 && u != v) {
                addEdgeList(graphList, u, v, w);
                addEdgeMatrix(graphMatrix, u, v, w);
                printf("\n=> Road successfully added from %s to %s with cost %d.\n", locations[u], locations[v], w);
            } else {
                printf("\n=> Error: Invalid input. Make sure 0 <= ID <= 9, weight > 0, and Source != Destination.\n");
            }
        } 
        else if (choice == 3) {
            int src;
            printf("\nEnter Source Location ID (0-9): ");
            scanf("%d", &src);
            if (src >= 0 && src < V) {
                dijkstraList(graphList, src, true);
            } else {
                printf("Invalid Location ID.\n");
            }
        } 
        else if (choice == 4) {
            int src;
            printf("\nEnter Source Location ID (0-9): ");
            scanf("%d", &src);
            if (src >= 0 && src < V) {
                dijkstraMatrix(graphMatrix, src, true);
            } else {
                printf("Invalid Location ID.\n");
            }
        }
        else if (choice == 5) {
            evaluatePerformance();
        }
        else if (choice == 6) {
            printf("\nExiting...\n");
            freeGraphList(graphList);
            break;
        } 
        else {
            printf("\nInvalid choice.\n");
        }
    }

    return 0;
}