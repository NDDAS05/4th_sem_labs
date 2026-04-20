#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. Recursive Method
unsigned long long fib_recursive(int n) {
  if (n <= 1) {
    return n;
  }
  return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// 2. Dynamic Programming Method (Tabulation)
unsigned long long fib_dp(int n) {
  if (n <= 1) {
    return n;
  }

  // Allocating memory for tabulation
  unsigned long long *dp =
      (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
  if (dp == NULL) {
    printf("Memory allocation failed.\n");
    exit(1);
  }

  dp[0] = 0;
  dp[1] = 1;

  for (int i = 2; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  unsigned long long result = dp[n];
  free(dp);

  return result;
}

int main() {
  int choice, n;
  unsigned long long result;
  clock_t start, end;
  double cpu_time_used;

  while (1) {
    printf("\n--- Fibonacci Calculator ---");
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
      printf("Enter the value of n (Max 93 for 64-bit integer limit): ");
      scanf("%d", &n);

      if (n < 0) {
        printf("Please enter a positive integer.\n");
        continue;
      } else if (n > 93) {
        printf("Warning: Results for n > 93 will overflow standard 64-bit "
               "integers.\n");
      }
    }

    switch (choice) {
    case 1:
      start = clock();
      result = fib_recursive(n);
      end = clock();
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("\n[Recursive] Fibonacci number %d is %llu\n", n, result);
      printf("Time taken: %f seconds\n", cpu_time_used);
      break;

    case 2:
      start = clock();
      result = fib_dp(n);
      end = clock();
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("\n[Dynamic Programming] Fibonacci number %d is %llu\n", n,
             result);
      printf("Time taken: %f seconds\n", cpu_time_used);
      break;

    case 3:
      // Test DP first to avoid making the user wait before seeing any output
      start = clock();
      result = fib_dp(n);
      end = clock();
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("\n[Dynamic Programming] Result: %llu | Time: %f seconds\n",
             result, cpu_time_used);

      if (n > 45) {
        printf("Skipping Recursive test. 'n' is too large and will take an "
               "excessive amount of time.\n");
      } else {
        start = clock();
        result = fib_recursive(n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("[Recursive]         Result: %llu | Time: %f seconds\n", result,
               cpu_time_used);
      }
      break;

    default:
      printf("\nInvalid choice. Please select a valid option.\n");
    }
  }

  return 0;
}
