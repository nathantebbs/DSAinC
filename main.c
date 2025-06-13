#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(int arr[], int size) {
    if (arr == NULL || size <= 1) return;
    for (size_t i = 1; i < size; i++) {
        for (size_t j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            swap(&arr[j - 1], &arr[j]);
        }
    }
}

void printArr(int arr[], int size) {
    if (arr == NULL || size <= 1) return;

    printf("Arr:");
    for (int i = 0; i < size; i++) {
        printf(" %d", arr[i]);
    }

    printf("\n");
}

int main() {
    // Default starting data
    int inputArray[] = {4, 5, 10, 9, 23, 1, 65, 8};
    int size = sizeof(inputArray) / sizeof(int);


    printArr(inputArray, size);
    printf("Input Size: %d\n", size);

    insertionSort(inputArray, size);

    printf("AFTER INSERTION SORT:\n");
    printArr(inputArray, size);
}
