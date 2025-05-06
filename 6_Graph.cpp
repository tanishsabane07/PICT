// Represent a given graph using adjacency list to perform DFS and BFS.
// Use the map of the area around the college as the graph. Identify the
// prominent landmarks as nodes and perform DFS and BFS on that.

#include<iostream>
#include<queue>
using namespace std;

void DFS(int node, int adj[][20], int visited[])
{
    visited[node] = 1;
    cout<<node<<" ";
    for(int i = 0; i<20; i++)
    {
        if(!visited[i] && adj[node][i])
        {
            DFS(i, adj, visited);
        }
    }
}

void BFS(int &start, int adj[][20], int visited[])
{
    queue<int> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int i = 0; i < 20; i++)
        {
            if (!visited[i] && adj[node][i])
            {
                visited[i] = 1;
                q.push(i);
            }
        }
    }
}


int main()
{
    int v, e;
    cout<<"Enter number of vertices: ";
    cin>>v;
    cout<<"Enter number of edges: ";
    cin>>e;

    int adj[20][20] = {0};
    int visited1[20] = {0};
    int visited2[20] = {0};

    for(int i = 0; i<e; i++)
    {
        cout<<"Enter the vertices between which an edge is present: ";
        int x, y;
        cin>>x>>y;
        adj[x][y] = 1;
        adj[y][x] = 1;
    }

    int start; 
    cout<<"Enter starting node for BFS and DFS: ";
    cin>>start;

    cout<<"\nDFS Traversal: ";
    DFS(start, adj, visited1);

    cout<<"\nBFS Traversal: ";
    BFS(start, adj, visited2);

    return 0;
}