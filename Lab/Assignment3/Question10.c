#include <stdio.h>
#define N 3
#define SIZE 10

int queues[N][SIZE];
int front[N], rear[N];

void init() {
    for (int i = 0; i < N; i++)
        front[i] = rear[i] = -1;
}

void enqueue(int q, int val) {
    if (rear[q] == SIZE - 1) {
        printf("Queue %d Overflow\n", q);
        return;
    }
    if (front[q] == -1) front[q] = 0;
    queues[q][++rear[q]] = val;
}

int dequeue(int q) {
    if (front[q] == -1 || front[q] > rear[q]) {
        printf("Queue %d Underflow\n", q);
        return -1;
    }
    return queues[q][front[q]++];
}

void display(int q) {
    if (front[q] == -1 || front[q] > rear[q]) {
        printf("Queue %d is empty\n", q);
        return;
    }
    for (int i = front[q]; i <= rear[q]; i++)
        printf("%d ", queues[q][i]);
    printf("\n");
}

int main() {
    init();
    enqueue(0, 10);
    enqueue(1, 20);
    enqueue(2, 30);
    display(0);
    display(1);
    display(2);
    return 0;
}
