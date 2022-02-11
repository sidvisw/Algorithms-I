#include <iostream>
#include <climits>
using namespace std;

/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name:Sidharth Vishwakarma
Roll Number:20CS10082
HackerRank ID:sid_visw
********************************/
#define SIZE 1000
// your code here
struct StringCount
{
    string str;
    int count;
};

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
    HashTable *hashTable = HT;
    HT->array = NULL;
    HT = NULL;
    delete hashTable->array; //deleting the array associated with hash table
    delete hashTable;        //deleting the hash table
}
//hash table ADT ends here

//mergesort implementation
void merging_func(StringCount points[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    StringCount L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = points[l + i];
    for (j = 0; j < n2; j++)
        R[j] = points[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].count >= R[j].count)
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
void mergesort(StringCount arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merging_func(arr, l, m, r);
    }
}

bool IIndicesBehind(string *ans, int index, string str, int I) //ultility function to find the presence of same magnet in previous I indices
{
    for (int i = index - 1; i >= index - I && i >= 0; i--) //loop backwards till I
    {
        if (ans[i] == str) //if a same magnet is found
            return true;   //return true
    }
    return false; //if not found then return false
}

int findMaxCount(StringCount arr[], int arrSize, int I, string *ans, int index) //function to find the max value magnet which is not placed in previous I indices
{
    int max = INT_MIN;                //initialize max to INT_MIN
    int maxIndex = -1;                //initialize maxIndex to -1
    for (int i = 0; i < arrSize; i++) //loop till all array elements
    {
        if (max < arr[i].count && !IIndicesBehind(ans, index, arr[i].str, I)) //if a max value magnet is found which does not occur in previous I indices
        {
            //update max and maxIndex
            max = arr[i].count;
            maxIndex = i;
        }
    }
    return maxIndex; //return the maxIndex
}

string *getAnswer(StringCount arr[], int arrSize, HashTable *HT, int I, int n) //ultility function the will give the magnets organised
{
    string *ans = new string[n]; //initialize the answer array of strings
    for (int i = 0; i < n; i++)
    {
        ans[i] = ""; //make every index as ""
    }
    for (int i = 0; i < n; i++) //loop n times
    {
        int max = findMaxCount(arr, arrSize, I, ans, i); //find max index which is not in previous I indices
        if (max == -1)                                   //if no max found
        {
            return NULL; //return NUll
        }
        ans[i] = arr[max].str; //if max found then append the max value in answer
        arr[max].count--;      //decrement the count of that max value
    }
    return ans; //return the answer
}

bool containVowel(string str) //function to check if the string contains a vowel or not
{
    for (int i = 0; i < str.size(); i++) //loop for all string characters
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u') //if vowel found
            return true;                                                                       //return true
    }
    return false; //if not found return false
}

bool inPrevious(StringCount arr[], int size, string key) //funtion to check if a string is already avaliable in StringCount array
{
    for (int i = 0; i < size; i++) //loop for all elements
    {
        if (arr[i].str == key) //if element exists already
            return true;       //return true
    }
    return false; //if not exist return false
}

//driver function
int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    cin >> t; //input test cases
    while (t--)
    {
        int n, I;
        cin >> n >> I;                    //input n and I
        scanf("\n");                      //flush the newline character
        HashTable *HT = Initialize(SIZE); //initilaize hash table
        StringCount arr[n];               //string count array to store the string along with its count
        int arrSize = 0;                  //size of string count array
        for (int i = 0; i < n; i++)       //loop n times
        {
            string key;
            cin >> key;                         //input the magnet name
            if (!inPrevious(arr, arrSize, key)) //if it do not exists already
                arr[arrSize++].str = key;       //then append it onto string count array
            int value = Search(HT, key);        //search for element
            if (value == 0 || value == -1)      //if not found
            {
                Insert(HT, key, 1); //insert it in hash table with value = 1
            }
            else //if it already exists in hash table
            {
                IncreaseValue(HT, key); //then increment its value
            }
        }
        for (int i = 0; i < arrSize; i++)
        {
            arr[i].count = Search(HT, arr[i].str); //store the count in string count array
        }
        mergesort(arr, 0, arrSize - 1);                  //sort according to count
        string *ans = getAnswer(arr, arrSize, HT, I, n); //get the answer
        if (ans == NULL)                                 //if answer==NULL
            cout << "-1" << endl;                        //then print -1
        else
        {
            for (int i = 0; i < n - 1; i++) //loop for all elements of answer array
            {
                //condition if the string contain vowel or not
                bool cond1 = containVowel(ans[i]);
                bool cond2 = containVowel(ans[i + 1]);
                if (cond1 && cond2) //if both contain vowel
                {
                    cout << ans[i] << " # "; //print # after the ith string
                }
                else if (cond1 || cond2) //if any one contain vowel
                {
                    cout << ans[i] << " | "; //print | after the ith string
                }
                else
                {
                    cout << ans[i] << " "; //else just print space after ith string
                }
            }
            cout << ans[n - 1] << endl; //output the last string
        }
        DeleteTable(HT); //delete the hash table
    }
    return 0;
}