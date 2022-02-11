#include <bits/stdc++.h>
using namespace std;
struct Pair
{
    int x, y;
};
void getValidNeighbours(Pair p, Pair arr[], int &size, bool **visited, int n)
{
    Pair adj[] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
    for (int i = 0; i < 4; i++)
    {
        Pair neigh = {p.x + adj[i].x, p.y + adj[i].y};
        if (neigh.x >= 0 && neigh.x < n && neigh.y >= 0 && neigh.y < n && !visited[neigh.x][neigh.y])
            arr[size++] = neigh;
    }
}
bool allVisited(bool **visited, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visited[i][j] == false)
            {
                return false;
            }
        }
    }
    return true;
}
void getPath(int **grid, int n, Pair start, Pair end, Pair path[], int &size)
{
    bool **visited = new bool *[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = new bool[n];
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
        }
    }
    Pair nearest[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            nearest[i][j] = start;
        }
    }
    int distance[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            distance[i][j] = INT_MAX;
        }
    }
    Pair neigh[4];
    int sizeNeigh = 0;
    getValidNeighbours(start, neigh, sizeNeigh, visited, n);
    for (int i = 0; i < sizeNeigh; i++)
    {
        distance[neigh[i].x][neigh[i].y] = max(grid[start.x][start.y], grid[neigh[i].x][neigh[i].y]);
    }
    visited[start.x][start.y] = true;
    while (!allVisited(visited,n))
    {
        Pair neigh[n * n];
        int sizeNeigh = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (visited[i][j])
                {
                    getValidNeighbours({i, j}, neigh, sizeNeigh, visited, n);
                }
            }
        }
        int minDist = INT_MAX;
        Pair vnear;
        for (int i = 0; i < sizeNeigh; i++)
        {
            if (distance[neigh[i].x][neigh[i].y] < minDist)
            {
                minDist = distance[neigh[i].x][neigh[i].y];
                vnear = neigh[i];
            }
        }
        visited[vnear.x][vnear.y]=true;
        sizeNeigh=0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if(visited[i][j]){
                    getValidNeighbours({i,j},neigh,sizeNeigh,visited,n);
                }
            }
        }
        for (int i = 0; i < sizeNeigh; i++)
        {
            if(max(distance[vnear.x][vnear.y],grid[neigh[i].x][neigh[i].y])<distance[neigh[i].x][neigh[i].y]){
                distance[neigh[i].x][neigh[i].y]=max(distance[vnear.x][vnear.y],grid[neigh[i].x][neigh[i].y]);
                nearest[neigh[i].x][neigh[i].y]=vnear;
            }
        }
    }
    path[size++] = end;
    while (path[size - 1].x != start.x || path[size - 1].y != start.y)
    {
        path[size] = nearest[path[size - 1].x][path[size - 1].y];
        size++;
    }
}
main()
{
    // input from console
    int n;
    cin >> n;
    int **grid = new int *[n];
    for (int i = 0; i < n; i++)
    {
        grid[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
        }
    }
    Pair start, end;
    cin >> start.x >> start.y >> end.x >> end.y;
    Pair path[n * n];
    int size = 0;
    getPath(grid, n, start, end, path, size);
    for (int i = size - 1; i >= 0; i--)
    {
        if (i == 0)
            cout << "(" << path[i].x << "," << path[i].y << ")";
        else
            cout << "(" << path[i].x << "," << path[i].y << ")"
                 << "->";
    }
}