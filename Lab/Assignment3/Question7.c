#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int stack[SIZE];
int top = -1;

void push(int val) {
    stack[++top] = val;
}

int pop() {
    return stack[top--];
}

int evaluatePostfix(char* exp) {
    int i = 0, a, b;
    while (exp[i]) {
        if (isdigit(exp[i]))
            push(exp[i] - '0');
        else {
            b = pop();
            a = pop();
            switch (exp[i]) {
                case '+': push(a + b); break;
                case '-': push(a - b); break;
                case '*': push(a * b); break;
                case '/': push(a / b); break;
            }
        }
        i++;
    }
    return pop();
}

int main() {
    char exp[SIZE];
    printf("Enter postfix expression: ");
    scanf("%s", exp);
    printf("Result: %d\n", evaluatePostfix(exp));
    return 0;
}
