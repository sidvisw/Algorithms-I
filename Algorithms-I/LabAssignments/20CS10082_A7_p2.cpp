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

//function to initialize the M array
void createMarray(int a[],int n,int M[],int k){
    for(int i=0;i<n;i++){
        M[i]=a[i];
        for(int j=1;j<=k&&i+j<n;j++){
            M[i]+=a[i+j];
        }
        for(int j=1;j<=k&&i-j>=0;j++){
            M[i]+=a[i-j];
        }
    }
}

//function to find the index which contains the minimum value
int findMinIndex(int a[],int n){
    int minIndex=n-1;
    int minVal=a[n-1];
    for(int i=n-2;i>=0;i--){
        if(a[i]<minVal){
            minVal=a[i];
            minIndex=i;
        }
    }
    return minIndex;
}

//function to find the minimal element in an array
int findMinVal(int a[],int n){
    int minVal=a[0];
    for (int i = 1; i < n; i++)
    {
        if(a[i]<minVal){
            minVal=a[i];
        }
    }
    return minVal;
}

//driver function
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin>>t;
    while(t--){
        //taking input from user
        int n,k;
        long long x;
        cin>>n>>x>>k;
        int a[n];
        for (int i = 0; i < n; i++)
        {
            cin>>a[i];
        }

        //working of algorithm
        int M[n];
        createMarray(a,n,M,k);
        while(x--){
            int index=findMinIndex(M,n);
            a[index]++;
            createMarray(a,n,M,k);
        }
        //output to console
        cout<<findMinVal(M,n)<<endl;
    }
    return 0;
}
