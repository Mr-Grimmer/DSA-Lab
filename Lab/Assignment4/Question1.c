#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* createTree() {
    int data;
    printf("Enter data (-1 for NULL): ");
    scanf("%d", &data);
    if (data == -1) return NULL;
    Node* root = createNode(data);
    printf("Left child of %d:\n", data);
    root->left = createTree();
    printf("Right child of %d:\n", data);
    root->right = createTree();
    return root;
}

void preorder(Node* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    Node *root = NULL;
    int choice;
    do {
        printf("\n1. Create\n2. Preorder\n3. Inorder\n4. Postorder\n5. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: root = createTree(); break;
            case 2: preorder(root); break;
            case 3: inorder(root); break;
            case 4: postorder(root); break;
        }
    } while (choice != 5);
    return 0;
}