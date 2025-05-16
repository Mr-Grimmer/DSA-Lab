#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int power;
    struct Node* next;
} Node;

Node* createNode(int coeff, int power) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->power = power;
    newNode->next = NULL;
    return newNode;
}

void insertTerm(Node** poly, int coeff, int power) {
    Node* newNode = createNode(coeff, power);
    if (*poly == NULL || (*poly)->power < power) {
        newNode->next = *poly;
        *poly = newNode;
        return;
    }

    Node* temp = *poly;
    while (temp->next && temp->next->power > power)
        temp = temp->next;

    if (temp->next && temp->next->power == power) {
        temp->next->coeff += coeff;
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void display(Node* poly) {
    while (poly) {
        printf("%dx^%d", poly->coeff, poly->power);
        poly = poly->next;
        if (poly) printf(" + ");
    }
    printf("\n");
}

Node* addPoly(Node* poly1, Node* poly2) {
    Node* result = NULL;
    while (poly1 && poly2) {
        if (poly1->power > poly2->power) {
            insertTerm(&result, poly1->coeff, poly1->power);
            poly1 = poly1->next;
        } else if (poly1->power < poly2->power) {
            insertTerm(&result, poly2->coeff, poly2->power);
            poly2 = poly2->next;
        } else {
            insertTerm(&result, poly1->coeff + poly2->coeff, poly1->power);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1) {
        insertTerm(&result, poly1->coeff, poly1->power);
        poly1 = poly1->next;
    }
    while (poly2) {
        insertTerm(&result, poly2->coeff, poly2->power);
        poly2 = poly2->next;
    }

    return result;
}

Node* subtractPoly(Node* poly1, Node* poly2) {
    Node* result = NULL;
    while (poly1 && poly2) {
        if (poly1->power > poly2->power) {
            insertTerm(&result, poly1->coeff, poly1->power);
            poly1 = poly1->next;
        } else if (poly1->power < poly2->power) {
            insertTerm(&result, -poly2->coeff, poly2->power);
            poly2 = poly2->next;
        } else {
            insertTerm(&result, poly1->coeff - poly2->coeff, poly1->power);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1) {
        insertTerm(&result, poly1->coeff, poly1->power);
        poly1 = poly1->next;
    }
    while (poly2) {
        insertTerm(&result, -poly2->coeff, poly2->power);
        poly2 = poly2->next;
    }

    return result;
}

Node* multiplyPoly(Node* poly1, Node* poly2) {
    Node* result = NULL;
    for (Node* i = poly1; i; i = i->next) {
        for (Node* j = poly2; j; j = j->next) {
            insertTerm(&result, i->coeff * j->coeff, i->power + j->power);
        }
    }
    return result;
}

// Menu
int main() {
    Node *poly1 = NULL, *poly2 = NULL, *result = NULL;
    int choice, coeff, power;

    while (1) {
        printf("\n--- POLYNOMIAL MENU ---\n");
        printf("1. Insert term into Polynomial 1\n");
        printf("2. Insert term into Polynomial 2\n");
        printf("3. Display Polynomial 1\n");
        printf("4. Display Polynomial 2\n");
        printf("5. Add Polynomials\n");
        printf("6. Subtract Polynomials (Poly1 - Poly2)\n");
        printf("7. Multiply Polynomials\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter coefficient and power: ");
                scanf("%d %d", &coeff, &power);
                insertTerm(&poly1, coeff, power);
                break;
            case 2:
                printf("Enter coefficient and power: ");
                scanf("%d %d", &coeff, &power);
                insertTerm(&poly2, coeff, power);
                break;
            case 3:
                printf("Polynomial 1: ");
                display(poly1);
                break;
            case 4:
                printf("Polynomial 2: ");
                display(poly2);
                break;
            case 5:
                result = addPoly(poly1, poly2);
                printf("Sum: ");
                display(result);
                break;
            case 6:
                result = subtractPoly(poly1, poly2);
                printf("Difference: ");
                display(result);
                break;
            case 7:
                result = multiplyPoly(poly1, poly2);
                printf("Product: ");
                display(result);
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
