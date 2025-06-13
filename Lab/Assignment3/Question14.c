#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

// Define the queue structure
typedef struct {
    int items[SIZE];
    int front, rear;
} Queue;

// Initialize queue
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is empty
int isEmpty(Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

// Enqueue operation
void enqueue(Queue *q, int value) {
    if (q->rear == SIZE - 1) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

// Dequeue operation
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front++];
}

// Display the queue
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

// Function to replace every occurrence of e with x in queue p
void replace(Queue *q, int e, int x) {
    if (isEmpty(q)) {
        printf("Queue is empty, nothing to replace.\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++) {
        if (q->items[i] == e) {
            q->items[i] = x;
        }
    }
}

int main() {
    Queue q;
    initQueue(&q);

    // Sample input
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 20);
    enqueue(&q, 40);

    printf("Original Queue:\n");
    displayQueue(&q);

    int e = 20;
    int x = 99;
    printf("Replacing all occurrences of %d with %d...\n", e, x);
    replace(&q, e, x);

    printf("Queue after replacement:\n");
    displayQueue(&q);

    return 0;
}
