#include <bits/stdc++.h>
using namespace std;
typedef struct
{
    int x, y;
} Pair;

Pair getMaxSubArray(int arr[], int beg, int end)
{
    if (beg == end)
        return {beg, end};
    else
    {
        int mid = (beg + end) / 2;
        Pair p1 = getMaxSubArray(arr, beg, mid);
        Pair p2 = getMaxSubArray(arr, mid + 1, end);
        int sum_p1 = 0, sum_p2 = 0;
        for (int i = p1.x; i <= p1.y; i++)
        {
            sum_p1 += arr[i];
        }
        for (int i = p2.x; i <= p2.y; i++)
        {
            sum_p2 += arr[i];
        }
        int cross_sum1 = arr[mid], index1;
        for (int i = mid; i >= beg; i--)
        {
            int tempSum = cross_sum1;
            if (i != mid)
                cross_sum1 += arr[i];
            index1 = i;
            if (cross_sum1 < tempSum)
            {
                cross_sum1 = tempSum;
                index1 = i + 1;
                break;
            }
        }
        int cross_sum2 = arr[mid + 1], index2;
        for (int i = mid + 1; i <= end; i++)
        {
            int tempSum = cross_sum2;
            if (i != mid + 1)
                cross_sum2 += arr[i];
            index2 = i;
            if (cross_sum2 < tempSum)
            {
                cross_sum2 = tempSum;
                index2 = i - 1;
                break;
            }
        }
        int cross_sum = cross_sum1 + cross_sum2;
        if (sum_p1 > cross_sum && sum_p1 > sum_p2)
            return p1;
        else if (sum_p2 > sum_p1 && sum_p2 > cross_sum)
            return p2;
        else
            return {index1, index2};
    }
}
main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    Pair tuple = getMaxSubArray(arr, 0, n - 1);
    cout << tuple.x << "," << tuple.y << endl;
}