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

//function to find the meeting room of luke and leia
struct node *findMeetRoom(struct node *root, int luke, int leia)
{
    if (!root)
    {
        return NULL;
    }
    if (root->data < luke && root->data < leia)
    {
        return findMeetRoom(root->right, luke, leia);
    }
    else if (root->data > luke && root->data > leia)
    {
        return findMeetRoom(root->left, luke, leia);
    }
    else
    {
        return root;
    }
}

//function to find the level at which they meet
int findLevel(struct node *root, struct node *meetRoom, int level)
{
    if (!root)
    {
        return -1;
    }
    else if (root->data == meetRoom->data)
    {
        return level;
    }
    int levelLeft = findLevel(root->left, meetRoom, level + 1);
    int levelRight = findLevel(root->right, meetRoom, level + 1);
    if (levelLeft != -1)
    {
        return levelLeft;
    }
    else
    {
        return levelRight;
    }
}

//function to find sum of all nodes at a given level
int sumLevel(struct node *root, int level)
{
    if (root == NULL)
    {
        return 0;
    }
    struct Queue *queue = createQueue(SIZE);
    Enqueue(root, queue);
    int lvl = 0, sum = 0;
    bool flag = false;
    while (!isEmpty(queue))
    {
        int qsize = queue->rear-queue->front+1;
        for (int i = 0; i < qsize; i++)
        {
            struct node *ptr = Dequeue(queue);
            if (lvl == level)
            {
                flag = true;
                sum += ptr->data;
            }
            else
            {
                if (ptr->left != NULL)
                {
                    Enqueue(ptr->left, queue);
                }
                if (ptr->right != NULL)
                {
                    Enqueue(ptr->right, queue);
                }
            }
        }
        lvl++;
        if (flag)
            break;
    }
    return sum;
}

//function to find the parent of the node provided to it
struct node *findParent(struct node *root, struct node *node, struct node *parent)
{
    struct node *ptr1, *ptr2;
    if (!root)
        return NULL;
    else if (root->data == node->data)
        return parent;
    else
    {
        ptr1 = findParent(root->left, node, root);
        ptr2 = findParent(root->right, node, root);
    }
    if (ptr1)
    {
        return ptr1;
    }
    else
    {
        return ptr2;
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
        int luke, leia, threshold;
        cin >> luke >> leia >> threshold;//take input
        cout << "Case #" << tcase << ": ";
        if (!linearSearch(array, n, luke) || !linearSearch(array, n, leia))//if node is not in the tree print -1
        {
            cout << "-1" << endl;
            continue;
        }
        struct node *meetRoom = findMeetRoom(root, luke, leia);
        cout << meetRoom->data << " ";//output meet room
        int levelOfMeet = findLevel(root, meetRoom, 0);
        cout << levelOfMeet << " ";//output level of meet
        struct node *parent = meetRoom;
        cout<<sumLevel(root,levelOfMeet)<<" ";//output sum of node at meet level
        while (levelOfMeet != -1)
        {
            
            if (sumLevel(root,levelOfMeet) < threshold)
            {
                cout << "Escaped! " << parent->data << endl;//if way found then print escaped
                break;
            }
            parent = findParent(root, parent, NULL);
            levelOfMeet--;
        }
        if (levelOfMeet == -1)
            cout << "Trapped!" << endl;//if no way the print trapped
    }
    return 0;
}