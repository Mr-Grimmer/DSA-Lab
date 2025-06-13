#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIORITIES 5

typedef struct MNode {
    int data;
    struct MNode *next;
} MNode;

MNode *multiPQ[MAX_PRIORITIES] = {NULL};

void insertMulti(int data, int priority) {
    if (priority < 0 || priority >= MAX_PRIORITIES) {
        printf("Invalid priority\n");
        return;
    }

    MNode *temp = malloc(sizeof(MNode));
    temp->data = data;
    temp->next = NULL;

    if (!multiPQ[priority]) {
        multiPQ[priority] = temp;
    } else {
        MNode *cur = multiPQ[priority];
        while (cur->next) cur = cur->next;
        cur->next = temp;
    }
}

int removeMulti() {
    for (int i = MAX_PRIORITIES - 1; i >= 0; i--) {
        if (multiPQ[i]) {
            MNode *temp = multiPQ[i];
            int data = temp->data;
            multiPQ[i] = temp->next;
            free(temp);
            return data;
        }
    }
    return -1; // All queues empty
}

void displayMulti() {
    printf("Priority Queue (Multiple Linked Lists):\n");
    for (int i = MAX_PRIORITIES - 1; i >= 0; i--) {
        printf("Priority %d: ", i);
        MNode *cur = multiPQ[i];
        while (cur) {
            printf("%d ", cur->data);
            cur = cur->next;
        }
        printf("\n");
    }
}

int main() {
    insertMulti(10, 2);
    insertMulti(20, 4);
    insertMulti(30, 1);
    insertMulti(40, 3);

    displayMulti();
    printf("Removed: %d\n", removeMulti());
    displayMulti();

    return 0;
}
