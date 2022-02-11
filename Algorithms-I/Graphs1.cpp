#include <bits/stdc++.h>
using namespace std;
typedef struct node
{
    int nodeVal;
    struct node *next;
} Node;

void addEdge(Node *node_arr[], int node, int adj)
{
    Node *ptr = new Node;
    ptr->nodeVal = adj;
    ptr->next = node_arr[node];
    node_arr[node] = ptr;
}

void print_adj_list(Node *node_arr[], int nodes)
{
    for (int i = 0; i < nodes; i++)
    {
        Node *ptr = node_arr[i];
        cout << "Node " << i << ": ";
        while (ptr != NULL)
        {
            cout << ptr->nodeVal << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }
}
void visit(bool *visited, int node)
{
    visited[node] = true;
    cout << "We visited node " << node << endl;
}
void dfs(int nodes, Node *node_arr[], bool *visited, int node)
{
    visit(visited, node);
    Node *ptr = node_arr[node];
    while (ptr != NULL)
    {
        if (!visited[ptr->nodeVal])
        {
            dfs(nodes, node_arr, visited, ptr->nodeVal);
        }
        ptr = ptr->next;
    }
}
main()
{
    int nodes, edges;
    cin >> nodes >> edges;
    Node *node_arr[nodes];
    for (int i = 0; i < nodes; i++)
    {
        node_arr[i] = NULL;
    }
    for (int i = 0; i < edges; i++)
    {
        int m, n;
        cin >> m >> n;
        addEdge(node_arr, m, n);
    }
    bool *visited = new bool[nodes];
    for (int i = 0; i < nodes; i++)
    {
        visited[i] = false;
    }
    print_adj_list(node_arr, nodes);

    for (int i = 0; i < nodes; i++)
    {
        if (!visited[i])
        {
            dfs(nodes, node_arr, visited, i);
        }
    }
}