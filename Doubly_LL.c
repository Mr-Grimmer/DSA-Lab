#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node* head = NULL;

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void printList() {
    Node* temp = head;
    printf("List: ");
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void insertFront(int data) {
    Node* newNode = createNode(data);
    if (head) {
        newNode->next = head;
        head->prev = newNode;
    }
    head = newNode;
}

void insertEnd(int data) {
    Node* newNode = createNode(data);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

void insertAfterK(int k, int data) {
    Node* temp = head;
    for (int i = 1; temp && i < k; i++)
        temp = temp->next;
    if (!temp) return;
    Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next)
        temp->next->prev = newNode;
    temp->next = newNode;
}

void insertAfterValue(int value, int data) {
    Node* temp = head;
    while (temp && temp->data != value)
        temp = temp->next;
    if (!temp) return;
    Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next)
        temp->next->prev = newNode;
    temp->next = newNode;
}

void insertBeforeK(int k, int data) {
    if (k == 1) {
        insertFront(data);
        return;
    }
    Node* temp = head;
    for (int i = 1; temp && i < k; i++)
        temp = temp->next;
    if (!temp) return;
    Node* newNode = createNode(data);
    newNode->next = temp;
    newNode->prev = temp->prev;
    if (temp->prev)
        temp->prev->next = newNode;
    temp->prev = newNode;
    if (temp == head)
        head = newNode;
}

void insertBeforeValue(int value, int data) {
    Node* temp = head;
    while (temp && temp->data != value)
        temp = temp->next;
    if (!temp) return;
    if (temp == head) {
        insertFront(data);
        return;
    }
    Node* newNode = createNode(data);
    newNode->prev = temp->prev;
    newNode->next = temp;
    temp->prev->next = newNode;
    temp->prev = newNode;
}

void deleteFirst() {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    if (head)
        head->prev = NULL;
    free(temp);
}

void deleteLast() {
    if (!head) return;
    Node* temp = head;
    if (!temp->next) {
        free(temp);
        head = NULL;
        return;
    }
    while (temp->next)
        temp = temp->next;
    temp->prev->next = NULL;
    free(temp);
}

void deleteAfterK(int k) {
    Node* temp = head;
    for (int i = 1; temp && i < k; i++)
        temp = temp->next;
    if (!temp || !temp->next) return;
    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    if (toDelete->next)
        toDelete->next->prev = temp;
    free(toDelete);
}

void deleteBeforeK(int k) {
    if (k <= 1 || !head) return;
    Node* temp = head;
    for (int i = 1; temp && i < k; i++)
        temp = temp->next;
    if (!temp || !temp->prev) return;
    Node* toDelete = temp->prev;
    if (toDelete == head) {
        head = temp;
        head->prev = NULL;
    } else {
        toDelete->prev->next = temp;
        temp->prev = toDelete->prev;
    }
    free(toDelete);
}

void deleteKth(int k) {
    if (!head) return;
    Node* temp = head;
    for (int i = 1; temp && i < k; i++)
        temp = temp->next;
    if (!temp) return;
    if (temp == head)
        head = temp->next;
    if (temp->prev)
        temp->prev->next = temp->next;
    if (temp->next)
        temp->next->prev = temp->prev;
    free(temp);
}

void deleteByValue(int value) {
    Node* temp = head;
    while (temp && temp->data != value)
        temp = temp->next;
    if (!temp) return;
    if (temp == head)
        head = temp->next;
    if (temp->prev)
        temp->prev->next = temp->next;
    if (temp->next)
        temp->next->prev = temp->prev;
    free(temp);
}

void reverseList() {
    Node* temp = NULL;
    Node* current = head;
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp)
        head = temp->prev;
}

// Menu-driven program
int main() {
    int choice, data, k, value;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Insert at Front\n2. Insert at End\n3. Insert after Kth node\n4. Insert after value\n");
        printf("5. Insert before Kth node\n6. Insert before value\n7. Delete First\n8. Delete Last\n");
        printf("9. Delete after Kth node\n10. Delete before Kth node\n11. Delete Kth node\n12. Delete by value\n");
        printf("13. Print List\n14. Reverse List\n15. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: printf("Enter data: "); scanf("%d", &data); insertFront(data); break;
            case 2: printf("Enter data: "); scanf("%d", &data); insertEnd(data); break;
            case 3: printf("Enter position (k): "); scanf("%d", &k); printf("Enter data: "); scanf("%d", &data); insertAfterK(k, data); break;
            case 4: printf("Enter value to search: "); scanf("%d", &value); printf("Enter data to insert: "); scanf("%d", &data); insertAfterValue(value, data); break;
            case 5: printf("Enter position (k): "); scanf("%d", &k); printf("Enter data: "); scanf("%d", &data); insertBeforeK(k, data); break;
            case 6: printf("Enter value to search: "); scanf("%d", &value); printf("Enter data to insert: "); scanf("%d", &data); insertBeforeValue(value, data); break;
            case 7: deleteFirst(); break;
            case 8: deleteLast(); break;
            case 9: printf("Enter position (k): "); scanf("%d", &k); deleteAfterK(k); break;
            case 10: printf("Enter position (k): "); scanf("%d", &k); deleteBeforeK(k); break;
            case 11: printf("Enter position (k): "); scanf("%d", &k); deleteKth(k); break;
            case 12: printf("Enter value: "); scanf("%d", &value); deleteByValue(value); break;
            case 13: printList(); break;
            case 14: reverseList(); printf("List reversed.\n"); break;
            case 15: exit(0);
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}
