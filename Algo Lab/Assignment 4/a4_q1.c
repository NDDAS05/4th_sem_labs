#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  double clk;
  float median;
} metric;

int *init(bool fill) {
  int *arr = (int *)malloc(sizeof(int) * 110000);

  if (!arr) {
    printf("Allocation failed.");
    return NULL;
  }

  if (fill) {
    int random_bias = (rand() % 41) - 20;

    for (int i = 0; i < 110000; i++) {
      int mark = rand() % 101;
      mark += random_bias;

      if (mark < 0) mark = 0;
      if (mark > 100) mark = 100;

      arr[i] = mark;
    }
  }

  return arr;
}

int *freeArr(int *arr) {
  if (arr) free(arr);
  return NULL;
}

void memCpy(int *destn, int *source) {
  if (destn && source)
    memcpy(destn, source, sizeof(int) * 110000);
  else
    printf("Invalid source or destination.\n");
}

int randPvt(int low, int high) {
  return low + rand() % (high - low + 1);
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int midPvt(int *arr, int low, int high) {
  int mid = low + (high - low) / 2;

  if ((arr[low] <= arr[mid] && arr[mid] <= arr[high]) ||
      (arr[high] <= arr[mid] && arr[mid] <= arr[low]))
    return mid;
  else if ((arr[mid] <= arr[low] && arr[low] <= arr[high]) ||
           (arr[high] <= arr[low] && arr[low] <= arr[mid]))
    return low;
  else
    return high;
}

int pivot_location(int *arr, int left, int right, bool useMedian3) {
  int p_index;

  if (!useMedian3)
    p_index = randPvt(left, right);      // Random pivot
  else
    p_index = midPvt(arr, left, right);  // Median-of-3 pivot

  swap(&arr[p_index], &arr[left]);

  int i = left;
  int j = right;

  while (i < j) {
    while (arr[i] <= arr[left] && i < right) i++;
    while (arr[j] > arr[left]) j--;

    if (i < j)
      swap(&arr[i], &arr[j]);
  }

  swap(&arr[left], &arr[j]);
  return j;
}

int quickSelect(int *arr, int low, int high, int val_index, bool useMedian3) {
  if (low == high)
    return arr[low];

  if (low < high) {
    int p_index = pivot_location(arr, low, high, useMedian3);

    if (p_index == val_index)
      return arr[p_index];
    else if (p_index > val_index)
      return quickSelect(arr, low, p_index - 1, val_index, useMedian3);
    else
      return quickSelect(arr, p_index + 1, high, val_index, useMedian3);
  }

  return -1;
}

void test(metric *m, int *arr, const char *method) {
  int *cpyArr = init(false);
  memCpy(cpyArr, arr);

  clock_t start, end;
  int mid1, mid2;

  if (!strcmp("Random Quick Select", method)) {
    start = clock();

    mid1 = quickSelect(cpyArr, 0, 110000 - 1, (110000 / 2) - 1, false);
    mid2 = quickSelect(cpyArr, 110000 / 2, 110000 - 1, 110000 / 2, false);

    m->median = (mid1 + mid2) * 0.5;

    end = clock();
  }
  else {
    start = clock();

    mid1 = quickSelect(cpyArr, 0, 110000 - 1, (110000 / 2) - 1, true);
    mid2 = quickSelect(cpyArr, 110000 / 2, 110000 - 1, 110000 / 2, true);

    m->median = (mid1 + mid2) * 0.5;

    end = clock();
  }

  m->clk = (double)(end - start) / CLOCKS_PER_SEC;

  freeArr(cpyArr);
}

int main() {
  srand(time(NULL));

  metric m = {0, 0};
  int *arr = init(true);

  printf("Finding median using Random Pivot Quick Select:\n");
  printf("===============================================\n");
  test(&m, arr, "Random Quick Select");
  printf("\tMedian: %f\n\tRequired Time: %f\n\n", m.median, m.clk);

  printf("Finding median using Median-of-3 Quick Select:\n");
  printf("==============================================\n");
  test(&m, arr, "Median3 Quick Select");
  printf("\tMedian: %f\n\tRequired Time: %f\n", m.median, m.clk);

  freeArr(arr);
  return 0;
}
