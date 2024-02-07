#include <stdio.h>
#include <stdlib.h>

// Define a function pointer type for comparison function
typedef int (*CompareFunc)(const void*, const void*);

// Function to merge two subarrays of arr[]
void merge(void* arr, int l, int m, int r, size_t size, CompareFunc compare) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    void* L = malloc(n1 * size);
    void* R = malloc(n2 * size);

    // Copy data to temporary arrays L[] and R[]
    char* arrChars = (char*)arr;
    for (int i = 0; i < n1; i++)
        memcpy(L + i * size, arrChars + (l + i) * size, size);
    for (int j = 0; j < n2; j++)
        memcpy(R + j * size, arrChars + (m + 1 + j) * size, size);

    // Merge the temporary arrays back into arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (compare(L + i * size, R + j * size) <= 0) {
            memcpy(arrChars + k * size, L + i * size, size);
            i++;
        } else {
            memcpy(arrChars + k * size, R + j * size, size);
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        memcpy(arrChars + k * size, L + i * size, size);
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        memcpy(arrChars + k * size, R + j * size, size);
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Function to perform merge sort on arr[l..r]
void mergeSort(void* arr, int l, int r, size_t size, CompareFunc compare) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, size, compare);
        mergeSort(arr, m + 1, r, size, compare);
        merge(arr, l, m, r, size, compare);
    }
}

// Function to perform binary search on a sorted array
int binarySearch(const void* arr, int l, int r, size_t size, const void* x, CompareFunc compare) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int cmp = compare(arr + mid * size, x);
        if (cmp == 0)
            return mid;
        (cmp < 0) ? (l = mid + 1) : (r = mid - 1);
    }
    return -1;
}

// Comparison function for integers
int compareInt(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Comparison function for doubles
int compareDouble(const void* a, const void* b) {
    double diff = *(double*)a - *(double*)b;
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}

// Function to print an array of integers
void printIntArray(const int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Function to print an array of doubles
void printDoubleArray(const double arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%.2lf ", arr[i]);
    printf("\n");
}

int main() {
    int intArr[] = {12, 11, 13, 5, 6, 7};
    int intArrSize = sizeof(intArr) / sizeof(intArr[0]);

    double doubleArr[] = {12.5, 11.2, 13.7, 5.1, 6.8, 7.3};
    int doubleArrSize = sizeof(doubleArr) / sizeof(doubleArr[0]);

    printf("Given integer array is: ");
    printIntArray(intArr, intArrSize);
    mergeSort(intArr, 0, intArrSize - 1, sizeof(int), compareInt);
    printf("Sorted integer array is: ");
    printIntArray(intArr, intArrSize);

    printf("Given double array is: ");
    printDoubleArray(doubleArr, doubleArrSize);
    mergeSort(doubleArr, 0, doubleArrSize - 1, sizeof(double), compareDouble);
    printf("Sorted double array is: ");
    printDoubleArray(doubleArr, doubleArrSize);

    // Binary search option
    int intSearchKey;
    printf("Enter the integer element to search: ");
    scanf("%d", &intSearchKey);
    int intResult = binarySearch(intArr, 0, intArrSize - 1, sizeof(int), &intSearchKey, compareInt);
    printf("Integer element %d is %s\n", intSearchKey, (intResult == -1) ? "not present" : "present");

    double doubleSearchKey;
    printf("Enter the double element to search: ");
    scanf("%lf", &doubleSearchKey);
    int doubleResult = binarySearch(doubleArr, 0, doubleArrSize - 1, sizeof(double), &doubleSearchKey, compareDouble);
    printf("Double element %.2lf is %s\n", doubleSearchKey, (doubleResult == -1) ? "not present" : "present");

    return 0;
}