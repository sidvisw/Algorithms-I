#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name:Sidharth Vishwakarma
Roll Number:20CS10082
HackerRank ID:sid_visw
********************************/

using namespace std;

struct battalion
{
    char beta;
    int num;
};

void merging_func_battalion(struct battalion points[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    struct battalion L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = points[l + i];
    for (j = 0; j < n2; j++)
        R[j] = points[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].beta <= R[j].beta)
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

void merging_func_units(struct battalion points[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    struct battalion L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = points[l + i];
    for (j = 0; j < n2; j++)
        R[j] = points[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].num >= R[j].num)
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

void mergesort_battalion(struct battalion arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergesort_battalion(arr, l, m);
        mergesort_battalion(arr, m + 1, r);

        merging_func_battalion(arr, l, m, r);
    }
}

void mergesort_units(struct battalion arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergesort_units(arr, l, m);
        mergesort_units(arr, m + 1, r);

        merging_func_units(arr, l, m, r);
    }
}

void print_soldiers_left(struct battalion *different_battalions, int number_types)
{
    for (int i = 0; i < number_types; i++)
    {

        printf("There are %d units left in %c-battalion\n", different_battalions[i].num, different_battalions[i].beta);
    }
}

void setup_2d_array(char **arr_type, int **arr_seq, int r, int c, int grid_size)
{
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (i == r && j == c)
            {
                arr_type[i][j] = '*';
                arr_seq[i][j] = -1;
            }
            else
            {
                arr_type[i][j] = '@';
                arr_seq[i][j] = 0;
            }
        }
    }
}

void print_array(char **arr_type, int **arr_seq, int grid_size)
{
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
            printf("%c \t", arr_type[i][j]);
        printf("\n");
    }

    printf("\n");

    // The grid is sequence
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
            printf("%6d \t", arr_seq[i][j]);
        printf("\n");
    }

    printf("\n");
}

// function to get the battalion that need to be placed
char get_battalion_name(struct battalion *different_battalions, int m)
{
    struct battalion sorted[m];
    for (int i = 0; i < m; i++)
    {
        sorted[i] = different_battalions[i];
    }
    mergesort_battalion(sorted, 0, m - 1);
    mergesort_units(sorted, 0, m - 1);
    int i = 0;
    for (i = 0; i < m; i++)
    {
        if (sorted[0].beta == different_battalions[i].beta)
        {
            different_battalions[i].num--;
            return different_battalions[i].beta;
        }
    }
    return '\0';
}

// function to place the soldiers of a battalion
void place(struct battalion *different_battalions, char **strategy, int **sequence, int &cnt, int m, int x1, int y1, int x2,
           int y2, int x3, int y3)
{
    cnt++;
    char ch = get_battalion_name(different_battalions, m);
    sequence[x1][y1] = cnt;
    strategy[x1][y1] = ch;
    sequence[x2][y2] = cnt;
    strategy[x2][y2] = ch;
    sequence[x3][y3] = cnt;
    strategy[x3][y3] = ch;
}

// function to do the task
int place_soldiers(struct battalion *different_battalions, char **strategy, int **sequence, int &cnt, int m, int n, int x, int y)
{
    int r = -1, c = -1;

    // base case
    if (n == 2)
    {
        cnt++;
        char ch = get_battalion_name(different_battalions, m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (sequence[x + i][y + j] == 0)
                {
                    sequence[x + i][y + j] = cnt;
                    strategy[x + i][y + j] = ch;
                }
            }
        }
        return 0;
    }
    // finding mine location
    for (int i = x; i < x + n; i++)
    {
        for (int j = y; j < y + n; j++)
        {
            if (sequence[i][j] != 0)
                r = i, c = j;
        }
    }

    // If soldiers are to be placed is 1st quadrant
    if (r < x + n / 2 && c < y + n / 2)
        place(different_battalions, strategy, sequence, cnt, m, x + n / 2, y + (n / 2) - 1, x + n / 2,
              y + n / 2, x + n / 2 - 1, y + n / 2);

    // If soldiers are to be placed is 3rd quadrant
    else if (r >= x + n / 2 && c < y + n / 2)
        place(different_battalions, strategy, sequence, cnt, m, x + (n / 2) - 1, y + (n / 2), x + (n / 2),
              y + n / 2, x + (n / 2) - 1, y + (n / 2) - 1);

    // If soldiers are to be placed is 2nd quadrant
    else if (r < x + n / 2 && c >= y + n / 2)
        place(different_battalions, strategy, sequence, cnt, m, x + n / 2, y + (n / 2) - 1, x + n / 2,
              y + n / 2, x + n / 2 - 1, y + n / 2 - 1);

    // If soldiers are to be placed is 4th quadrant
    else if (r >= x + n / 2 && c >= y + n / 2)
        place(different_battalions, strategy, sequence, cnt, m, x + (n / 2) - 1, y + (n / 2), x + (n / 2),
              y + (n / 2) - 1, x + (n / 2) - 1,
              y + (n / 2) - 1);

    // dividng it again in 4 quadrants
    place_soldiers(different_battalions, strategy, sequence, cnt, m, n / 2, x, y + n / 2);
    place_soldiers(different_battalions, strategy, sequence, cnt, m, n / 2, x, y);
    place_soldiers(different_battalions, strategy, sequence, cnt, m, n / 2, x + n / 2, y);
    place_soldiers(different_battalions, strategy, sequence, cnt, m, n / 2, x + n / 2, y + n / 2);

    return 0;
}

int main()
{
    // take inputs from the command line correctly
    int cnt = 0;
    int n, x, y;
    cin >> n >> x >> y;
    char **strategy = new char *[n];
    int **sequence = new int *[n];
    for (int i = 0; i < n; i++)
    {
        strategy[i] = new char[n];
        sequence[i] = new int[n];
    }
    setup_2d_array(strategy, sequence, x, y, n);

    /* use the structure type_battalion and create a array "different_battalions" to 
       get the types and number of units per type */
    int m;
    cin >> m;
    struct battalion *different_battalions = new struct battalion[m];
    for (int i = 0; i < m; i++)
    {
        getchar();
        cin >> different_battalions[i].beta >> different_battalions[i].num;
    }

    place_soldiers(different_battalions, strategy, sequence, cnt, m, n, 0, 0);

    //uncomment the following two lines when submitting to moodle/testing your code on custom input
    print_array(strategy, sequence, n);
    printf("\n");

    //you only need to print this when submitting the code to HackerRank.
    print_soldiers_left(different_battalions, m);
    return 0;
}