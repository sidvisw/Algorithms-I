#include <bits/stdc++.h>
using namespace std;
typedef struct Pair
{
    int x, y;
} Pair;

// defining structure for node
typedef struct node
{
    Pair data;
    struct node *next;
} Node;
// defining structure for stack
typedef struct stack
{
    int size;
    Node *top;
} Stack;
// function to create a stack
Stack *createStack()
{
    Stack *stack = new Stack;
    stack->size = 0;
    stack->top = NULL;
    return stack;
}
// function to check if a stack is empty or not
bool isEmpty(Stack *stack)
{
    return stack->top == NULL;
}
// peek function for stack
Pair peek(Stack *stack)
{
    if (!isEmpty(stack))
    {
        return stack->top->data;
    }
    else
    {
        cout << "\nStack underflow";
        exit(-1);
    }
}
// pop function for stack
Pair pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        cout << "\nStack underflow";
        exit(-1);
    }
    Node *ptr = stack->top;
    stack->top = stack->top->next;
    Pair del_data = ptr->data;
    delete ptr;
    stack->size--;
    return del_data;
}
// push function for stack
void push(Stack *stack, Pair item)
{
    Node *ptr = new Node;
    ptr->data = item;
    ptr->next = stack->top;
    stack->top = ptr;
    stack->size++;
}

typedef struct GraphNode
{
    Pair point;
    struct GraphNode *next;
} graphNode;
typedef struct NodeArray
{
    Pair point;
    graphNode *head;
} nodeArray;
typedef struct VisitedArray
{
    Pair point;
    bool visitVal;
} visitedArray;
void createAdjList(int **field, nodeArray &node_arr, int n)
{
    if (node_arr.point.x - 1 >= 0 && field[node_arr.point.x - 1][node_arr.point.y] != -1)
    {
        graphNode *ptr = new graphNode;
        ptr->point.x = node_arr.point.x - 1;
        ptr->point.y = node_arr.point.y;
        ptr->next = node_arr.head;
        node_arr.head = ptr;
    }
    if (node_arr.point.y - 1 >= 0 && field[node_arr.point.x][node_arr.point.y - 1] != -1)
    {
        graphNode *ptr = new graphNode;
        ptr->point.x = node_arr.point.x;
        ptr->point.y = node_arr.point.y - 1;
        ptr->next = node_arr.head;
        node_arr.head = ptr;
    }
    if (node_arr.point.x + 1 < n && field[node_arr.point.x + 1][node_arr.point.y] != -1)
    {
        graphNode *ptr = new graphNode;
        ptr->point.x = node_arr.point.x + 1;
        ptr->point.y = node_arr.point.y;
        ptr->next = node_arr.head;
        node_arr.head = ptr;
    }
    if (node_arr.point.y + 1 < n && field[node_arr.point.x][node_arr.point.y + 1] != -1)
    {
        graphNode *ptr = new graphNode;
        ptr->point.x = node_arr.point.x;
        ptr->point.y = node_arr.point.y + 1;
        ptr->next = node_arr.head;
        node_arr.head = ptr;
    }
}
void printAdjList(nodeArray node_arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        graphNode *ptr = node_arr[i].head;
        cout << "(" << node_arr[i].point.x << "," << node_arr[i].point.y << ")->";
        while (ptr != NULL)
        {
            cout << "(" << ptr->point.x << "," << ptr->point.y << ") ";
            ptr = ptr->next;
        }
        cout << endl;
    }
}
int searchVisitedArray(VisitedArray *visited, int n, Pair p)
{
    for (int i = 0; i < n*n; i++)
    {
        if (visited[i].point.x == p.x && visited[i].point.y == p.y)
            return i;
    }
    return -1;
}
int searchNodeArray(nodeArray node_arr[], int k, Pair p)
{
    for (int i = 0; i < k; i++)
    {
        if (node_arr[i].point.x == p.x && node_arr[i].point.y == p.y)
            return i;
    }
    return -1;
}
bool dfs(Pair start, Pair end, Stack *stk, int n, nodeArray node_arr[], int k, VisitedArray *visited)
{
    bool pathfound = false;
    push(stk, start);
    int i = searchVisitedArray(visited, n, start);
    visited[i].visitVal = true;
    if (start.x == end.x && start.y == end.y)
        return true;
    int j = searchNodeArray(node_arr, k, start);
    graphNode *ptr = node_arr[j].head;
    while (ptr != NULL)
    {
        int index = searchVisitedArray(visited, n, ptr->point);
        if (!visited[index].visitVal)
        {
            Pair pt = ptr->point;
            pathfound = dfs(pt, end, stk, n, node_arr, k, visited);
            if (pathfound)
                break;
        }
        ptr = ptr->next;
    }
    if (!pathfound)
        pop(stk);
    return pathfound;
}

main()
{
    Stack *stk = createStack();
    int n, m;
    cin >> n >> m;
    int **field = new int *[n];
    for (int i = 0; i < n; i++)
    {
        field[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            field[i][j] = 0;
        }
    }
    Pair start, end;
    cin >> start.x >> start.y;
    cin >> end.x >> end.y;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        field[x][y] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
    visitedArray *visited = new visitedArray[n * n];
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[k].point= {i,j};
            visited[k].visitVal = false;
            k++;
        }
    }
    // for (int i = 0; i < k; i++)
    // {
    //     cout<<"("<<visited[i].point.x<<","<<visited[i].point.y<<")->"<<visited[i].visitVal<<endl;
    // }
    nodeArray node_arr[n * n] = {{0, 0, NULL}};
    k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (field[i][j] != -1)
            {
                node_arr[k].point = {i,j};
                createAdjList(field, node_arr[k], n);
                k++;
            }
        }
    }
    // printAdjList(node_arr, k);
    bool pathfound = dfs(start, end, stk, n, node_arr, k, visited);
    if (pathfound)
        cout << "Path Found" << endl;
    else
        cout << "Path not found" << endl;
    Pair pathArray[stk->size];
    int size=stk->size;
    for (int i = 0; i < size; i++)
    {
        pathArray[i]=pop(stk);
    }
    
    for (int i = size-1; i >= 0; i--)
    {
        cout<<"("<<pathArray[i].x<<","<<pathArray[i].y<<") ";
    }
    
}