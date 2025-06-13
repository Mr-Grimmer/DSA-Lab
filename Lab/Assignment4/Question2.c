#include <stdio.h>
#define SIZE 100

int tree[SIZE];

void initTree() {
    for (int i = 0; i < SIZE; i++)
        tree[i] = -1;
}

void createTree() {
    int n, i, val;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter value at index %d: ", i);
        scanf("%d", &val);
        tree[i] = val;
    }
}

void preorder(int index) {
    if (index >= SIZE || tree[index] == -1) return;
    printf("%d ", tree[index]);
    preorder(2 * index + 1);
    preorder(2 * index + 2);
}

void inorder(int index) {
    if (index >= SIZE || tree[index] == -1) return;
    inorder(2 * index + 1);
    printf("%d ", tree[index]);
    inorder(2 * index + 2);
}

void postorder(int index) {
    if (index >= SIZE || tree[index] == -1) return;
    postorder(2 * index + 1);
    postorder(2 * index + 2);
    printf("%d ", tree[index]);
}

int main() {
    int choice;
    initTree();
    do {
        printf("\n1. Create\n2. Preorder\n3. Inorder\n4. Postorder\n5. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createTree(); break;
            case 2: preorder(0); break;
            case 3: inorder(0); break;
            case 4: postorder(0); break;
        }
    } while (choice != 5);
    return 0;
}