#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  } else {
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
  printf("\nIdx | Parent | Rank\n");
  printf("-------------------\n");
  
  int limit = (size > 15) ? 10 : size;
  
  for (int i = 0; i < limit; i++) {
    printf("%3d | %6d | %4d\n", i, d->parent[i], d->rank[i]);
  }
  
  if (size > 15) {
    printf("... | ...... | ....\n");
    for (int i = size - 5; i < size; i++) {
      printf("%3d | %6d | %4d\n", i, d->parent[i], d->rank[i]);
    }
  }
  printf("\n");
}

int main() {
  srand(time(NULL));
  DSU student;
  student.parent = NULL;
  student.rank = NULL;

  int size, operation_count, x, y, choice;
  printf("Enter the number of elements (n): ");
  if (scanf("%d", &size) != 1)
    return 1;

  init(&student, size);
  printf("DSU initialized with %d elements (0 to %d).\n", size, size - 1);
  display(&student, size);

  printf("Enter the number of Union operations: ");
  scanf("%d", &operation_count);

  while (operation_count--) {
    printf("\n====================================\n");
    x = rand() % size; 
    y = rand() % size;

    printf("Action: Union(%d, %d)\n", x, y);
    Union(&student, x, y);
    display(&student, size);
    printf("====================================\n");
  }

  do {
    printf("\nFind representative of any student of any group after the "
           "operations [-1 to quit]: ");
    scanf("%d", &choice);
    if (choice >= 0 && choice < size)
      printf("Representative of %d: %d\n", choice, find(&student, choice));
    else if (choice != -1)
      printf("Invalid index.\n");
  } while (choice != -1);

  freeDSU(&student);
  return 0;
}