#include <stdio.h>

#define SIZE 100

char stack[SIZE];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return (top == -1) ? '\0' : stack[top--];
}

int isBalanced(char* expr) {
    char ch;
    for (int i = 0; expr[i]; i++) {
        ch = expr[i];
        if (ch == '(' || ch == '{' || ch == '[')
            push(ch);
        else if (ch == ')' || ch == '}' || ch == ']') {
            char temp = pop();
            if ((ch == ')' && temp != '(') ||
                (ch == '}' && temp != '{') ||
                (ch == ']' && temp != '['))
                return 0;
        }
    }
    return top == -1;
}

int main() {
    char expr[SIZE];
    printf("Enter expression: ");
    scanf("%s", expr);
    if (isBalanced(expr))
        printf("Balanced\n");
    else
        printf("Not Balanced\n");
    return 0;
}
