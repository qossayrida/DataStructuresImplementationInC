#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

void push(int value);
void pop();
int Top();
int IsEmpty();
void MakeEmpty();

int stack[MAX_SIZE];
int top = -1;


int main() {
    push(5);
    push(10);
    push(15);
    printf("Top value: %d\n", Top());
    pop();
    printf("Top value: %d\n", Top());
    pop();
    printf("Top value: %d\n", Top());
    pop();
    pop();
    printf("Is stack empty? %s\n", IsEmpty() ? "Yes" : "No");
    MakeEmpty();
    printf("Is stack empty? %s\n", IsEmpty() ? "Yes" : "No");
    return 0;
}

void push(int value) {
    if (top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    top++;
    stack[top] = value;
}

void pop() {
    if (top == -1) {
        printf("Stack underflow\n");
    }
    top--;
}

int Top() {
    if (top == -1) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack[top];
}

int IsEmpty() {
    if (top == -1) {
        return 1;
    }
    return 0;
}

void MakeEmpty() {
    top = -1;
}
