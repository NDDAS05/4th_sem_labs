#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF INT_MAX
#define V 6

struct Node {
  int dest;
  int weight;
  struct Node *next;
};

struct List {
  struct Node *head;
};

struct MinHeapNode {
  int v;
  int key;
};

struct MinHeap {
  int size;
  int capacity;
  int *pos;
  struct MinHeapNode **array;
};

struct Node *newNode(int dest, int weight) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->dest = dest;
  node->weight = weight;
  node->next = NULL;
  return node;
}

void addEdge(struct List *adj, int src, int dest, int weight) {
  struct Node *node = newNode(dest, weight);
  node->next = adj[src].head;
  adj[src].head = node;

  node = newNode(src, weight);
  node->next = adj[dest].head;
  adj[dest].head = node;
}

struct MinHeapNode *newMinHeapNode(int v, int key) {
  struct MinHeapNode *node =
      (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
  node->v = v;
  node->key = key;
  return node;
}

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b) {
  struct MinHeapNode *t = *a;
  *a = *b;
  *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size &&
      minHeap->array[left]->key < minHeap->array[smallest]->key)
    smallest = left;

  if (right < minHeap->size &&
      minHeap->array[right]->key < minHeap->array[smallest]->key)
    smallest = right;

  if (smallest != idx) {
    minHeap->pos[minHeap->array[smallest]->v] = idx;
    minHeap->pos[minHeap->array[idx]->v] = smallest;
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap) {
  if (minHeap->size == 0)
    return NULL;
  struct MinHeapNode *root = minHeap->array[0];
  struct MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
  minHeap->array[0] = lastNode;
  minHeap->pos[root->v] = minHeap->size - 1;
  minHeap->pos[lastNode->v] = 0;
  --minHeap->size;
  minHeapify(minHeap, 0);
  return root;
}

void decreaseKey(struct MinHeap *minHeap, int v, int key) {
  int i = minHeap->pos[v];
  minHeap->array[i]->key = key;
  while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
    minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
    minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
    swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

int isInMinHeap(struct MinHeap *minHeap, int v) {
  return minHeap->pos[v] < minHeap->size;
}

void primMST(struct List *adj) {
  int parent[V];
  int key[V];
  int order[V];
  int orderIdx = 0;

  struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
  minHeap->capacity = V;
  minHeap->size = V;
  minHeap->pos = (int *)malloc(V * sizeof(int));
  minHeap->array =
      (struct MinHeapNode **)malloc(V * sizeof(struct MinHeapNode *));

  for (int v = 0; v < V; ++v) {
    parent[v] = -1;
    key[v] = INF;
    minHeap->array[v] = newMinHeapNode(v, key[v]);
    minHeap->pos[v] = v;
  }

  key[0] = 0;
  decreaseKey(minHeap, 0, key[0]);

  while (minHeap->size != 0) {
    struct MinHeapNode *minHeapNode = extractMin(minHeap);
    int u = minHeapNode->v;
    order[orderIdx++] = u;

    struct Node *pCrawl = adj[u].head;
    while (pCrawl != NULL) {
      int v = pCrawl->dest;
      if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v]) {
        key[v] = pCrawl->weight;
        parent[v] = u;
        decreaseKey(minHeap, v, key[v]);
      }
      pCrawl = pCrawl->next;
    }
  }

  int totalCost = 0;
  printf("Edges in the MST:\n");
  for (int i = 1; i < V; ++i) {
    printf("C%d - C%d: %d lakhs\n", parent[i] + 1, i + 1, key[i]);
    totalCost += key[i];
  }
  printf("\nTotal Minimum Cost: %d lakhs\n", totalCost);
  printf("Order of vertices added: ");
  for (int i = 0; i < V; i++) {
    printf("C%d ", order[i] + 1);
  }
  printf("\n");
}

int main() {
  struct List adj[V];
  for (int i = 0; i < V; i++)
    adj[i].head = NULL;

  addEdge(adj, 0, 1, 3); // (C1, C2) = 3
  addEdge(adj, 0, 2, 1); // (C1, C3) = 1
  addEdge(adj, 0, 3, 6); // (C1, C4) = 6
  addEdge(adj, 1, 2, 5); // (C2, C3) = 5
  addEdge(adj, 1, 4, 3); // (C2, C5) = 3
  addEdge(adj, 2, 3, 5); // (C3, C4) = 5
  addEdge(adj, 2, 5, 4); // (C3, C6) = 4
  addEdge(adj, 3, 5, 2); // (C4, C6) = 2
  addEdge(adj, 4, 5, 6); // (C5, C6) = 6

  primMST(adj);

  return 0;
}
