#include <bits/stdc++.h>
using namespace std;
typedef struct node
{
    int nodeVal;
    struct node *next;
} Node;
typedef struct queue
{
    Node *front;
    Node *rear;
    int size;
} Queue;
Queue *createQueue()
{
    Queue *q = new Queue;
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}
void enqueue(Queue *q, int item)
{
    if (q->size == 0)
    {
        Node *new_node = new Node;
        new_node->nodeVal = item;
        new_node->next = NULL;
        q->front = new_node;
        q->rear = new_node;
        q->size++;
    }
    else
    {
        Node *new_node = new Node;
        new_node->nodeVal = item;
        new_node->next = NULL;
        q->rear->next = new_node;
        q->rear = new_node;
        q->size++;
    }
}
int dequeue(Queue *q)
{
    if (q->size == 0)
    {
        cout << "\nQueue Underflow";
        exit(-1);
    }
    else if (q->size == 1)
    {
        Node *ptr = q->front;
        q->front = q->rear = NULL;
        int temp = ptr->nodeVal;
        delete ptr;
        q->size--;
        return temp;
    }
    else
    {
        Node *ptr = q->front;
        q->front = q->front->next;
        int temp = ptr->nodeVal;
        delete ptr;
        q->size--;
        return temp;
    }
}

typedef struct GraphNode
{
    int nodeNum;
    struct GraphNode *next;
} graphNode;
void addEdge(graphNode *node_arr[], int node, int adj)
{
    graphNode *ptr = new graphNode;
    ptr->nodeNum = adj;
    ptr->next = node_arr[node];
    node_arr[node] = ptr;
}

void visit(bool *visited, int node)
{
    visited[node] = true;
    cout << "We visited node " << node << endl;
}
void bfs(Queue *q, int nodes, graphNode *node_arr[], bool *visited, int node)
{
    visit(visited, node);
    enqueue(q, node);
    while (q->size != 0)
    {
        graphNode *ptr = node_arr[node];
        while (ptr != NULL)
        {
            if (!visited[ptr->nodeNum])
            {
                visit(visited, ptr->nodeNum);
                enqueue(q, ptr->nodeNum);
            }
            ptr=ptr->next;
        }
        node=dequeue(q);
    }
}
void print_adj_list(graphNode *node_arr[], int nodes)
{
    for (int i = 0; i < nodes; i++)
    {
        graphNode *ptr = node_arr[i];
        cout << "Node " << i << ": ";
        while (ptr != NULL)
        {
            cout << ptr->nodeNum << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }
}

main()
{
    Queue *q = createQueue();
    int nodes, edges;
    cin >> nodes >> edges;
    graphNode *node_arr[nodes];
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
    print_adj_list(node_arr,nodes);
    for (int i = 0; i < nodes; i++)
    {
        if (!visited[i])
        {
            bfs(q, nodes, node_arr, visited, i);
        }
    }
}