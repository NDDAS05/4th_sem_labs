#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100000

typedef struct {
  unsigned long long comp;
  int curr_rec_depth;
  int max_rec_depth;
} COMP;

int *init(int *arr, int size) {
  arr = (int *)malloc(sizeof(int) * size);
  if (arr)
    return arr;
  printf("Allocation failed. Exiting program.\n");
  exit(1);
}

int *freeArr(int *arr) {
  if (arr)
    free(arr);
  return NULL;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int *gen_80_array(int *arr) {
  if (!arr) {
    arr = init(arr, MAX);

    for (int i = 0; i < MAX; i++) {
      if (i < (MAX / 10) * 8)
        arr[i] = i;
      else
        arr[i] = rand();
    }

    return arr;
  }

  printf("Existing array found. Can not overwrite data.\n");
  return arr;
}

void cpy_arr(int *destn, int *source) {
  memcpy(destn, source, MAX * sizeof(int));
}

int partition(int *arr, int low, int high, COMP *cp) {
  int i = low;
  int j = high;
  int pivot = arr[low];

  while (i < j) {
    while (i < MAX && arr[i] <= pivot) {
      cp->comp++;
      i++;
    }
    cp->comp++;

    while (arr[j] > pivot) {
      cp->comp++;
      j--;
    }
    cp->comp++;

    if (i < j) {
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[low], &arr[j]);
  return j;
}

void quickSort(int *arr, int low, int high, COMP *cp) {
  cp->curr_rec_depth++;
  cp->max_rec_depth = (cp->curr_rec_depth >= cp->max_rec_depth)
                          ? cp->curr_rec_depth
                          : cp->max_rec_depth;

  if (low < high) {
    int p_index = partition(arr, low, high, cp);

    quickSort(arr, low, p_index - 1, cp);
    quickSort(arr, p_index + 1, high, cp);
  }
  cp->curr_rec_depth--;
}

void merge(int *arr, int *temp, int low, int mid, int high, COMP *cp) {
  int *n1 = temp;
  int *n2 = temp + (mid - low + 1);
  int size1 = (mid - low + 1);
  int size2 = high - mid;
  int index = low, i, j;

  for (i = 0; i < size1; i++, index++) {
    n1[i] = arr[index];
  }

  for (j = 0; j < size2; j++, index++) {
    n2[j] = arr[index];
  }

  index = low, i = 0, j = 0;

  while (i < size1 && j < size2) {
    if (n1[i] > n2[j]) {
      cp->comp++;
      arr[index] = n2[j];
      j++;
      index++;
    } else {
      cp->comp++;
      arr[index] = n1[i];
      i++;
      index++;
    }
  }

  while (i < size1) {
    arr[index] = n1[i];
    index++;
    i++;
  }

  while (j < size2) {
    arr[index] = n2[j];
    index++;
    j++;
  }
}

void mergeSort(int *arr, int *temp, int low, int high, COMP *cp) {
  cp->curr_rec_depth++;
  cp->max_rec_depth = (cp->curr_rec_depth >= cp->max_rec_depth)
                          ? cp->curr_rec_depth
                          : cp->max_rec_depth;

  if (low < high) {
    int mid = low + (high - low) / 2;
    mergeSort(arr, temp, low, mid, cp);
    mergeSort(arr, temp, mid + 1, high, cp);

    merge(arr, temp, low, mid, high, cp);
  }
  cp->curr_rec_depth--;
}

void logger(const char *algo, double time, COMP *cp) {
  FILE *fp = fopen("Q3_comparison_data.txt", "a");
  if (!fp)
    return;
  int sortType = strcmp(algo, "Merge") == 0 ? 0 : 1;
  // Format: sortType Number_of_Comparisons Max_Recursion_Depth Time_Taken
  fprintf(fp, "%d %llu %d %f\n", sortType, cp->comp, cp->max_rec_depth, time);
  fclose(fp);
}

void test_bench() {
  printf("  Quick Sort\n=================================\n");

  int *mainArr = NULL;
  int *cpyArr = NULL;
  mainArr = gen_80_array(mainArr);
  cpyArr = init(cpyArr, MAX);
  cpy_arr(cpyArr, mainArr);

  FILE *fp = fopen("Q3_comparison_data.txt", "w");
  if (fp)
    fclose(fp);

  clock_t start, end;
  double total_time;

  COMP metrics = {0, 0, 0};

  start = clock();
  quickSort(mainArr, 0, MAX - 1, &metrics);
  end = clock();
  total_time = (double)(end - start) / CLOCKS_PER_SEC;
  printf("\t>> Time Elapsed: %f\n\t>> Maximum Recursion Depth: %d\n\t>> Total "
         "number of comparisons: %llu\n",
         total_time, metrics.max_rec_depth, metrics.comp);
  logger("Quick", total_time, &metrics);

  metrics.comp = 0;
  metrics.max_rec_depth = 0;
  metrics.curr_rec_depth = 0;

  printf("  Merge Sort \n========================================\n");
  int *tempArr = NULL;
  tempArr = init(tempArr, MAX);

  start = clock();
  mergeSort(cpyArr, tempArr, 0, MAX - 1, &metrics);
  end = clock();
  total_time = (double)(end - start) / CLOCKS_PER_SEC;
  printf("\t>> Time Elapsed: %f\n\t>> Maximum Recursion Depth: %d\n\t>> Total "
         "number of comparisons: %llu\n",
         total_time, metrics.max_rec_depth, metrics.comp);
  logger("Merge", total_time, &metrics);

  freeArr(mainArr);
  freeArr(cpyArr);
  freeArr(tempArr);
}

int main() {
  srand(time(NULL));
  test_bench();
  return 0;
}
