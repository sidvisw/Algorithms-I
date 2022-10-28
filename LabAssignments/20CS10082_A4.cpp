/*****************************************
IMPORTANT: 
Write your Name, Roll number and Hackerrank ID here.

Name:Sidharth Vishwakarma
Roll Number:20CS10082
Hackerrank ID:sid_visw
*****************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <string.h>
#include <stdlib.h>

using namespace std;
//structure to store data in the form of pairs(x,y)
typedef struct
{
    int x, y;
} Points;
//structure for implementing the queue
typedef struct
{
    int *Arr;
    int queue_size, start_id, end_id;
} QUEUE;
//function to create a queue with no elements in it
void init(QUEUE *qP, int size)
{
    qP->Arr = new int[size];
    qP->queue_size = 0;
    qP->start_id = -1;
    qP->end_id = -1;
}
//function to check whether the queue is empty or not
int isempty(QUEUE qP)
{
    return qP.queue_size == 0;
}
//enqueuing function to insert an element in the queue
void enqueue(QUEUE *qP, int data)
{
    if (qP->end_id == 1e5 - 1)
    {
        cout << "\nQueue Overflow";
        exit(-1);
    }
    else if (qP->end_id == -1)
    {
        qP->end_id = qP->start_id = 0;
        qP->Arr[qP->end_id] = data;
        qP->queue_size++;
    }
    else
    {
        qP->end_id++;
        qP->Arr[qP->end_id] = data;
        qP->queue_size++;
    }
}
//dequeuing function to remove an element from the queue
int dequeue(QUEUE *qP)
{
    int ret_data;
    if (qP->start_id == -1)
    {
        cout << "\nQueue underflow";
        exit(-1);
    }
    else if (qP->start_id == qP->end_id)
    {
        ret_data = qP->Arr[qP->start_id];
        qP->start_id = qP->end_id = -1;
        qP->queue_size--;
    }
    else
    {
        ret_data = qP->Arr[qP->start_id];
        qP->start_id++;
        qP->queue_size--;
    }
    return ret_data;
}
//display function to display the contents of the queue
void display_queue(QUEUE *qP)
{
    if (isempty(*qP))
    {
        cout << "\nQueue Underflow";
        exit(-1);
    }
    for (int i = qP->start_id; i <= qP->end_id; i++)
    {
        cout << qP->Arr[i] << " ";
    }
    cout << endl;
}

//a function to find the node having zero indegree and return its index
int findZeroIndegree(int indegree[], int nodes, bool *visited)
{
    for (int i = 0; i < nodes; i++)
    {
        if (indegree[i] == 0 && visited[i] == false)
        {
            visited[i] = true;
            return i;
        }
    }
    return -1;
}
//function to do topological sorting through BFS and store it in an array
int topologicalSort(int **adj_mat, int nodes, bool *visited, int *topoSort)
{
    for (int i = 0; i < nodes; i++)//mark all nodes as not visited
    {
        visited[i] = false;
    }
    int size = 0;
    QUEUE *qP = new QUEUE;
    init(qP, 1e5);//initializing queue
    int indegree[nodes];
    for (int j = 0; j < nodes; j++)//loop to calculate indegree of different nodes
    {
        int sum = 0;
        for (int i = 0; i < nodes; i++)
        {
            sum += adj_mat[i][j];
        }
        indegree[j] = sum;
    }
    int enqNode = findZeroIndegree(indegree, nodes, visited);//finding zero indegree nodes
    if (enqNode == -1)
        return 0;
    enqueue(qP, enqNode);//enqueue the node with zero indegree
    while (!isempty(*qP))
    {
        int deqNode = dequeue(qP);//dequeing the node
        topoSort[size++] = deqNode;//adding it to topologically sorted array
        int node_neigh[nodes], k = 0;
        for (int i = 0; i < nodes; i++)//loop to gather the neighbours of the dequeued node
        {
            if (adj_mat[deqNode][i])
            {
                node_neigh[k++] = i;
            }
        }
        for (int i = 0; i < k; i++)//loop to decrement the degree of the neighbours
        {
            indegree[node_neigh[i]]--;
        }
        enqNode = findZeroIndegree(indegree, nodes, visited);//find the next node with zero indegree
        if (enqNode == -1)
        {
            break;
        }
        enqueue(qP, enqNode);//enqueue the next node
    }
    return size;
}

//driver function
int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int nodes, edges;
    cin >> nodes >> edges;//taking # of nodes and # of edges as input
    int **adj_mat = new int *[nodes];
    for (int i = 0; i < nodes; i++)//initializing the adjacency matrix
    {
        adj_mat[i] = new int[nodes];
        for (int j = 0; j < nodes; j++)
        {
            adj_mat[i][j] = 0;
        }
    }
    for (int i = 0; i < edges; i++)//embarking edges on the adjacency matrix
    {
        int m, n;
        cin >> m >> n;
        adj_mat[m][n] = 1;
    }
    bool *visited = new bool[nodes];//array to store visit value of the nodes
    int *topoSort = new int[nodes];//array to store the topologically sorted elements
    int size = topologicalSort(adj_mat, nodes, visited, topoSort);
    if (size == nodes)//check the existence of a cycle
    {
        for (int i = 0; i < size; i++)
        {
            if (i == size - 1)
                cout << topoSort[i] << endl;
            else
                cout << topoSort[i] << ",";
        }
    }
    else
    {
        cout << "unconquerable" << endl;//if a cycle is there then print unconquerable
        exit(0);
    }

    Points allowEdges[100];
    int k = 0;
    for (int i = 0; i < nodes; i++)//exploring the possibilities of and other edge formation without the formation of cycle
    {
        for (int j = 0; j < nodes; j++)
        {
            if (i != j && adj_mat[i][j] != 1)
            {
                adj_mat[i][j] = 1;
                if (topologicalSort(adj_mat, nodes, visited, topoSort) == nodes)
                {
                    allowEdges[k++] = {i, j};
                }
                else
                {
                    adj_mat[i][j] = 0;
                }
            }
        }
    }
    cout << k << endl;
    for (int i = k - 1; i >= 0; i--)//print the possibilities of edges
    {
        cout << allowEdges[i].x << " " << allowEdges[i].y << endl;
    }
    return 0;
}

/* Code ends here */