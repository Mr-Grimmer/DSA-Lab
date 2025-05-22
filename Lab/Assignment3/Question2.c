#include <stdio.h>
#define MAX 100
#define N 3  // Number of stacks

typedef struct {
    int arr[MAX];
    int top[N];
    int size; // size of each stack
} MultiStack;

void init(MultiStack *ms, int size) {
    ms->size = size;
    for (int i = 0; i < N; i++) {
        ms->top[i] = -1;
    }
}

int isFull(MultiStack *ms, int sn) {
    return ms->top[sn] == ms->size - 1;
}

int isEmpty(MultiStack *ms, int sn) {
    return ms->top[sn] == -1;
}

void push(MultiStack *ms, int sn, int val) {
    if (isFull(ms, sn)) {
        printf("Stack %d overflow\n", sn);
        return;
    }
    ms->arr[sn * ms->size + ++ms->top[sn]] = val;
}

int pop(MultiStack *ms, int sn) {
    if (isEmpty(ms, sn)) {
        printf("Stack %d underflow\n", sn);
        return -1;
    }
    return ms->arr[sn * ms->size + ms->top[sn]--];
}

int peek(MultiStack *ms, int sn) {
    if (isEmpty(ms, sn)) {
        printf("Stack %d is empty\n", sn);
        return -1;
    }
    return ms->arr[sn * ms->size + ms->top[sn]];
}

int main() {
    MultiStack ms;
    init(&ms, MAX / N);
    
    push(&ms, 0, 10);
    push(&ms, 1, 20);
    push(&ms, 2, 30);
    push(&ms, 0, 40);
    
    printf("Top of stack 0: %d\n", peek(&ms, 0));
    printf("Pop from stack 1: %d\n", pop(&ms, 1));
    
    return 0;
}
