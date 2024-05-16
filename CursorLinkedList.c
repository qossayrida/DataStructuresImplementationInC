#include <stdio.h>
#include <stdlib.h>
#define spaceSize 11

typedef int List;
typedef int Position;

void InitializeCursorSpace();
List CursorList();
int CursorAlloc();
List MakeEmpty( List L );
int IsEmpty( List L );
int IsLast();
void Insert( int X, List L );
Position Find( int X, List L );
Position FindPrevious( int X, List L );
void Delete( int X, List L );
void CursorFree( Position P );
void DeleteList( List L );
void PrintList( List L );

struct node {
    int element;
    int next;
};

struct node cursorSpace[spaceSize];

int main(){
    InitializeCursorSpace();
    for(int i = 0; i < spaceSize ; i++ ){
        printf("%d\t",cursorSpace[i].next);
    }
    return 7;
}

List CursorList(){
    List L = CursorAlloc();
    cursorSpace[ L ].next = 0;
    return L;
}

void InitializeCursorSpace(){
    for(int i = 0; i<spaceSize-1; i++)
        cursorSpace[i].next=i+1;

    cursorSpace[spaceSize - 1].next = 0;
}

int CursorAlloc(){
    Position P;

    P = cursorSpace[ 0 ].next;
    cursorSpace[ 0 ].next = cursorSpace[ P ].next;
    if( P == 0 ){
        printf("Out of space!\n");
        return -1;
    }
    return P;
}

List MakeEmpty( List L ){
    if( L )
        DeleteList( L );
    L = CursorAlloc();
    if( L == 0 )
        printf("Out of memory!");
    cursorSpace[ L ].next = 0;
    return L;
}

int IsEmpty( List L ){
    return cursorSpace[ L ].next == 0; //header
}

int IsLast( Position P, List L ){
    return cursorSpace[ P ].next == 0;
}

void Insert( int X, List L ){
    Position TmpCell, P = L;
    TmpCell = CursorAlloc( );
    while( P && cursorSpace[P].next != 0)
        P = cursorSpace[P].next;
    cursorSpace[ TmpCell ].element = X;
    cursorSpace[ TmpCell ].next = cursorSpace[ P ].next;
    cursorSpace[ P ].next = TmpCell;
}

Position Find( int X, List L ) {
    Position P;
    P = cursorSpace[ L ].next;
    while( P && cursorSpace[ P ].element != X )
        P = cursorSpace[ P ].next;
    return P;
}

Position FindPrevious( int X, List L ){
    Position P;
    P = L;
    while( cursorSpace[ P ].next && cursorSpace[ cursorSpace[ P ].next ].element != X )
        P = cursorSpace[ P ].next;
    return P;
}

void Delete( int X, List L ){
    Position P, TmpCell;
    P = FindPrevious( X, L );
    if( !IsLast( P, L ) ){
        TmpCell = cursorSpace[ P ].next;
        cursorSpace[ P ].next = cursorSpace[ TmpCell ].next;
        CursorFree( TmpCell );
    }
}

void CursorFree( Position P ){
    cursorSpace[ P ].next = cursorSpace[ 0 ].next;
    cursorSpace[ 0 ].next = P;
}

void DeleteList( List L ){
    Position P, Tmp;
    P = cursorSpace[ L ].next; /* Header assumed */
    cursorSpace[ L ].next = 0;
    while( P != 0 ){
        Tmp = cursorSpace[ P ].next;
        CursorFree( P );
        P = Tmp;
    }
}

void PrintList( List L ){
    Position P = L;
    while( P != 0 ){
        printf("%3d \t %3d \t %3d\n", P,cursorSpace[P].element, cursorSpace[P].next);
        P = cursorSpace[P].next;
    }
}