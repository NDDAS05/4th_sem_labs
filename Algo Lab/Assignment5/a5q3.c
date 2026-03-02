#include <stdio.h>
#include <stdlib.h>

typedef struct DSU {
    int *parent;
    int *rank;
    int components; // To track the number of disconnected sets at any point
} DSU;

void init(DSU *d, int size) {
    d->parent = (int *)malloc(sizeof(int) * size);
    d->rank = (int *)malloc(sizeof(int) * size);
    d->components = size;
    
    for (int i = 0; i < size; i++) {
        d->parent[i] = i;
        d->rank[i] = 0;
    }
}

void freeDSU(DSU *d) {
    if (d->parent) free(d->parent);
    if (d->rank) free(d->rank);
    d->parent = NULL;
    d->rank = NULL;
}

int find(DSU *d, int x) {
    if (d->parent[x] == x)
        return x;

    return d->parent[x] = find(d, d->parent[x]);
}

int Union(DSU *d, int x, int y) {
    int root1 = find(d, x);
    int root2 = find(d, y);
    
    if (root1 == root2) {
        return root1; 
    }

    d->components--;
    
    if (d->rank[root1] < d->rank[root2]) {
        d->parent[root1] = root2;
        return root2;
    } else if (d->rank[root1] > d->rank[root2]) {
        d->parent[root2] = root1;
        return root1;
    } else {
        d->parent[root2] = root1;
        d->rank[root1]++;
        return root1;
    }
}

int main() {
    int n;
    printf("Enter the total number of buildings initially (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for N.\n");
        return 1;
    }

    DSU city;
    init(&city, n);

    int choice, u, v, leader;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Construct Road (Union)\n");
        printf("2. Find Building Representative (Find)\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Enter buildings to connect (u v, from 0 to %d): ", n - 1);
                scanf("%d %d", &u, &v);
                
                if (u < 0 || u >= n || v < 0 || v >= n) {
                    printf("Invalid building numbers.\n");
                    break;
                }
                
                if (find(&city, u) == find(&city, v)) {
                    printf("Buildings %d and %d are already connected.\n", u, v);
                } else {
                    Union(&city, u, v);
                    printf("Road constructed successfully between %d and %d.\n", u, v);
                }
                
                if (city.components == 1) {
                    printf("The entire city is now Fully Connected.\n");
                } else {
                    printf("City is not fully connected yet. Remaining components: %d\n", city.components);
                }
                break;
                
            case 2:
                printf("Enter building number to find its leader: ");
                scanf("%d", &u);
                if (u < 0 || u >= n) {
                    printf("Invalid building number.\n");
                } else {
                    leader = find(&city, u);
                    printf("The representative (leader) for building %d is %d.\n", u, leader);
                }
                break;
                
            case 3:
                freeDSU(&city);
                printf("Memory freed. Exiting program...\n");
                return 0;
                
            default:
                printf("Please select 1, 2, or 3.\n");
        }
    }
    
    freeDSU(&city);
    return 0;
}