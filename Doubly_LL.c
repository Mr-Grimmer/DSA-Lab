#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void printList(Node* head) {
    if (!head) {
        printf("List is empty.\n");
        return;
    }
    while (head) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void insertFront(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head)
        (*head)->prev = newNode;
    *head = newNode;
}

void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

void insertAfterK(Node* head, int k, int data) {
    while (k-- && head) head = head->next;
    if (!head) {
        printf("Invalid position.\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = head->next;
    newNode->prev = head;
    if (head->next)
        head->next->prev = newNode;
    head->next = newNode;
}

void insertAfterValue(Node* head, int val, int data) {
    while (head && head->data != val) head = head->next;
    if (!head) {
        printf("Value not found.\n");
        return;
    }
    insertAfterK(head, 0, data);
}

void insertBeforeK(Node** head, int k, int data) {
    if (k == 0 || !*head) {
        insertFront(head, data);
        return;
    }
    Node* temp = *head;
    for (int i = 0; i < k && temp; i++) temp = temp->next;
    if (!temp) {
        printf("Invalid position.\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = temp;
    newNode->prev = temp->prev;
    if (temp->prev)
        temp->prev->next = newNode;
    else
        *head = newNode;
    temp->prev = newNode;
}

void insertBeforeValue(Node** head, int val, int data) {
    Node* temp = *head;
    while (temp && temp->data != val) temp = temp->next;
    if (!temp) {
        printf("Value not found.\n");
        return;
    }
    insertBeforeK(head, 0, data); // handle edge case
    if (temp == *head)
        insertFront(head, data);
    else
        insertBeforeK(head, 0, data);
}

void deleteFirst(Node** head) {
    if (!*head) return;
    Node* temp = *head;
    *head = temp->next;
    if (*head)
        (*head)->prev = NULL;
    free(temp);
}

void deleteLast(Node** head) {
    if (!*head) return;
    Node* temp = *head;
    while (temp->next) temp = temp->next;
    if (temp->prev)
        temp->prev->next = NULL;
    else
        *head = NULL;
    free(temp);
}

void deleteAfterK(Node* head, int k) {
    while (k-- && head) head = head->next;
    if (!head || !head->next) {
        printf("Invalid position.\n");
        return;
    }
    Node* del = head->next;
    head->next = del->next;
    if (del->next)
        del->next->prev = head;
    free(del);
}

void deleteBeforeK(Node** head, int k) {
    if (k <= 1 || !*head) {
        printf("Invalid position.\n");
        return;
    }
    Node* temp = *head;
    for (int i = 1; i < k - 1 && temp; i++) temp = temp->next;
    if (!temp) {
        printf("Invalid position.\n");
        return;
    }
    if (temp == *head)
        deleteFirst(head);
    else {
        temp->prev->next = temp->next;
        if (temp->next)
            temp->next->prev = temp->prev;
        free(temp);
    }
}

void deleteK(Node** head, int k) {
    if (!*head) return;
    Node* temp = *head;
    for (int i = 0; i < k && temp; i++) temp = temp->next;
    if (!temp) {
        printf("Invalid position.\n");
        return;
    }
    if (temp->prev)
        temp->prev->next = temp->next;
    else
        *head = temp->next;
    if (temp->next)
        temp->next->prev = temp->prev;
    free(temp);
}

void deleteByValue(Node** head, int val) {
    Node* temp = *head;
    while (temp && temp->data != val) temp = temp->next;
    if (!temp) {
        printf("Value not found.\n");
        return;
    }
    if (temp->prev)
        temp->prev->next = temp->next;
    else
        *head = temp->next;
    if (temp->next)
        temp->next->prev = temp->prev;
    free(temp);
}

void reverseList(Node** head) {
    Node* temp = NULL;
    Node* current = *head;
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp)
        *head = temp->prev;
}

int main() {
    Node* head = NULL;
    int choice, data, k, val;

    while (1) {
        printf("\n1. Create list\n2. Print list\n3. Insert front\n4. Insert end\n5. Insert after k\n6. Insert after value\n");
        printf("7. Insert before k\n8. Insert before value\n9. Delete first\n10. Delete last\n11. Delete after k\n");
        printf("12. Delete before k\n13. Delete kth\n14. Delete by value\n15. Reverse list\n0. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                head = NULL;
                printf("List created.\n");
                break;
            case 2:
                printList(head);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                insertFront(&head, data);
                break;
            case 4:
                printf("Enter data: ");
                scanf("%d", &data);
                insertEnd(&head, data);
                break;
            case 5:
                printf("Enter k and data: ");
                scanf("%d%d", &k, &data);
                insertAfterK(head, k, data);
                break;
            case 6:
                printf("Enter value and data: ");
                scanf("%d%d", &val, &data);
                insertAfterValue(head, val, data);
                break;
            case 7:
                printf("Enter k and data: ");
                scanf("%d%d", &k, &data);
                insertBeforeK(&head, k, data);
                break;
            case 8:
                printf("Enter value and data: ");
                scanf("%d%d", &val, &data);
                insertBeforeValue(&head, val, data);
                break;
            case 9:
                deleteFirst(&head);
                break;
            case 10:
                deleteLast(&head);
                break;
            case 11:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteAfterK(head, k);
                break;
            case 12:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteBeforeK(&head, k);
                break;
            case 13:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteK(&head, k);
                break;
            case 14:
                printf("Enter value: ");
                scanf("%d", &val);
                deleteByValue(&head, val);
                break;
            case 15:
                reverseList(&head);
                break;
            case 0:
                exit(0);
        }
    }
    return 0;
}
