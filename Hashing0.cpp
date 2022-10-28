#include <bits/stdc++.h>
using namespace std;
typedef struct HashNode
{
    int key, value;
    struct HashNode *next;
} HashNode;

typedef struct HashTable
{
    int size;
    struct HashNode **table;
} HashTable;

void insert(HashTable &HT, int key, int value)
{
    int index = key % HT.size;
    HashNode *node = new HashNode;
    node->key = key;
    node->value = value;
    node->next = HT.table[index];
    HT.table[index] = node;
}

void deleteCounterParty(HashTable &counterpartyHT, HashTable &portfolioHT, int counterpartyNo)
{
    int portfolios[100], numPortfolio = 0;

    //deleting in counterparty hash table starts
    int index = counterpartyNo % counterpartyHT.size;
    HashNode *ptr = counterpartyHT.table[index];
    while (ptr != NULL && ptr->key == counterpartyNo)
    {
        portfolios[numPortfolio++] = ptr->value;
        HashNode *p = ptr;
        counterpartyHT.table[index] = ptr->next;
        ptr = ptr->next;
        delete p;
    }
    if (ptr != NULL)
        while (ptr->next != NULL)
        {
            if (ptr->next->key == counterpartyNo)
            {
                portfolios[numPortfolio++] = ptr->next->value;
                HashNode *p = ptr->next;
                ptr->next = ptr->next->next;
                delete p;
            }
            ptr = ptr->next;
        }
    //deleting in counterparty hash table ends

    //deleting in portfolio hash table starts
    for (int i = 0; i < numPortfolio; i++)
    {
        int index = portfolios[i] % portfolioHT.size;
        HashNode *ptr = portfolioHT.table[index];
        while (ptr != NULL && ptr->key == portfolios[i] && ptr->value == counterpartyNo)
        {
            HashNode *p = ptr;
            portfolioHT.table[index] = ptr->next;
            ptr = ptr->next;
            delete p;
        }
        while (ptr != NULL && ptr->next != NULL)
        {
            if (ptr->next->key == portfolios[i] && ptr->next->value == counterpartyNo)
            {
                HashNode *p = ptr->next;
                ptr->next = ptr->next->next;
                delete p;
            }
            ptr = ptr->next;
        }
    }
    //deleting in portfolio hash table ends
}

void writeOutput(HashTable counterpartyHT, HashTable portfolioHT)
{
    for (int i = 0; i < portfolioHT.size; i++)
    {
        HashNode *ptr = portfolioHT.table[i];
        if (ptr == NULL)
        {
            cout << "p " << i << " -1 -1" << endl;
        }
        while (ptr != NULL)
        {
            cout << "p " << i << " " << ptr->key << " " << ptr->value << endl;
            ptr = ptr->next;
        }
    }
    for (int i = 0; i < counterpartyHT.size; i++)
    {
        HashNode *ptr = counterpartyHT.table[i];
        if (ptr == NULL)
        {
            cout << "c " << i << " -1 -1" << endl;
        }
        while (ptr != NULL)
        {
            cout << "c " << i << " " << ptr->key << " " << ptr->value << endl;
            ptr = ptr->next;
        }
    }
}

main()
{
    int size, n;
    cin >> size >> n;
    HashTable counterpartyHT, portfolioHT;
    counterpartyHT.size = portfolioHT.size = size;
    counterpartyHT.table = new HashNode *[counterpartyHT.size];
    portfolioHT.table = new HashNode *[portfolioHT.size];
    for (int i = 0; i < counterpartyHT.size; i++)
    {
        counterpartyHT.table[i] = NULL;
    }
    for (int i = 0; i < portfolioHT.size; i++)
    {
        portfolioHT.table[i] = NULL;
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
            int counterpartyNo;
            cin >> counterpartyNo;
            deleteCounterParty(counterpartyHT, portfolioHT, counterpartyNo);
        }
        else
        {
            cout << "Invalid input...Please try again..." << endl;
            i--;
        }
    }

    writeOutput(counterpartyHT, portfolioHT);
}