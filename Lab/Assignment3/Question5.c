#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node **tops;
    int n;  // number of stacks
} MultiStackLL;

void init(MultiStackLL *ms, int n) {
    ms->n = n;
    ms->tops = (Node **)malloc(n * sizeof(Node *));
    for (int i = 0; i < n; i++) {
        ms->tops[i] = NULL;
    }
}

void push(MultiStackLL *ms, int sn, int val) {
    if (sn < 0 || sn >= ms->n) {
        printf("Invalid stack number\n");
        return;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = ms->tops[sn];
    ms->tops[sn] = newNode;
}

int pop(MultiStackLL *ms, int sn) {
    if (sn < 0 || sn >= ms->n) {
        printf("Invalid stack number\n");
        return -1;
    }
    if (ms->tops[sn] == NULL) {
        printf("Stack %d underflow\n", sn);
        return -1;
    }
    Node *temp = ms->tops[sn];
    int val = temp->data;
    ms->tops[sn] = temp->next;
    free(temp);
    return val;
}

int peek(MultiStackLL *ms, int sn) {
    if (sn < 0 || sn >= ms->n) {
        printf("Invalid stack number\n");
        return -1;
    }
    if (ms->tops[sn] == NULL) {
        printf("Stack %d is empty\n", sn);
        return -1;
    }
    return ms->tops[sn]->data;
}

void freeAll(MultiStackLL *ms) {
    for (int i = 0; i < ms->n; i++) {
        while (ms->tops[i] != NULL) {
            Node *temp = ms->tops[i];
            ms->tops[i] = temp->next;
            free(temp);
        }
    }
    free(ms->tops);
}

int main() {
    MultiStackLL ms;
    init(&ms, 3); // 3 stacks
    
    push(&ms, 0, 10);
    push(&ms, 1, 20);
    push(&ms, 2, 30);
    push(&ms, 0, 40);
    
    printf("Top of stack 0: %d\n", peek(&ms, 0));
    printf("Pop from stack 1: %d\n", pop(&ms, 1));
    
    freeAll(&ms);
    return 0;
}
