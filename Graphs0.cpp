#include<bits/stdc++.h>
using namespace std;
void visit(bool *visited,int node){
    visited[node]=true;
    cout<<"We visited "<<node<<" node"<<endl;
}
void dfs(int nodes,int **adj_mat,bool *visited,int node){
    visit(visited,node);
    int node_neigh[nodes],k=0;
    for (int i = 0; i < nodes; i++)
    {
        if(adj_mat[node][i]){
            node_neigh[k++]=i;
        }
    }
    for (int i = 0; i < k; i++)
    {
        if(!visited[node_neigh[i]]){
            dfs(nodes,adj_mat,visited,node_neigh[i]);
        }
    }
}
main()
{
    int nodes,edges;
    cin>>nodes>>edges;
    int **adj_mat=new int*[nodes];
    for (int i = 0; i < nodes; i++)
    {
        adj_mat[i]=new int[nodes];
        for (int j = 0; j < nodes; j++)
        {
            adj_mat[i][j]=0;
        }
        
    }
    for (int i = 0; i < edges; i++)
    {
        int m,n;
        cin>>m>>n;
        adj_mat[m][n]=1;
    }
    bool *visited=new bool[nodes];
    for (int i = 0; i < nodes; i++)
    {
        visited[i]=false;
    }
    for (int i = 0; i < nodes; i++)
    {
        if(!visited[i]){
            dfs(nodes,adj_mat,visited,i);
        }
    }
    cout<<"The adjacentcy mat for the graph is...\n";
    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < nodes; j++)
        {
            cout<<adj_mat[i][j]<<" ";
        }
        cout<<endl;
    }
}