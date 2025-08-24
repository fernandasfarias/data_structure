#include <stdio.h>
#include <stdlib.h>

// Reference: The Youtube Channel "Programe seu futuro".

typedef struct node{
    int value;
    struct node *left, *right;
}Node;

typedef struct{
    Node *root;
}BinaryTree;

void leftInsertion(Node *node, int number){
    if(node->left == NULL){
        Node *newNode = (Node*)malloc(sizeof(Node));

        newNode->value = number;
        newNode->left = NULL;
        newNode->right = NULL;
        node->left = newNode;
    }
    else{
        if(number < node->left->value){
           leftInsertion(node->left, number);
        }
        if (number > node->left->value){
            rightInsertion(node->left, number);
        }
    }
}

void rightInsertion(Node *node, int number){
    if (node->right == NULL){
        Node *newNode = (Node*)malloc(sizeof(Node));

        newNode->value = number;
        newNode->left = NULL;
        newNode->right = NULL;
        node->right = newNode;
    }
    else{
        if (number < node->right->value){
            leftInsertion(node->right, number);
        }
        if (number > node->right->value){
            rightInsertion(node->right, number);
        }
    }
}

void insertion(BinaryTree *tree, int number){
    // First case: The tree is empty.
    if(tree->root == NULL){
        Node *newNode = (Node*)malloc(sizeof(Node));

        newNode->value = number;
        newNode->left = NULL;
        newNode->right = NULL;
        tree->root = newNode;
    }
    // Second case: There is at least one element at the tree.
    else{
        if(number < tree->root->value){
            leftInsertion(tree->root, number);
        }
        if (number > tree->root->value){
            rightInsertion(tree->root, number);
        }
    }
}

// Inorder
void printing(Node *root){
    if (root != NULL){
        printing(root->left);
        printf("%d ", root->value);
        printing(root->right);
    }
}

Node* insertion_NewVersion(Node *root, int value){
    if(root == NULL){
        Node *newNode = (Node*)malloc(sizeof(Node));

        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    else{
        if(value < root->value){
            root->left = insertion_NewVersion(root->left, value);
        }
        if (value > root->value){
            root->right = insertion_NewVersion(root->right, value);
        }
        return root;
    }
}

int lenght(Node *root){
    if(root == NULL){
        return 0;
    }
    else{
        return 1 + lenght(root->left) + lenght(root->right);
    }
}

Node* removing(Node *root, int key){
    if(root == NULL){
        printf("Value not found.");
        return NULL;
    }
    else{
        if(root->value == key){
            // first case: leaf node
            if (root->left == NULL && root->right == NULL){
                free(root);
                return NULL;
            }
            else{ // second case: remove nodes that have at least one child.
                if(root->left == NULL || root->right == NULL){
                    Node *aux;
                    if(root->left != NULL){
                        aux = root->left;
                    }
                    else{
                        aux = root->right;
                    }
                    free(root);
                    return aux;
                }
                else{
                    Node *aux = root->left; // through left
                    
                    while(aux->right != NULL) aux = aux->right;

                    root->value = aux->value;
                    aux->value = key;
                    root->left = removing(root->left, key);

                    return root;
                }
            }
        }
        else{
            if(key < root->value){
                root->left = removing(root->left, key);
            }
            else{
                root->right = removing(root->right, key);
            }
            return root;
        }
    }
}

int main(){
    int op, value;
    BinaryTree tree; // used for the old version
    Node *root = NULL;

    do{
        printf("\n\n0 - Out\n1 - Insertion\n2 - Printing\n3 - Lenght\n4 - Remove\n");
        scanf("%d", &op);

        switch(op){
            case 0:
                printf("Exiting the Program...\n");
                break;
            case 1:
                printf("Type a value: ");
                scanf("%d", &value);
                root = insertion_NewVersion(root, value);
                //insertion(&tree, value);
                break;
            case 2:
                printf("\nPrinting the binary tree:\n");
                printing(root);
                break;
            case 3:
                printf("Lenght: %d\n", lenght(root));
                break;
            case 4:
                printf("Type a value to remove: ");
                scanf("%d", &value);
                root = removing(root, value);
                break;
            default:
                printf("Invalid number!\n");
                break;
        }
    }while(op != 0);
    return 0;
}