#define MAX 5

typedef struct {
    int items[MAX];
    int front, rear;
} CircularQueue;

void initCQ(CircularQueue *q) {
    q->front = q->rear = -1;
}

int isFull(CircularQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

int isEmpty(CircularQueue *q) {
    return q->front == -1;
}

void enqueueCQ(CircularQueue *q, int value) {
    if (isFull(q)) return;
    if (isEmpty(q)) q->front = 0;
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
}

int dequeueCQ(CircularQueue *q) {
    if (isEmpty(q)) return -1;
    int data = q->items[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front = (q->front + 1) % MAX;
    return data;
}
