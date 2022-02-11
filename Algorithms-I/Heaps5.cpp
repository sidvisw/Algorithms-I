#include <bits/stdc++.h>
using namespace std;
struct crane
{
    int index;
    int l, r, k;
};

//heap ADT starts
struct heap
{
    crane list[100001];
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
        if (H->list[index].r <= H->list[index / 2].r)
            return;
        swap(H->list[index], H->list[index / 2]);
        index = index / 2;
    }
}
void insert(heap *H, crane item)
{
    H->list[H->size + 1] = item;
    H->size++;
    heapify(H, H->size);
}
crane *findMax(heap *H)
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
        if (r > H->size || H->list[l].r > H->list[r].r)
            maxIndex = l;
        if (H->list[index].r > H->list[maxIndex].r)
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
void buildHeap(heap *H, crane arr[], int size)
{
    for (int i = 1; i <= size; i++)
    {
        H->list[i] = arr[i - 1];
    }
    H->size = size;
    for (int i = H->size / 2; i >= 1; i--)
    {
        maxHeapify(H, i);
    }
}
//heap ADT ends

bool allDead(int z[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (z[i] != 0)
            return false;
    }
    return true;
}

main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        int z[n];
        for (int i = 0; i < n; i++)
        {
            cin >> z[i];
        }
        crane c[m];
        for (int i = 0; i < m; i++)
        {
            cin >> c[i].l >> c[i].r >> c[i].k;
            c[i].l--;
            c[i].r--;
            c[i].index = i;
        }

        int i,beamCtr = 0;
        for (i = 0; i < n; i++)
        {
            heap *H = new heap;
            initHeap(H);
            crane arr[m];
            int size = 0;
            for (int j = 0; j < m; j++)
            {
                if (c[j].l <= i && c[j].k != 0)
                {
                    arr[size++] = c[j];
                }
            }
            buildHeap(H, arr, size);
            while (z[i] != 0)
            {
                crane*ptr=findMax(H);
                if(ptr!=NULL){
                    beamCtr++;
                    ptr->k--;
                    c[ptr->index].k--;
                    for(int j=ptr->l;j<=ptr->r;j++){
                        z[j]--;
                    }
                    if(ptr->k==0){
                        deleteMax(H);
                    }
                }
                else{
                    cout<<"NO"<<endl;
                    break;
                }
            }
            delete H;
            if(z[i]!=0)break;
        }
        if(i>=n){
            cout<<"YES "<<beamCtr<<endl;
        }
    }
}