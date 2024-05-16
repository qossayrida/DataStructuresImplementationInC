#include <stdio.h>
#include <stdlib.h>

typedef struct node* List;
typedef List Position;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(List P,List L);
List Find(int X,List L);
List FindPrevious(int X,List L);
void Delete(int X,List L);
void Insert(int X,List L,List P);
void PrintList(List L);
void DeleteList(List L);
int size (List L);
int compare (List L1,List L2);
int compare1 (List L1,List L2);

struct node {
    int Data;
    List Next ;
};

int main(){
    List L1=MakeEmpty(NULL);
    List L2=MakeEmpty(NULL);

    Insert(11,L1,L1);
    Insert(2,L1,L1);
    Insert(1,L1,L1);

    PrintList(L1);

    Insert(33,L2,L2);
    Insert(31,L2,L2);
    Insert(11,L2,L2);

    PrintList(L2);

    printf("%d", compare(L1,L2));


    return 7;
}

int compare (List L1,List L2){
    List ptr = L2;
    while (L1->Next != NULL){
        L1=L1->Next;
        while(L2->Next != NULL){
            L2=L2->Next;
            if (L1->Data == L2->Data)
                return 0;
        }
        L2=ptr;
    }
    return 1;
}

int compare1 (List L1,List L2){
    if (L1->Next == NULL || L2->Next == NULL)
        return 1 ;
    else if (L1->Next->Data == L2->Next->Data)
        return 0 ;
    else if (L1->Next->Data < L2->Next->Data)
        return compare1(L1->Next,L2);
    else
        return compare1(L1,L2->Next);
}

int size (List L){
    Position ptr = L->Next;
    int count=0 ;
    while (ptr != NULL){
        count++;
        ptr=ptr->Next;
    }
    return count;
}

int IsEmpty(List L){
    return L->Next == NULL;
}

int IsLast(List P,List L){
    return P->Next == NULL;

}

Position FindPrevious(int X,List L){
    Position P;
    P = L;
    while(P->Next != NULL && P->Next->Data != X)
        P = P->Next;
    return P;
}

Position Find(int X,List L){
    Position P;
    P = L->Next;
    while(P != NULL && P->Data != X)
        P = P->Next;
    return P;
}

void Delete(int X,List L){
    Position P, temp;
    P = FindPrevious(X, L);
    if( !IsLast(P, L) ){
        temp = P->Next;
        P->Next = temp->Next;
        free(temp);
    }
}

void Insert(int X,List L,List P){
    Position temp;
    temp = (Position)malloc(sizeof(struct node));
    temp->Data = X;
    temp->Next = P->Next;
    P->Next = temp;
}

void PrintList(List L){
    Position P = L;
    if( IsEmpty(L))
        printf("Empty list\n");
    else
    do{
        P=P->Next;
        printf("%d\t", P->Data);
    }while( !IsLast(P, L) );
    printf("\n");
}

void DeleteList(List L){
    Position P, temp;
    P = L->Next;
    L->Next = NULL;
    while(P != NULL){
        temp = P->Next;
        free(P);
        P=temp;
    }
}

List MakeEmpty(List L){
    if(L != NULL)
        DeleteList( L );
    L = (List)malloc(sizeof(struct node));
    if(L == NULL)
        printf("Out of memory!\n");
    L->Next = NULL;
    return L;
}

/*
void reverse(List L) {
  Position current = L->Next;
  Position temp = NULL;
  int flag = 1 ;

 if (current == NULL || current->Next == NULL)
    return ;

  while (current != NULL) {
    temp = current->Prev;
    current->Prev = current->Next;
    current->Next = temp;
    if (flag){
        flag--;
        current->Next = NULL ;
    }
    current = current->Prev;
  }

  if (temp != NULL) {
    L->Next = temp->Prev;
    L->Next->Prev = L ;
  }
}
*/