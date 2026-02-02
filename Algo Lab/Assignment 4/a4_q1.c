#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  double clk;
  float median;
} metric;

// Maximum marks: 100

int *init(bool fill) {
  int *arr = (int *)malloc(sizeof(int) * 110000);

  if (!arr) {
    printf("Allocation failed.");
    return NULL;
  }

  if (fill) {
    // 1. Random bias : So that for last elements, median is not always 50
    int random_bias = (rand() % 41) - 20;

    for (int i = 0; i < 110000; i++) {
      int mark = rand() % 101;
      mark += random_bias;
      if (mark < 0)
        mark = 0;
      if (mark > 100)
        mark = 100;

      arr[i] = mark;
    }
  }

  return arr;
}
int *freeArr(int *arr) {
  if (arr) {
    free(arr);
  }
  return NULL;
}

void memCpy(int *destn, int *source) {
  if (destn && source)
    memcpy(destn, source, sizeof(int) * 110000);
  else
    printf("Invalid source or destination.\n");
}

int randPvt(int low, int high) { return low + rand() % (high - low + 1); }

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int midPvt(int *arr, int low, int high) {
  int mid = low + (high - low) / 2;

  if ((arr[low] <= arr[high]) != (arr[low] <= arr[mid]))
    return low;
  else if ((arr[mid] <= arr[high]) != (arr[mid] <= arr[low]))
    return mid;
  else
    return high;
}

int pivot_location(int *arr, int left, int right, bool QuickSort) {
  int p_index;
  if (!QuickSort)
    p_index = randPvt(left, right);
  else
    p_index = midPvt(arr, left, right);

  swap(&arr[p_index], &arr[left]);
  int i = left;
  int j = right;

  while (i < j) {
    while (arr[i] <= arr[left] && i < right)
      i++;
    while (arr[j] > arr[left])
      j--;
    if (i < j)
      swap(&arr[i], &arr[j]);
  }

  swap(&arr[left], &arr[j]);
  return j;
}

int quickSelect(int *arr, int low, int high, int val_index) {
  if (low == high && low == val_index)
    return arr[low];

  if (low < high) {
    int p_index = pivot_location(arr, low, high, false);
    if (p_index == val_index)
      return arr[p_index];
    else if (p_index > val_index)
      return quickSelect(arr, low, p_index - 1, val_index);
    else
      return quickSelect(arr, p_index + 1, high, val_index);
  }

  return -1;
}

void quickSort(int *arr, int low, int high) {
  if (low < high) {
    int p_index = pivot_location(arr, low, high, true);

    quickSort(arr, low, p_index - 1);
    quickSort(arr, p_index + 1, high);
  }
}

void test(metric *m, int *arr, const char *method) {
  int *cpyArr = init(false);
  memCpy(cpyArr, arr);
  clock_t start, end;
  int mid1, mid2;
  if (!strcmp("Quick Select", method)) // Quick Select it is
  {
    start = clock();
    mid1 = quickSelect(cpyArr, 0, 110000 - 1, (110000 / 2) - 1);
    // One side is sorted.
    mid2 = quickSelect(cpyArr, 110000 / 2, 110000 - 1, 110000 / 2);
    m->median = (mid1 + mid2) * 0.5;
    end = clock();
    m->clk = (double)(end - start) / CLOCKS_PER_SEC;
  }

  else {
    start = clock();
    quickSort(cpyArr, 0, 110000 - 1);
    mid1 = cpyArr[110000 / 2 - 1];
    mid2 = cpyArr[110000 / 2];
    m->median = (mid1 + mid2) * 0.5;
    end = clock();
    m->clk = (double)(end - start) / CLOCKS_PER_SEC;
  }

  freeArr(cpyArr);
}

int main() {
  srand(time(NULL));
  metric m = {0, 0};
  int *arr = init(true);

  printf("Finding median using Quick Select: "
         "\n=======================================\n");
  test(&m, arr, "Quick Select");
  printf("\tMedian: %f\n\tRequired Time: %f\n", m.median, m.clk);

  printf("Finding median using Quick Sort: "
         "\n========================================\n");
  test(&m, arr, "Quick Sort");
  printf("\tMediam: %f\n\tRequired Time: %f\n", m.median, m.clk);

  return 0;
}
