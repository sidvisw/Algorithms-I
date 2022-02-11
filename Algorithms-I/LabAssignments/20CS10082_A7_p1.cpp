#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/*
Name- Sidharth Vishwakarma
Roll No.- 20CS10082
Hackerrank ID- sid_visw
*/

//function to linear search an element in del arrary
bool isPresent(int arr[], int size, int item)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == item)
            return true;
    }
    return false;
}

//function to find the most negative value till ith index
int findMin(int a[], int n, int del[], int &size)
{
    int min = 0;
    int minIndex=0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] < min && !isPresent(del, size, i))
        {
            min = a[i];
            minIndex=i;
        }
    }
    del[size++] = minIndex;//accordingly update del array
    return minIndex;
}
int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    cin >> t;
    while (t--)
    {
        //input by user
        int n;
        long long x;
        cin >> n >> x;
        int a[n];
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        //working of algorithm
        int ctr = 0;
        int del[n], size = 0;
        for (int i = 0; i < n; i++)
        {
            x += a[i];
            ctr++;
            if (x <= 0)//condition check if we get our health as 0 or negative
            {
                int minIndex = findMin(a, i, del, size);
                x -= a[minIndex];
                ctr--;
            }
        }
        cout << ctr << endl; //output the answer
    }
    return 0;
}
