#include <stdio.h>
#include <stdlib.h> // Required for malloc, free, and NULL

// Node structure for doubly linked list
typedef struct DNode {
    int data;
    struct DNode *prev, *next;
} DNode;

// Deque structure
typedef struct {
    DNode *front, *rear;
} Deque;

// Initialize deque
void initDeque(Deque *dq) {
    dq->front = dq->rear = NULL;
}

// Insert at front
void insertFront(Deque *dq, int data) {
    DNode *node = (DNode *)malloc(sizeof(DNode));
    node->data = data;
    node->prev = NULL;
    node->next = dq->front;

    if (dq->front == NULL) {
        dq->rear = node;
    } else {
        dq->front->prev = node;
    }
    dq->front = node;
}

// Insert at rear
void insertRear(Deque *dq, int data) {
    DNode *node = (DNode *)malloc(sizeof(DNode));
    node->data = data;
    node->next = NULL;
    node->prev = dq->rear;

    if (dq->rear == NULL) {
        dq->front = node;
    } else {
        dq->rear->next = node;
    }
    dq->rear = node;
}

// Delete from front
int deleteFront(Deque *dq) {
    if (dq->front == NULL) {
        printf("Deque is empty!\n");
        return -1;
    }
    DNode *temp = dq->front;
    int data = temp->data;
    dq->front = temp->next;
    if (dq->front != NULL) {
        dq->front->prev = NULL;
    } else {
        dq->rear = NULL;
    }
    free(temp);
    return data;
}

// Delete from rear
int deleteRear(Deque *dq) {
    if (dq->rear == NULL) {
        printf("Deque is empty!\n");
        return -1;
    }
    DNode *temp = dq->rear;
    int data = temp->data;
    dq->rear = temp->prev;
    if (dq->rear != NULL) {
        dq->rear->next = NULL;
    } else {
        dq->front = NULL;
    }
    free(temp);
    return data;
}

// Display deque from front to rear
void displayDeque(Deque dq) {
    DNode *temp = dq.front;
    printf("Deque: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main to test
int main() {
    Deque dq;
    initDeque(&dq);

    insertFront(&dq, 10);
    insertFront(&dq, 20);
    insertRear(&dq, 30);
    insertRear(&dq, 40);

    displayDeque(dq);

    printf("Deleted from front: %d\n", deleteFront(&dq));
    printf("Deleted from rear: %d\n", deleteRear(&dq));

    displayDeque(dq);

    return 0;
}
