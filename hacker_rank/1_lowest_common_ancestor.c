#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *left, *right;
} Node;

Node* insertion(Node *root, int value){
    if(root == NULL){
        Node *newNode = (Node*)malloc(sizeof(Node));

        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    else{
        if(value < root->data){
            root->left = insertion(root->left, value);
        }
        if (value > root->data){
            root->right = insertion(root->right, value);
        }
        return root;
    }
}

Node *lca(Node *root, int v1, int v2){
    if (root == NULL) return NULL;
    else{
        if (v1 == root->data && v2 == root->data){
            return root;
        }
        else if (v1 > root->data && v2 > root->data){ // RIGHT
            return lca(root->right, v1, v2);
        }
        else if(v1 < root->data && v2 < root->data){ // LEFT
            return lca(root->left, v1, v2);
        }
        else return root;
    }
}

void printing(Node *root){
    if (root != NULL){
        printing(root->left);
        printf("%d ", root->data);
        printing(root->right);
    }
}

int main(){
    int op = -1, value, v1, v2;
    Node *root = NULL;

    while (op != 0){
        printf("\n0 - Out\n1 - Insertion\n2 - Lowest Common Ancestor\n3 - Print\n");

        printf("\nType your option: ");
        scanf("%d", &op);

        if (op == 0) break;
        else if (op == 1){
            printf("\nType a value: ");
            scanf("%d", &value);
            root = insertion(root, value);
        }
        else if (op == 2){
            printf("\nType V1: ");
            scanf("%d", &v1);
            printf("\nType V2: ");
            scanf("%d", &v2);
            root = lca(root, v1, v2);
            printf("\nThe lowest Common Ancestor is %d\n", root->data);
        }
        else{
            printing(root);
        }
    }
    return 0;
}