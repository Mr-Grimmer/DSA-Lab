#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void push(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

Node* createList(int n) {
    Node* head = NULL;
    int data;
    for (int i = 0; i < n; i++) {
        printf("Enter data: ");
        scanf("%d", &data);
        push(&head, data);
    }
    return head;
}

void printList(Node* head) {
    printf("Sorted list: ");
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void bubbleSortLinks(Node** head) {
    int swapped;
    Node **ptr;
    if (*head == NULL) return;
    do {
        swapped = 0;
        ptr = head;
        while ((*ptr)->next != NULL) {
            Node* a = *ptr;
            Node* b = a->next;
            if (a->data > b->data) {
                a->next = b->next;
                b->next = a;
                *ptr = b;
                swapped = 1;
            }
            ptr = &((*ptr)->next);
        }
    } while (swapped);
}

Node* insertionSortLinks(Node* head) {
    Node* sorted = NULL;
    while (head) {
        Node* curr = head;
        head = head->next;
        if (!sorted || curr->data < sorted->data) {
            curr->next = sorted;
            sorted = curr;
        } else {
            Node* temp = sorted;
            while (temp->next && temp->next->data < curr->data)
                temp = temp->next;
            curr->next = temp->next;
            temp->next = curr;
        }
    }
    return sorted;
}

Node* selectionSortLinks(Node* head) {
    Node* sorted = NULL;
    while (head) {
        Node **min = &head, *prev = NULL;
        for (Node **ptr = &head; (*ptr)->next; ptr = &((*ptr)->next))
            if ((*ptr)->next->data < (*min)->data)
                min = &((*ptr)->next);
        Node* temp = *min;
        *min = temp->next;
        temp->next = sorted;
        sorted = temp;
    }
    Node* rev = NULL;
    while (sorted) {
        Node* next = sorted->next;
        sorted->next = rev;
        rev = sorted;
        sorted = next;
    }
    return rev;
}

int main() {
    int n, choice;
    while (1) {
        printf("\n--- Linked List (Link) Sort Menu ---\n");
        printf("1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 4) break;

        printf("Enter number of nodes: ");
        scanf("%d", &n);
        Node* head = createList(n);

        switch (choice) {
            case 1: bubbleSortLinks(&head); break;
            case 2: head = insertionSortLinks(head); break;
            case 3: head = selectionSortLinks(head); break;
            default: printf("Invalid choice\n"); continue;
        }

        printList(head);
    }
    return 0;
}
