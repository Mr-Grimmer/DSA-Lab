#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
    int lthread, rthread;
} Node;

Node* insert(Node* root, int key) {
    Node *ptr = root, *par = NULL;
    while (ptr != NULL) {
        if (key == ptr->data) return root;
        par = ptr;
        if (key < ptr->data) {
            if (ptr->lthread == 0)
                ptr = ptr->left;
            else break;
        } else {
            if (ptr->rthread == 0)
                ptr = ptr->right;
            else break;
        }
    }

    Node *tmp = (Node*)malloc(sizeof(Node));
    tmp->data = key;
    tmp->lthread = tmp->rthread = 1;

    if (par == NULL) {
        root = tmp;
        tmp->left = tmp->right = NULL;
    } else if (key < par->data) {
        tmp->left = par->left;
        tmp->right = par;
        par->lthread = 0;
        par->left = tmp;
    } else {
        tmp->left = par;
        tmp->right = par->right;
        par->rthread = 0;
        par->right = tmp;
    }

    return root;
}

void inorder(Node* root) {
    Node* ptr = root;
    while (ptr->lthread == 0)
        ptr = ptr->left;
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        if (ptr->rthread == 1)
            ptr = ptr->right;
        else {
            ptr = ptr->right;
            while (ptr && ptr->lthread == 0)
                ptr = ptr->left;
        }
    }
}

int main() {
    Node *root = NULL;
    int ch, key;
    do {
        printf("\n1. Insert\n2. Inorder\n3. Exit\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Enter key: "); scanf("%d", &key); root = insert(root, key); break;
            case 2: inorder(root); break;
        }
    } while (ch != 3);
    return 0;
}