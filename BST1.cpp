#include <bits/stdc++.h>
using namespace std;
typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
    // struct node*parent;
} Node;

typedef struct
{
    Node **Arr;
    int queue_size, start_id, end_id;
} QUEUE;
//function to create a queue with no elements in it
void init(QUEUE *qP, int size)
{
    qP->Arr = new Node *[size];
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
void enqueue(QUEUE *qP, Node *data)
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
Node *dequeue(QUEUE *qP)
{
    Node *ret_data = new Node;
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
Node *getFront(QUEUE *qP)
{
    if (isempty(*qP))
    {
        cout << "\nQueue Underflow";
        exit(-1);
    }
    else
    {
        return qP->Arr[qP->start_id];
    }
}

Node *newNode(int data)
{
    Node *ptr = new Node;
    ptr->key = data;
    ptr->left = NULL;
    ptr->right = NULL;
    return ptr;
}

//taking the binary tree as a input from user
Node *gen_binTree(int keys[], int n)
{
    QUEUE *q = new QUEUE;
    init(q, 1e4);
    Node *root = newNode(keys[0]);
    enqueue(q, root);
    for (int i = 1; i < n; i += 2)
    {
        if (keys[i] == INT_MIN)
        {
            getFront(q)->right = newNode(keys[i + 1]);
            enqueue(q, getFront(q)->right);
        }
        else if (keys[i + 1] == INT_MIN)
        {
            getFront(q)->left = newNode(keys[i]);
            enqueue(q, getFront(q)->left);
        }
        else
        {
            getFront(q)->left = newNode(keys[i]);
            enqueue(q, getFront(q)->left);
            getFront(q)->right = newNode(keys[i + 1]);
            enqueue(q, getFront(q)->right);
        }
        dequeue(q);
    }
    return root;
}

//traversal techniques
void visit(Node *n)
{
    cout << "We visited node that contains the key " << n->key << endl;
}
void Preorder(Node *root)
{
    if (!root)
        return;
    visit(root);
    Preorder(root->left);
    Preorder(root->right);
}
void Inorder(Node *root)
{
    if (!root)
        return;
    Inorder(root->left);
    visit(root);
    Inorder(root->right);
}
void Postorder(Node *root)
{
    if (!root)
        return;
    Postorder(root->left);
    Postorder(root->right);
    visit(root);
}

//finding no. of nodes in a BTree
int numberNodes(Node *root)
{
    if (root == NULL)
        return 0;
    int c1 = numberNodes(root->left);
    int c2 = numberNodes(root->right);
    return c1 + c2 + 1;
}
//finding no. of leaf nodes in a tree
int numberLeaves(Node *root)
{
    if (root == NULL)
        return 0;
    int c1 = numberLeaves(root->left);
    int c2 = numberLeaves(root->right);
    if (c1 + c2 == 0)
        return 1;
    else
        return c1 + c2;
}

//driver function
main()
{
    int n, a[50];
    for (int i = 0; i < 50; i++)
    {
        a[i] = INT_MIN;
    }
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char s[5];
        scanf("%s", s);
        if (!strcmp(s, "null"))
        {
            a[i] = INT_MIN;
        }
        else
        {
            sscanf(s, "%d", &a[i]);
        }
    }
    Node *root = gen_binTree(a, n);

    //traversal codes
    // cout<<"Preorder traversal..."<<endl;
    // Preorder(root);
    // cout<<"Inorder traversal..."<<endl;
    // Inorder(root);
    // cout<<"Postorder traversal..."<<endl;
    // Postorder(root);

    //finding no. of nodes
    // cout << "No. of nodes is " << numberNodes(root) << endl;

    //finding no. of leaf nodes
    // cout << "no. of leaf nodes is " << numberLeaves(root) << endl;
}