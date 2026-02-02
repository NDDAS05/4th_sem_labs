#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STD 120000

int *init() {
  int *arr = (int *)malloc(sizeof(int) * STD);
  if (!arr) {
    printf("Failed to allocate memory.");
    return NULL;
  }
  return arr;
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
      j++;
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

  int numGroups = (n + 4) / 5; // groups of 5
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
  int *income = init();
  for (int i = 0; i < STD; i++)
    income[i] = (10000 + rand()) % 1000000; // example data

  double median = findMedian(income, STD);

  printf("Median Household Income = %.2lf\n", median);

  free(income);
  return 0;
}
