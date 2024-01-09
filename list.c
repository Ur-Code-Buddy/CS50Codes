#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *addr;
}node;

int printlist(node *root);

int main(void){
    node *root = malloc(sizeof(node));
    root ->value = 56;
    root ->addr = NULL;

    node *p = malloc(sizeof(node));
    p -> value = 22;
    p -> addr = root;

    root = p;


    node *s = malloc(sizeof(node));
    s -> value = 78;
    s -> addr = root;

    root = s;

    printlist(root);

    free(p->addr);
    free(p);
    free(root);

}

int printlist(node *root){
    if (root->addr == NULL){
        return 0;
    }
    while (root->addr != NULL){
        printf("value: %i\n",root->value);
        root = root->addr;
    }
    printf("value: %i\n",root->value);

    return 1;


}
