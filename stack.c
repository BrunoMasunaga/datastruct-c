/*Author: Bruno Masunaga
 *Project: Data Structures I
 *Text: Stack Implementation and Functions
*/

#include <stdio.h>
#include <stdlib.h>

int isEmpty;

typedef struct s_node StackNode;
struct s_node{
    int data;
    StackNode* next;
};

//creates a new node
StackNode* createNode(int data){
    StackNode* new = malloc(sizeof(StackNode));
    if (new == NULL) return NULL;
    new->data = data;
    new->next = NULL;
    return new;
}

//pushes an element to the stack
void push(int data, StackNode** root){
    StackNode* new = createNode(data);
    new->next = *root;
    *root = new;
}

//pops the top element of the stack
int pop(StackNode** root){
    isEmpty = 0;
    if (*root == NULL){
        isEmpty = 1;
        return 0;
    }
    StackNode* excluded = *root;
    int popped = excluded->data;
    *root = excluded->next;
    free(excluded);
    return popped;
}

//shows the hole stack, but pops every element in it
void printStack(StackNode** root){
    printf("[STACK]\n");
    while (*root != NULL){
        int popped = pop(root);
        printf("%d ", popped);
    }
}

int main() {

    StackNode* stack = NULL;
    char operation;

    printf("You can use the following functions:\nI: Pushes a new element to the list.\nR: Pops the top element of the list.\nP: Shows the hole stack, but pops every element in it. This one also quits the program.\n");

    while(1){
        scanf("%c", &operation);
        if (operation == 'I'){
            int data;
            scanf("%d", &data);
            push(data, &stack);
        }
        else if (operation == 'R'){
            int popped = pop(&stack);
            if(isEmpty == 0) printf("Popped: %d.\n", popped);
            else printf("The stack is empty!\n");
        }
        else if (operation == 'P'){
            printStack(&stack);
            break;
        }
    }

    return (EXIT_SUCCESS);
}
