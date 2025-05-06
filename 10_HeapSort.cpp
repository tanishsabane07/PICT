// Implement the Heap sort algorithm using heap data structure with
// modularity of programming language.

#include<iostream>
using namespace std;

void heapify(int arr[], int size)
{
    int parent = 1;

    while(parent <= size/2)
    {
        int left = parent * 2;
        int right = parent * 2 + 1;
        int largest = parent;

        if(left <= size && arr[left] > arr[largest])
        {
            largest = left;
        }
        if(right <= size && arr[right] > arr[largest])
        {
            largest = right;
        }

        if(largest != parent)
        {
            swap(arr[parent], arr[largest]);
            parent = largest;
        }
        else
        {
            break;
        }
    }
}

int main()
{
    int arr[8] = {0, 6, 17, 32, 19, 20, 21, 22};
//    index:         01, 02, 03, 04, 05, 06, 07

    for(int i = 2; i<8; i++)
    {
        int index = i;
        int parent = i/2;
        while(parent >= 1 && arr[index] > arr[parent])
        {
            swap(arr[parent], arr[index]);
            index = parent;
            parent = parent/2;
        }
    }

    int size = 7;

    for(int i = 1; i<8; i++)
    {
        swap(arr[1], arr[size]);
        size--;
        heapify(arr, size);
    }

    for(int i = 1; i<8; i++)
    {
        cout<<arr[i]<<" ";
    }

    return 0;
}