#include <stdio.h>
#include <stdlib.h>

struct Edge {
  int u, v, weight;
};

struct Graph {
  int V, E;
  struct Edge *edge;
};

struct Graph *createGraph(int V, int E) {
  struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
  graph->V = V;
  graph->E = E;
  graph->edge = (struct Edge *)malloc(graph->E * sizeof(struct Edge));
  return graph;
}

struct subset {
  int parent;
  int rank;
};

int find(struct subset subsets[], int i) {
  if (subsets[i].parent != i)
    subsets[i].parent = find(subsets, subsets[i].parent);
  return subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y) {
  int xroot = find(subsets, x);
  int yroot = find(subsets, y);

  if (subsets[xroot].rank < subsets[yroot].rank) {
    subsets[xroot].parent = yroot;
  } else if (subsets[xroot].rank > subsets[yroot].rank) {
    subsets[yroot].parent = xroot;
  } else {
    subsets[yroot].parent = xroot;
    subsets[xroot].rank++;
  }
}

int myComp(const void *a, const void *b) {
  struct Edge *a1 = (struct Edge *)a;
  struct Edge *b1 = (struct Edge *)b;
  return a1->weight > b1->weight;
}

void KruskalMST(struct Graph *graph) {
  int V = graph->V;
  struct Edge result[V];
  int e = 0;
  int i = 0;

  qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

  struct subset *subsets = (struct subset *)malloc(V * sizeof(struct subset));

  for (int v = 0; v < V; ++v) {
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }

  while (e < V - 1 && i < graph->E) {
    struct Edge next_edge = graph->edge[i++];

    int x = find(subsets, next_edge.u);
    int y = find(subsets, next_edge.v);

    if (x != y) {
      result[e++] = next_edge;
      Union(subsets, x, y);
    }
  }

  printf("Order of edges added to the Minimum Spanning Tree:\n");
  int minimumCost = 0;
  for (i = 0; i < e; ++i) {
    printf("Edge: (C%d, C%d) | Cost: %d Lakhs\n", result[i].u + 1,
           result[i].v + 1, result[i].weight);
    minimumCost += result[i].weight;
  }
  printf("\nTotal Minimum Cost = %d Lakhs\n", minimumCost);

  free(subsets);
}

int main() {
  int V = 6;
  int E = 9;
  struct Graph *graph = createGraph(V, E);

  graph->edge[0].u = 0;
  graph->edge[0].v = 1;
  graph->edge[0].weight = 3; // C1-C2
  graph->edge[1].u = 0;
  graph->edge[1].v = 2;
  graph->edge[1].weight = 1; // C1-C3
  graph->edge[2].u = 0;
  graph->edge[2].v = 3;
  graph->edge[2].weight = 6; // C1-C4
  graph->edge[3].u = 1;
  graph->edge[3].v = 2;
  graph->edge[3].weight = 5; // C2-C3
  graph->edge[4].u = 1;
  graph->edge[4].v = 4;
  graph->edge[4].weight = 3; // C2-C5
  graph->edge[5].u = 2;
  graph->edge[5].v = 3;
  graph->edge[5].weight = 5; // C3-C4
  graph->edge[6].u = 2;
  graph->edge[6].v = 5;
  graph->edge[6].weight = 4; // C3-C6
  graph->edge[7].u = 3;
  graph->edge[7].v = 5;
  graph->edge[7].weight = 2; // C4-C6
  graph->edge[8].u = 4;
  graph->edge[8].v = 5;
  graph->edge[8].weight = 6; // C5-C6

  KruskalMST(graph);

  free(graph->edge);
  free(graph);
  return 0;
}
