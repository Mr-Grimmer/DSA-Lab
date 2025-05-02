#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(Node* head) {
    if (!head) {
        printf("List is empty.\n");
        return;
    }
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void insertFront(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

void insertAfterK(Node* head, int k, int data) {
    while (k-- && head) head = head->next;
    if (!head) {
        printf("Invalid position.\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = head->next;
    head->next = newNode;
}

void insertAfterValue(Node* head, int val, int data) {
    while (head && head->data != val) head = head->next;
    if (!head) {
        printf("Value not found.\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = head->next;
    head->next = newNode;
}

void insertBeforeK(Node** head, int k, int data) {
    if (k == 0 || !*head) {
        insertFront(head, data);
        return;
    }
    Node* temp = *head;
    for (int i = 1; i < k - 1 && temp; i++) temp = temp->next;
    if (!temp || !temp->next) {
        printf("Invalid position.\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = temp->next;
    temp->next = newNode;
}

void insertBeforeValue(Node** head, int val, int data) {
    if (!*head) return;
    if ((*head)->data == val) {
        insertFront(head, data);
        return;
    }
    Node* temp = *head;
    while (temp->next && temp->next->data != val)
        temp = temp->next;
    if (!temp->next) {
        printf("Value not found.\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteFirst(Node** head) {
    if (!*head) return;
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteLast(Node** head) {
    if (!*head) return;
    if (!(*head)->next) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* temp = *head;
    while (temp->next->next)
        temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}

void deleteAfterK(Node* head, int k) {
    while (k-- && head) head = head->next;
    if (!head || !head->next) {
        printf("Invalid position.\n");
        return;
    }
    Node* temp = head->next;
    head->next = temp->next;
    free(temp);
}

void deleteBeforeK(Node** head, int k) {
    if (k <= 1 || !*head || !(*head)->next) {
        printf("Invalid position.\n");
        return;
    }
    if (k == 2) {
        deleteFirst(head);
        return;
    }
    Node* temp = *head;
    for (int i = 1; i < k - 2 && temp->next; i++) temp = temp->next;
    if (!temp->next || !temp->next->next) {
        printf("Invalid position.\n");
        return;
    }
    Node* del = temp->next;
    temp->next = del->next;
    free(del);
}

void deleteK(Node** head, int k) {
    if (k == 0) {
        deleteFirst(head);
        return;
    }
    Node* temp = *head;
    for (int i = 1; i < k && temp; i++) temp = temp->next;
    if (!temp || !temp->next) {
        printf("Invalid position.\n");
        return;
    }
    Node* del = temp->next;
    temp->next = del->next;
    free(del);
}

void deleteByValue(Node** head, int val) {
    if (!*head) return;
    if ((*head)->data == val) {
        deleteFirst(head);
        return;
    }
    Node* temp = *head;
    while (temp->next && temp->next->data != val)
        temp = temp->next;
    if (!temp->next) {
        printf("Value not found.\n");
        return;
    }
    Node* del = temp->next;
    temp->next = del->next;
    free(del);
}

Node* reverse(Node* head) {
    Node* prev = NULL;
    while (head) {
        Node* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

void sortList(Node** head) {
    if (!*head || !(*head)->next) return;
    for (Node* i = *head; i && i->next; i = i->next) {
        for (Node* j = i->next; j; j = j->next) {
            if (i->data > j->data) {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

bool search(Node* head, int key) {
    while (head) {
        if (head->data == key) return true;
        head = head->next;
    }
    return false;
}

Node* mergeSorted(Node* a, Node* b) {
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;
    while (a && b) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = (a) ? a : b;
    return dummy.next;
}

Node* concatenate(Node* a, Node* b) {
    if (!a) return b;
    Node* temp = a;
    while (temp->next) temp = temp->next;
    temp->next = b;
    return a;
}

bool isEqual(Node* a, Node* b) {
    while (a && b) {
        if (a->data != b->data) return false;
        a = a->next;
        b = b->next;
    }
    return (a == NULL && b == NULL);
}

// Menu
int main() {
    Node *list1 = NULL, *list2 = NULL;
    int choice, data, k, val;

    while (1) {
        printf("\n1. Create list\n2. Print list\n3. Insert front\n4. Insert end\n5. Insert after k\n6. Insert after value\n");
        printf("7. Insert before k\n8. Insert before value\n9. Delete first\n10. Delete last\n11. Delete after k\n");
        printf("12. Delete before k\n13. Delete kth\n14. Delete by value\n15. Reverse\n16. Sort\n17. Search\n");
        printf("18. Merge two sorted lists\n19. Concatenate\n20. Are equal\n0. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list1 = NULL;
                printf("List created.\n");
                break;
            case 2:
                printList(list1);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                insertFront(&list1, data);
                break;
            case 4:
                printf("Enter data: ");
                scanf("%d", &data);
                insertEnd(&list1, data);
                break;
            case 5:
                printf("Enter k and data: ");
                scanf("%d%d", &k, &data);
                insertAfterK(list1, k, data);
                break;
            case 6:
                printf("Enter value and data: ");
                scanf("%d%d", &val, &data);
                insertAfterValue(list1, val, data);
                break;
            case 7:
                printf("Enter k and data: ");
                scanf("%d%d", &k, &data);
                insertBeforeK(&list1, k, data);
                break;
            case 8:
                printf("Enter value and data: ");
                scanf("%d%d", &val, &data);
                insertBeforeValue(&list1, val, data);
                break;
            case 9:
                deleteFirst(&list1);
                break;
            case 10:
                deleteLast(&list1);
                break;
            case 11:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteAfterK(list1, k);
                break;
            case 12:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteBeforeK(&list1, k);
                break;
            case 13:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteK(&list1, k);
                break;
            case 14:
                printf("Enter value: ");
                scanf("%d", &val);
                deleteByValue(&list1, val);
                break;
            case 15:
                list1 = reverse(list1);
                break;
            case 16:
                sortList(&list1);
                break;
            case 17:
                printf("Enter value: ");
                scanf("%d", &val);
                printf("%s\n", search(list1, val) ? "Found" : "Not Found");
                break;
            case 18:
                printf("Creating second list (sorted). Enter 5 elements:\n");
                list2 = NULL;
                for (int i = 0; i < 5; i++) {
                    scanf("%d", &data);
                    insertEnd(&list2, data);
                }
                list1 = mergeSorted(list1, list2);
                break;
            case 19:
                printf("Creating second list. Enter 5 elements:\n");
                list2 = NULL;
                for (int i = 0; i < 5; i++) {
                    scanf("%d", &data);
                    insertEnd(&list2, data);
                }
                list1 = concatenate(list1, list2);
                break;
            case 20:
                printf("Creating second list. Enter 5 elements:\n");
                list2 = NULL;
                for (int i = 0; i < 5; i++) {
                    scanf("%d", &data);
                    insertEnd(&list2, data);
                }
                printf("%s\n", isEqual(list1, list2) ? "Equal" : "Not Equal");
                break;
            case 0:
                exit(0);
        }
    }
    return 0;
}
