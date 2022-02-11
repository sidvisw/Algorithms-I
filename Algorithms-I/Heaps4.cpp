#include<bits/stdc++.h>
using namespace std;
struct Pair
{
    int index,value;
};

//heap ADT starts
struct heap
{
    Pair list[1000001];
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
        if (H->list[index].value <= H->list[index / 2].value)
            return;
        swap(H->list[index], H->list[index / 2]);
        index = index / 2;
    }
}
void insert(heap *H, Pair item)
{
    H->list[H->size + 1] = item;
    H->size++;
    heapify(H, H->size);
}
Pair* findMax(heap *H)
{
    if (H->size == 0)
        return NULL;
    return &(H->list[1]);
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
        if (r > H->size || H->list[l].value > H->list[r].value)
            maxIndex = l;
        if (H->list[index].value > H->list[maxIndex].value)
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
void buildHeap(heap *H, Pair arr[], int size)
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
    int m,n;
    cin>>m>>n;
    Pair x[m];
    for (int i = 0; i < m; i++)
    {
        x[i].index=i;
        cin>>x[i].value;
    }
    heap*H=new heap;
    initHeap(H);
    buildHeap(H,x,m);
    int money=0;
    for (int i = 0; i < n; i++)
    {
        Pair *p;
        p=findMax(H);
        if(p!=NULL){
            money+=p->value;
            p->value--;
            maxHeapify(H,1);
        }
    }
    cout<<money<<endl;
}