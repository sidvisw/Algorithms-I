#include <bits/stdc++.h>
using namespace std;
int majorityElement(int arr[], int beg, int end)
{
    int size_half = (end - beg + 1) / 2;
    if (beg == end)
    {
        return arr[beg];
    }
    int mid = (beg + end) / 2;
    int major1 = majorityElement(arr, beg, mid);
    int major2 = majorityElement(arr, mid + 1, end);
    if (major1 == major2)
        return major1;
    else
    {
        int count_major1 = 0, count_major2 = 0;
        for (int i = beg; i <= end; i++)
        {
            if (arr[i] == major1)
            {
                count_major1++;
            }
            else if (arr[i] == major2)
            {
                count_major2++;
            }
        }
        if (count_major1 > size_half)
            return major1;
        else if (count_major2 > size_half)
            return major2;
        else
            return INT_MIN;
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
    int majorElement = majorityElement(arr, 0, n - 1);
    if (majorElement == INT_MIN)
    {
        cout << "No majority element found";
        exit(0);
    }
    cout << majorElement << endl;
}