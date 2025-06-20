#include <stdio.h>

int linearSearchIterative(int arr[], int n, int key) {
    for (int i = 0; i < n; i++)
        if (arr[i] == key) return i;
    return -1;
}

int linearSearchRecursive(int arr[], int n, int key, int index) {
    if (index >= n) return -1;
    if (arr[index] == key) return index;
    return linearSearchRecursive(arr, n, key, index + 1);
}

int binarySearchIterative(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int binarySearchRecursive(int arr[], int low, int high, int key) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (arr[mid] == key) return mid;
    else if (arr[mid] < key) return binarySearchRecursive(arr, mid + 1, high, key);
    else return binarySearchRecursive(arr, low, mid - 1, key);
}

void inputArray(int arr[], int *n) {
    printf("Enter number of elements: ");
    scanf("%d", n);
    printf("Enter %d elements:\n", *n);
    for (int i = 0; i < *n; i++)
        scanf("%d", &arr[i]);
}

int main() {
    int arr[100], n, key, result, choice;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Iterative Linear Search\n");
        printf("2. Recursive Linear Search\n");
        printf("3. Iterative Binary Search\n");
        printf("4. Recursive Binary Search\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) break;

        inputArray(arr, &n);
        printf("Enter element to search: ");
        scanf("%d", &key);

        switch (choice) {
            case 1:
                result = linearSearchIterative(arr, n, key);
                break;
            case 2:
                result = linearSearchRecursive(arr, n, key, 0);
                break;
            case 3:
                printf("Note: Make sure the array is sorted!\n");
                result = binarySearchIterative(arr, n, key);
                break;
            case 4:
                printf("Note: Make sure the array is sorted!\n");
                result = binarySearchRecursive(arr, 0, n - 1, key);
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }

        if (result != -1)
            printf("Element found at index: %d\n", result);
        else
            printf("Element not found.\n");
    }

    return 0;
}
