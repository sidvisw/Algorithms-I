#include <bits/stdc++.h>
using namespace std;
struct node
{
    node *parent;
    int rank;
};
void makeSet(node *&p)
{
    p = new node;
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

struct Triplet
{
    int p1, p2, t;
};

void merging_func(Triplet points[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Triplet L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = points[l + i];
    for (j = 0; j < n2; j++)
        R[j] = points[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].t <= R[j].t)
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
void mergesort(Triplet arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merging_func(arr, l, m, r);
    }
}
bool allFriends(node **person, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (findSet(person[i]) != findSet(person[j]))
                return false;
        }
    }
    return true;
}
main()
{
    int n;
    cin >> n;
    node **person = new node *[n];
    for (int i; i < n; i++)
    {
        makeSet(person[i]);
    }
    int m;
    cin >> m;
    Triplet T[m];
    for (int i = 0; i < m; i++)
    {
        cin >> T[i].p1 >> T[i].p2 >> T[i].t;
    }
    mergesort(T, 0, m - 1);
    int time = 0;
    for (int i = 0; i < m; i++)
    {
        if (!allFriends(person, n))
        {
            node *a = findSet(person[T[i].p1]);
            node *b = findSet(person[T[i].p2]);
            if (a != b)
            {
                time = T[i].t;
                mergeSet(a, b);
            }
        }
        else
        {
            break;
        }
    }
    cout << time << endl;
}