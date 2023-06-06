#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}
void heapify(int array[], int size, int i)
{
    if (size == 1)
    {
        return;
    }
    else
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < size && array[largest] < array[left])
        {
            largest = left;
        }
        if (right < size && array[largest] < array[right])
        {
            largest = right;
        }
        if (largest != i)
        {
            swap(&array[i], &array[largest]);
            heapify(array, size, largest);
        }
    }
}

void print_array(int v[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void build_heap(int arr[], int size)
{
    int i = size / 2 - 1;
    for (int j = i; j >= 0; j--)
    {
        heapify(arr, size, j);
    }
}

void insert(int array[], int new, int *size)
{
    if (*size == 0)
    {
        array[0] = new;
        *size += 1;
    }
    else
    {
        array[*size] = new;
        *size += 1;
        for (int i = *size / 2 - 1; i >= 0; i--)
        {
            heapify(array, *size, i);
        }
    }
}

void delete_root(int array[], int num, int *size)
{
    int i;
    for (i = 0; i < *size; i++)
    {
        if (num == array[i])
            break;
    }
    swap(&array[i], &array[*size - 1]);

    *size -= 1;
    for (i = *size / 2 - 1; i >= 0; i--)
    {
        heapify(array, *size, i);
    }
}

void heapsort(int arr[], int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    int v[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    int size = sizeof(v) / sizeof(v[0]);
    print_array(v, size);
    build_heap(v, size);
    print_array(v, size);
    insert(v, 100, &size);
    print_array(v, size);
    delete_root(v, 3, &size);
    print_array(v, size);
    heapsort(v, size);
    print_array(v, size);
    return 0;
}