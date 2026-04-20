#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int u, v, weight;
} Edge;

typedef struct {
  int parent;
} Subset;

int find(Subset subsets[], int i) {
  if (subsets[i].parent != i)
    subsets[i].parent = find(subsets, subsets[i].parent);
  return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
  int xroot = find(subsets, x);
  int yroot = find(subsets, y);
  subsets[xroot].parent = yroot;
}

int compareEdges(const void *a, const void *b) {
  return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

long kruskal(int V, int E, Edge edges[], Edge result[]) {
  long mst_weight = 0;
  qsort(edges, E, sizeof(Edge), compareEdges);
  Subset *subsets = (Subset *)malloc(V * sizeof(Subset));
  for (int v = 0; v < V; ++v)
    subsets[v].parent = v;
  int e = 0, i = 0;
  while (e < V - 1 && i < E) {
    Edge next_edge = edges[i++];
    int x = find(subsets, next_edge.u);
    int y = find(subsets, next_edge.v);
    if (x != y) {
      result[e++] = next_edge;
      mst_weight += next_edge.weight;
      Union(subsets, x, y);
    }
  }
  free(subsets);
  return mst_weight;
}

long prim(int V, int adj[V][V], Edge result[]) {
  int parent[V], key[V], mstSet[V];
  for (int i = 0; i < V; i++) {
    key[i] = INT_MAX;
    mstSet[i] = 0;
  }
  key[0] = 0;
  parent[0] = -1;
  for (int count = 0; count < V - 1; count++) {
    int min = INT_MAX, u;
    for (int v = 0; v < V; v++)
      if (!mstSet[v] && key[v] < min) {
        min = key[v];
        u = v;
      }
    mstSet[u] = 1;
    for (int v = 0; v < V; v++)
      if (adj[u][v] && !mstSet[v] && adj[u][v] < key[v]) {
        parent[v] = u;
        key[v] = adj[u][v];
      }
  }
  long mst_weight = 0;
  for (int i = 1; i < V; i++) {
    result[i - 1].u = parent[i];
    result[i - 1].v = i;
    result[i - 1].weight = adj[i][parent[i]];
    mst_weight += adj[i][parent[i]];
  }
  return mst_weight;
}

int main() {
  int V1, E1, V2, E2;

  printf("Smart City Power Grid\n--------------------------\n");

  printf("[STEP 1: Graph G1 (Sparse - Kruskal's)]\n");
  printf("Enter number of vertices and edges: ");
  scanf("%d %d", &V1, &E1);
  Edge *edgesG1 = (Edge *)malloc(E1 * sizeof(Edge));
  printf("Enter %d edges in 'src dest weight' format:\n", E1);
  for (int i = 0; i < E1; i++) {
    printf("  Edge %d: ", i + 1);
    scanf("%d %d %d", &edgesG1[i].u, &edgesG1[i].v, &edgesG1[i].weight);
  }

  printf("\n[STEP 2: Graph G2 (Dense - Prim's)]\n");
  printf("Enter number of vertices and edges: ");
  scanf("%d %d", &V2, &E2);
  int adjG2[V2][V2];
  for (int i = 0; i < V2; i++)
    for (int j = 0; j < V2; j++)
      adjG2[i][j] = 0;
  printf("Enter %d edges in 'src dest weight' format:\n", E2);
  for (int i = 0; i < E2; i++) {
    int u, v, w;
    printf("  Edge %d: ", i + 1);
    scanf("%d %d %d", &u, &v, &w);
    adjG2[u][v] = adjG2[v][u] = w;
  }

  printf("\n[STEP 3: High-Capacity Transmission Edge (maximum weight amongst "
         "all edges)]\n");
  Edge trans;
  printf("Enter the connecting edge 'G1_node G2_node weight': ");
  scanf("%d %d %d", &trans.u, &trans.v, &trans.weight);

  Edge *resG1 = malloc((V1 - 1) * sizeof(Edge)),
       *resG2 = malloc((V2 - 1) * sizeof(Edge));
  long costG1 = kruskal(V1, E1, edgesG1, resG1);
  long costG2 = prim(V2, adjG2, resG2);
  long total = costG1 + costG2 + trans.weight;

  printf("Global MST Results\n");
  printf("==========================================\n");
  for (int i = 0; i < V1 - 1; i++)
    printf("G1 Edge: %d -- %d (Weight: %d)\n", resG1[i].u, resG1[i].v,
           resG1[i].weight);
  for (int i = 0; i < V2 - 1; i++)
    printf("G2 Edge: %d -- %d (Weight: %d)\n", resG2[i].u, resG2[i].v,
           resG2[i].weight);
  printf("Bridge:  G1(%d) -- G2(%d) (Weight: %d)\n", trans.u, trans.v,
         trans.weight);
  printf("------------------------------------------\n");
  printf("Total MST cost: %ld\n", total);
  printf("==========================================\n");

  free(edgesG1);
  free(resG1);
  free(resG2);
  return 0;
}
