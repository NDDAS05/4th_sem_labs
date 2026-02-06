#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *init(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);
    if (!arr) {
        printf("Memory allocation failed.\n");
        exit(1);
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
    for (int i = low; i <= high; i++) {
        if (arr[i] == pivot) {
            swap(&arr[i], &arr[low]);
            break;
        }
    }

    int i = low;
    int j = high;

    while (i < j) {
        while (arr[i] <= pivot && i < high) i++;
        while (arr[j] > pivot) j--;

        if (i < j)
            swap(&arr[i], &arr[j]);
    }

    swap(&arr[low], &arr[j]);
    return j;
}

int medianOfMedians(int *arr, int low, int high, int k) {
    if (low == high)
        return arr[low];

    int n = high - low + 1;
    int numGroups = (n + 4) / 5;
    int medians[numGroups];

    for (int i = 0; i < numGroups; i++) {
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


int main() {

    srand(time(NULL));

    FILE *fp = fopen("results.txt", "w");
    fprintf(fp, "# n QS_best QS_avg QS_worst MoM_best MoM_avg MoM_worst\n");

    int sizes[] = {20000, 50000, 80000, 120000, 200000};
                  //  300000, 500000};
    int tests = 5;

    for (int s = 0; s < tests; s++) {

        int n = sizes[s];
        int k = n / 2;


        int *qs_best = init(n);
        int *qs_avg = init(n);
        int *qs_worst = init(n);

        int *mom_best = init(n);
        int *mom_avg = init(n);
        int *mom_worst = init(n);

        for (int i = 0; i < n; i++) {
            qs_worst[i] = i;
            mom_worst[i] = i;
        }

        // Best Case (Median at Last)

        for (int i = 0; i < n; i++) {
            qs_best[i] = i;
            mom_best[i] = i;
        }

        swap(&qs_best[n/2], &qs_best[n-1]);
        swap(&mom_best[n/2], &mom_best[n-1]);

        // Average Case (Random) 

        for (int i = 0; i < n; i++) {
            int val = rand();
            qs_avg[i] = val;
            mom_avg[i] = val;
        }

        clock_t start, end;

        start = clock();
        quickSelect(qs_best, 0, n - 1, k);
        end = clock();
        double qs_best_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        quickSelect(qs_avg, 0, n - 1, k);
        end = clock();
        double qs_avg_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        quickSelect(qs_worst, 0, n - 1, k);
        end = clock();
        double qs_worst_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        medianOfMedians(mom_best, 0, n - 1, k);
        end = clock();
        double mom_best_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        medianOfMedians(mom_avg, 0, n - 1, k);
        end = clock();
        double mom_avg_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        medianOfMedians(mom_worst, 0, n - 1, k);
        end = clock();
        double mom_worst_time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("n=%d\n", n);
        printf("QS -> Best:%f Avg:%f Worst:%f\n",
               qs_best_time, qs_avg_time, qs_worst_time);
        printf("MoM-> Best:%f Avg:%f Worst:%f\n\n",
               mom_best_time, mom_avg_time, mom_worst_time);

        fprintf(fp, "%d %f %f %f %f %f %f\n",
                n,
                qs_best_time, qs_avg_time, qs_worst_time,
                mom_best_time, mom_avg_time, mom_worst_time);

        free(qs_best);
        free(qs_avg);
        free(qs_worst);
        free(mom_best);
        free(mom_avg);
        free(mom_worst);
    }

    fclose(fp);
    return 0;
}
