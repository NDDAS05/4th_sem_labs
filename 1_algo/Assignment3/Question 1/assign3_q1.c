#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 100000

typedef struct {
  unsigned long long comp;
  double time_taken;
} Metrics;

int *init_array(int size) {
  int *arr = (int *)malloc(sizeof(int) * size);
  if (!arr) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
  return arr;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void gen_sorted_scores(int *arr) {
  int current_idx = 0;

  for (int score = 0; score <= 100; score++) {
    if (current_idx >= MAX) break;

    int repeat_no = rand() % 1000; 
    if (score == 100) {
      repeat_no = MAX - current_idx;
    }

    if (current_idx + repeat_no > MAX) {
      repeat_no = MAX - current_idx;
    }

    for (int k = 0; k < repeat_no; k++) {
      arr[current_idx++] = score;
    }
  }

  while (current_idx < MAX) {
    arr[current_idx++] = 100;
  }
}

void reverse_array(int *arr) {
  int start = 0;
  int end = MAX - 1;
  while (start < end) {
    swap(&arr[start], &arr[end]);
    start++;
    end--;
  }
}

void shuffle_array(int *arr) {
  for (int i = MAX - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swap(&arr[i], &arr[j]);
  }
}

int partition(int *arr, int low, int high, Metrics *m) {

  int random = low + rand() % (high - low + 1);
  swap(&arr[random], &arr[low]);
  
  int pivot = arr[low];
  int i = low + 1;
  int j = high;

  while (i <= j) {
    while (i <= high && arr[i] <= pivot) {
      m->comp++;
      i++;
    }
    m->comp++;

    while (j > low && arr[j] > pivot) {
      m->comp++;
      j--;
    }
    m->comp++;

    if (i < j) {
      swap(&arr[i], &arr[j]);
    }
  }

  swap(&arr[low], &arr[j]);
  return j;
}

void quickSort(int *arr, int low, int high, Metrics *m) {
  if (low < high) {
    int p_index = partition(arr, low, high, m);
    
    quickSort(arr, low, p_index - 1, m);
    quickSort(arr, p_index + 1, high, m);
  }
}

void run_sort_test(int *arr, const char *arr_type) {
  Metrics m = {0, 0.0};

  int *tempArr = init_array(MAX);
  memcpy(tempArr, arr, MAX * sizeof(int));

  clock_t start = clock();
  quickSort(tempArr, 0, MAX - 1, &m);
  clock_t end = clock();

  m.time_taken = (double)(end - start) / CLOCKS_PER_SEC;

  printf("Case: %s\n", arr_type);
  printf("------------------------------------------------\n");
  printf("  >> Input: %s\n", arr_type);
  printf("  >> Time Taken : %f seconds\n", m.time_taken);
  printf("  >> Number of Comparisons: %llu\n", m.comp);
  printf("------------------------------------------------\n\n");

  free(tempArr);
}

int main() {
  srand(time(NULL));

  printf("Algorithm: Randomized Quick Sort\n\n");

  int *mainArr = init_array(MAX);

  gen_sorted_scores(mainArr);
  run_sort_test(mainArr, "Sorted_Ascending");

  gen_sorted_scores(mainArr);
  reverse_array(mainArr);
  run_sort_test(mainArr, "Sorted_Descending");

  shuffle_array(mainArr); 
  run_sort_test(mainArr, "Random_Average");

  free(mainArr);
  return 0;
}