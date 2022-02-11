#include <bits/stdc++.h>
using namespace std;
typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;
Node *newNode(int data)
{
    Node *ptr = new Node;
    ptr->key = data;
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->parent = NULL;
    return ptr;
}
//insertion of an element
void insertKey(Node *&root, int key)
{
    Node *ptr = root;
    Node *temp;
    if (root == NULL)
    {
        root = newNode(key);
        return;
    }
    while (ptr != NULL)
    {
        if (key > ptr->key)
        {
            if (ptr->right == NULL)
            {
                ptr->right = newNode(key);
                ptr->right->parent = ptr;
                return;
            }
            ptr = ptr->right;
        }
        else
        {
            if (ptr->left == NULL)
            {
                ptr->left = newNode(key);
                ptr->left->parent = ptr;
                return;
            }
            ptr = ptr->left;
        }
    }
}
//searching of an element
Node *Search(Node *root, int element)
{
    Node *ptr = root;
    while (ptr != NULL)
    {
        if (ptr->key == element)
        {
            return ptr;
        }
        else if (element > ptr->key)
        {
            ptr = ptr->right;
        }
        else
        {
            ptr = ptr->left;
        }
    }
    return NULL;
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
//finding max
int BSTmax(Node *root)
{
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root->key;
}
//finding min
int BSTmin(Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root->key;
}
//finding successor
int Successor(Node *root, int input)
{
    Node *x = Search(root, input);
    if (x->right != NULL)
    {
        return BSTmin(x->right);
    }
    Node *y = x->parent;
    while (y != NULL && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y->key;
}
//finding predecessor
int Predecessor(Node *root, int input)
{
    Node *x = Search(root, input);
    if (x->left != NULL)
    {
        return BSTmax(x->left);
    }
    Node *y = x->parent;
    while (y != NULL && x == y->left)
    {
        x = y;
        y = y->parent;
    }
    return y->key;
}

//deleting a node
int BSTDelete(Node *&root, int input)
{
    Node *y = Search(root, input);
    int temp = y->key;
    if (y->left == NULL && y->right == NULL)
    {
        if (y->parent->left == y)
        {
            y->parent->left = NULL;
            delete y;
            return temp;
        }
        else
        {
            y->parent->right = NULL;
            delete y;
            return temp;
        }
    }
    else if (y->left != NULL && y->right == NULL)
    {
        if (y->parent->left == y)
        {
            y->parent->left = y->left;
            y->left->parent = y->parent;
            delete y;
            return temp;
        }
        else
        {
            y->parent->right = y->left;
            y->left->parent = y->parent;
            delete y;
            return temp;
        }
    }
    else if (y->left == NULL && y->right != NULL)
    {
        if (y->parent->left == y)
        {
            y->parent->left = y->right;
            y->right->parent = y->parent;
            delete y;
            return temp;
        }
        else
        {
            y->parent->right = y->right;
            y->right->parent = y->parent;
            delete y;
            return temp;
        }
    }
    else
    {
        Node *successor = Search(root, Successor(root, y->key));
        int temporary = successor->key;
        BSTDelete(root,successor->key);
        y->key=temporary;
        return temp;
    }
}
main()
{
    Node *root = NULL;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int key;
        cin >> key;
        insertKey(root, key);
    }
    //traversal codes
    cout << "Preorder traversal..." << endl;
    Preorder(root);
    int input;
    cin >> input;
    int del = BSTDelete(root, input);
    cout << "Deleted node is " << del << endl;
    //traversal codes
    cout << "Preorder traversal..." << endl;
    Preorder(root);
    cin >> input;
    del = BSTDelete(root, input);
    cout << "Deleted node is " << del << endl;
    //traversal codes
    cout << "Preorder traversal..." << endl;
    Preorder(root);
    cin >> input;
    del = BSTDelete(root, input);
    cout << "Deleted node is " << del << endl;
    //traversal codes
    cout << "Preorder traversal..." << endl;
    Preorder(root);
}