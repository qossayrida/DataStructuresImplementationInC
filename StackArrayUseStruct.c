#include <stdio.h>
#include <stdlib.h>
#define MINSTACKSIZE 5

typedef struct StackRecord* Stack;

Stack CreateStack(int size);
void Push(int x,Stack S);
int Top (Stack S);
void Pop(Stack S);
int IsEmpty(Stack S);
int IsFull(Stack S);
void MakeNull(Stack S);
void DisposeStack(Stack S);


struct StackRecord {
    int Top;
    int Capacity;
    int *Array;
};

int main (){

}

Stack CreateStack(int size){
    Stack S;
    if( size < MINSTACKSIZE )
        printf("Stack size is too small");

    S = (Stack) malloc( sizeof( struct StackRecord ) );

    if( S == NULL )
        printf("Out of space!!!");
    S->Array = (int*) malloc( sizeof(int) * size );

    if( S->Array == NULL )
        printf("Out of space!!!");

    S->Top = -1;
    S->Capacity = size ;
    return S ;
}

void Push(int x,Stack S){
    if(IsFull( S ))
        printf("Full stack");
    else
        S->Array[++S->Top] = x;
}

int Top (Stack S){
    if(IsEmpty(S))
        printf("Empty stack");
    else
        return S->Array[S->Top];
    return -1;
}

void Pop(Stack S){
    if(IsEmpty(S))
        printf("Empty stack");
    else
        S->Top--;
}

int IsEmpty(Stack S){
    return S->Top == -1 ;
}

int IsFull(Stack S){
    return S->Top == S->Capacity-1;
}

void MakeNull(Stack S){
    S->Top = -1;
}

void DisposeStack(Stack S) {
    if (S != NULL) {
        free(S->Array);
        free(S);
    }
}
