#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front, *rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue *q, int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(Queue *q) {
    if (q->front == NULL) return -1;
    Node *temp = q->front;
    int val = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return val;
}

void display(Queue q) {
    Node *cur = q.front;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);
    int choice, value;
    while (1) {
        printf("1.Enqueue 2.Dequeue 3.Display 4.Exit\n");
        scanf("%d", &choice);
        if (choice == 1) {
            scanf("%d", &value);
            enqueue(&q, value);
        } else if (choice == 2) {
            int val = dequeue(&q);
            if (val == -1) printf("Queue is empty\n");
            else printf("Dequeued: %d\n", val);
        } else if (choice == 3) {
            display(q);
        } else {
            break;
        }
    }
    return 0;
}