#include <bits/stdc++.h>
using namespace std;
struct Pair
{
    int x, y;
};
void getMinSpanTree(int **adjMat, int n, Pair F[], int &sizeF)
{
    int nearest[n];
    int distance[n];
    for (int i = 0; i < n; i++)
    {
        nearest[i] = 0;
        distance[i] = adjMat[0][i];
    }
    distance[0] = -1;
    int rep=n-1;
    while (rep--)
    {
        int min = INT_MAX;
        int vnear;
        for (int i = 0; i < n; i++)
        {
            if (distance[i] >= 0 && distance[i] < min)
            {
                min = distance[i];
                vnear = i;
            }
        }
        Pair e={vnear,nearest[vnear]};
        F[sizeF++]=e;
        distance[vnear]=-1;
        for (int i = 0; i < n; i++)
        {
            if(adjMat[i][vnear]<distance[i]){
                distance[i]=adjMat[i][vnear];
                nearest[i]=vnear;
            }
        }
    }
}
main()
{
    int n, m;
    cin >> n >> m;
    int **adjMat = new int *[n];
    for (int i = 0; i < n; i++)
    {
        adjMat[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                adjMat[i][j] = 0;
            else
                adjMat[i][j] = INT_MAX;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        adjMat[v1][v2] = w;
        adjMat[v2][v1] = w;
    }

    Pair F[m];
    int sizeF = 0;
    getMinSpanTree(adjMat, n, F, sizeF);
    int minSpanMat[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            minSpanMat[i][j]=-1;
        }
    }
    
    for (int i = 0; i < sizeF; i++)
    {
        minSpanMat[F[i].x][F[i].y]=adjMat[F[i].x][F[i].y];
        minSpanMat[F[i].y][F[i].x]=adjMat[F[i].y][F[i].x];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout<<minSpanMat[i][j]<<" ";
        }
        cout<<endl;
    }
    
}