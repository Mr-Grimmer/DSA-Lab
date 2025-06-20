#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createList(int n) {
    Node *head = NULL, *temp = NULL, *newNode;
    for (int i = 0; i < n; i++) {
        newNode = (Node*)malloc(sizeof(Node));
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &newNode->data);
        newNode->next = NULL;
        if (!head) head = newNode;
        else temp->next = newNode;
        temp = newNode;
    }
    return head;
}

void printList(Node* head) {
    printf("Sorted List: ");
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void bubbleSort(Node* head) {
    if (!head) return;
    for (Node* i = head; i->next; i = i->next)
        for (Node* j = head; j->next; j = j->next)
            if (j->data > j->next->data) {
                int tmp = j->data;
                j->data = j->next->data;
                j->next->data = tmp;
            }
}

void insertionSort(Node* head) {
    for (Node* i = head->next; i; i = i->next) {
        for (Node* j = head; j != i; j = j->next) {
            if (j->data > i->data) {
                int tmp = j->data;
                j->data = i->data;
                i->data = tmp;
            }
        }
    }
}

void selectionSort(Node* head) {
    for (Node* i = head; i; i = i->next) {
        Node* min = i;
        for (Node* j = i->next; j; j = j->next)
            if (j->data < min->data) min = j;
        int tmp = i->data;
        i->data = min->data;
        min->data = tmp;
    }
}

int main() {
    int n, choice;
    while (1) {
        printf("\n--- Linked List (Data) Sort Menu ---\n");
        printf("1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 4) break;

        printf("Enter number of nodes: ");
        scanf("%d", &n);
        Node* head = createList(n);

        switch (choice) {
            case 1: bubbleSort(head); break;
            case 2: insertionSort(head); break;
            case 3: selectionSort(head); break;
            default: printf("Invalid choice\n"); continue;
        }

        printList(head);
    }
    return 0;
}
