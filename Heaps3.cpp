#include<bits/stdc++.h>
using namespace std;
//heap ADT starts
struct heap
{
    int list[100001];
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

main()
{
    int n;
    cin>>n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin>>arr[i];
    }
    heap*H=new heap;
    initHeap(H);
    cout<<"-1"<<endl<<"-1"<<endl;
    insert(H,arr[0]);
    insert(H,arr[1]);
    for (int i = 2; i < n; i++)
    {
        insert(H,arr[i]);
        int prod=1;
        prod*=H->list[1];
        int maxindex=2;
        int minindex=3;
        if(H->list[3]>H->list[2]){
            maxindex=3;
            minindex=2;
        }
        prod*=H->list[maxindex];
        int num1=H->list[minindex];
        int num2=(2*maxindex<=H->size)?H->list[2*maxindex]:INT_MIN;
        int num3=(2*maxindex<=H->size)?H->list[2*maxindex+1]:INT_MIN;
        prod*=max({num1,num2,num3});
        cout<<prod<<endl;
    }
}