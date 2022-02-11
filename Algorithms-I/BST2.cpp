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
    while (ptr!=NULL)
    {
        if (key > ptr->key)
        {
            if(ptr->right==NULL){
                ptr->right=newNode(key);
                ptr->right->parent=ptr;
                return;
            }
            ptr = ptr->right;
        }
        else
        {
            if(ptr->left==NULL){
                ptr->left=newNode(key);
                ptr->left->parent=ptr;
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
    // cout << "Preorder traversal..." << endl;
    // Preorder(root);

    //finding successor and predecessor
    int input;
    cin >> input;
    cout << "The successor of " << input << " is " << Successor(root, input) << endl;
    cout << "The predecessor of " << input << " is " << Predecessor(root, input) << endl;

    //searching of an element
    // Node *searchedNode = Search(root, input);
    // if (searchedNode != NULL)
    // {
    //     if (searchedNode->parent != NULL)
    //     {
    //         cout << "The parent of your searched node is " << searchedNode->parent->key << endl;
    //     }
    //     else
    //     {
    //         cout << "The parent of your seached node dosen't exist" << endl;
    //     }
    //     if (searchedNode->left != NULL)
    //     {
    //         cout << "The left node of your searched node is " << searchedNode->left->key << endl;
    //     }
    //     else
    //     {
    //         cout << "The left node of your seached node dosen't exist" << endl;
    //     }
    //     if (searchedNode->right != NULL)
    //     {
    //         cout << "The right node of your searched node is " << searchedNode->right->key << endl;
    //     }
    //     else
    //     {
    //         cout << "The right node of your seached node dosen't exist" << endl;
    //     }
    // }
    // else
    // {
    //     cout << "Searched node not in the BST" << endl;
    // }
}