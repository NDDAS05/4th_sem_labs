#include <stdio.h>
#include <stdlib.h>

int *init(int size) {
  int *arr = (int *)malloc(sizeof(int) * size);

  if (arr)
    return arr;
  else {
    printf("Allocation failed.\n");
    return NULL;
  }
}

void freeArr(int *arr) {
  free(arr);
  arr = NULL;
}

void merge(int *arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int *L = init(n1);
  int *R = init(n2);

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j])
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }

  while (i < n1)
    arr[k++] = L[i++];

  while (j < n2)
    arr[k++] = R[j++];

  freeArr(L);
  freeArr(R);
}

void mergeSort(int *arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

int main() {
  int k, n;

  printf("Enter number of sets (k): ");
  scanf("%d", &k);

  printf("Enter maximum elements per set (n): ");
  scanf("%d", &n);

  int *arr = init(k * n);
  int total = 0;

  for (int i = 0; i < k; i++) {
    int size;
    printf("\nEnter size of set %d: ", i + 1);
    scanf("%d", &size);

    printf("Enter elements of set %d:\n", i + 1);
    for (int j = 0; j < size; j++) {
      scanf("%d", &arr[total++]);
    }
  }

  mergeSort(arr, 0, total - 1);

  int *uni = init(total);
  int uSize = 0;

  uni[uSize++] = arr[0];
  for (int i = 1; i < total; i++) {
    if (arr[i] != arr[i - 1])
      uni[uSize++] = arr[i];
  }

  printf("\nUnion of all sets:\n");
  for (int i = 0; i < uSize; i++)
    printf("%d ", uni[i]);

  freeArr(arr);
  freeArr(uni);
  return 0;
}
