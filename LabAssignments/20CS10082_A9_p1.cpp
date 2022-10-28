/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name:Sidharth Vishwakarma
Roll Number:20CS10082
HackerRank ID:sid_visw
********************************/

#include <iostream>
#include <climits>
using namespace std;

struct Pair //structure to store edge as a pair
{
    int x, y;
};

void getMaxSpanTree(int **adjMat, int n, Pair F[], int &sizeF) //function to get maximum spanning tree
{
    int farthest[n];            //array to store farthest node
    int distance[n];            //array to store distance to the farthest node
    for (int i = 0; i < n; i++) //make node 1 as the farthest node
    {
        farthest[i] = 0;
        distance[i] = adjMat[0][i];
    }
    distance[0] = -1;
    int rep = n - 1;
    while (rep--) //loop n-1 times
    {
        int max = INT_MIN;
        int vfar;
        for (int i = 0; i < n; i++) //find maximum edge length vertex
        {
            if (distance[i] >= 0 && distance[i] > max)
            {
                max = distance[i];
                vfar = i;
            }
        }
        Pair e = {vfar, farthest[vfar]};
        F[sizeF++] = e; //append e on F
        distance[vfar] = -1;
        for (int i = 0; i < n; i++) //update the farthest and distance array
        {
            if (adjMat[i][vfar] > distance[i] && distance[i] >= 0)
            {
                distance[i] = adjMat[i][vfar];
                farthest[i] = vfar;
            }
        }
    }
}

struct node //node for maximum spanning tree
{
    int val;
    node *parent;
};
node *createNode(int val) //create node for tree
{
    node *n = new node;
    n->parent = NULL;
    n->val = val;
    return n;
}
void makeTree(node **arr, int n, Pair F[], int sizeF) //construct the tree
{
    for (int i = 0; i < sizeF; i++) //loop for all edges in F
    {
        int v1 = F[i].x;
        int v2 = F[i].y;
        arr[v1]->parent = arr[v2];
    }
}
bool found(node *arr[], int size, node *item) //function to find node in and node array
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == item)
            return true;
    }
    return false;
}
node *findCommonParent(node *a, node *b, int n) //function to find common parent in tree
{
    node *parent[n];
    int sizeP = 0;
    node *ptr = a;
    while (ptr != NULL)
    {
        parent[sizeP++] = ptr;
        ptr = ptr->parent;
    }
    ptr = b;
    while (ptr != NULL)
    {
        if (found(parent, sizeP, ptr))
            return ptr;
        ptr = ptr->parent;
    }
    return NULL;
}

int main() //driver function
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, q;
    cin >> n >> q;           //input of n an q
    int m = n * (n - 1) / 2; //initialize m
    int **adjMat = new int *[n];
    for (int i = 0; i < n; i++) //initialize adjacency matrix
    {
        adjMat[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                adjMat[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) //allot values in adjacency matrix
    {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        v1--;
        v2--;
        adjMat[v1][v2] = w;
        adjMat[v2][v1] = w;
    }

    Pair F[m];
    int sizeF = 0;
    getMaxSpanTree(adjMat, n, F, sizeF); //get the maximum spanning tree
    int sum = 0;
    for (int i = 0; i < sizeF; i++)
    {
        sum += adjMat[F[i].x][F[i].y];
    }
    cout << sum << endl; //output

    int **mat = new int *[n];
    for (int i = 0; i < n; i++) //initialize adjacency matrix for maximum spanning tree
    {
        mat[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            mat[i][j] = -1;
        }
    }
    for (int i = 0; i < sizeF; i++) //populate ajacency matrix
    {
        mat[F[i].x][F[i].y] = adjMat[F[i].x][F[i].y];
        mat[F[i].y][F[i].x] = adjMat[F[i].y][F[i].x];
    }

    node **arr = new node *[n];
    for (int i = 0; i < n; i++) //create n nodes of maximum spanning tree
    {
        arr[i] = createNode(i);
    }
    makeTree(arr, n, F, sizeF); //construct the tree

    for (int i = 0; i < q; i++) //loop q times
    {
        int v1, v2, w;
        cin >> v1 >> v2 >> w; //input
        v1--;
        v2--;
        if (arr[v1]->parent == arr[v2] || arr[v2]->parent == arr[v1]) //if an edge exists then output the sum+difference
        {
            cout << sum - mat[v1][v2] + w << endl;
        }
        else
        {
            node *parent = findCommonParent(arr[v1], arr[v2], n); //find common parent
            int min = INT_MAX;
            node *ptr = arr[v1];
            while (ptr != parent) //find min edge length for v1
            {
                if (min > mat[ptr->val][ptr->parent->val])
                {
                    min = mat[ptr->val][ptr->parent->val];
                }
                ptr = ptr->parent;
            }
            ptr = arr[v2];
            while (ptr != parent) //find min edge length for v2
            {
                if (min > mat[ptr->val][ptr->parent->val])
                {
                    min = mat[ptr->val][ptr->parent->val];
                }
                ptr = ptr->parent;
            }
            if (min < w) //if min is less than w
            {
                cout << sum - min + w << endl; //output sum-min+w
            }
            else //else
            {
                cout << sum << endl; //output sum
            }
        }
    }
    return 0;
}