#include <bits/stdc++.h>
using namespace std;
typedef struct
{
    int x;
    int y;
} key;
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
        if (L[i].x <= R[j].x)
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
key *merge(key *left, int n1, key *right, int n2)
{
    key *result = new key[n1 + n2];
    int i, j, k = 0, last_seen_ht_left = 0, last_seen_ht_right = 0;
    for (i = 0, j = 0; i < n1 && j < n2;)
    {
        if (left[i].x < right[j].x)
        {
            last_seen_ht_left = left[i].y;
            result[k++] = {left[i].x, max(last_seen_ht_left, last_seen_ht_right)};
            i++;
        }
        else if (left[i].x == right[j].x)
        {
            if (left[i].y > right[j].y)
            {
                last_seen_ht_left = left[i].y;
                result[k++] = {left[i].x, max(last_seen_ht_left, last_seen_ht_right)};
                i++;
            }
            else
            {
                last_seen_ht_right = right[j].y;
                result[k++] = {right[j].x, max(last_seen_ht_left, last_seen_ht_right)};
                j++;
            }
        }
        else
        {
            last_seen_ht_right = right[j].y;
            result[k++] = {right[j].x, max(last_seen_ht_left, last_seen_ht_right)};
            j++;
        }
    }
    while (i < n1)
    {
        result[k++] = left[i];
        i++;
    }
    while (j < n2)
    {
        result[k++] = right[j];
        j++;
    }
    return result;
}

key *get_def_vis(int a[][3], int beg, int end)
{
    if (beg == end)
    {
        key *result = new key[2];
        result[0].x = a[beg][0];
        result[0].y = a[beg][2];
        result[1].x = a[beg][1];
        result[1].y = 0;
        return result;
    }
    else
    {
        int mid = (beg + end) / 2;
        key *left = new key[2 * (mid - beg + 1)], *right = new key[2 * (end - mid)];
        left = get_def_vis(a, beg, mid);
        right = get_def_vis(a, mid + 1, end);
        return merge(left, 2 * (mid - beg + 1), right, 2 * (end - mid));
    }
}

main()
{
    int a[50][3];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    // mergesort(points, 0, n - 1);
    key *result = new key[2 * n];
    result = get_def_vis(a, 0, n - 1);
    key finalresult[100];
    int k = 0;
    key prev = {-1, -1};
    for (int i = 0; i < 2 * n; i++)
    {
        if (prev.y != result[i].y && prev.x != result[i].x)
        {
            finalresult[k++] = result[i];
            prev = result[i];
        }
    }
    finalresult[k - 1].y = 0;
    for (int i = 0; i < k; i++)
    {
        cout << finalresult[i].x << " " << finalresult[i].y << endl;
    }
}