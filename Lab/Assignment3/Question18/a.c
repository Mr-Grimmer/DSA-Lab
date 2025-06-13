#include <stdio.h>
#define MAX 100

typedef struct {
    int items[MAX];
    int size;
} PriorityArray;

void insertPA(PriorityArray *pq, int value) {
    int i = pq->size++;
    while (i > 0 && pq->items[i - 1] < value) {
        pq->items[i] = pq->items[i - 1];
        i--;
    }
    pq->items[i] = value;
}

int removePA(PriorityArray *pq) {
    if (pq->size == 0) return -1;
    return pq->items[--pq->size];
}

void displayPA(PriorityArray pq) {
    printf("Priority Queue (Array): ");
    for (int i = 0; i < pq.size; i++)
        printf("%d ", pq.items[i]);
    printf("\n");
}

int main() {
    PriorityArray pq = {.size = 0};
    insertPA(&pq, 30);
    insertPA(&pq, 10);
    insertPA(&pq, 50);
    insertPA(&pq, 20);

    displayPA(pq);

    printf("Removed: %d\n", removePA(&pq));
    displayPA(pq);

    return 0;
}
