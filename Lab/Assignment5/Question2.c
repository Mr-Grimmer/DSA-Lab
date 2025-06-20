#include <stdio.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key)
            arr[j + 1] = arr[j--];
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min]) min = j;
        int tmp = arr[i];
        arr[i] = arr[min];
        arr[min] = tmp;
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
        printf("\n--- Sorting Menu ---\n");
        printf("1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        printf("Enter number of elements: ");
        scanf("%d", &n);
        printf("Enter %d elements:\n", n);
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

        switch (choice) {
            case 1: bubbleSort(arr, n); break;
            case 2: insertionSort(arr, n); break;
            case 3: selectionSort(arr, n); break;
            default: printf("Invalid choice\n"); continue;
        }

        printArray(arr, n);
    }
    return 0;
}
