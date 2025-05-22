#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int person;
    struct Node* next;
    struct Node* prev;
} Node;

Node* create_circle_doubly(int n) {
    Node* head = NULL;
    Node* temp = NULL;
    Node* prev = NULL;

    for (int i = 1; i <= n; i++) {
        temp = (Node*)malloc(sizeof(Node));
        temp->person = i;
        temp->next = NULL;
        temp->prev = NULL;

        if (head == NULL) {
            head = temp;
            prev = temp;
        } else {
            prev->next = temp;
            temp->prev = prev;
            prev = temp;
        }
    }
    // close the circle
    head->prev = prev;
    prev->next = head;

    return head;
}

int find_last_person_doubly(int n, int k) {
    Node* head = create_circle_doubly(n);
    Node* ptr = head;

    while (ptr != ptr->next) {
        // skip k-1 people
        for (int i = 1; i < k; i++) {
            ptr = ptr->next;
        }
        // remove current person
        Node* to_remove = ptr;
        to_remove->prev->next = to_remove->next;
        to_remove->next->prev = to_remove->prev;

        ptr = to_remove->next;
        free(to_remove);
    }
    int last_person = ptr->person;
    free(ptr);
    return last_person;
}

int main() {
    int n, k;
    printf("Enter number of people and skip count: ");
    scanf("%d%d", &n, &k);

    int last_person = find_last_person_doubly(n, k);
    printf("The last person remaining is: %d\n", last_person);
    return 0;
}
