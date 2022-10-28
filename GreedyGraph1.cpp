#include <bits/stdc++.h>
using namespace std;
struct Pair
{
	int x, y;
};
void getValidNeighbours(char **mat, int n, int m, bool **visited, Pair pt, Pair arr[], int &size)
{
	Pair adj[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	for (int i = 0; i < 4; i++)
	{
		Pair neigh;
		neigh.x = pt.x + adj[i].x;
		neigh.y = pt.y + adj[i].y;
		if (neigh.x >= 0 && neigh.x < n && neigh.y >= 0 && neigh.y < m && mat[neigh.x][neigh.y] == 'O' && !visited[neigh.x][neigh.y])
			arr[size++] = neigh;
	}
}
void getMinSteps(char **mat, Pair start, int **distance, int n, int m)
{
	bool **visited = new bool *[n];
	for (int i = 0; i < n; i++)
	{
		visited[i] = new bool[m];
		for (int j = 0; j < m; j++)
		{
			visited[i][j] = 0;
		}
	}
	Pair nearest[n][m];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			nearest[i][j] = start;
		}
	}
	distance[start.x][start.y] = 0;
	Pair neighbours[4];
	int neighSize = 0;
	getValidNeighbours(mat, n, m, visited, start, neighbours, neighSize);
	for (int i = 0; i < neighSize; i++)
	{
		distance[neighbours[i].x][neighbours[i].y] = 1;
	}
	visited[start.x][start.y] = 1;
	while (true)
	{
		Pair neighbours[n * m];
		int neighSize = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (visited[i][j])
					getValidNeighbours(mat, n, m, visited, {i, j}, neighbours, neighSize);
			}
		}
		if (neighSize == 0)
			break;
		int min = INT_MAX;
		Pair vnear;
		for (int i = 0; i < neighSize; i++)
		{
			if (distance[neighbours[i].x][neighbours[i].y] < min)
			{
				min = distance[neighbours[i].x][neighbours[i].y];
				vnear = neighbours[i];
			}
		}
		visited[vnear.x][vnear.y] = 1;
		neighSize = 0;
		getValidNeighbours(mat, n, m, visited, vnear, neighbours, neighSize);
		for (int i = 0; i < neighSize; i++)
		{
			if (distance[vnear.x][vnear.y] + 1 < distance[neighbours[i].x][neighbours[i].y])
			{
				nearest[neighbours[i].x][neighbours[i].y] = vnear;
				distance[neighbours[i].x][neighbours[i].y] = distance[vnear.x][vnear.y] + 1;
			}
		}
	}
}
main()
{
	int n, m, q;
	cin >> n >> m >> q;
	char **mat = new char *[n];
	for (int i = 0; i < n; i++)
	{
		mat[i] = new char[m + 1];
		cin >> mat[i];
	}
	Pair start;
	cin >> start.x >> start.y;
	start.x--;
	start.y--;
	Pair end[q];
	for (int i = 0; i < q; i++)
	{
		cin >> end[i].x >> end[i].y;
		end[i].x--;
		end[i].y--;
	}
	int **distance = new int *[n];
	for (int i = 0; i < n; i++)
	{
		distance[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			distance[i][j] = INT_MAX;
		}
	}
	getMinSteps(mat, start, distance, n, m);
	for (int i = 0; i < q; i++)
	{
		if (distance[end[i].x][end[i].y] == INT_MAX)
		{
			cout << "-1" << endl;
		}
		else
		{
			cout << distance[end[i].x][end[i].y] << endl;
		}
	}
}