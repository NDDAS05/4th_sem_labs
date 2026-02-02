#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct min_max{
    int max;
    int min;
}min_max;

min_max naiveWay(int* arr, int size, long long *count)
{
    min_max result;
    int i;

    if(size==1){
        result.min=arr[0];
        result.max=arr[0];
        return result;
    }

    result.min=result.max=arr[0];
    for(i=1;i<size;i++)
    {   
        (*count)++;
        if(arr[i]>result.max) 
        {
            result.max=arr[i];
        }
        
        (*count)++;
        if(arr[i]<result.min) 
        {
            result.min=arr[i];
        }
    }

    return result;
}

min_max Div_N_Con(int* arr, int low, int high, long long *count)
{
    min_max result, left, right;
    int mid;

    if(low==high)
    {
        result.max=result.min=arr[low];
        return result;
    }

    if(high==low+1)
    {
        (*count)++;
        if(arr[low] > arr[high])
        {
            result.max=arr[low];
            result.min=arr[high];
        }
        else{
            result.max=arr[high];
            result.min=arr[low];
        }

        return result;
    }
    
    mid=low+(high-low)/2;

    left = Div_N_Con(arr, low, mid, count);
    right = Div_N_Con(arr, mid+1, high, count);

    (*count)++;
    if(left.min < right.min) result.min=left.min;
    else result.min=right.min;

    (*count)++;
    if(left.max > right.max) result.max=left.max;
    else result.max=right.max;

    return result;
}

int main()
{
    int sizes[]={100,1000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000};
    int num_tests= 12;

    long long naive_count=0;
    long long dNc_count=0;
    min_max result;

    FILE *fp =fopen("comparison_data.txt", "w");
    if(!fp)
    {
        printf("Error occured. \n");
        return 1;
    }

    printf("Running tests...\n");
    printf("Size\t\tNaive\t\tDivide And Conquer\n");

    srand(time(0));
    for(int i=0;i<num_tests;i++)
    {
        int n=sizes[i];
        int *arr=(int*)malloc(sizeof(int)* n);
        for(int j=0; j<n;j++)
        {
            arr[j]=rand();
        }
        
        naive_count=0;
        result=naiveWay(arr, n, &naive_count);
        
        dNc_count=0;
        result=Div_N_Con(arr, 0, n-1, &dNc_count);
        
        fprintf(fp, "%d %lld %lld\n", n, naive_count, dNc_count);
        printf("%d\t\t%lld\t\t%lld\n", n, naive_count, dNc_count);
        free(arr);
    }

    fclose(fp);
    printf("Data written to: comparison_data.txt\n");
    return 0;
}