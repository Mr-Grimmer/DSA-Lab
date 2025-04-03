#include <stdio.h>

#define MAX_SIZE 100  

void create(int arr[], int *size) {
    printf("Enter number of elements: ");
    scanf("%d", size);
    printf("Enter elements: ");
    for (int i = 0; i < *size; i++) {
        scanf("%d", &arr[i]);
    }
}

void display(int arr[], int size) {
    if (size == 0) {
        printf("List is empty.\n");
        return;
    }
    printf("List elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int count(int size) {
    return size;
}

void reverse(int arr[], int size) {
    for (int i = 0, j = size - 1; i < j; i++, j--) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void index_of(int arr[], int size, int element) {
    int found = 0;
    printf("Indices of %d: ", element);
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            printf("%d ", i);
            found = 1;
        }
    }
    if (!found)
        printf("Not found");
    printf("\n");
}

void indexed_element(int arr[], int size, int index) {
    if (index >= 0 && index < size)
        printf("Element at index %d: %d\n", index, arr[index]);
    else
        printf("Invalid index.\n");
}

void insert(int arr[], int *size, int index, int element) {
    if (*size >= MAX_SIZE || index < 0 || index > *size) {
        printf("Invalid operation.\n");
        return;
    }
    for (int i = *size; i > index; i--)
        arr[i] = arr[i - 1];

    arr[index] = element;
    (*size)++;
}

void delete(int arr[], int *size, int index) {
    if (index < 0 || index >= *size) {
        printf("Invalid index.\n");
        return;
    }
    for (int i = index; i < *size - 1; i++)
        arr[i] = arr[i + 1];

    (*size)--;
}

void merge(int arr1[], int *size1, int arr2[], int size2) {
    if (*size1 + size2 > MAX_SIZE) {
        printf("Merge operation exceeds max size.\n");
        return;
    }
    for (int i = 0; i < size2; i++)
        arr1[*size1 + i] = arr2[i];

    *size1 += size2;
}

void split(int arr[], int *size, int index, int newArr[], int *newSize) {
    if (index < 0 || index >= *size) {
        printf("Invalid split index.\n");
        return;
    }

    *newSize = *size - index;
    for (int i = 0; i < *newSize; i++)
        newArr[i] = arr[index + i];

    *size = index;
}

void sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main() {
    int arr[MAX_SIZE], arr2[MAX_SIZE], size = 0, size2 = 0;
    int choice, element, index;

    do {
        printf("\nMenu:\n");
        printf("1. Create\n2. Display\n3. Count\n4. Reverse\n5. Index of element\n6. Indexed element\n");
        printf("7. Insert\n8. Delete\n9. Merge\n10. Split\n11. Sort\n0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create(arr, &size);
                break;
            case 2:
                display(arr, size);
                break;
            case 3:
                printf("Total elements: %d\n", count(size));
                break;
            case 4:
                reverse(arr, size);
                printf("List reversed.\n");
                break;
            case 5:
                printf("Enter element: ");
                scanf("%d", &element);
                index_of(arr, size, element);
                break;
            case 6:
                printf("Enter index: ");
                scanf("%d", &index);
                indexed_element(arr, size, index);
                break;
            case 7:
                printf("Enter index and element: ");
                scanf("%d %d", &index, &element);
                insert(arr, &size, index, element);
                break;
            case 8:
                printf("Enter index to delete: ");
                scanf("%d", &index);
                delete(arr, &size, index);
                break;
            case 9:
                printf("Enter number of elements to merge: ");
                scanf("%d", &size2);
                printf("Enter elements: ");
                for (int i = 0; i < size2; i++) {
                    scanf("%d", &arr2[i]);
                }
                merge(arr, &size, arr2, size2);
                printf("Lists merged.\n");
                break;
            case 10:
                printf("Enter split index: ");
                scanf("%d", &index);
                split(arr, &size, index, arr2, &size2);
                printf("List split successfully.\n");
                break;
            case 11:
                sort(arr, size);
                printf("List sorted.\n");
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
