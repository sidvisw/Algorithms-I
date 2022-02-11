#include <bits/stdc++.h>
using namespace std;
struct node
{
    node *parent;
    int rank;
};
void makeSet(node *&p)
{
    p=new node;
    p->rank = 0;
    p->parent = p;
}
node *findSet(node *ptr)
{
    if (ptr->parent != ptr)
    {
        ptr->parent = findSet(ptr->parent);
    }
    return ptr->parent;
}
bool mergeSet(node *x, node *y)
{
    if (x == y)
        return false;
    if (x->rank < y->rank)
    {
        x->parent = y;
    }
    else if (x->rank > y->rank)
    {
        y->parent = x;
    }
    else
    {
        x->parent = y;
        y->rank++;
    }
    return true;
}
void printGrid(int m, int n, bool **H, bool **V)
{
    cout << "+   +";
    for (int i = 0; i < n - 1; i++)
    {
        cout << "---+";
    }
    cout << endl;
    for (int i = 0; i < m; i++)
    {
        cout << "|   ";
        for (int j = 0; j < n - 1; j++)
        {
            if (V[i][j])
            {
                cout << "    ";
            }
            else
            {
                cout << "|   ";
            }
        }
        if (i == m - 1)
        {
            cout << " " << endl
                 << "+";
            for (int j = 0; j < n; j++)
            {
                cout << "---+";
            }
            cout << endl;
            break;
        }
        else
        {
            cout << "|" << endl;
        }
        cout << "+";
        for (int j = 0; j < n; j++)
        {
            if (H[i][j])
            {
                cout << "   +";
            }
            else
            {
                cout << "---+";
            }
        }
        cout << endl;
    }
}
bool findTreasure(int m, int n, node ***C, bool **H, bool **V)
{
    int i = 0;
    while (i < m * n - 1)
    {
        int wall = rand() % 2;
        if (wall)
        {
            int x = rand() % (m - 1);
            int y = rand() % n;
            node *a = findSet(C[x][y]);
            node *b = findSet(C[x + 1][y]);
            if (a != b)
            {
                H[x][y] = true;
                mergeSet(a, b);
                i++;
            }
        }
        else
        {
            int x = rand() % m;
            int y = rand() % (n - 1);
            node *a = findSet(C[x][y]);
            node *b = findSet(C[x][y + 1]);
            if (a != b)
            {
                V[x][y] = true;
                mergeSet(a, b);
                i++;
            }
        }
    }
    if (findSet(C[0][0]) == findSet(C[m - 1][n - 1]))
        return true;
    return false;
}
main()
{
    srand((unsigned int)time(NULL));
    int m, n;
    char str[10];
    scanf("%[^\n]%*c", str);
    if (strlen(str) == 0)
    {
        m = 10;
        n = 10;
    }
    else
    {
        sscanf(str, "%d%d", &m, &n);
    }
    node ***C = new node **[m];
    for (int i = 0; i < m; i++)
    {
        C[i] = new node *[n];
        for (int j = 0; j < n; j++)
        {
            makeSet(C[i][j]);
        }
    }
    bool **H = new bool *[m - 1];
    bool **V = new bool *[m];
    for (int i = 0; i < m - 1; i++)
    {
        H[i] = new bool[n];
        for (int j = 0; j < n; j++)
        {
            H[i][j] = false;
        }
    }
    for (int i = 0; i < m; i++)
    {
        V[i] = new bool[n - 1];
        for (int j = 0; j < n - 1; j++)
        {
            V[i][j] = false;
        }
    }
    cout << "Initial Grid" << endl;
    printGrid(m, n, H, V);
    if (findTreasure(m, n, C, H, V))
    {
        cout << "The final chamber can be reached from the start chamber." << endl;
        cout << "Final Grid" << endl;
        printGrid(m, n, H, V);
    }
}