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
bool linearSearch(int arr[], int size, struct node *node)
{
    if (!node)
        return true;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == node->data)
        {
            return true;
        }
    }
    return false;
}

//appending function to append in covered
void appendFunc(int arr[], int &size, int item)
{
    arr[size++] = item;
}

//function performing depth first search to find no. of sensors
void dfs(struct node *root, int &sensors, int covered[], int &size, struct node *parent)
{
    if (!root)
        return;
    dfs(root->left, sensors, covered, size, root);//performing dfs in left subtree
    dfs(root->right, sensors, covered, size, root);//performing dfs in right subtree
    if (parent == NULL && !linearSearch(covered, size, root) || !linearSearch(covered, size, root->left) || !linearSearch(covered, size, root->right))
    {
        //according appending into covered and incrementing sensors
        sensors++;
        appendFunc(covered, size, root->data);
        if (parent)
            appendFunc(covered, size, parent->data);
        if (root->left)
            appendFunc(covered, size, root->left->data);
        if (root->right)
            appendFunc(covered, size, root->right->data);
    }
}

//working function to find no. of sensors
int minSensorRequired(struct node *root)
{
    int sensors = 0;
    int covered[10000], size = 0;
    dfs(root, sensors, covered, size, NULL);
    return sensors;
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
        cout << "Case #" << tcase << ": ";
        cout << minSensorRequired(root) << endl;
    }
    return 0;
}