#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_array(int *arr, int size);
void print_array(int *arr, int size);

int *init(int size) {
  int *arr = (int *)malloc(sizeof(int) * size);
  if (arr)
    return arr;
  else
    exit(1);
}

int *freeArr(int *arr) {
  if (!arr) {
    free(arr);
    return NULL;
  }

  return arr;
}

void fill_array(int *arr, int size) {
  int rnd_int;
  for (int i = 0; i < size; i++) {
    rnd_int = rand() % 100 + 1;
    arr[i] = rnd_int;
  }

  print_array(arr, size);
}

void print_array(int *arr, int size) {
  if (arr) {
    for (int i = 0; i < size; i++)
      printf("%d ", arr[i]);
  }
  printf("\n");
}

void largest4_smallest3(int *arr, int size) {

  fill_array(arr, size);
  int l1 = -1, l2 = -1, l3 = -1, l4 = -1, s1 = 101, s2 = 101, s3 = 101;
  for (int i = 0; i < size; i++) {
    if (arr[i] >= l1) {
      l4 = l3;
      l3 = l2;
      l2 = l1;
      l1 = arr[i];
    }

    else if (arr[i] >= l2) {
      l4 = l3;
      l3 = l2;
      l2 = arr[i];
    }

    else if (arr[i] >= l3) {
      l4 = l3;
      l3 = arr[i];
    }

    else if (arr[i] >= l4) {
      l4 = arr[i];
    }

    if (arr[i] <= s1) {
      s3 = s2;
      s2 = s1;
      s1 = arr[i];
    }

    else if (arr[i] <= s2) {
      s3 = s2;
      s2 = arr[i];
    }

    else if (arr[i] <= s3) {

      s3 = arr[i];
    }
  }

  printf("\n4th largest: %d\n3rd Smallest: %d\n", l4, s3);
}

int main() {
  srand(time(NULL));
  int size;
  printf("Enter size of array: ");
  scanf("%d", &size);

  while (size < 10) {
    printf("Array size must be >= 10.\nEnter size of array: ");
    scanf("%d", &size);
  }

  int *arr = init(size);

  largest4_smallest3(arr, size);
  return 0;
}
