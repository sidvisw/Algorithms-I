#include<bits/stdc++.h>
using namespace std;
int findShift(int a[],int beg,int end){
    if(beg==end) return 0;
    else if(beg==end-1){
        if(a[beg]>a[end]) return 1;
        else return 0;
    }
    int mid=(beg+end)/2;
    if(a[mid]<a[mid+1]&&a[mid]<a[mid-1]) return mid;
    else{
        if(a[mid]<a[0]) return findShift(a,beg,mid);
        else return findShift(a,mid,end);
    }
}
main()
{
    int a[]={13,15,19,2,5,8};
    cout<<findShift(a,0,5)<<endl;
}