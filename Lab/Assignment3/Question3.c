#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void init(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
int isFull(Stack *s) { return s->top == MAX - 1; }

void push(Stack *s, int val) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->arr[++(s->top)] = val;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

int main() {
    Stack s;
    init(&s);
    FILE *fp = fopen("data.txt", "r");
    if (!fp) {
        printf("Cannot open file\n");
        return 1;
    }
    
    int num;
    while (fscanf(fp, "%d", &num) == 1) {
        push(&s, num);
    }
    fclose(fp);
    
    printf("Data in reverse order:\n");
    while (!isEmpty(&s)) {
        printf("%d ", pop(&s));
    }
    printf("\n");
    return 0;
}
