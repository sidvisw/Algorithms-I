#include <iostream>
using namespace std;

/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name:Sidharth Vishwakarma
Roll Number:20CS10082
HackerRank ID:sid_visw
********************************/

// your code here
//hash table ADT starts here
typedef struct HashNode //hash node structure for storing values in hash table
{
    string key;
    int value;
} HashNode;

typedef struct HashTable //hash table structure for facilitating hash table in which hash node will be stored
{
    int size;
    HashNode *array;
} HashTable;
int Hash(string key, int size) //hash function for computing the hash value of any key
{
    int h = 0, p = 31; //take p=31 as given
    for (int i = 0; i < key.size(); i++)
    {
        h = (p * h + ((int)(key[i] - 'a') + 1)) % size; //computing hash value
    }
    return h;
}
HashTable *Initialize(int size) //initialising hash table
{
    HashTable *HT = new HashTable;
    HT->size = size; //initialize the size
    HT->array = new HashNode[size];
    for (int i = 0; i < HT->size; i++)
    {
        HT->array[i] = {"", 0}; //make every hash node contain empty string and value=0
    }
    return HT;
}
int Search(HashTable *HT, string key) //search for an element in hash table
{
    int index = Hash(key, HT->size); //compute hash value
    for (int i = 0; i < HT->size; i++)
    {
        if (HT->array[(index + i) % HT->size].key == key)
        {
            return HT->array[(index + i) % HT->size].value; //if key found then return its value
        }
        if (HT->array[(index + i) % HT->size].key == "")
        {
            return -1; //else if not found return -1
        }
    }
    return -1; //else if not found return -1
}
int Insert(HashTable *HT, string key, int value) //insert an element in hash table
{
    int index = Hash(key, HT->size); //compute hash value
    for (int i = 0; i < HT->size; i++)
    {
        if (HT->array[(index + i) % HT->size].value == 0) //if an empty cell is found
        {
            //we insert the key and value given to us
            HT->array[(index + i) % HT->size].key = key;
            HT->array[(index + i) % HT->size].value = value;
            return (index + i) % HT->size; //return the index of insertion
        }
    }
    return -1; //if no space available return -1
}
int Delete(HashTable *HT, string key) //delete an element in a hash table
{
    int index = Hash(key, HT->size); //compute hash value
    for (int i = 0; i < HT->size; i++)
    {
        if (HT->array[(index + i) % HT->size].key == key) //if element found
        {
            HT->array[(index + i) % HT->size].key = "A"; //mark the hash node as available(A)
            HT->array[(index + i) % HT->size].value = 0; //put its value=0
        }
        if (HT->array[(index + i) % HT->size].key == "")
        {
            return -1; //if element not found return -1
        }
    }
    return -1; //if element not found return -1
}
int IncreaseValue(HashTable *HT, string key) //increase value of a given key in hash table
{
    int index = Hash(key, HT->size);   //find hash value
    for (int i = 0; i < HT->size; i++) //search for key
    {
        if (HT->array[(index + i) % HT->size].key == key) //if key found
        {
            HT->array[(index + i) % HT->size].value++; //increment its value
            return (index + i) % HT->size;             //return the index in hash table
        }
        if (HT->array[(index + i) % HT->size].key == "") //if key not found
        {
            return -1; //return -1
        }
    }
    return -1; //if key not found return -1
}
void Print(HashTable *HT) //printing the hash table
{
    for (int i = 0; i < HT->size; i++) //loop for all the hash nodes in hash table
    {
        if (HT->array[i].value == 0) //if no element exists there in hash table
        {
            cout << "(,0) "; //then print "(,0)"
        }
        else //if value exists in hash table
        {
            cout << "(" << HT->array[i].key << "," << HT->array[i].value << ") "; //print the "(key,value)" pair
        }
    }
    cout << endl;
}
void DeleteTable(HashTable *HT) //deleting the whole table
{
    HashTable*hashTable=HT;
    HT->array=NULL;
    HT=NULL;
    delete hashTable->array; //deleting the array associated with hash table
    delete hashTable;        //deleting the hash table
}
//hash table ADT ends here

//driver function
int main()
{
    /* Enter your code. Read input from STDIN. Print output to STDOUT */
    int t;
    cin >> t; //input test cases
    while (t--)
    {
        int size, n;
        cin >> size >> n;                 //input size and N
        HashTable *HT = Initialize(size); //initialize the hash table
        for (int i = 0; i < n; i++)       //taking inputs
        {
            string str;
            cin >> str;
            if (str == "I") //insert operation
            {
                string key;
                int value;
                cin >> key >> value;
                Insert(HT, key, value); //insert into hash table
            }
            if (str == "IV") //increase value operation
            {
                string key;
                cin >> key;
                IncreaseValue(HT, key); //increase the value of the given key in hash table
            }
            if (str == "D") //delete operation
            {
                string key;
                cin >> key;
                Delete(HT, key); //delete the element with the given key in hash table
            }
        }
        Print(HT);       //print the hash table
        DeleteTable(HT); //delete the whole hash table
    }
    return 0;
}