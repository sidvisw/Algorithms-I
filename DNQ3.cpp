#include <bits/stdc++.h>
using namespace std;
int median_find(int a[], int a_size, int b[], int b_size)
{
    int a_beg = 0;
    int a_end = a_size - 1;
    int b_beg = 0;
    int b_end = b_size - 1;
    int x = (a_size + b_size) / 2;
    while (true)
    {
        int a_mid = (a_beg + a_end) / 2;
        int b_mid = (b_beg + b_end) / 2;
        if (a[a_mid] > b[x - a_mid - 1] && a[a_mid] <= b[x - a_mid])
        {
            return a[a_mid];
        }
        else if (a[a_mid] < b[x - a_mid])
            a_beg = a_mid + 1;
        else
            a_end = a_mid - 1;
        if (b[b_mid] > a[x - b_mid - 1] && b[b_mid] <= a[x - b_mid])
        {
            return b[b_mid];
        }
        else if (b[b_mid] < a[x - b_mid])
            b_beg = b_mid + 1;
        else
            b_end = b_mid - 1;
    }
}
main()
{
    int a[20], b[20];
    int a_size, b_size;
    for (int i = 0; i < 20; i++)
    {
        a[i]=b[i]=INT_MAX;
    }
    cin >> a_size;
    for (int i = 0; i < a_size; i++)
    {
        cin >> a[i];
    }
    cin >> b_size;
    for (int i = 0; i < b_size; i++)
    {
        cin >> b[i];
    }
    int median = median_find(a, a_size, b, b_size);
    cout << median << endl;
}