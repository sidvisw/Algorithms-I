#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
Name-Sidharth Vishwakarma
Roll No.-20CS10082
Hackerrank ID-sid_visw
*/

//person structure
struct person
{
    int pId;
    int d;
    int t;
    int c;
    int sum;
};

//Pair to facilitate storage of person dependency
struct Pair
{
    int x, y;
};

//mergesort implementation
void merging_func(person points[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    person L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = points[l + i];
    for (j = 0; j < n2; j++)
        R[j] = points[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].d <= R[j].d)
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
void mergesort(person arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merging_func(arr, l, m, r);
    }
}

//heap ADT starts
struct heap //structure for storing heap
{
    person list[100001];
    int numPersons;
};
void initHeap(heap *H) //initializes heap
{
    H->numPersons = 0; //makes heap size = 0
}
void heapify(heap *H, int index, int indexOf[]) //heapify for inserting
{
    while (index > 1)
    {
        if (H->list[index].c < H->list[index / 2].c)
            return;
        if (H->list[index].c == H->list[index / 2].c && H->list[index / 2].pId < H->list[index].pId)
            return;
        // updating the sum value of nodes
        int temp = H->list[index].sum;                                                         //storing index sum in temp
        H->list[index].sum = H->list[index / 2].sum - H->list[index].c + H->list[index / 2].c; //modifying index sum
        H->list[index / 2].sum = temp;                                                         //modifying index / 2 sum
        //modifying the array which store index of heap elements
        indexOf[H->list[index / 2].pId] = index;
        indexOf[H->list[index].pId] = index / 2;
        swap(H->list[index], H->list[index / 2]); //swapping index and index/2
        index = index / 2;
    }
}
void insertPerson(heap *H, person item, int indexOf[]) //insert function
{
    indexOf[item.pId] = H->numPersons + 1;
    H->list[H->numPersons + 1] = item;
    H->numPersons++;
    int index = H->numPersons / 2;
    while (index >= 1) //loop until heap is reached and update the sum for every ancestor
    {
        H->list[index].sum += item.c;
        index /= 2;
    }
    heapify(H, H->numPersons, indexOf); //heapify to gain value property
}
person *extractMaxJob(heap *H) //findmax function
{
    if (H->numPersons == 0) //if heap is empty the return NULL
        return NULL;
    return &(H->list[1]); //return the max element pointer
}
void maxHeapify(heap *H, int index, int indexOf[]) //max heapify for delete
{
    while (true)
    {
        int l = 2 * index;
        int r = 2 * index + 1;
        if (l > H->numPersons)
            return;
        int maxIndex = r;
        if (r > H->numPersons || H->list[l].c > H->list[r].c)
            maxIndex = l;
        if (H->list[l].c == H->list[r].c)
        {
            if (H->list[l].pId < H->list[r].pId)
            {
                maxIndex = l;
            }
            else
                maxIndex = r;
        }
        if (H->list[index].c > H->list[maxIndex].c)
            return;
        if (H->list[index].c == H->list[maxIndex].c && H->list[index].pId < H->list[maxIndex].pId)
            return;
        //modifying the sum of the heaps during max heapify
        int temp = H->list[index].sum;                                         //storing index sum in temp
        H->list[index].sum = H->list[maxIndex].sum;                            //updating index sum
        H->list[maxIndex].sum = temp - H->list[maxIndex].c + H->list[index].c; //updating maxIndex sum
        //modifying the index array that store heap elements index
        indexOf[H->list[maxIndex].pId] = index;
        indexOf[H->list[index].pId] = maxIndex;
        swap(H->list[index], H->list[maxIndex]); //swapping index with maxIndex
        index = maxIndex;
    }
}
void deleteMax(heap *H, int indexOf[]) //delete fumction
{
    //updating index array
    indexOf[H->list[1].pId] = 0;
    indexOf[H->list[H->numPersons].pId] = 1;
    H->list[H->numPersons].sum = H->list[1].sum - H->list[H->numPersons].c;
    int index = H->numPersons / 2;
    while (index > 1) //loop for all ancestors and update their sum value
    {
        H->list[index].sum -= H->list[H->numPersons].c;
        index /= 2;
    }
    H->list[1] = H->list[H->numPersons]; //make heap element at numPerson the first element
    H->numPersons--;
    maxHeapify(H, 1, indexOf); //max heapify to restore the value property
}
void increaseKey(heap *H, int index) //increase key function
{
    H->list[index].c += H->list[index].sum; //increases sum by summing cost with sum
}
//heap ADT ends

//function to find dependency
int findDependent(int pId, Pair depend[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (pId == depend[i].x)
            return depend[i].y;
    }
    return 0;
}

//function to get initial day allotted
int findDays(int pId, Pair arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (pId == arr[i].x)
            return arr[i].y;
    }
    return -1;
}

void modScheduler(person personList[], int n, int d, Pair depend[], int p, int indexOf[]) //modified scheduler function
{
    int schedule[d], size = 0;
    mergesort(personList, 0, n - 1);
    Pair days[n];
    //storing initial days alloted in another array
    for (int i = 0; i < n; i++)
    {
        days[i] = {personList[i].pId, personList[i].t};
    }
    for (int i = 1; i < personList[0].d; i++)
    {
        schedule[size++] = 0;
    }
    heap *H = new heap;
    initHeap(H);
    int day = personList[0].d;
    int iter = 0;
    while (day <= d)
    {
        while (iter < n && day == personList[iter].d)
        {
            insertPerson(H, personList[iter], indexOf);
            iter++;
        }
        person *ptr = extractMaxJob(H);
        if (ptr)
        {
            schedule[size++] = ptr->pId;
            ptr->t--;
            if (ptr->t == 0)
            {
                int dependent = findDependent(ptr->pId, depend, p);
                deleteMax(H, indexOf);
                if (dependent && findDays(dependent, days, n) == H->list[indexOf[dependent]].t) //if a person depends on another
                {
                    increaseKey(H, indexOf[dependent]);      //then increase the key of the dependent
                    heapify(H, indexOf[dependent], indexOf); //heapify to restore the value property
                }
            }
        }
        else
        {
            schedule[size++] = 0;
        }
        day++;
    }
    //output
    int cost = 0;
    for (int i = 1; i <= H->numPersons; i++)
    {
        cost += (H->list[i].c) * (H->list[i].t);
    }
    cout << cost << endl;
    for (int i = 0; i < size; i++)
    {
        cout << schedule[i] << " ";
    }
    cout << endl;
}

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    //input
    int n, d, p;
    cin >> n >> d >> p;
    person arr[n];
    int indexOf[n + 1];
    for (int i = 1; i < n + 1; i++)
    {
        indexOf[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].pId >> arr[i].d >> arr[i].t >> arr[i].c;
        arr[i].sum = 0;
    }
    Pair depend[p];             //Pair to store dependency
    for (int i = 0; i < p; i++) //loop to get input of dependent pairs
    {
        cin >> depend[i].x >> depend[i].y;
    }

    modScheduler(arr, n, d, depend, p, indexOf); //modified scheduler to schedule lectures
    return 0;
}
