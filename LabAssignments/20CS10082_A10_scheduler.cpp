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

//person structure to store information about person
struct person
{
    int pId;
    int d;
    int t;
    int c;
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
struct heap //heap structure to store the heap
{
    person list[100001];
    int numPersons;
};
void initHeap(heap *H) //initialize heap with heap size = 0
{
    H->numPersons = 0;
}
void heapify(heap *H, int index) //heapify for insert
{
    while (index > 1)
    {
        if (H->list[index].c < H->list[index / 2].c) //if parent has higher key then return
            return;
        if (H->list[index].c == H->list[index / 2].c && H->list[index / 2].pId < H->list[index].pId) //in case of tie choose the one with lower pId
            return;
        swap(H->list[index], H->list[index / 2]); //swap the parent and child
        index = index / 2;                        //modify the index
    }
}
void insertPerson(heap *H, person item) //insert function
{
    H->list[H->numPersons + 1] = item; //put item at last index
    H->numPersons++;
    heapify(H, H->numPersons); //heapify to get desired value property
}
person *extractMaxPerson(heap *H) //find max function
{
    if (H->numPersons == 0) //if heap empty the return NULL
        return NULL;
    return &(H->list[1]); //return the pointer to the heap max element
}
void maxHeapify(heap *H, int index) //max heapify for delete
{
    while (true)
    {
        int l = 2 * index;     //left parent
        int r = 2 * index + 1; //right parent
        if (l > H->numPersons) //if there are no more items in heap then return
            return;
        int maxIndex = r;                                     //initialize maxIndex to right parent
        if (r > H->numPersons || H->list[l].c > H->list[r].c) //if right parent does not exists or left parent value is higher then make maxIndex as left parent
            maxIndex = l;
        if (H->list[l].c == H->list[r].c) //in case of ties choose the one with lower pId
        {
            if (H->list[l].pId < H->list[r].pId)
                maxIndex = l;
            else
                maxIndex = r;
        }
        if (H->list[index].c > H->list[maxIndex].c) //if maxIndex value is less then return
            return;
        if (H->list[index].c == H->list[maxIndex].c && H->list[index].pId < H->list[maxIndex].pId) //if both values are equal but index has less pId than maxIndex then return
            return;
        swap(H->list[index], H->list[maxIndex]); //swap index with maxIndex
        index = maxIndex;                        //modify the index
    }
}
void deleteMax(heap *H) //delete function
{
    H->list[1] = H->list[H->numPersons]; //make the value at index 1 to the last heap value
    H->numPersons--;
    maxHeapify(H, 1); //max heapify to restore the value property
}
//heap ADT ends

void scheduler(person personList[], int n, int d) //scheduler function
{
    int schedule[d], size = 0;                //array to store schedule
    mergesort(personList, 0, n - 1);          //sort according to cost
    for (int i = 1; i < personList[0].d; i++) //handles the case if no person arrives initially
    {
        schedule[size++] = 0;
    }
    heap *H = new heap;        //create heap
    initHeap(H);               //initialize heap
    int day = personList[0].d; //initialize day
    int iter = 0;              //iter for iterating through personList
    while (day <= d)           //loop untill day<=d
    {
        while (iter < n && day == personList[iter].d) //insert the persons who had arrived into the heap
        {
            insertPerson(H, personList[iter]);
            iter++;
        }
        person *p = extractMaxPerson(H); //extract max cost person
        if (p)
        {
            schedule[size++] = p->pId; //schedule the lecture
            p->t--;
            if (p->t == 0) //if the person has completed all his lectures then delete it from the heap
            {
                deleteMax(H);
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
        cost += (H->list[i].c) * (H->list[i].t); //increamenting the cost for those persons who are still in heap
    }
    cout << cost << endl;          //output the cost
    for (int i = 0; i < size; i++) //output the schedule
    {
        cout << schedule[i] << " ";
    }
    cout << endl;
}

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    //input
    int n, d;
    cin >> n >> d;
    person arr[n];              //array to store persons
    for (int i = 0; i < n; i++) //taking input
    {
        cin >> arr[i].pId >> arr[i].d >> arr[i].t >> arr[i].c;
    }

    scheduler(arr, n, d); //scheduler function to schedule
    return 0;
}
