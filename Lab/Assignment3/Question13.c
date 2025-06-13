#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
    int items[SIZE];
    int front, rear;
} Queue;

void enqueue(Queue *q, int value) {
    if (q->rear == SIZE - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(Queue *q) {
    if (q->front == -1 || q->front > q->rear) return -1;
    return q->items[q->front++];
}

void reverse(Queue *q) {
    if (q->front > q->rear) return;
    int x = dequeue(q);
    reverse(q);
    q->items[++q->rear] = x;
}

void display(Queue q) {
    for (int i = q.front; i <= q.rear; i++) printf("%d ", q.items[i]);
    printf("\n");
}

int main() {
    Queue q = {.front = -1, .rear = -1};
    enqueue(&q, 1); enqueue(&q, 2); enqueue(&q, 3);
    reverse(&q);
    display(q);
}
