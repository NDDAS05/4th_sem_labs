#include <stdio.h>
#include <stdlib.h>

typedef struct DSU {
  int *parent; // parent[i]=i;
  int *rank;   // Only parent index holds valid rank.
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

int find(DSU *d, int x) // Returns root of the tree where the element is.
{
  if (d->parent[x] == x)
    return x; // Base Case: Parent's Parent is Parent itself.
  // It returns root of the tree

  // Path Compression : Every time we visit a node, we update its parent to the
  // parent of the tree itself.
  // In recursion, instead of calling return
  // find(parent[x]); we do parent[x] = find(parent[x]); return parent[x];

  // Since base case returns the "root of the tree",
  // every other node accessed due to recursive call find(parent[x]) will have
  // their parent updated to "root of the tree" while returning.

  return d->parent[x] = find(d, d->parent[x]);
}

int Union(DSU *d, int x, int y) // Returns root of the Union-ed tree.
{
  int root1 = find(d, x);
  int root2 = find(d, y);
  // We find the tree roots first. Further operation will be on tree root, not
  // element specific.
  // [ Since union "combines" two SETs, does NOTHING ELEMENT SPECIFIC. ]
  // We need to know the set/tree the element belongs to, not the
  // element itself.

  // If both belong to the same set
  if (root1 == root2)
    return root1; // Or root2.

  // If rank[root1] == rank[root2],
  // Then: Assign any one to other. Say we make "root2" to point "root1".
  // In that case,   RANK OF root1     will be      +1.
  else if (d->rank[root1] == d->rank[root2]) {
    // We make root2 point to root1.
    // Thus, parent of root2 will be root1
    // AND, height of root1 tree will become +1

    d->parent[root2] = root1;
    (d->rank[root1])++;
    return root1;
  }

  // Ranks of root1 and root2 are un-equal.
  else {
    // Since this is "UNION BY RANK",
    // if rank[root1] > rank[root2],
    // root2 will point to root1.
    // AND, height will be that of max(rootoot1, root2)
    // In this case height/rank = root1.

    if (d->rank[root1] > d->rank[root2]) {
      d->parent[root2] = root1;
      // d->rank[root2] = d->rank[root1] NOT NEEDED,
      // as we do operations on root, which, for root2 tree, is already changed.

      return root1;
    } else { // rank[root2] > rank[root1]
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