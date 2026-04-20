#include <stdio.h>
#include <stdlib.h>

typedef struct DSU {
  int *parent;
  int *rank;
} DSU;

void fillZero(DSU *d, int size) {
  for (int i = 0; i < size; i++) {
    d->rank[i] = 0;
  }
}
void fillParent(DSU *d, int size) {
  for (int i = 0; i < size; i++) {
    d->parent[i] = i;
  }
}

void init(DSU *d, int size) {
  d->parent = (int *)malloc(sizeof(int) * size);
  fillParent(d, size);
  d->rank = (int *)malloc(sizeof(int) * size);
  fillZero(d, size);
}

void freeDSU(DSU *d) {
  if ((d->parent) && (d->rank)) {
    free(d->parent);
    d->parent = NULL;
    free(d->rank);
    d->rank = NULL;
  }
}

int find(DSU *d, int x)
{
  if (d->parent[x] == x)
    return x;
  return d->parent[x] = find(d, d->parent[x]);
}

int Union(DSU *d, int x, int y)
{
  int root1 = find(d, x);
  int root2 = find(d, y);

  if (root1 == root2)
    return root1;

  else if (d->rank[root1] == d->rank[root2]) {
    d->parent[root2] = root1;
    (d->rank[root1])++;
    return root1;
  }

  else {
    if (d->rank[root1] > d->rank[root2]) {
      d->parent[root2] = root1;

      return root1;
    } else {
      d->parent[root1] = root2;
      return root2;
    }
  }
}

void display(DSU *d, int size) {
  printf("\nIndex:  ");
  for (int i = 0; i < size; i++)
    printf("%d ", i);
  printf("\nParent: ");
  for (int i = 0; i < size; i++)
    printf("%d ", d->parent[i]);
  printf("\nRank:   ");
  for (int i = 0; i < size; i++)
    printf("%d ", d->rank[i]);
  printf("\n");
}

int main() {
  DSU myDsu;
  myDsu.parent = NULL;
  myDsu.rank = NULL;

  int size, choice, x, y;

  printf("Enter the number of elements (n): ");
  if (scanf("%d", &size) != 1)
    return 1;

  init(&myDsu, size);
  printf("DSU initialized with %d elements (0 to %d).\n", size, size - 1);

  while (1) {
    printf("\nChoose an option:");
    printf("\n1. Union(x, y)");
    printf("\n2. Find(x)");
    printf("\n3. Check if x and y are in same set");
    printf("\n4. Display Arrays");
    printf("\n5. Exit");
    printf("\nChoice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter two elements to union: ");
      scanf("%d %d", &x, &y);
      if (x >= 0 && x < size && y >= 0 && y < size) {
        int root = Union(&myDsu, x, y);
        printf("Union successful. New root is: %d\n", root);
      } else {
        printf("Error: Elements out of bounds.\n");
      }
      break;

    case 2:
      printf("Enter element to find: ");
      scanf("%d", &x);
      if (x >= 0 && x < size) {
        printf("Root of %d is: %d\n", x, find(&myDsu, x));
      } else {
        printf("Error: Element out of bounds.\n");
      }
      break;

    case 3:
      printf("Enter two elements to check: ");
      scanf("%d %d", &x, &y);
      if (x >= 0 && x < size && y >= 0 && y < size) {
        if (find(&myDsu, x) == find(&myDsu, y))
          printf("Common Head =(%d).\n", find(&myDsu, x));
        else
          printf("Head of %d: %d\nHead of %d: %d\n", x, find(&myDsu, x), y,
                 find(&myDsu, y));
      }
      break;

    case 4:
      display(&myDsu, size);
      break;

    case 5:
      freeDSU(&myDsu);
      printf("Memory freed. Exiting...\n");
      return 0;

    default:
      printf("Invalid choice.\n");
    }
  }
}
