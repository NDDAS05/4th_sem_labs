#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int* init(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    return arr;
}

int* freeArr(int* arr) {
    if (arr != NULL) {
        free(arr);
        arr = NULL;
    }
    return arr;
}


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void insertionSort(int* arr, int n) {
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


double findMed(int *A, int n, int *B, int m) {

    if (n > m)
        return findMed(B, m, A, n);

    int low = 0, high = n;
    int total = n + m;
    int half = (total + 1) / 2;

    while (low <= high) {

        int i = (low + high) / 2;
        int j = half - i;

        int Aleft  = (i == 0) ? INT_MIN : A[i - 1];
        int Aright = (i == n) ? INT_MAX : A[i];

        int Bleft  = (j == 0) ? INT_MIN : B[j - 1];
        int Bright = (j == m) ? INT_MAX : B[j];

        if (Aleft <= Bright && Bleft <= Aright) {

            if (total % 2 == 0) {
                int leftMax  = (Aleft > Bleft) ? Aleft : Bleft;
                int rightMin = (Aright < Bright) ? Aright : Bright;
                return (leftMax + rightMin) / 2.0;
            } else {
                return (Aleft > Bleft) ? Aleft : Bleft;
            }
        }
        else if (Aleft > Bright)
            high = i - 1;
        else
            low = i + 1;
    }

    return -1;
}

int main() {

    int n, m;

    printf("Enter size of first array: ");
    scanf("%d", &n);

    printf("Enter size of second array: ");
    scanf("%d", &m);

    int* A = init(n);
    int* B = init(m);

    printf("Enter elements of first array:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Enter elements of second array:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &B[i]);

    /* Sort both arrays */
    insertionSort(A, n);
    insertionSort(B, m);

    double median = findMed(A, n, B, m);

    printf("Median of combined arrays = %.2f\n", median);

    A = freeArr(A);
    B = freeArr(B);

    return 0;
}
