#include <bits/stdc++.h>
using namespace std;
struct range
{
    int l, r;
};
int find_m(range R[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (R[i].r > max)
        {
            max = R[i].r;
        }
    }
    return max;
}
bool nextPermute(int A[], int n)
{
    int pos = -1;
    for (int i = 0; i < n - 1; i++)
    {
        if (A[i] < A[i + 1])
            pos = i;
    }
    if (pos == -1)
        return false;
    int swapPos = n - 1;
    while (A[pos] > A[swapPos])
        swapPos -= 1;
    swap(A[pos], A[swapPos]);
    while (pos + 1 < n - 1)
    {
        swap(A[pos + 1], A[n - 1]);
        pos++;
        n--;
    }
    return true;
}
bool isPossible(range R[], int A[], int n, int mid)
{
    int x = R[A[0]].l;
    for (int i = 1; i < n; i++)
    {
        x = max(R[A[i]].l, x + mid);
        if (x > R[A[i]].r)
            return false;
    }
    return true;
}
void printTimings(range R[], int A[], int n, int maxL){
    int x[n];
    x[A[0]]=R[A[0]].l;
    for (int i = 1; i < n; i++)
    {
        x[A[i]]=max(R[A[i]].l,x[A[i-1]]+maxL);
    }
    for (int i = 0; i < n; i++)
    {
        cout<<x[i]<<" ";
    }
    cout<<endl;
}
main()
{
    int n, m;
    cin >> n;
    range R[n];
    for (int i = 0; i < n; i++)
    {
        cin >> R[i].l >> R[i].r;
    }
    m = find_m(R, n);
    int A[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = i;
    }
    bool cond = true;
    int maxL = 0;
    int correctOrder[n];
    while (cond)
    {
        int beg = 1, end = m;
        while (beg <= end)
        {
            int mid = (beg + end) / 2;
            if (isPossible(R, A, n, mid))
            {
                if (mid > maxL)
                {
                    maxL = mid;
                    for (int i = 0; i < n; i++)
                    {
                        correctOrder[i] = A[i];
                    }
                }
                beg = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }
        cond = nextPermute(A, n);
    }
    cout << maxL << endl;
    printTimings(R, correctOrder, n, maxL);
}