#include <stdio.h>
#define SIZE 100

int x[SIZE], y[SIZE];
int fx = -1, rx = -1;
int fy = -1, ry = -1;

void enqueueX(int val) {
    if (rx == SIZE - 1) {
        printf("Queue X Overflow\n");
        return;
    }
    if (fx == -1) fx = 0;
    x[++rx] = val;
}

void enqueueY(int val) {
    if (ry == SIZE - 1) {
        printf("Queue Y Overflow\n");
        return;
    }
    if (fy == -1) fy = 0;
    y[++ry] = val;
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

void appendQueueXtoY() {
    if (fx == -1 || fx > rx) {
        printf("Queue X is empty, nothing to append.\n");
        return;
    }

    for (int i = fx; i <= rx; i++) {
        if (ry == SIZE - 1) {
            printf("Queue Y Overflow while appending\n");
            return;
        }
        if (fy == -1) fy = 0;
        y[++ry] = x[i];
    }
    printf("Queue X appended to Queue Y successfully.\n");
}

int main() {
    enqueueX(1);
    enqueueX(2);
    enqueueX(3);

    enqueueY(10);
    enqueueY(20);

    printf("Before appending:\n");
    displayQueue('X', x, fx, rx);
    displayQueue('Y', y, fy, ry);

    appendQueueXtoY();

    printf("After appending:\n");
    displayQueue('Y', y, fy, ry);

    return 0;
}
