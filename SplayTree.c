#include<stdio.h>
#include<stdlib.h>

typedef struct Node* newNode;
typedef newNode SplayTree;

SplayTree splay(int key,SplayTree root);
SplayTree Insert(int X,SplayTree T);
SplayTree search(int key,SplayTree root);
newNode rightRotate(newNode x);
newNode leftRotate(newNode x);

struct Node {
    int Element;
    newNode Left;
    newNode Right;
};

int main(){

}

SplayTree Insert(int X,SplayTree T){
    if( T == NULL){
        T = (newNode)malloc(sizeof(struct Node));
        if( T == NULL)
            printf("Out of space");
        else{
            T->Element= X;
            T->Left = T->Right = NULL;
        }
    }
    else if( X < T->Element )
        T->Left = Insert( X, T->Left);
    else if( X > T->Element)
        T->Right = Insert( X, T->Right );

    T=splay(X,T);
    return T;
}

newNode rightRotate(newNode x) {
    newNode y = x->Left;
    x->Left = y->Right;
    y->Right = x;
    return y;
}

newNode leftRotate(newNode x) {
    newNode y = x->Right;
    x->Right = y->Left;
    y->Left = x;
    return y;
}

SplayTree splay(int key,SplayTree root){

    if (root == NULL || root->Element == key)
        return root;

    if (root->Element > key) {
        if (root->Left == NULL)
            return root;

        if (root->Left->Element > key){ // Zig-Zig (Left Left)
            // First recursively bring the key as root of left-left
            root->Left->Left = splay(key,root->Left->Left);
            // Do first rotation for root, second rotation is done after else
            root = rightRotate(root);
        }
        else if (root->Left->Element < key){// Zig-Zag (Left Right)
            // First recursively bring the key as root of left-right
            root->Left->Right = splay(key,root->Left->Right);
            // Do first rotation for root->left
            if (root->Left->Right != NULL)
                root->Left = leftRotate(root->Left);
        }

        // Do second rotation for root
        return (root->Left == NULL) ? root : rightRotate(root);
    }
    else{// Key lies in right subtree
        // Key is not in tree, we are done
        if (root->Right == NULL)
            return root;


        if (root->Right->Element > key) {// Zag-Zig (Right Left)
            // Bring the key as root of right-left
            root->Right->Element = splay(key,root->Right->Left);
            // Do first rotation for root->right
            if (root->Right->Left != NULL)
                root->Right = rightRotate(root->Right);
        }
        else if (root->Right->Element < key){// Zag-Zag (Right Right)
            // Bring the key as root of right-right and do first rotation
            root->Right->Right = splay(key,root->Right->Right);
            root = leftRotate(root);
        }

        // Do second rotation for root
        return (root->Right == NULL) ? root : leftRotate(root);
    }
}

SplayTree search(int key,SplayTree root) {
    return splay(key, root);
}
