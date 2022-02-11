#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h> //for working with strings
/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name:Sidharth Vishwakarma
Roll Number:20CS10082
HackerRank ID:sid_visw
********************************/

using namespace std;
#define MAX 10000
struct date
{
    int m, d, h;
};
struct dpArray
{
    int count;
    char seq[100];
};

//function to find no. of days
int findDays(date start, date end)
{
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int n1 = start.d;
    for (int i = 0; i < start.m - 1; i++)
        n1 += monthDays[i];
    int n2 = end.d;
    for (int i = 0; i < end.m - 1; i++)
        n2 += monthDays[i];
    return n2 - n1;
}

bool isValid(date start, int hr, int hour)
{
    if (hr > hour)
        return true;
    return (start.h + hr) % 24;
}

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    //input from user
    date start, end;
    char temp[3];
    scanf("2021-%[^-]-%d %d", temp, &start.d, &start.h);
    sscanf(temp, "%d", &start.m);
    scanf("\n");
    scanf("2021-%[^-]-%d %d", temp, &end.d, &end.h);
    sscanf(temp, "%d", &end.m);
    int w, a;
    cin >> w >> a;

    int days = findDays(start, end);
    int hr = days * 24 + (end.h - start.h);
    dpArray dp[hr + a + 1];
    int size = hr + a + 1;

    //initialization
    for (int i = 0; i < size; i++)
    {
        dp[i] = {MAX, {'\0'}};
    }
    dp[0].count = 0;
    for (int i = w; i < size; i += w)
    {
        if (!isValid(start, i, hr))
            break;
        for (int j = 0; i - j > 0; j += a)
        {
            if (!isValid(start, i - j, hr))
                break;
            if (dp[i - j].count >= i / w + j / a)
            {
                dp[i - j].count = i / w + j / a;
                strcpy(dp[i - j].seq, "");
                for (int k = 0; k < i / w; k++)
                {
                    strcat(dp[i - j].seq, "w");
                }
                for (int k = 0; k < j / a; k++)
                {
                    strcat(dp[i - j].seq, "a");
                }
            }
            int next = i - j + w;
            while (isValid(start, next, hr) && next < size)
            {
                if (dp[next].count >= dp[i - j].count + (next - i + j) / w)
                {
                    dp[next].count = dp[i - j].count + (next - i + j) / w;
                    strcpy(dp[next].seq, dp[i - j].seq);
                    for (int k = 0; k < (next - i + j) / w; k++)
                    {
                        strcat(dp[next].seq, "w");
                    }
                }
                next += w;
            }
        }
    }

    //DP algorithm
    int t = 2000;
    while (t--)
    {
        for (int i = 0; i < size; i++)
        {
            if (isValid(start, i, hr))
            {
                if ((i - w < 0) && !(i + a >= size))
                {
                    if (dp[i].count >= 1 + dp[i + a].count)
                    {
                        dp[i].count = 1 + dp[i + a].count;
                        strcpy(dp[i].seq, dp[i + a].seq);
                        strcat(dp[i].seq, "a");
                    }
                }
                else if (!(i - w < 0) && (i + a >= size))
                {
                    if (dp[i].count >= 1 + dp[i - w].count)
                    {
                        dp[i].count = 1 + dp[i - w].count;
                        strcpy(dp[i].seq, dp[i - w].seq);
                        strcat(dp[i].seq, "w");
                    }
                }
                else if (!(i - w < 0) && !(i + a >= size))
                {
                    if (dp[i - w].count < dp[i + a].count)
                    {
                        if (dp[i].count >= 1 + dp[i - w].count)
                        {
                            dp[i].count = 1 + dp[i - w].count;
                            strcpy(dp[i].seq, dp[i - w].seq);
                            strcat(dp[i].seq, "w");
                        }
                    }
                    else
                    {
                        if (dp[i].count >= 1 + dp[i + a].count)
                        {
                            dp[i].count = 1 + dp[i + a].count;
                            strcpy(dp[i].seq, dp[i + a].seq);
                            strcat(dp[i].seq, "a");
                        }
                    }
                }
            }
        }
    }

    //output
    for (int i = 0; i < size; i++)
    {
        cout << "index=" << i << " " << dp[i].count << " " << dp[i].seq << endl;
    }
    // if(dp[hr].count>=MAX){
    //     cout<<"0"<<endl;
    //     exit(0);
    // }
    // cout<<dp[hr].count<<endl;
    // for (int i = 0; i < strlen(dp[hr].seq); i++)
    // {
    //     cout<<dp[hr].seq[i]<<endl;
    // }
    return 0;
}