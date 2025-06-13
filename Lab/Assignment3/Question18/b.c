#include <stdio.h>
#include <stdlib.h>

typedef struct PNode {
    int data;
    struct PNode *next;
} PNode;

void insertPL(PNode **head, int data) {
    PNode *temp = malloc(sizeof(PNode));
    temp->data = data;
    temp->next = NULL;

    if (*head == NULL || data > (*head)->data) {
        temp->next = *head;
        *head = temp;
    } else {
        PNode *cur = *head;
        while (cur->next && cur->next->data >= data)
            cur = cur->next;
        temp->next = cur->next;
        cur->next = temp;
    }
}

int removePL(PNode **head) {
    if (*head == NULL) return -1;
    int data = (*head)->data;
    PNode *temp = *head;
    *head = (*head)->next;
    free(temp);
    return data;
}

void displayPL(PNode *head) {
    printf("Priority Queue (Linked List): ");
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    PNode *pq = NULL;

    insertPL(&pq, 40);
    insertPL(&pq, 10);
    insertPL(&pq, 60);
    insertPL(&pq, 30);

    displayPL(pq);
    printf("Removed: %d\n", removePL(&pq));
    displayPL(pq);

    return 0;
}
