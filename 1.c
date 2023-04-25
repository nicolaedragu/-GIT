#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];
int size = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < size && heap[left] > heap[largest])
    {
        largest = left;
    }

    if (right < size && heap[right] > heap[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(&heap[i], &heap[largest]);
        max_heapify(largest);
    }
}

void insert(int value)
{
    if (size >= MAX_HEAP_SIZE)
    {
        printf("Heap overflow!\n");
        return;
    }

    heap[size++] = value;
    int i = size - 1;

    while (i != 0 && heap[(i - 1) / 2] < heap[i])
    {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extract_max()
{
    if (size <= 0)
    {
        printf("Heap underflow!\n");
        return -1;
    }

    int max = heap[0];
    heap[0] = heap[size - 1];
    size--;
    max_heapify(0);

    return max;
}

void print_heap()
{
    printf("Max-Heap: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main()
{
    insert(4);
    insert(8);
    insert(3);
    insert(7);
    insert(1);

    print_heap();

    printf("Max element: %d\n", extract_max());

    print_heap();

    return 0;
}