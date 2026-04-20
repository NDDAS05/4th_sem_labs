#include <stdio.h>
#include <stdlib.h>

int *init(int size) {
  int *arr = (int *)malloc(sizeof(int) * size);
  if (arr)
    return arr;
  else {
    printf("Error occured.\n");
    return NULL;
  }
}
int *freeArr(int *arr) {
  if (arr == NULL)
    return NULL;

  free(arr);
  return NULL;
}

void merge(int *arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int L[n1], R[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];

  for (int i = 0; i < n2; i++)
    R[i] = arr[mid + 1 + i];

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
}

void mergeSort(int *arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

int isDuplicate(int *arr, int size, int value) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == value) {
      return 1;
    }
  }
  return 0;
}

int isSubset(int *A, int sizeA, int *B, int sizeB) {
  int i = 0, j = 0;
  while (i < sizeA && j < sizeB) {
    if (A[i] == B[j]) {
      i++;
      j++;
    }

    else if (A[i] > B[j]) {
      j++;
    }

    else
      return 0;
  }

  return (i == sizeA);
}

int main() {
  int sizeA, sizeB;

  printf("Enter number of elements of set A: ");
  scanf("%d", &sizeA);

  printf("Enter number of elements in set B: ");
  scanf("%d", &sizeB);

  int *A = init(sizeA);
  int *B = init(sizeB);

  printf("Enter elements of set A: ");
  for (int i = 0; i < sizeA; i++) {

    int x;
    scanf("%d", &x);

    if (isDuplicate(A, i, x)) {
      printf("Already exists. Enter different value.\n");
      i--;
    } else
      A[i] = x;
  }

  printf("Enter elements of set B: ");
  for (int i = 0; i < sizeB; i++) {

    int x;
    scanf("%d", &x);

    if (isDuplicate(B, i, x)) {
      printf("Already exists. Enter different value.\n");
      i--;
    } else
      B[i] = x;
  }

  mergeSort(A, 0, sizeA - 1);
  mergeSort(B, 0, sizeB - 1);

  if (isSubset(A, sizeA, B, sizeB)) {
    printf("\nSet A is a subset of set B.");

    if (sizeA < sizeB)
      printf("Set A is a proper subset of set B.\n");
    else
      printf("Set A is not proper subset of set B.\n");

  } else
    printf("\nSet A is not a subset of set B.\n");

  freeArr(A);
  freeArr(B);
  return 0;
}
