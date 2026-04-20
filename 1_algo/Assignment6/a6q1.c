#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define E_SPARSE 120
#define E_DENSE 4500
#define DISPLAY_LIMIT 10

typedef struct Node {
  int dest;
  int weight;
  struct Node *next;
} Node;

Node *createNode(int dest, int weight) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->dest = dest;
  newNode->weight = weight;
  newNode->next = NULL;
  return newNode;
}

bool edgeExistsList(Node *adj[], int u, int v) {
  Node *temp = adj[u];
  while (temp != NULL) {
    if (temp->dest == v)
      return true;
    temp = temp->next;
  }
  return false;
}

void addEdgeList(Node *adj[], int u, int v, int weight) {
  Node *newNode1 = createNode(v, weight);
  newNode1->next = adj[u];
  adj[u] = newNode1;

  Node *newNode2 = createNode(u, weight);
  newNode2->next = adj[v];
  adj[v] = newNode2;
}

void displayAdjList(Node *adj[], bool isWeighted) {
  for (int i = 0; i < DISPLAY_LIMIT; i++) {
    Node *temp = adj[i];
    printf("Vertex %2d: ", i);
    if (temp == NULL) {
      printf("None");
    }
    while (temp != NULL) {
      if (isWeighted) {
        printf("-> [v:%d, wt:%d] ", temp->dest, temp->weight);
      } else {
        printf("-> %d ", temp->dest);
      }
      temp = temp->next;
    }
    printf("\n");
  }
  printf("... (remaining %d vertices hidden for clarity.)\n",
         N - DISPLAY_LIMIT);
}

void displayAdjMatrix(int matrix[N][N]) {
  printf("     ");
  for (int j = 0; j < DISPLAY_LIMIT; j++) {
    printf("[%2d] ", j);
  }
  printf("...\n");

  for (int i = 0; i < DISPLAY_LIMIT; i++) {
    printf("[%2d] ", i);
    for (int j = 0; j < DISPLAY_LIMIT; j++) {
      if (matrix[i][j] == 0) {
        printf("  .  ");
      } else {
        printf("%3d  ", matrix[i][j]);
      }
    }
    printf("...\n");
  }
  printf("\n(remaining %dx%d matrix hidden for clarity)\n", N - DISPLAY_LIMIT,
         N - DISPLAY_LIMIT);
}

int main() {
  srand(time(NULL));

  Node *sparse_unweighted[N] = {NULL};
  Node *sparse_weighted[N] = {NULL};

  int sparse_edges = 0;
  while (sparse_edges < E_SPARSE) {
    int u = rand() % N;
    int v = rand() % N;

    if (u != v && !edgeExistsList(sparse_unweighted, u, v)) {
      int weight = (rand() % 100) + 1;
      addEdgeList(sparse_unweighted, u, v, 0);
      addEdgeList(sparse_weighted, u, v, weight);
      sparse_edges++;
    }
  }

  int (*dense_unweighted)[N] = calloc(N, sizeof(*dense_unweighted));
  int (*dense_weighted)[N] = calloc(N, sizeof(*dense_weighted));

  int dense_edges = 0;
  while (dense_edges < E_DENSE) {
    int u = rand() % N;
    int v = rand() % N;

    if (u != v && dense_unweighted[u][v] == 0) {
      int weight = (rand() % 100) + 1;

      dense_unweighted[u][v] = 1;
      dense_unweighted[v][u] = 1;

      dense_weighted[u][v] = weight;
      dense_weighted[v][u] = weight;

      dense_edges++;
    }
  }

  printf("\nSPARSE GRAPH (%d Vertices, %d Edges) - PREVIEW\n", N, E_SPARSE);
  printf("=====================================================\n");

  printf("\nUnweighted Adjacency List\n");
  displayAdjList(sparse_unweighted, false);

  printf("\nWeighted Adjacency List\n");
  displayAdjList(sparse_weighted, true);

  printf("\nDENSE GRAPH (%d Vertices, %d Edges) - PREVIEW\n", N, E_DENSE);
  printf("=====================================================\n");

  printf("\nUnweighted Adjacency Matrix (Top-Left 10x10)\n");
  displayAdjMatrix(dense_unweighted);

  printf("\nWeighted Adjacency Matrix (Top-Left 10x10)\n");
  displayAdjMatrix(dense_weighted);

  for (int i = 0; i < N; i++) {
    Node *temp = sparse_unweighted[i];
    while (temp) {
      Node *next = temp->next;
      free(temp);
      temp = next;
    }
    temp = sparse_weighted[i];
    while (temp) {
      Node *next = temp->next;
      free(temp);
      temp = next;
    }
  }
  free(dense_unweighted);
  free(dense_weighted);

  return 0;
}
