#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100000

typedef struct {
  unsigned long long comp_count;
  int max_rec_depth;
  int curr_rec_depth;
} COMP;

int *init(int *arr) {
  arr = (int *)malloc(sizeof(int) * MAX);
  if (arr)
    return arr;
  else {
    printf("Allocation failed.");
    exit(1);
  }
}

void freeArr(int *arr) {
  if (arr) {
    free(arr);
    arr = NULL;
  }
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void shuffle(int *arr) {
  for (int i = 0; i < MAX; i++) {
    swap(&arr[rand() % MAX], &arr[rand() % MAX]);
  }
}

int *cpy_arr(int *source, int *destn) {
  if (source && destn)
    memcpy(destn, source, MAX * sizeof(int));
  return destn;
}

int *gen_90_arr(int *arr) {
  if (arr) {
    int dup = rand();
    int i;
    for (i = 0; i < MAX; i++) {
      if (i < (MAX * 9) / 10)
        arr[i] = dup;
      else
        arr[i] = rand();
    }

    shuffle(arr);

    return arr;
  }

  else {
    printf("No array found.\n");
    return NULL;
  }
}

int *gen_50_arr(int *arr) {
  if (arr) {
    int dup = rand(), i;
    for (i = 0; i < MAX; i++) {
      if (i < (MAX * 5) / 10)
        arr[i] = dup;
      else
        arr[i] = rand();
    }

    shuffle(arr);

    return arr;
  }

  else {
    printf("No array found.\n");
    return NULL;
  }
}

int *gen_10_arr(int *arr) {
  if (arr) {
    int dup = rand(), i;
    for (i = 0; i < MAX; i++) {
      if (i < (MAX * 1) / 10)
        arr[i] = dup;
      else
        arr[i] = rand();
    }

    return arr;
  }

  else {
    printf("No array found.\n");
    return NULL;
  }
}

int median_pivot(int *arr, int low, int high) {
  int mid = low + (high - low) / 2;

  if ((arr[low] > arr[mid]) != (arr[low] > arr[high]))
    return low;
  else if ((arr[mid] > arr[low]) != (arr[mid] > arr[high]))
    return mid;
  else
    return high;
}

int partition(int *arr, int low, int high, COMP *cp, bool sort_flag) {

  int p_index;

  if (sort_flag == true) {
    p_index = low + rand() % (high - low + 1);
  } else {
    p_index = median_pivot(arr, low, high);
  }

  swap(&arr[low], &arr[p_index]);

  int pivot = arr[low];
  int i = low;
  int j = high;

  while (i < j) {
    cp->comp_count++;
    while (arr[i] <= pivot && i < high) {
      i++;
      cp->comp_count++;
    }
    cp->comp_count++;

    while (arr[j] > pivot) {
      j--;
      cp->comp_count++;
    }
    cp->comp_count += 2;
    if (i < j)
      swap(&arr[i], &arr[j]);
  }
  cp->comp_count++;

  swap(&arr[low], &arr[j]);
  return j;
}

void quicksort(int *arr, int low, int high, COMP *cp, bool sort_flag) {
  cp->curr_rec_depth++;
  if (cp->curr_rec_depth > cp->max_rec_depth)
    cp->max_rec_depth = cp->curr_rec_depth;

  if (low < high) {
    int p_index = partition(arr, low, high, cp, sort_flag);

    quicksort(arr, low, p_index - 1, cp, sort_flag);
    quicksort(arr, p_index + 1, high, cp, sort_flag);
  }

  cp->curr_rec_depth--;
}

void logger(int dup_pct, const char *algo, double time, unsigned long long comp,
            int depth) {
  FILE *fp = fopen("Q2_data.txt", "a");
  if (!fp)
    return;

  // Format: Percentage Algorithm Time Comparisons Recursion_Depth
  //  Algorithm: 0 for Standard
  //             1 for Randomized

  int algo_num = (strcmp(algo, "Standard") == 0) ? 0 : 1;
  fprintf(fp, "%d %d %.6f %llu %d\n", dup_pct, algo_num, time, comp, depth);
  fclose(fp);
}

void test_bench(int *mainArr, int pct_duplicate) {

  int *dupArr = NULL;
  dupArr = init(dupArr);
  clock_t start, end;

  cpy_arr(mainArr, dupArr);
  COMP metrics = {0, 0, 0};
  // Standard pivot
  start = clock();
  quicksort(mainArr, 0, MAX - 1, &metrics, false);
  end = clock();
  printf("\t>> Algorithm: Standard\n\t>> Time Taken: %f\n\t>> Number of "
         "Comparisons: %llu\n\t>> Max Recursion Depth: %d\n",
         ((double)(end - start)) / CLOCKS_PER_SEC, metrics.comp_count,
         metrics.max_rec_depth);
  logger(pct_duplicate, "Standard", ((double)(end - start)) / CLOCKS_PER_SEC,
         metrics.comp_count, metrics.max_rec_depth);
  printf("\n----------------------------------------\n");

  // Randomized Pivot
  metrics.comp_count = 0;
  metrics.max_rec_depth = 0;
  metrics.curr_rec_depth = 0;

  start = clock();
  quicksort(dupArr, 0, MAX - 1, &metrics, true);
  end = clock();
  printf("\t>> Algorithm: Randomized\n\t>> Time Taken: %f\n\t>> Number of "
         "Comparisons: %llu\n\t>> Max Recursion Depth: %d\n",
         ((double)(end - start)) / CLOCKS_PER_SEC, metrics.comp_count,
         metrics.max_rec_depth);
  logger(pct_duplicate, "Randomized", ((double)(end - start)) / CLOCKS_PER_SEC,
         metrics.comp_count, metrics.max_rec_depth);

  freeArr(dupArr);
}

int main() {
  srand(time(NULL));

  int *mainArr = NULL;
  mainArr = init(mainArr);

  // For 90% duplicate array
  mainArr = gen_90_arr(mainArr);
  printf("\nFor 90%% duplicate array\n===============================\n");
  test_bench(mainArr, 90);

  // For 50% duplicate array
  mainArr = gen_50_arr(mainArr);
  printf("\nFor 50%% duplicate array\n===============================\n");
  test_bench(mainArr, 50);

  // For 10% duplicate array
  mainArr = gen_10_arr(mainArr);
  printf("\nFor 10%% duplicate array\n===============================\n");
  test_bench(mainArr, 10);

  freeArr(mainArr);
  return 0;
}
