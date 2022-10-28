#include <bits/stdc++.h>
using namespace std;
//heap ADT starts
struct heap
{
    int list[100];
    int size;
};
void initHeap(heap *&H)
{
    H->size = 0;
}
void heapify(heap *H, int index)
{
    while (index > 1)
    {
        if (H->list[index] <= H->list[index / 2])
            return;
        swap(H->list[index], H->list[index / 2]);
        index = index / 2;
    }
}
void insert(heap *H, int item)
{
    H->list[H->size + 1] = item;
    H->size++;
    heapify(H, H->size);
}
bool findMax(heap *H, int &item)
{
    if (H->size == 0)
        return false;
    item = H->list[1];
    return true;
}
void maxHeapify(heap *H, int index)
{
    while (true)
    {
        int l = 2 * index;
        int r = 2 * index + 1;
        if (l > H->size)
            return;
        int maxIndex = r;
        if (r > H->size || H->list[l] > H->list[r])
            maxIndex = l;
        if (H->list[index] > H->list[maxIndex])
            return;
        swap(H->list[index], H->list[maxIndex]);
        index = maxIndex;
    }
}
void deleteMax(heap *H)
{
    H->list[1] = H->list[H->size];
    H->size--;
    maxHeapify(H, 1);
}
void buildHeap(heap *H, int arr[], int size)
{
    for (int i = 1; i <= size; i++)
    {
        H->list[i] = arr[i-1];
    }
    H->size = size;
    for (int i = size / 2; i >= 1; i--)
    {
        maxHeapify(H, i);
    }
}
//heap ADT ends

//driver function
main()
{
    heap *myHeap=new heap;
    initHeap(myHeap);
    int n;
    cin >> n;
    int arr[n];

    //buildHeap with O(nlogn) complexity
    // for (int i = 0; i < n; i++)
    // {
    //     int item;
    //     cin>>item;
    //     insert(myHeap,item);
    // }

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    //buildHeap with O(n) complexity
    buildHeap(myHeap, arr, n);

    //implemented heap sort
    for (int i = 0; i < n; i++)
    {
        int item;
        findMax(myHeap, item);
        cout << item << " ";
        deleteMax(myHeap);
    }
}