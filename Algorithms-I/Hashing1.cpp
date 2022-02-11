#include <bits/stdc++.h>
using namespace std;

typedef struct HashNode
{
    int key, value;
} HashNode;

typedef struct HashTable
{
    int size;
    struct HashNode **table;
} HashTable;

void insert(HashTable &HT, int key, int value)
{
    int index1 = key % HT.size;
    int index2 = value % HT.size;
    HT.table[index1][index2] = {key, value};
}

void deleteCounterparty(HashTable &counterpartyHT, HashTable &portfolioHT, int counterpartyId)
{
    int portfolios[100], numPortfolio = 0;
    int index = counterpartyId % counterpartyHT.size;
    for (int i = 0; i < counterpartyHT.size; i++)
    {
        if (counterpartyHT.table[index][i].key == counterpartyId)
        {
            portfolios[numPortfolio++] = counterpartyHT.table[index][i].value;
            counterpartyHT.table[index][i] = {-1, -1};
        }
    }

    for (int i = 0; i < numPortfolio; i++)
    {
        int index1 = portfolios[i] % portfolioHT.size;
        int index2 = counterpartyId % portfolioHT.size;
        portfolioHT.table[index1][index2] = {-1, -1};
    }
}

void writeOutput(HashTable counterpartyHT, HashTable portfolioHT)
{
    for (int i = 0; i < portfolioHT.size; i++)
    {
        bool cond = true;
        for (int j = 0; j < portfolioHT.size; j++)
        {
            if (portfolioHT.table[i][j].key != -1)
            {
                cout << "p " << i << " " << portfolioHT.table[i][j].key << " " << portfolioHT.table[i][j].value << endl;
                cond = false;
            }
        }
        if (cond)
        {
            cout << "p " << i << " -1 -1" << endl;
        }
    }

    for (int i = 0; i < counterpartyHT.size; i++)
    {
        bool cond = true;
        for (int j = 0; j < counterpartyHT.size; j++)
        {
            if (counterpartyHT.table[i][j].key != -1)
            {
                cout << "c " << i << " " << counterpartyHT.table[i][j].key << " " << counterpartyHT.table[i][j].value << endl;
                cond = false;
            }
        }
        if (cond)
        {
            cout << "c " << i << " -1 -1" << endl;
        }
    }
}

main()
{
    int size, n;
    cin >> size >> n;
    HashTable counterpartyHT, portfolioHT;
    counterpartyHT.size = portfolioHT.size = size;
    counterpartyHT.table = new HashNode *[size];
    portfolioHT.table = new HashNode *[size];
    for (int i = 0; i < size; i++)
    {
        counterpartyHT.table[i] = new HashNode[size];
        portfolioHT.table[i] = new HashNode[size];
        for (int j = 0; j < size; j++)
        {
            counterpartyHT.table[i][j] = {-1, -1};
            portfolioHT.table[i][j] = {-1, -1};
        }
    }
    for (int i = 0; i < n; i++)
    {
        char ch;
        cin >> ch;
        if (ch == '+')
        {
            int counterpartyId, portfolioNo;
            cin >> counterpartyId >> portfolioNo;
            insert(counterpartyHT, counterpartyId, portfolioNo);
            insert(portfolioHT, portfolioNo, counterpartyId);
        }
        else if (ch == '-')
        {
            int counterpartyId;
            cin >> counterpartyId;
            deleteCounterparty(counterpartyHT, portfolioHT, counterpartyId);
        }
        else
        {
        }
    }

    writeOutput(counterpartyHT, portfolioHT);
}