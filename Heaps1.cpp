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
void heapify(heap *H, int index)
{
    while (index > 1)
    {
        if (H->list[index].remLength >= H->list[index / 2].remLength)
            return;
        swap(H->list[index], H->list[index / 2]);
        index = index / 2;
    }
}
void insertJob(heap *H, job item)
{
    H->list[H->numJobs + 1] = item;
    H->numJobs++;
    heapify(H, H->numJobs);
}
bool extractMinJob(heap *H, job *j)
{
    if (H->numJobs == 0)
        return false;
    *j = H->list[1];
    return true;
}
void minHeapify(heap *H, int index)
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
        swap(H->list[index], H->list[minIndex]);
        index = minIndex;
    }
}
void deleteMin(heap *H)
{
    H->list[1] = H->list[H->numJobs];
    H->numJobs--;
    minHeapify(H, 1);
}
//heap ADT ends

//driver function
main()
{
    int n;
    cin >> n;
    job arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].jobId >> arr[i].startTime >> arr[i].jobLength;
        arr[i].remLength = arr[i].jobLength;
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
            insertJob(H, arr[iter]);
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
                deleteMin(H);
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