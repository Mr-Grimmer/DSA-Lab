#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* insert(Node* root, int key) {
    if (root == NULL) {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = key;
        temp->left = temp->right = NULL;
        return temp;
    }
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    return root;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* delete(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = delete(root->left, key);
    else if (key > root->data)
        root->right = delete(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root); return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root); return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, key;
    do {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Inorder\n5. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Enter value: "); scanf("%d", &key); root = insert(root, key); break;
            case 2: printf("Enter value to search: "); scanf("%d", &key); 
                    printf(search(root, key) ? "Found\n" : "Not Found\n"); break;
            case 3: printf("Enter value to delete: "); scanf("%d", &key); root = delete(root, key); break;
            case 4: inorder(root); break;
        }
    } while (choice != 5);
    return 0;
}