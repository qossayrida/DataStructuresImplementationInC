#include <stdio.h>
#include <stdlib.h>

typedef struct node* Pos;
typedef Pos Stack;

int IsEmpty( Stack S );
Stack CreateStack();
void MakeEmpty( Stack S );
void Pop( Stack S );
int Top( Stack S );
void Push( int X, Stack S );
void DisposeStack( Stack S );

struct node{
    int Element;
    Pos Next;
};

int main() {

    return 0;
}

int IsEmpty( Stack S ){
    return S->Next == NULL;
}

Stack CreateStack(){
    Stack S= (Stack)malloc(sizeof(struct node));
    if( S == NULL )
        printf("Out of space!");
    S->Next = NULL;
    MakeEmpty( S );
    return S;
}

void MakeEmpty( Stack S ){
    if( S == NULL )
        printf("Out of space!");
    else
    while( !IsEmpty( S ))
        Pop(S);
}

void Pop( Stack S ){
    Pos firstCell;
    if( IsEmpty( S ) )
        printf("Empty stack" );
    else{
        firstCell = S->Next;
        S->Next = S->Next->Next;
        free(firstCell);
    }
}

int Top( Stack S ){
    if( !IsEmpty( S ) )
        return S->Next->Element;
    printf("Empty stack");
    return 0;
}

void Push( int X, Stack S ){
    Pos temp;
    temp = ( Stack )malloc( sizeof( struct node ) );
    if( temp == NULL)
        printf("Out of space!");
    else{
        temp->Element = X;
        temp->Next = S->Next;
        S->Next = temp;
    }
}

void DisposeStack( Stack S ){
    MakeEmpty( S );
    free( S );
}