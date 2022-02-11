#include <bits/stdc++.h>
using namespace std;
struct key
{
    int v1, v2;
    int w;
};
void merging_func(key points[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    key L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = points[l + i];
    for (j = 0; j < n2; j++)
        R[j] = points[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].w <= R[j].w)
        {
            points[k] = L[i];
            i++;
        }
        else
        {
            points[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        points[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        points[k] = R[j];
        j++;
        k++;
    }
}
void mergesort(key arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);

        merging_func(arr, l, m, r);
    }
}
struct node
{
    node *parent;
    int rank;
};
void makeSet(node *&p)
{
    p=new node;
    p->rank = 0;
    p->parent = p;
}
node *findSet(node *ptr)
{
    if (ptr->parent != ptr)
    {
        ptr->parent = findSet(ptr->parent);
    }
    return ptr->parent;
}
bool mergeSet(node *x, node *y)
{
    if (x == y)
        return false;
    if (x->rank < y->rank)
    {
        x->parent = y;
    }
    else if (x->rank > y->rank)
    {
        y->parent = x;
    }
    else
    {
        x->parent = y;
        y->rank++;
    }
    return true;
}
void getMinSpanTree(key*edges,int n,int m,key F[],int&sizeF){
    node**arr=new node*[n];
    for (int i = 0; i < n; i++)
    {
        makeSet(arr[i]);
    }
    for (int i = 0; i < m; i++)
    {
        node*a=findSet(arr[edges[i].v1]);
        node*b=findSet(arr[edges[i].v2]);
        if(a!=b){
            mergeSet(a,b);
            F[sizeF++]=edges[i];
        }
    }
}
main()
{
    int n, m;
    cin >> n >> m;
    key *edges=new key[m];
    for (int i = 0; i < m; i++)
    {
        cin>>edges[i].v1>>edges[i].v2>>edges[i].w;
    }
    mergesort(edges,0,m-1);
    key F[m];
    int sizeF = 0;
    getMinSpanTree(edges,n, m, F, sizeF);
    int minSpanMat[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            minSpanMat[i][j]=-1;
        }
    }
    
    for (int i = 0; i < sizeF; i++)
    {
        minSpanMat[F[i].v1][F[i].v2]=F[i].w;
        minSpanMat[F[i].v2][F[i].v1]=F[i].w;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout<<minSpanMat[i][j]<<" ";
        }
        cout<<endl;
    }
    
}