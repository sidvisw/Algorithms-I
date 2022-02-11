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

//structure to define the node in disjoint set
struct node
{
    node *parent;
    int rank;
};
//ultility function to create a singleton sets of data
void makeSet(node *&p)
{
    p = new node;
    p->rank = 0;
    p->parent = p;
}
//ultility function to find the node ID or the head node by applying path compression
node *find(node *ptr)
{
    if (ptr->parent != ptr)
    {
        ptr->parent = find(ptr->parent);
    }
    return ptr->parent;
}
//ultility function to do union by rank of two disjoint sets
bool unionNode(node *x, node *y)
{
    if (x == y)
        return false;
    if (x->rank < y->rank)
    {
        x->parent = y;
    }
    else if (x->rank > y->rank)
    {
        y->parent = x;
    }
    else
    {
        x->parent = y;
        y->rank++;
    }
    return true;
}

//ultility function to check whether all nodes are connected or not
bool allConnected(node **zaphod, node **arthur, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            //finds the heads of nodes
            node *a = find(zaphod[i]);
            node *b = find(zaphod[j]);
            node *x = find(arthur[i]);
            node *y = find(arthur[j]);
            if (a != b || x != y) //checks if nodes are from same set
            {
                return false; //return false if any one is not connected
            }
        }
    }
    return true; //if everone is connected then returns true
}

//the main working function that calculates the answer of maximum edges to be removed
int maxEdgesToRemove(bool **type1, bool **type2, bool **type3, int n, int m)
{
    //initializing the nodes for both zaphod and arthur
    node **zaphod = new node *[n];
    node **arthur = new node *[n];
    //make singleton sets out of them
    for (int i = 0; i < n; i++)
    {
        makeSet(zaphod[i]);
        makeSet(arthur[i]);
    }
    int edgeCount = 0; //variable to store count of edge
    //looping on type 3 edges to first include them - greedy choice
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (type3[i][j]) //check if edge exists
            {
                //find the head of the nodes
                node *a = find(zaphod[i]);
                node *b = find(zaphod[j]);
                node *x = find(arthur[i]);
                node *y = find(arthur[j]);
                if (a != b || x != y) //check if they don't belong to same set
                {
                    if (a != b)
                        unionNode(a, b); //union operation
                    if (x != y)
                        unionNode(x, y); //union operation
                    edgeCount++;
                }
            }
        }
    }
    //looping on the type 2 edges
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (type2[i][j]) //check for edge
            {
                //finding heads
                node *a = find(arthur[i]);
                node *b = find(arthur[j]);
                if (a != b) //check if they are in same set
                {
                    unionNode(a, b); //union operation
                    edgeCount++;
                }
            }
        }
    }
    //looping for type 1 edges
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (type1[i][j]) //check for edge
            {
                //find heads
                node *a = find(zaphod[i]);
                node *b = find(zaphod[j]);
                if (a != b) //check if they are in same set
                {
                    unionNode(a, b); //union operation
                    edgeCount++;
                }
            }
        }
    }
    if (!allConnected(zaphod, arthur, n)) //check if they can visit all planets or not
        return -1;                        //return -1 if they cannot
    return m - edgeCount;                 //return the edges which you can remove
}

//driver function
int main()
{
    //part 1 starts
    int n, m;
    cin >> n >> m;
    //initializing matrices of type 1, 2 and 3 with the value provided
    bool **type1 = new bool *[n];
    bool **type2 = new bool *[n];
    bool **type3 = new bool *[n];
    for (int i = 0; i < n; i++)
    {
        type1[i] = new bool[n];
        type2[i] = new bool[n];
        type3[i] = new bool[n];
        for (int j = 0; j < n; j++)
        {
            type1[i][j] = type2[i][j] = type3[i][j] = false;
        }
    }
    //loop for filling up the matrix
    for (int i = 0; i < m; i++)
    {
        int type, n1, n2;
        cin >> type >> n1 >> n2;
        if (type == 1)
        {
            type1[n1][n2] = 1;
            type1[n2][n1] = 1;
        }
        else if (type == 2)
        {
            type2[n1][n2] = 1;
            type2[n2][n1] = 1;
        }
        else
        {
            type3[n1][n2] = 1;
            type3[n2][n1] = 1;
        }
    }
    //loop for outputting the matrix according to the format
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            string str = "";
            //appending appropriate numbers to str according to edges
            if (type1[i][j])
                str.append("1#");
            if (type2[i][j])
                str.append("2#");
            if (type3[i][j])
                str.append("3#");
            if (str.size() == 0) //check for no existance of edge
                cout << "0    ";
            else //else print the edges in the format given
            {
                str.pop_back();
                cout << str << "    ";
            }
        }
        cout << endl;
    }
    //part 1 ends

    //part 2 starts
    cout << endl;
    cout << "Edges Removed = " << maxEdgesToRemove(type1, type2, type3, n, m) << endl;
    //part 2 ends

    return 0;
}
