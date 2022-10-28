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

//insertion in a binary tree
void insert_binTree(Node*&root, int key)
{
    if(!root){
        root=newNode(key);
    }
    else{
        QUEUE*q=new QUEUE;
        init(q,1e4);
        enqueue(q,root);
        while(!isempty(*q)){
            Node*deqNode=dequeue(q);
            if(!deqNode->left){
                deqNode->left=newNode(key);
                return;
            }
            else if(!deqNode->right){
                deqNode->right=newNode(key);
                return;
            }
            enqueue(q,deqNode->left);
            enqueue(q,deqNode->right);
        }
    }
}

//traversal techniques
void visit(Node* n){
    cout<<"We visited node that contains the key "<<n->key<<endl;
}
void Preorder(Node* root){
    if(!root)return;
    visit(root);
    Preorder(root->left);
    Preorder(root->right);
}
void Inorder(Node*root){
    if(!root)return;
    Inorder(root->left);
    visit(root);
    Inorder(root->right);
}
void Postorder(Node*root){
    if(!root)return;
    Postorder(root->left);
    Postorder(root->right);
    visit(root);
}

main()
{
    //taking input from the user
    Node *root = NULL;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int key;
        cin >> key;
        insert_binTree(root, key);
    }

    //traversal codes
    cout<<"Preorder traversal..."<<endl;
    Preorder(root);
    cout<<"Inorder traversal..."<<endl;
    Inorder(root);
    cout<<"Postorder traversal..."<<endl;
    Postorder(root);
}