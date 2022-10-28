#include <bits/stdc++.h>
using namespace std;
int *mergeArray(int *, int, int *, int);
int *mergesort(int *a, int beg, int end)
{
    if (beg >= end)
        return a + beg;
    else
    {
        int mid = (beg + end) / 2;
        return mergeArray(mergesort(a, beg, mid), mid - beg + 1, mergesort(a, mid + 1, end), end - mid);
    }
}
int *mergeArray(int *a, int size1, int *b, int size2)
{
    int *c = new int[size1 + size2], k = 0;
    int i, j;
    for (i = 0, j = 0; i < size1 && j < size2;)
    {
        if (a[i] < b[j])
        {
            c[k++] = a[i++];
        }
        else if (a[i] > b[i])
        {
            c[k++] = b[j++];
        }
        else
        {
            c[k++] = a[i++];
            c[k++] = b[j++];
        }
    }
    while (i < size1)
    {
        c[k++] = a[i++];
    }
    while (j < size2)
    {
        c[k++] = b[j++];
    }
    return c;
}
int binarysearch(int *a, int beg, int last, int key)
{
    if (beg>=last){
        if(a[beg]==key) return beg;
        else return -1;
    }
    int mid = (beg + last) / 2;
    if (a[mid] == key)
        return mid;
    else if (a[mid] < key)
        return binarysearch(a, mid + 1, last, key);
    else
        return binarysearch(a, beg, mid - 1, key);
}
main()
{
    int *a;
    int n;
    cin >> n;
    a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int key;
    cin >> key;
    int *c=new int[n];
    c = mergesort(a, 0, n - 1);
    int index = binarysearch(a, 0, n - 1, key);
    for (int i = 0; i < n; i++)
    {
        cout << c[i] << " ";
    }
    cout << endl
         << index;
}