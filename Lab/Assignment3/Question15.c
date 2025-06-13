#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front, *rear;
} QueueLL;

void enqueueLL(QueueLL *q, int data) {
    Node *temp = malloc(sizeof(Node));
    temp->data = data; temp->next = NULL;
    if (!q->rear) q->front = q->rear = temp;
    else q->rear->next = temp, q->rear = temp;
}

int dequeueLL(QueueLL *q) {
    if (!q->front) return -1;
    Node *temp = q->front;
    int data = temp->data;
    q->front = temp->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return data;
}

void displayLL(QueueLL q) {
    Node *cur = q.front;
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}
