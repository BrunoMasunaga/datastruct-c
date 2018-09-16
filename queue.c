/*Author: Bruno Masunaga
 *Project: Data Structures I
 *Text: Queue Implementation and Functions
*/

#include <stdio.h>
#include <stdlib.h>

int isEmpty;

typedef struct s_node QueueNode;
struct s_node{
    int data;
    QueueNode* next;
};

typedef struct s_queue Queue;
struct s_queue{
    QueueNode* head;
    QueueNode* tail;
};

//creates a new queue
Queue createQueue(){
    Queue queue;
    queue.head = NULL;
    queue.tail = NULL;
    return queue;
}

//creates a new node
QueueNode* createNode(int data){
    QueueNode* new = malloc(sizeof(QueueNode));
    if (new == NULL) return NULL;
    new->data = data;
    new->next = NULL;
    return new;
}

//enqueue a new element to the queue
void enqueue(int data, Queue* queue){
    if(queue->head == NULL){
        queue->head = createNode(data);
        queue->tail = queue->head;
        return;
    }
    queue->tail->next = createNode(data);
    queue->tail = queue->tail->next;
}

//dequeue the first element in the queue
int dequeue(Queue* queue){
    isEmpty = 0;
    if (queue->head == NULL){
        isEmpty = 1;
        return 0;
    }
    QueueNode* excluded = queue->head;
    int dequeued = excluded->data;
    queue->head = excluded->next;
    free(excluded);
    return dequeued;
}

//shows the hole queue, but dequeues every element in it
void printQueue(Queue* queue){
    printf("[QUEUE]\n");
    while (queue->head != NULL){
        int dequeued = dequeue(queue);
        printf("%d ", dequeued);
    }
}

int main() {

    Queue queue = createQueue();
    char operation;

    printf("You can use the following functions:\nI: Enqueues a new element to the list.\nR: Dequeues the top element of the list.\nP: Shows the hole queue, but dequeues every element in it. This one also quits the program.\n");

    while(1){
        scanf("%c", &operation);
        if (operation == 'I'){
            int data;
            scanf("%d", &data);
            enqueue(data, &queue);
        }
        else if (operation == 'R'){
            int dequeued = dequeue(&queue);
            if(isEmpty == 0) printf("Dequeued: %d.\n", dequeued);
            else printf("The queue is empty!\n");
        }
        else if (operation == 'P'){
            printQueue(&queue);
            break;
        }
    }

    return (EXIT_SUCCESS);
}
