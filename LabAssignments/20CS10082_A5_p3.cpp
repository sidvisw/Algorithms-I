/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name:Sidharth Vishwakarma
Roll Number:20CS10082
HackerRank ID:sid_visw
********************************/

#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;
// For Queue Size
#define SIZE 5000
// A tree node
struct node
{
    int data;
    struct node *right, *left;
};

// A queue node
struct Queue
{
    int front, rear;
    int size;
    struct node **array;
};

// A utility function to create a new tree node
struct node *newNode(int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to create a new Queue
struct Queue *createQueue(int size)
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));

    queue->front = queue->rear = -1;
    queue->size = size;

    queue->array = (struct node **)malloc(queue->size * sizeof(struct node *));

    int i;
    for (i = 0; i < size; ++i)
        queue->array[i] = NULL;

    return queue;
}

// Standard Queue Functions
int isEmpty(struct Queue *queue)
{
    return queue->front == -1;
}

int isFull(struct Queue *queue)
{
    return queue->rear == queue->size - 1;
}

int hasOnlyOneItem(struct Queue *queue)
{
    return queue->front == queue->rear;
}

void Enqueue(struct node *root, struct Queue *queue)
{
    if (isFull(queue))
        return;

    queue->array[++queue->rear] = root;

    if (isEmpty(queue))
        ++queue->front;
}

struct node *Dequeue(struct Queue *queue)
{
    if (isEmpty(queue))
        return NULL;

    struct node *temp = queue->array[queue->front];

    if (hasOnlyOneItem(queue))
        queue->front = queue->rear = -1;
    else
        ++queue->front;

    return temp;
}

struct node *getFront(struct Queue *queue)
{
    return queue->array[queue->front];
}

// A utility function to check if a tree node
// has both left and right children
int hasOneChild(struct node *temp)
{
    return temp && (temp->left || temp->right);
}
int hasBothChild(struct node *temp)
{
    return temp && temp->left && temp->right;
}

// Function to insert a new node in complete binary tree
void insert(struct node **root, int data, struct Queue *queue)
{
    // Create a new node for given data
    struct node *temp = newNode(data);

    // If the tree is empty, initialize the root with new node.
    if (!*root)
        *root = temp;

    else
    {
        // get the front node of the queue.
        struct node *front;
        front = getFront(queue);
        while (front->data == -1)
        {
            Dequeue(queue);
            front = getFront(queue);
        }
        // If the left child of this front node doesnt exist, set the
        // left child as the new node
        if (!front->left)
            front->left = temp;

        // If the right child of this front node doesnt exist, set the
        // right child as the new node
        else if (!front->right)
            front->right = temp;

        // If the front node has both the left child and right child,
        // Dequeue() it.
        if (hasBothChild(front))
        {
            if (front->left->data == -1)
            {
                front->left = NULL;
            }
            if (front->right->data == -1)
            {
                front->right = NULL;
            }
            Dequeue(queue);
        }
    }

    // Enqueue() the new node for later insertions
    Enqueue(temp, queue);
}

//function to see if the test case is invalid or not
bool linearSearch(int arr[], int size, int element)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == element)
        {
            return true;
        }
    }
    return false;
}

//searching of an element
struct node *Search(struct node *root, int element)
{
    struct node *ptr = root;
    while (hasOneChild(ptr))
    {
        if (ptr->data == element)
        {
            return ptr;
        }
        else if (element > ptr->data)
        {
            if (ptr->right == NULL)
                break;
            ptr = ptr->right;
        }
        else
        {
            if (ptr->left == NULL)
                break;
            ptr = ptr->left;
        }
    }
    return ptr;
}

void getPath(struct node *start, struct node *end, int path[], int &size)
{
    if (!start)
        return;
    if (end == Search(start->left, end->data))
    {
        path[size++] = start->data;
        getPath(start->left, end, path, size);
    }
    if (end == Search(start->right, end->data))
    {
        path[size++] = start->data;
        getPath(start->right, end, path, size);
    }
}

void printPath(struct node *root, struct node *start, struct node *end)
{
    if (!root)
        return;
    int path1[10000], size1 = 0;
    int path2[10000], size2 = 0;
    getPath(root, start, path1, size1);
    getPath(root, end, path2, size2);
    int i = 0;
    for (i = 0; i < size1 && i < size2; i++)
    {
        if (path1[i] != path2[i])
            break;
    }
    i--;
    if (i == -1)
        i += 2;
    for (int k = size1 - 1; k >= i; k--)
    {
        cout << path1[k] << " ";
    }
    for (int k = i + 1; k <= size2 - 1; k++)
    {
        cout << path2[k] << " ";
    }
}

//driver function
int main()
{
    // Read the inputs from stdin and print output to stdout.
    int t;
    cin >> t;
    for (int tcase = 1; tcase <= t; tcase++)
    {
        // For creating the tree, initialize a struct node called root.
        struct node *root = NULL;
        struct Queue *queue = createQueue(SIZE);
        // insert each element of array into tree by using this: insert(&root, array[i], queue)
        int n;
        cin >> n;
        int array[n];
        for (int i = 0; i < n; i++)
        {
            cin >> array[i];
            insert(&root, array[i], queue);
        }
        int luke, leia;
        cin >> luke >> leia;
        cout << "Case #" << tcase << ": ";
        if (!linearSearch(array, n, luke) && !linearSearch(array, n, leia))
        {
            cout << "-1" << endl;
            continue;
        }
        struct node *hidluke, *hidleia;
        if (!linearSearch(array, n, luke))
        {
            hidluke = Search(root, luke);
            hidleia = Search(root, leia);
            cout << hidluke->data << endl;
            printPath(root, hidleia, hidluke);
            cout << hidluke->data << endl;
        }
        else
        {
            hidluke = Search(root, luke);
            hidleia = Search(root, leia);
            cout << hidleia->data << endl;
            printPath(root, hidluke, hidleia);
            cout << hidleia->data << endl;
        }
    }
    return 0;
}