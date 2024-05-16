#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node* Node;

Node MakeEmpty(Node T);
Node Find(int X, Node T);
Node FindMin(Node T);
Node FindMax(Node T);
Node Insert(int X, Node T);
Node Delete(int X, Node T);
//int isBST(Node root);
//int isBSTUtil(Node node, int min, int max);

struct Node{
    int Element;
    Node Left;
    Node Right;
};


int main(){

}

Node MakeEmpty(Node T){
    if(T != NULL){
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Node Find(int X, Node T){
    if( T == NULL)
        return NULL;
    else if( X < T->Element )
        return Find( X, T->Left );
    else if( X > T->Element )
        return Find(X, T->Right);
    else
        return T;
}

Node FindMin(Node T){
    if(T == NULL)
        return NULL;
    else if(T -> Left == NULL)
        return T;
    else
        return FindMin(T->Left );
}

Node FindMax(Node T){
    if(T == NULL)
        return NULL;
    else if(T -> Right == NULL)
        return T;
    else
        return FindMax(T->Right);
}

Node Insert(int X, Node T){
    if( T == NULL){
        T = (Node)malloc(sizeof( struct Node ) );
        if( T == NULL)
            printf("Out of space");
        else{
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    }
    else if( X < T->Element )
        T->Left = Insert( X, T->Left);
    else if( X > T->Element)
        T->Right = Insert( X, T->Right );
    return T;
}

Node Delete(int X, Node T){
    Node TmpCell;
    if(T == NULL)
        printf( "Element not found" );
    else if( X < T->Element )
        T->Left = Delete( X, T->Left );
    else if( X > T->Element )
        T->Right = Delete( X, T->Right );
    else
        if( T->Left && T->Right ){
            TmpCell = FindMin( T->Right );
            T->Element = TmpCell->Element;
            T->Right = Delete( T->Element, T->Right );
        }
        else{
            TmpCell = T;
            if( T->Left == NULL )
                T = T->Right;
            else if( T->Right == NULL )
                T = T->Left;
            free(TmpCell);
        }
    return T;
}

//int isBSTUtil(Node node, int min, int max) {
//    if (node == NULL)
//        return 1;
//
//    if (node->Element < min || node->Element > max)
//        return 0;
//
//    return isBSTUtil(node->Left, min, node->Element) && isBSTUtil(node->Right, node->Element, max);
//}
//
//int isBST(Node root) {
//    Node max =  FindMax(root) ;
//    Node min =  FindMin(root) ;
//    return isBSTUtil(root, min->Element, max->Element);
//}
