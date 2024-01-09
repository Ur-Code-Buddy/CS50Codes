#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *addr;
} node;

void printList(node *root) {
    while (root != NULL) {
        printf("%i ", root->value);
        root = root->addr;
    }
    printf("\n");
}

int main(void) {
    // Creating the first node
    node *root = malloc(sizeof(node));
    root->value = 56;
    root->addr = NULL;

    // Creating the second node
    node *p = malloc(sizeof(node));
    p->value = 22;
    p->addr = root;

    // Updating the root to the second node
    root = p;

    // Creating the third node
    node *s = malloc(sizeof(node));
    s->value = 78;
    s->addr = root;

    // Updating the root to the third node
    root = s;

    // Printing the values in the list
    printList(root);

    // Freeing the memory
    free(root);
    free(p);
    free(s);

    return 0;
}
