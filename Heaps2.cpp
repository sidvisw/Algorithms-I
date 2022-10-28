#include <bits/stdc++.h>
using namespace std;
//job structure
struct job
{
    int jobId;
    int startTime;
    int jobLength;
    int remLength;
};

//Pair to facilitate storage of job dependency
struct Pair
{
    int x,y;
};

//heap ADT starts
struct heap
{
    job list[100];
    int numJobs;
};
void initHeap(heap *H)
{
    H->numJobs = 0;
}
void heapify(heap *H, int index,int indexOf[])
{
    while (index > 1)
    {
        if (H->list[index].remLength >= H->list[index / 2].remLength)
            return;
        indexOf[H->list[index/2].jobId]=index;
        indexOf[H->list[index].jobId]=index/2;
        swap(H->list[index], H->list[index / 2]);
        index = index / 2;
    }
}
void insertJob(heap *H, job item,int indexOf[])
{
    indexOf[item.jobId]=H->numJobs+1;
    H->list[H->numJobs + 1] = item;
    H->numJobs++;
    heapify(H, H->numJobs,indexOf);
}
bool extractMinJob(heap *H, job *j)
{
    if (H->numJobs == 0)
        return false;
    *j = H->list[1];
    return true;
}
void minHeapify(heap *H, int index,int indexOf[])
{
    while (true)
    {
        int l = 2 * index;
        int r = 2 * index + 1;
        if (l > H->numJobs)
            return;
        int minIndex = r;
        if (r > H->numJobs || H->list[l].remLength < H->list[r].remLength)
            minIndex = l;
        if (H->list[index].remLength < H->list[minIndex].remLength)
            return;
        indexOf[H->list[minIndex].jobId]=index;
        indexOf[H->list[index].jobId]=minIndex;
        swap(H->list[index], H->list[minIndex]);
        index = minIndex;
    }
}
void deleteMin(heap *H,int indexOf[])
{
    indexOf[H->list[1].jobId]=0;
    indexOf[H->list[H->numJobs].jobId]=1;
    H->list[1] = H->list[H->numJobs];
    H->numJobs--;
    minHeapify(H, 1,indexOf);
}
//heap ADT ends

//function to find dependency
int findDependent(int jobId,Pair depend[],int size){
    for (int i = 0; i < size; i++)
    {
        if(jobId==depend[i].x)return depend[i].y;
    }
    return 0;
}

//function to get start time of any job
int findStartTime(int jobId,job arr[],int size){
    for (int i = 0; i < size; i++)
    {
        if(jobId==arr[i].jobId)return arr[i].startTime;
    }
    return -1;
}

//driver function
main()
{
    int n,m;
    cin >> n>>m;
    job arr[n];
    int indexOf[n+1];
    for (int i = 1; i < n+1; i++)
    {
        indexOf[i]=0;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].jobId >> arr[i].startTime >> arr[i].jobLength;
        arr[i].remLength = arr[i].jobLength;
    }
    Pair depend[m];
    for (int i = 0; i < m; i++)
    {
        int x,y;
        cin>>x>>y;
        depend[i]={x,y};
    }
    for (int i = 0; i < arr[0].startTime; i++)
    {
        cout << "0 ";
    }
    heap *H = new heap;
    initHeap(H);
    int time = arr[0].startTime;
    int iter = 0;
    while (H->numJobs > 0 || iter < n)
    {
        while (time == arr[iter].startTime && iter < n)
        {
            insertJob(H, arr[iter],indexOf);
            iter++;
        }
        job *minJob = new job;
        bool extracted = extractMinJob(H, minJob);
        if (extracted)
        {
            cout << minJob->jobId << " ";
            H->list[1].remLength--;
            if (H->list[1].remLength == 0)
            {
                int dependent=findDependent(H->list[1].jobId,depend,m);
                deleteMin(H,indexOf);
                if(dependent&&findStartTime(dependent,arr,n)>time){
                    H->list[indexOf[dependent]].remLength/=2;
                    heapify(H,indexOf[dependent],indexOf);
                }
            }
        }
        else
        {
            cout << "0 ";
        }
        delete minJob;
        time++;
    }
}