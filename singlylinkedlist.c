/*Author: Bruno Masunaga
 *Project: Data Structures I
 *Text: Singly Linked List Implementation and Functions
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct s_node ListNode;
struct s_node{
    int data;
    ListNode* next;
};

//creates a new node
ListNode* createNode(int data){
    ListNode* new = malloc(sizeof(ListNode));
    if (new == NULL) return NULL;
    new->data = data;
    new->next = NULL;
    return new;
}

//inserts an element in the end of the list
void insertEnd(int data, ListNode** root){
    if(*root == NULL){
        *root = createNode(data);
        return;
    }
    insertEnd(data, &((*root)->next));
}

//inserts an element in the beginning of the list
void insertBegin(int data, ListNode** root){
    ListNode* new = createNode(data);
    new->next = *root;
    *root = new;
}

//removes an element from the list
void removeNode(int data, ListNode** root){
    if (*root == NULL) return;
    if ((*root)->data == data){
        ListNode* excluded = *root;
        *root = excluded->next;
        free(excluded);
        return;
    }
    removeNode(data, &((*root)->next));
}

//searches an element in the list (returns it's index)
int searchNode(int data, ListNode* root){
    int index = 0;
    while (root != NULL){
        if (root->data == data) return index;
        index++;
        root = root->next;
    }
    return -1;
}

//gets the list size
int getSize(ListNode* root){
    int size = 0;
    while(root != NULL){
        size++;
        root = root->next;
    }
    return size;
}

//gives access to the node of an element in the list, given it's index
ListNode* accessNode(int index, ListNode* root){
    int size = getSize(root);
    if (index > size) return NULL;
    for (size = 0; size < index; size++) root = root->next;
    return root;
}

//prints the whole list
void printList(ListNode* root){
    if (root == NULL) return;
    printf("%d ", root->data);
    printList(root->next);
}

//frees the list from memory
void freeList(ListNode* root){
    if (root == NULL) return;
    freeList(root->next);
    free(root);
}

int main() {

    ListNode* list = NULL;
    char operation;

    printf("You can use the following functions:\nB: Inserts an element in the beginning of the list.\nE: Inserts an element in the end of the list.\nR: Removes an element from the list.\nS: Searches an element in the list.\nZ: Shows the size of the list.\nP: Prints the whole list.\nQ: Quit.\nType the letter followed by the element when it's needed.\n");

    while(1){
        scanf("%c", &operation);
        if (operation == 'E'){
            int data;
            scanf("%d", &data);
            insertEnd(data, &list);
        }
        else if (operation == 'B'){
            int data;
            scanf("%d", &data);
            insertBegin(data, &list);
        }
        else if (operation == 'R'){
            int data;
            scanf("%d", &data);
            removeNode(data, &list);
        }
        else if (operation == 'S'){
            int data;
            scanf("%d", &data);
            int indexSearch = searchNode(data, list);
            if (indexSearch == -1) printf("There's no such element in the list.\n");
            else printf("The element %d is in the position %d.\n", data, indexSearch);
        }
        else if (operation == 'P'){
            printf("[LIST]\n");
            printList(list);
            printf("\n");
        }
        else if (operation == 'Z'){
            int size = getSize(list);
            printf("The list size is %d.\n", size);
        }
        else if (operation == 'Q'){
            freeList(list);
            break;
        }
    }

    return (EXIT_SUCCESS);
}
