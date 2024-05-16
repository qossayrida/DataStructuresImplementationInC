#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Node;
typedef struct Queue* Queue;


Node newNode(int data);
Queue createQueue();
int isEmpty(Queue q);
void enqueue(int x,Queue q);
int dequeue(Queue q);
void displayQueue(Queue q);
void freeQueue(Queue q);

struct Node {
    int data;
    Node next;
};

struct Queue {
    Node front;
    Node rear;
};

// Example usage
int main() {
    Queue q = createQueue();

    enqueue(1, q);
    enqueue(2, q);
    enqueue(4, q);

    displayQueue(q);  // Output: 1 2 3

    dequeue(q);
    displayQueue(q);  // Output: 2 3

    dequeue(q);
    dequeue(q);
    dequeue(q);
    displayQueue(q);  // Output: Queue is empty

    freeQueue(q);
    return 0;
}

Node newNode(int data) {
    Node temp = (Node)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

Queue createQueue() {
    Queue q = (Queue)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(Queue q) {
    return q->front == NULL;
}

void enqueue(int x,Queue q) {
    Node temp = newNode(x);
    if (isEmpty(q)) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

int dequeue(Queue q) {
    if (isEmpty(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    Node temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    int data = temp->data;
    free(temp);
    return data;
}

void displayQueue(Queue q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }

    Node temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeQueue(Queue q) {
    Node temp = q->front;
    while (temp != NULL) {
        Node next = temp->next;
        free(temp);
        temp = next;
    }
    free(q);
}

