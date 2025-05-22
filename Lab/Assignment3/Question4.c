#include <stdbool.h>

bool areStacksEqual(Stack *s1, Stack *s2) {
    if (s1->top != s2->top) return false;
    
    for (int i = 0; i <= s1->top; i++) {
        if (s1->arr[i] != s2->arr[i]) return false;
    }
    return true;
}
