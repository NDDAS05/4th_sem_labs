#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int matrixChainRecursive(int p[], int i, int j) {
  if (i == j) {
    return 0;
  }

  int min_cost = INT_MAX;
  int count;

  for (int k = i; k < j; k++) {
    count = matrixChainRecursive(p, i, k) + matrixChainRecursive(p, k + 1, j) +
            p[i - 1] * p[k] * p[j];

    if (count < min_cost) {
      min_cost = count;
    }
  }

  return min_cost;
}

int matrixChainDP(int p[], int n) {
  int m[n][n];

  for (int i = 1; i < n; i++) {
    m[i][i] = 0;
  }

  for (int L = 2; L < n; L++) {
    for (int i = 1; i < n - L + 1; i++) {
      int j = i + L - 1;
      m[i][j] = INT_MAX;
      for (int k = i; k <= j - 1; k++) {
        int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
        if (q < m[i][j]) {
          m[i][j] = q;
        }
      }
    }
  }

  return m[1][n - 1];
}

int main() {
  int choice;
  int n;
  clock_t start, end;
  double cpu_time_used;

  while (1) {
    printf("\n\tMatrix Chain Multiplication");
    printf("\n1. Calculate using Recursive Method");
    printf("\n2. Calculate using Dynamic Programming Method");
    printf("\n3. Compare Performance of Both Methods");
    printf("\n4. Exit");
    printf("\nEnter your choice (1-4): ");
    scanf("%d", &choice);

    if (choice == 4) {
      printf("Exiting program.\n");
      break;
    }

    if (choice >= 1 && choice <= 3) {
      printf("Enter the number of matrices: ");
      int num_matrices;
      scanf("%d", &num_matrices);
      n = num_matrices + 1;

      int *p = (int *)malloc(n * sizeof(int));
      if (p == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
      }

      printf("Enter the %d dimensions array (such as, for 3 matrices of 10x30, "
             "30x5, 5x60 enter: 10 30 5 60):\n",
             n);
      for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
      }

      switch (choice) {
      case 1:
        start = clock();
        int min_ops_rec = matrixChainRecursive(p, 1, n - 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\n[Recursive] Minimum scalar multiplications: %d\n",
               min_ops_rec);
        printf("Time taken: %f seconds\n", cpu_time_used);
        break;

      case 2:
        start = clock();
        int min_ops_dp = matrixChainDP(p, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\n[Dynamic Programming] Minimum scalar multiplications: %d\n",
               min_ops_dp);
        printf("Time taken: %f seconds\n", cpu_time_used);
        break;

      case 3:
        start = clock();
        int dp_res = matrixChainDP(p, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\n[Dynamic Programming] Result: %d | Time: %f seconds\n",
               dp_res, cpu_time_used);

        start = clock();
        int rec_res = matrixChainRecursive(p, 1, n - 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("[Recursive]         Result: %d | Time: %f seconds\n", rec_res,
               cpu_time_used);

        break;
      }
      free(p);
    } else {
      printf("\nInvalid choice.\n");
    }
  }

  return 0;
}
