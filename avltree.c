/*Author: Bruno Masunaga
 *Project: Data Structures I
 *Text: AVL Tree Implementation and Functions
*/

#include <stdio.h>
#include <stdlib.h>

int existElem = 0;

typedef struct s_node AVLTreeNode;
struct s_node{
    int data;
    int height;
    AVLTreeNode* right;
    AVLTreeNode* left;
};

//creates a new node
AVLTreeNode* createNode(int data){
    AVLTreeNode* new = malloc(sizeof(AVLTreeNode));
    if (new == NULL) return NULL;
    new->data = data;
    new->height = 0;
    new->right = NULL;
    new->left = NULL;
    return new;
}

//searches an element in the AVL tree (returns the number of comparisons)
int searchNode(int data, AVLTreeNode* root){
    int comp = 0;
    existElem = 0;
    while (root != NULL){
        comp++;
        if (root->data == data){
            existElem = 1;
            return comp;
        }
        if (root->data < data) root = root->right;
        else root = root->left;
    }
    return comp;
}

//gets the AVL tree height
int getHeight(AVLTreeNode* node){
    if (node == NULL) return -1;
    int hLeft = getHeight(node->left);
    int hRight = getHeight(node->right);
    if (hLeft > hRight){
        node->height = hLeft+1;
        return hLeft+1;
    }
    else{
        node->height = hRight+1;
        return hRight+1;
    }
}

//gets the balance factor of a node from the AVL tree
int getFactor(AVLTreeNode* node){
    if (node == NULL) return 0;
    int hLeft = getHeight(node->left);
    int hRight = getHeight(node->right);
    int factor = hLeft - hRight;
    return factor;
}

//simple rotation at right side (LL)
void rotationLL(AVLTreeNode** disbNode){
    AVLTreeNode* leftChild = (*disbNode)->left;
    (*disbNode)->left = leftChild->right;
    leftChild->right = *disbNode;
    *disbNode = leftChild;
}

//simple rotation at left side (RR)
void rotationRR(AVLTreeNode** disbNode){
    AVLTreeNode* rightChild = (*disbNode)->right;
    (*disbNode)->right = rightChild->left;
    rightChild->left = *disbNode;
    *disbNode = rightChild;
}

//double rotation at right side (LR)
void rotationLR(AVLTreeNode** disbNode){
    rotationRR(&((*disbNode)->left));
    rotationLL(disbNode);
}

//double rotation at left side (RL)
void rotationRL(AVLTreeNode** disbNode){
    rotationLL(&((*disbNode)->right));
    rotationRR(disbNode);
}

//finds the heavier subtree of a node from AVL tree
int findHeavier(AVLTreeNode* node){
    int subRight = getHeight(node->right);
    int subLeft = getHeight(node->left);
    if (subLeft > subRight) return 1;
    else if (subLeft < subRight) return -1;
    else return 0;
}

//balance process of an disbalanced node of the AVL tree
void balance(AVLTreeNode** root){
    if (*root == NULL) return;
    AVLTreeNode* cursor = *root;
    int fb = getFactor(cursor);
    if (fb == -2){
        int heavier = findHeavier(cursor->right);
        if (heavier == 1) rotationRL(root);
        else rotationRR(root);
    }
    else if (fb == 2){
        int heavier = findHeavier(cursor->left);
        if (heavier == -1) rotationLR(root);
        else rotationLL(root);
    }
}

//inserts an element in the tree
void insertNode(int data, AVLTreeNode** root){
    if (*root == NULL){
        *root = createNode(data);
        return;
    }
    else if ((*root)->data == data) return;
    AVLTreeNode* cursor = *root;
    if (data < cursor->data){
        insertNode(data, &(cursor->left));
        balance(root);
    }
    else{
        insertNode(data, &(cursor->right));
        balance(root);
    }
    int updateHeight = getHeight(*root);
}

//finds the successor of a node in the AVL tree
AVLTreeNode* findSuccessor(AVLTreeNode* root){
    AVLTreeNode* successor = root;
    AVLTreeNode* nextSuccessor = successor->left;
    while(nextSuccessor != NULL){
        successor = nextSuccessor;
        nextSuccessor = nextSuccessor->left;
    }
    return successor;
}

//removes an element from the AVL tree
int removeNode(int data, AVLTreeNode** root){
    if (*root == NULL) return 0;
    int removalControl;
    AVLTreeNode* cursor = *root;

    if (data < cursor->data){
        removalControl = removeNode(data, &(cursor->left));
        if (removalControl == 1) balance(root);
    }

    else if (data > cursor->data){
        removalControl = removeNode(data, &(cursor->right));
        if (removalControl == 1) balance(root);
    }

    if (cursor->data == data){
        if (cursor->left == NULL || cursor->right == NULL){
            if (cursor->left != NULL) *root = cursor->left;
            else *root = cursor->right;
            free(cursor);
        }
        else{
            AVLTreeNode* sucessor = findSuccessor(cursor->right);
            cursor->data = sucessor->data;
            removalControl = removeNode(cursor->data, &(cursor->right));
            balance(root);
        }
        removalControl = 1;
    }
    int updateHeight = getHeight(*root);
    return removalControl;
}

//verifies if it's AVL tree
int verifyAVL(AVLTreeNode* root){
    if (root == NULL) return 0;
    int factor = getFactor(root);
    if (abs(factor) > 1) return 1;
    int factorLeft = verifyAVL(root->left);
    int factorRight = verifyAVL(root->right);
    if (factorLeft == 1 || factorRight == 1) return 1;
    return 0;
}

//prints the whole AVL tree in pre-order
void printTree(AVLTreeNode* root){
    if (root == NULL) return;
    printf("%d ", root->data);
    printTree(root->left);
    printTree(root->right);
}

//frees the AVL tree from memory
void freeTree(AVLTreeNode* root){
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {

    AVLTreeNode* tree = NULL;
    char operation;

    printf("You can use the following functions:\nI: Inserts an element in the tree.\nR: Removes an element from the tree.\nS: Searches an element in the tree.\nP: Prints the whole tree in pre-order.\nH: Shows the height of the tree.\nV: Verifies if the tree is AVL.\nQ: Quit.\nType the letter followed by the element when it's needed.\n");

    while(1){
        scanf("%c", &operation);
        if (operation == 'I'){
            int data;
            scanf("%d", &data);
            insertNode(data, &tree);
        }
        else if (operation == 'R'){
            int data;
            scanf("%d", &data);
            removeNode(data, &tree);
        }
        else if (operation == 'S'){
            int data;
            scanf("%d", &data);
            int comp = searchNode(data, tree);
            if (existElem == 0) printf("There's no such element in the tree.\n");
            else printf("The element %d is in the tree and took %d comparisons to find it.\n", data, comp);
        }
        else if (operation == 'P'){
            printf("[TREE]\n");
            printTree(tree);
            printf("\n");
        }
        else if (operation == 'H'){
            int height = getHeight(tree);
            printf("The tree height is %d.\n", height);
        }
        else if (operation == 'V'){
            int isAVL = verifyAVL(tree);
            if (isAVL == 0) printf("It's a AVL Tree.\n");
            else printf("It isn't a AVL Tree.\n");
        }
        else if (operation == 'Q'){
            freeTree(tree);
            break;
        }
    }

    return (EXIT_SUCCESS);
}
