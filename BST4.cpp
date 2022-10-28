#include <bits/stdc++.h>
using namespace std;
//array structure to store the freq and corresponding char
typedef struct
{
    char ch;
    int freq;
} Array;
typedef struct
{
    char ch;
    char code[1000];
} Huffman;

//merge sort implementation
void merging_func(Array points[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Array L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = points[l + i];
    for (j = 0; j < n2; j++)
        R[j] = points[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].freq <= R[j].freq)
        {
            points[k] = L[i];
            i++;
        }
        else
        {
            points[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        points[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        points[k] = R[j];
        j++;
        k++;
    }
}
void mergesort(Array arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);

        merging_func(arr, l, m, r);
    }
}

//node defining and adding function
typedef struct node
{
    char *ch;
    int freq;
    struct node *left;
    struct node *right;
    struct node *next;
} Node;
Node *newNode(char *ch, int freq)
{
    Node *ptr = new Node;
    ptr->ch = ch;
    ptr->freq = freq;
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->next = NULL;
    return ptr;
}

//function to find index in Huffman Array
int findIndex(char ch, Huffman H[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (H[i].ch == ch)
        {
            return i;
        }
    }
    return -1;
}

//traversal techniques
void TreeTraverse(Node *T, char *C, Huffman H[], int size)
{
    if (!T)
        return;
    if (T->left == NULL && T->right == NULL)
    {
        strcpy(H[findIndex(T->ch[0], H, size)].code, C);
    }
    else
    {
        TreeTraverse(T->left, strcpy(C, strcat(C, "0")), H, size);
        C[strlen(C) - 1] = '\0';
        TreeTraverse(T->right, strcpy(C, strcat(C, "1")), H, size);
        C[strlen(C) - 1] = '\0';
    }
}

//function for searching char in symbols
int searchChar(Array symbols[], int size, char ch)
{
    for (int i = 0; i < size; i++)
    {
        if (symbols[i].ch == ch)
        {
            return i;
        }
    }
    return -1;
}

//function to create a linked list
Node *createLinkedList(Array symbols[], int size)
{
    char str[2] = {symbols[0].ch, '\0'};
    char *s = new char[2];
    strcpy(s, str);
    Node *head = newNode(s, symbols[0].freq);
    Node *ptr = head;
    for (int i = 1; i < size; i++)
    {
        str[0] = symbols[i].ch;
        str[1] = '\0';
        char *s = new char[2];
        strcpy(s, str);
        Node *p = newNode(s, symbols[i].freq);
        ptr->next = p;
        ptr = ptr->next;
    }
    return head;
}

//function to merge two nodes
Node *mergeNodes(Node *node1, Node *node2, int nodeIndex)
{
    char str[3] = {'N', char('0' + nodeIndex), '\0'};
    Node *newnode = newNode(str, node1->freq + node2->freq);
    newnode->left = node1;
    newnode->right = node2;
    return newnode;
}

//function to insert the merged nodes
void sortedInsertion(Node *&head, Node *element)
{
    Node *ptr = head;
    if (!head)
    {
        head = element;
    }
    else if (head->freq > element->freq)
    {
        element->next = head;
        head = element;
    }
    else
    {
        while (ptr->next != NULL && ptr->next->freq < element->freq)
        {
            ptr = ptr->next;
        }
        element->next = ptr->next;
        ptr->next = element;
    }
}

//driver function
main()
{
    int t, k = 0;
    Array symbols[50];
    cin >> t;
    while (t--)
    {
        cin.ignore();
        char str[50];
        cin>>str;
        for (int i = 0; i < strlen(str); i++)
        {
            int index = searchChar(symbols, k, str[i]);
            if (index != -1)
            {
                symbols[index].freq++;
            }
            else
            {
                symbols[k++] = {str[i], 1};
            }
        }
    }
    mergesort(symbols, 0, k - 1);
    // for (int i = 0; i < k; i++)
    // {
    //     cout<<symbols[i].ch<<" "<<symbols[i].freq<<endl;
    // }
    Node *listhead = createLinkedList(symbols, k);
    Node *ptr = listhead;
    // while(ptr!=NULL){
    //     cout<<ptr->ch<<" "<<ptr->freq<<endl;
    //     ptr=ptr->next;
    // }
    int nodeIndex = 0;
    while (listhead->next)
    {
        Node *mergedNodes = mergeNodes(listhead, listhead->next, nodeIndex);
        nodeIndex++;
        listhead = listhead->next->next;
        sortedInsertion(listhead, mergedNodes);
    }

    //creating Huffman array
    Huffman H[k];
    for (int i = 0; i < k; i++)
    {
        H[i].ch = symbols[i].ch;
    }
    char *C = new char[1000];
    strcpy(C, "");
    TreeTraverse(listhead, C, H, k);
    char input[1000];

    //encoder
    cout << "Enter the text to be encoded: ";
    cin >> input;
    char *output = new char[1000];
    strcpy(output, "");
    for (int i = 0; i < strlen(input); i++)
    {
        strcpy(output, strcat(output, H[findIndex(input[i], H, k)].code));
    }
    cout << "The encoded text for " << input << " is " << output << endl;

    //decoder
    cout << "Enter the text to be decoded: ";
    cin >> input;
    char cache[1000] = "";
    strcpy(output, "");
    for (int i = 0; i < strlen(input); i++)
    {
        char b[2] = {input[i], '\0'};
        strcpy(cache, strcat(cache, b));
        for (int j = 0; j < k; j++)
        {
            if (!strcmp(cache, H[j].code))
            {
                char s[2] = {H[j].ch, '\0'};
                strcpy(output, strcat(output, s));
                strcpy(cache, "");
            }
        }
    }
    cout << "The decoded text of " << input << " is " << output << endl;
}