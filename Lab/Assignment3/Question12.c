#include <stdio.h>

#define SIZE 100

int q1[SIZE], q2[SIZE];
int f1 = -1, r1 = -1;
int f2 = -1, r2 = -1;

void enqueue1(int val) {
    if (r1 == SIZE - 1) {
        printf("Queue 1 Overflow\n");
        return;
    }
    if (f1 == -1) f1 = 0;
    q1[++r1] = val;
}

void enqueue2(int val) {
    if (r2 == SIZE - 1) {
        printf("Queue 2 Overflow\n");
        return;
    }
    if (f2 == -1) f2 = 0;
    q2[++r2] = val;
}

int areQueuesEqual() {
    if ((r1 - f1) != (r2 - f2)) return 0;
    for (int i = 0; f1 + i <= r1 && f2 + i <= r2; i++) {
        if (q1[f1 + i] != q2[f2 + i]) return 0;
    }
    return 1;
}

void displayQueue(char name, int* q, int f, int r) {
    if (f == -1 || f > r) {
        printf("Queue %c is empty\n", name);
        return;
    }
    printf("Queue %c: ", name);
    for (int i = f; i <= r; i++)
        printf("%d ", q[i]);
    printf("\n");
}

int main() {
    enqueue1(5); enqueue1(10); enqueue1(15);
    enqueue2(5); enqueue2(10); enqueue2(15);

    displayQueue('1', q1, f1, r1);
    displayQueue('2', q2, f2, r2);

    if (areQueuesEqual())
        printf("Queues are equal\n");
    else
        printf("Queues are not equal\n");

    return 0;
}
