#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

typedef struct {
    int* data;
    int capacity;
    int size;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->data = (int*)malloc(capacity * sizeof(int));
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int index) {
    int parent = (index - 1) / 2;
    if (parent >= 0 && heap->data[index] < heap->data[parent]) {
        swap(&heap->data[index], &heap->data[parent]);
        heapifyUp(heap, parent);
    }
}

void heapifyDown(MinHeap* heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = 0;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;

    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}

void insert(MinHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap is full. Cannot insert any more elements.\n");
        return;
    }

    heap->data[heap->size] = value;
    heapifyUp(heap, heap->size);
    heap->size++;
}

int extractMin(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty. Cannot extract minimum element.\n");
        return -1;
    }

    int min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return min;
}

void editElement(MinHeap* heap,int index, int newValue) {
    if (index < 0 || index >= heap->size) {
        printf("Invalid index.\n");
        return;
    }

    int oldValue = heap->data[index];
    heap->data[index] = newValue;

    if (newValue < oldValue) {
        heapifyUp(heap, index);
    } else if (newValue > oldValue) {
        heapifyDown(heap, index);
    }
}

int main() {
    MinHeap* heap = createMinHeap(7);

    insert(heap, 4);
    insert(heap, 8);
    insert(heap, 2);
    insert(heap, 5);
    insert(heap, 3);

    printHeap(heap);
    editElement(heap,1,1);
    printHeap(heap);

    int min = extractMin(heap);
    printf("Extracted minimum: %d\n", min);
    printf("Extracted minimum: %d\n",extractMin(heap));
    printf("Extracted minimum: %d\n",extractMin(heap));
    printf("Extracted minimum: %d\n",extractMin(heap));
    printf("Extracted minimum: %d\n",extractMin(heap));
    printf("Extracted minimum: %d\n",extractMin(heap));


    destroyHeap(heap);

    return 0;
}