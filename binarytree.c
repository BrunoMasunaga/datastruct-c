/*Author: Bruno Masunaga
 *Project: Data Structures I
 *Text: Binary Tree Implementation and Functions
*/

#include <stdio.h>
#include <stdlib.h>

int existElem = 0;

typedef struct s_treenode TreeNode;
struct s_treenode{
    int data;
    TreeNode* left;
    TreeNode* right;
};

//creates a new node
TreeNode* createNode(int data){
    TreeNode* new = malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->left = NULL;
    new->right = NULL;
    new->data = data;
    return new;
}

//searches an element in the tree (returns the number of comparisons)
int searchNode(int data, TreeNode* root){
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

//inserts an element in the tree
void insertNode(int data, TreeNode** root){
    if (*root == NULL){
        *root = createNode(data);
        return;
    }
    else if ((*root)->data == data) return;
    TreeNode* cursor = *root;
    if (data < cursor->data) insertNode(data, &(cursor->left));
    else insertNode(data, &(cursor->right));
}

//finds the successor of a node in the tree
TreeNode* findSuccessor(TreeNode* root){
    TreeNode* successor = root;
    TreeNode* nextSuccessor = successor->left;
    while(nextSuccessor != NULL){
        successor = nextSuccessor;
        nextSuccessor = nextSuccessor->left;
    }
    return successor;
}

//removes an element from the tree
void removeNode(int data, TreeNode** root){
    if (*root == NULL) return;
    TreeNode* cursor = *root;

    if(data < cursor->data) removeNode(data, &(cursor->left));
    else if (data > cursor->data) removeNode(data, &(cursor->right));

    if(cursor->data == data){
        if(cursor->left == NULL || cursor->right == NULL){
            if(cursor->left != NULL) *root = cursor->left;
            else *root = cursor->right;
            free(cursor);
        }
        else{
            TreeNode* successor = findSuccessor(cursor->right);
            cursor->data = successor->data;
            removeNode(cursor->data, &(cursor->right));
        }
    }
}

//gets the tree height
int getHeight(TreeNode* root){
    TreeNode* cursor = root;
    if (cursor == NULL) return -1;
    int hLeft = getHeight(cursor->left)+1;
    int hRight = getHeight(cursor->right)+1;
    if (hLeft > hRight) return hLeft;
    return hRight;
}

//prints the whole tree in pre-order
void printTree(TreeNode* root){
    if (root == NULL) return;
    printf("%d ", root->data);
    printTree(root->left);
    printTree(root->right);
}

//frees the tree from memory
void freeTree(TreeNode* root){
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {

    TreeNode* tree = NULL;
    char operation;

    printf("You can use the following functions:\nI: Inserts an element in the tree.\nR: Removes an element from the tree.\nS: Searches an element in the tree.\nP: Prints the whole tree in pre-order.\nH: Shows the height of the tree.\nQ: Quit.\nType the letter followed by the element when it's needed.\n");

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
        else if (operation == 'Q'){
            freeTree(tree);
            break;
        }
    }

    return (EXIT_SUCCESS);
}
