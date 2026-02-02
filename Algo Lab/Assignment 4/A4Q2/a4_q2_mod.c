#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STD 120000

int *init(int n) {
  int *arr = (int *)malloc(sizeof(int) * n);
  if (!arr) {
    printf("Failed to allocate memory.");
    return NULL;
  }
  return arr;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partitionQS(int *arr, int low, int high) {
  int pivot = arr[high];
  int i = low;

  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      swap(&arr[i], &arr[j]);
      i++;
    }
  }

  swap(&arr[i], &arr[high]);
  return i;
}

int quickSelect(int *arr, int low, int high, int k) {
  if (low <= high) {
    int pivotIndex = partitionQS(arr, low, high);

    if (pivotIndex == k)
      return arr[pivotIndex];
    else if (pivotIndex > k)
      return quickSelect(arr, low, pivotIndex - 1, k);
    else
      return quickSelect(arr, pivotIndex + 1, high, k);
  }
  return -1;
}

void insertionSort(int *arr, int n) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

int partition(int *arr, int low, int high, int pivot) {
  int i = low;
  while (i <= high) {
    if (arr[i] == pivot)
      swap(&arr[i], &arr[low]);
    break;
  }

  i = low;
  int j = high;

  while (i < j) {
    while (arr[i] <= pivot && i < high)
      i++;
    while (arr[j] > pivot)
      j--;
    if (i < j)
      swap(&arr[i], &arr[j]);
  }
  swap(&arr[j], &arr[low]);
  return j;
}

int medianOfMedians(int *arr, int low, int high, int k) {
  if (low == high)
    return arr[low];

  int n = high - low + 1;
  int i;

  int numGroups = (n + 4) / 5;
  int medians[numGroups];

  for (i = 0; i < numGroups; i++) {
    int subLow = low + i * 5;
    int subHigh = subLow + 4;
    if (subHigh > high)
      subHigh = high;

    int size = subHigh - subLow + 1;

    insertionSort(&arr[subLow], size);
    medians[i] = arr[subLow + size / 2];
  }

  int medianPivot;
  if (numGroups == 1)
    medianPivot = medians[0];
  else
    medianPivot = medianOfMedians(medians, 0, numGroups - 1, numGroups / 2);

  int pivotIndex = partition(arr, low, high, medianPivot);

  int rank = pivotIndex - low;

  if (rank == k)
    return arr[pivotIndex];
  else if (rank > k)
    return medianOfMedians(arr, low, pivotIndex - 1, k);
  else
    return medianOfMedians(arr, pivotIndex + 1, high, k - rank - 1);
}

double findMedian(int arr[], int n) {
  if (n % 2 == 1)
    return medianOfMedians(arr, 0, n - 1, n / 2);
  else {
    int m1 = medianOfMedians(arr, 0, n - 1, n / 2 - 1);
    int m2 = medianOfMedians(arr, 0, n - 1, n / 2);
    return (m1 + m2) / 2.0;
  }
}

int main() {
  srand(time(NULL));
  FILE *fp = fopen("results.txt", "w");
  fprintf(fp, "# n QuickSelect MedianOfMedians\n");

  int sizes[] = {20000,  50000,  80000,  120000, 200000,
                 300000, 500000, 700000, 1000000};
  int tests = 9;

  for (int s = 0; s < tests; s++) {
    int n = sizes[s];

    int *arr1 = init(n);
    int *arr2 = init(n);

    for (int i = 0; i < n; i++)
      arr1[i] = (10000 + rand()) % 1000000;

    memcpy(arr2, arr1, n * sizeof(int));

    int k = n / 2;

    clock_t start = clock();
    quickSelect(arr1, 0, n - 1, k);
    clock_t end = clock();
    double time_qs = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    medianOfMedians(arr2, 0, n - 1, k);
    end = clock();
    double time_mom = (double)(end - start) / CLOCKS_PER_SEC;

    printf("n=%d  QS=%f  MoM=%f\n", n, time_qs, time_mom);
    fprintf(fp, "%d %f %f\n", n, time_qs, time_mom);

    free(arr1);
    free(arr2);
  }

  fclose(fp);
  return 0;
}
