#include <stdio.h>

void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] < pivot)
            swap(&arr[++i], &arr[j]);
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] < R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void printArray(int arr[], int n) {
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[100], n, choice;
    while (1) {
        printf("\n--- Recursive Array Sort Menu ---\n");
        printf("1. Quick Sort\n2. Merge Sort\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 3) break;

        printf("Enter number of elements: ");
        scanf("%d", &n);
        printf("Enter %d elements:\n", n);
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

        switch (choice) {
            case 1: quickSort(arr, 0, n - 1); break;
            case 2: mergeSort(arr, 0, n - 1); break;
            default: printf("Invalid choice\n"); continue;
        }

        printArray(arr, n);
    }
    return 0;
}
