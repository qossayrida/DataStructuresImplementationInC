#include<stdio.h>
#include <stdlib.h>
#define MinQueueSize 5

typedef struct QueueRecord* Queue;

int IsEmpty( Queue Q );
int IsFull( Queue Q );
Queue MakeQueue(int MaxElements);
void MakeEmpty(Queue Q);
void DisposeQueue(Queue Q);
int Succ(int Value, Queue Q);
void Enqueue(int X, Queue Q);
int Front(Queue Q);
void Dequeue(Queue Q);
int FrontAndDequeue(Queue Q);

struct QueueRecord{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    int *Array;
};

int main(){
    Queue q = MakeQueue(12);

    for(int i=0; i<10; i++ )
        Enqueue(i, q);

    while( !IsEmpty(q))
        printf("%d\n", FrontAndDequeue(q));

    DisposeQueue (q);
    return 0;
}

int IsEmpty(Queue Q){
    return Q->Size == 0;
}

int IsFull(Queue Q){
    return Q->Size == Q->Capacity;
}

Queue MakeQueue(int MaxElements){
    Queue Q;
    if( MaxElements < MinQueueSize )
        printf("Queue size is too small\n");
    Q = (Queue)malloc(sizeof( struct QueueRecord ));
    if( Q == NULL)
        printf("Out of space");
    Q->Array = (int*)malloc(sizeof(int) * MaxElements);
    if( Q->Array == NULL )
        printf("Out of space");
    Q->Capacity = MaxElements;
    MakeEmpty(Q);
    return Q;
}

void MakeEmpty(Queue Q){
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

void DisposeQueue(Queue Q){
    if( Q != NULL ){
        free( Q->Array );
        free( Q );
    }
}

int Succ(int Value, Queue Q){
    if( ++Value == Q->Capacity )
        Value = 0;
    return Value;
}

void Enqueue(int X, Queue Q){
    if( IsFull( Q ) )
        printf("Full Queue");
    else{
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
    }
}

int Front(Queue Q){
    if(!IsEmpty(Q))
        return Q->Array[ Q->Front ];
    printf("Empty Queue!");
    return 0;
}

void Dequeue(Queue Q){
    if(IsEmpty(Q))
        printf("Empty Queue!");
    else{
        Q->Size--;
        Q->Front = Succ( Q->Front, Q );
    }
}

int FrontAndDequeue(Queue Q){
    int X = 0;
    if(IsEmpty(Q))
        printf("Empty Queue!");
    else{
        Q->Size--;
        X = Q->Array[ Q->Front ];
        Q->Front = Succ( Q->Front, Q );
    }
    return X;
}
