#include <stdio.h>
#include <stdlib.h>

typedef struct avl_node* AVLNode;
typedef AVLNode AVLTree;

int max(int a, int b);
int height(AVLNode T);
AVLTree createAVLTree();
AVLNode Find(int X, AVLTree T);
int FindCount(int X, AVLTree T);
AVLNode singleRotateWithLeft(AVLNode K2);
AVLNode singleRotateWithRight(AVLNode K1);
AVLNode doubleRotateWithLeft(AVLNode K3);
AVLNode doubleRotateWithRight(AVLNode K1);
int getBalance(AVLNode T);
AVLTree Insert(int X, AVLTree T);
AVLNode findMin(AVLTree T);
AVLTree Delete(int X, AVLTree T);

struct avl_node{
    int element;
    AVLNode left;
    AVLNode right;
    int height;
};

int main(){
    AVLTree a = createAVLTree();

    a = Insert(1,a);
    a = Insert(2,a);
    a = Insert(3,a);

    return 0;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode T) {
    if (T == NULL) {
        return -1;
    }
    else {
        return T->height;
    }
}

AVLTree createAVLTree() {
    return NULL;
}

AVLNode Find(int X, AVLTree T) {
    if (T == NULL) {
        return NULL;
    } else if (X < T->element) {
        return Find(X, T->left);
    } else if (X > T->element) {
        return Find(X, T->right);
    } else {
        return T;
    }
}

AVLNode singleRotateWithLeft(AVLNode K2) {
    AVLNode K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;
    K2->height = max(height(K2->left), height(K2->right)) + 1;
    K1->height = max(height(K1->left), K2->height) + 1;
    return K1;
}

AVLNode singleRotateWithRight(AVLNode K1) {
    AVLNode K2 = K1->right;
    K1->right = K2->left;
    K2->left = K1;
    K1->height = max(height(K1->left), height(K1->right)) + 1;
    K2->height = max(height(K2->right), K1->height) + 1;
    return K2;
}

AVLNode doubleRotateWithLeft(AVLNode K3) {
    K3->left = singleRotateWithRight(K3->left);
    return singleRotateWithLeft(K3);
}

AVLNode doubleRotateWithRight(AVLNode K1) {
    K1->right = singleRotateWithLeft(K1->right);
    return singleRotateWithRight(K1);
}

int getBalance(AVLNode T) {
    if (T == NULL) {
        return 0;
    } else {
        return height(T->left) - height(T->right);
    }
}

AVLTree Insert(int X, AVLTree T) {
    if (T == NULL) {
        T = (AVLTree)malloc(sizeof(struct avl_node));
        if (T == NULL) {
            printf("Out of memory!\n");
            exit(1);
        }
        T->element = X;
        T->height = 0;
        T->left = T->right = NULL;
    } else if (X < T->element) {
        T->left = Insert(X, T->left);
        if (height(T->left) - height(T->right) == 2) {
            if (X < T->left->element) {
                T = singleRotateWithLeft(T);
            } else {
                T = doubleRotateWithLeft(T);
            }
        }
    } else if (X > T->element) {
        T->right = Insert(X, T->right);
        if (height(T->right) - height(T->left) == 2) {
            if (X > T->right->element) {
                T = singleRotateWithRight(T);
            } else {
                T = doubleRotateWithRight(T);
            }
        }
    }
    T->height = max(height(T->left), height(T->right)) + 1;
    return T;
}

AVLNode findMin(AVLTree T) {
    if (T == NULL) {
        return NULL;
    } else if (T->left == NULL) {
        return T;
    } else {
        return findMin(T->left);
    }
}

AVLTree Delete(int X, AVLTree T) {
    AVLNode temp;
    if (T == NULL) {
        printf("Element not found\n");
        return T;
    }
    else if (X < T->element) {
        T->left = Delete(X, T->left);
        if (height(T->right) - height(T->left) == 2) {
            if (height(T->right->left) > height(T->right->right)) {
                T = doubleRotateWithRight(T);
            } else {
                T = singleRotateWithRight(T);
            }
        }
    }
    else if (X > T->element) {
        T->right = Delete(X, T->right);
        if (height(T->left) - height(T->right) == 2) {
            if (height(T->left->right) > height(T->left->left)) {
                T = doubleRotateWithLeft(T);
            } else {
                T = singleRotateWithLeft(T);
            }
        }
    }
    else {
        if (T->left == NULL && T->right == NULL) {
            free(T);
            T = NULL;
        } else if (T->left == NULL) {
            temp = T;
            T = T->right;
            free(temp);
        } else if (T->right == NULL) {
            temp = T;
            T = T->left;
            free(temp);
        } else {
            temp = findMin(T->right);
            T->element = temp->element;
            T->right = Delete(T->element, T->right);
            if (height(T->left) - height(T->right) == 2) {
                if (height(T->left->right) > height(T->left->left)) {
                    T = doubleRotateWithLeft(T);
                } else {
                    T = singleRotateWithLeft(T);
                }
            }
        }
    }

    if (T != NULL) {
        T->height = max(height(T->left), height(T->right)) + 1;
    }

    return T;
}

