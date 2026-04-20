#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b) { return (a > b) ? a : b; }

int knapsackRecursive(int W, int wt[], int val[], int n) {
  if (n == 0 || W == 0) {
    return 0;
  }

  if (wt[n - 1] > W) {
    return knapsackRecursive(W, wt, val, n - 1);
  } else {
    return max(val[n - 1] + knapsackRecursive(W - wt[n - 1], wt, val, n - 1),
               knapsackRecursive(W, wt, val, n - 1));
  }
}

int knapsackDP(int W, int wt[], int val[], int n) {
  int i, w;

  int **K = (int **)malloc((n + 1) * sizeof(int *));
  for (i = 0; i <= n; i++) {
    K[i] = (int *)malloc((W + 1) * sizeof(int));
  }

  for (i = 0; i <= n; i++) {
    for (w = 0; w <= W; w++) {
      if (i == 0 || w == 0) {
        K[i][w] = 0;
      } else if (wt[i - 1] <= w) {
        K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
      } else {
        K[i][w] = K[i - 1][w];
      }
    }
  }

  int result = K[n][W];

  for (i = 0; i <= n; i++) {
    free(K[i]);
  }
  free(K);

  return result;
}

int main() {
  int choice, n, W;
  clock_t start, end;
  double cpu_time_used;

  while (1) {
    printf("\n0/1 Knapsack Problem ");
    printf("\n1. Calculate using Resursive Method");
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
      printf("Enter the number of packages: ");
      scanf("%d", &n);

      if (n <= 0) {
        printf("Number of packages must be positive.\n");
        continue;
      }

      int *val = (int *)malloc(n * sizeof(int));
      int *wt = (int *)malloc(n * sizeof(int));

      printf("Enter the profits (values) of the packages:\n");
      for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
      }

      printf("Enter the weights of the packages:\n");
      for (int i = 0; i < n; i++) {
        scanf("%d", &wt[i]);
      }

      printf("Enter the maximum weight capacity of the truck: ");
      scanf("%d", &W);

      switch (choice) {
      case 1:
        start = clock();
        int max_profit_rec = knapsackRecursive(W, wt, val, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\n[Recursive] Maximum Profit: %d\n", max_profit_rec);
        printf("Time taken: %f seconds\n", cpu_time_used);
        break;

      case 2:
        start = clock();
        int max_profit_dp = knapsackDP(W, wt, val, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\n[Dynamic Programming] Maximum Profit: %d\n", max_profit_dp);
        printf("Time taken: %f seconds\n", cpu_time_used);
        break;

      case 3:
        start = clock();
        int dp_res = knapsackDP(W, wt, val, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\n[Dynamic Programming] Result: %d | Time: %f seconds\n",
               dp_res, cpu_time_used);

        start = clock();
        int rec_res = knapsackRecursive(W, wt, val, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("[Recursive]         Result: %d | Time: %f seconds\n", rec_res,
               cpu_time_used);

        break;
      }

      free(val);
      free(wt);
    } else {
      printf("\nInvalid choice. Please select a valid option.\n");
    }
  }

  return 0;
}
