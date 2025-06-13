#include <stdio.h>
#define N 100

int pq2D[N][2];  // [][0] = data, [][1] = priority
int size2D = 0;

void insert2D(int data, int priority) {
    int i = size2D++;
    while (i > 0 && pq2D[i - 1][1] < priority) {
        pq2D[i][0] = pq2D[i - 1][0];
        pq2D[i][1] = pq2D[i - 1][1];
        i--;
    }
    pq2D[i][0] = data;
    pq2D[i][1] = priority;
}

int remove2D() {
    if (size2D == 0) return -1;
    return pq2D[--size2D][0];
}

void display2D() {
    printf("Priority Queue (2D Array):\n");
    for (int i = 0; i < size2D; i++)
        printf("Data: %d, Priority: %d\n", pq2D[i][0], pq2D[i][1]);
}

int main() {
    insert2D(100, 1);
    insert2D(200, 3);
    insert2D(300, 2);
    insert2D(400, 4);

    display2D();
    printf("Removed: %d\n", remove2D());
    display2D();

    return 0;
}
