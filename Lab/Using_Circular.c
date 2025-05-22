#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int person;
    struct Node* next;
} Node;

Node* create_circle(int n) {
    Node* head = NULL;
    Node* temp = NULL;
    Node* prev = NULL;

    for (int i = 1; i <= n; i++) {
        temp = (Node*)malloc(sizeof(Node));
        temp->person = i;
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
        } else {
            prev->next = temp;
        }
        prev = temp;
    }
    prev->next = head; // make circular
    return head;
}

int find_last_person_singly(int n, int k) {
    Node* head = create_circle(n);
    Node* ptr = head;
    Node* prev = NULL;

    while (ptr != ptr->next) {
        // skip k-1 people alive
        for (int i = 1; i < k; i++) {
            prev = ptr;
            ptr = ptr->next;
        }
        // remove current person
        prev->next = ptr->next;
        free(ptr);
        ptr = prev->next;
    }
    int last_person = ptr->person;
    free(ptr);
    return last_person;
}

int main() {
    int n, k;
    printf("Enter number of people and skip count: ");
    scanf("%d%d", &n, &k);

    int last_person = find_last_person_singly(n, k);
    printf("The last person remaining is: %d\n", last_person);
    return 0;
}
