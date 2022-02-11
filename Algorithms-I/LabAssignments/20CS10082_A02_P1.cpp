#include <iostream>
#include <string.h> //for using strcmp
using namespace std;

/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name:Sidharth Vishwakarma
Roll Number:20CS10082
HackerRank ID:sid_visw
********************************/

#define RANGE 10000

//defining the structure Flower
typedef struct
{
    char *color;
    int npetals;
    int leaves;
    int radius;
    int height;
} Flower;

void countSort_height(Flower flower[], long n)
{
    Flower output[n];
    int count[RANGE+1], i;
    memset(count, 0, sizeof(count));
    for (i = 0;i<n; ++i)
        ++count[flower[i].height];
    for (i = 1; i <= RANGE; ++i)
        count[i] += count[i - 1];
    for (i = 0;i<n; ++i)
    {
        output[count[flower[i].height] - 1] = flower[i];
        --count[flower[i].height];
    }
    for (i = 0;i<n; ++i)
        flower[i] = output[i];
}
void countSort_radius(Flower flower[], long n)
{
    Flower output[n];
    int count[RANGE+1], i;
    memset(count, 0, sizeof(count));
    for (i = 0;i<n; ++i)
        ++count[flower[i].radius];
    for (i = 1; i <= RANGE; ++i)
        count[i] += count[i - 1];
    for (i = 0;i<n; ++i)
    {
        output[count[flower[i].radius] - 1] = flower[i];
        --count[flower[i].radius];
    }
    for (i = 0;i<n; ++i)
        flower[i] = output[i];
}
void countSort_leaves(Flower flower[], long n)
{
    Flower output[n];
    int count[RANGE+1], i;
    memset(count, 0, sizeof(count));
    for (i = 0;i<n; ++i)
        ++count[flower[i].leaves];
    for (i = 1; i <= RANGE; ++i)
        count[i] += count[i - 1];
    for (i = 0;i<n; ++i)
    {
        output[count[flower[i].leaves] - 1] = flower[i];
        --count[flower[i].leaves];
    }
    for (i = 0;i<n; ++i)
        flower[i] = output[i];
}
void countSort_npetals(Flower flower[], long n)
{
    Flower output[n];
    int count[RANGE+1], i;
    memset(count, 0, sizeof(count));
    for (i = 0;i<n; ++i)
        ++count[flower[i].npetals];
    for (i = 1; i <= RANGE; ++i)
        count[i] += count[i - 1];
    for (i = 0;i<n; ++i)
    {
        output[count[flower[i].npetals] - 1] = flower[i];
        --count[flower[i].npetals];
    }
    for (i = 0;i<n; ++i)
        flower[i] = output[i];
}

//driver code
int main()
{
    bool found = false; //variable to decide whether princess found or not
    int n;
    cin >> n; //taking size input
    Flower flower[100];
    //taking inputs from the user
    for (int i = 0; i < n; i++)
    {
        flower[i].color = new char[7];
        scanf("\n");
        scanf("%[^,],%d,%d,%d,%d", flower[i].color, &flower[i].npetals, &flower[i].leaves, &flower[i].radius, &flower[i].height);
    }

    countSort_height(flower, n);
    countSort_radius(flower, n);
    countSort_leaves(flower, n);
    countSort_npetals(flower, n);

    //loop that finds common element and prints which one is the princess
    for(int i=0,j=i+1;j<n;i++,j++){
        if(flower[i].npetals==flower[j].npetals&&flower[i].leaves==flower[j].leaves&&flower[i].radius==flower[j].radius&&flower[i].height==flower[j].height){
            found=true;
            if(!strcmp(flower[i].color,"white"))
                printf("%s,%d,%d,%d,%d\n",flower[i].color,flower[i].npetals,flower[i].leaves,flower[i].radius,flower[i].height);
            else
                printf("%s,%d,%d,%d,%d\n",flower[j].color,flower[j].npetals,flower[j].leaves,flower[j].radius,flower[j].height);
        }
    }

    //if not found then print "RIP"
    if (!found)
        cout << "RIP";
    return 0;
}