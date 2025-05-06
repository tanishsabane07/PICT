#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main()
{
    int v, e;
    cout<<"Enter the number of vertices: ";
    cin>>v;
    cout<<"Enter the numbe of edges: ";
    cin>>e;

    vector<vector<pair<int, int> > > adj(v);
    vector<int> visited(v);

    for(int i = 0; i<e; i++)
    {
        int x, y, w;
        cout<<"Enter end-point vertices of the edge: ";
        cin>>x>>y;
        cout<<"Enter edge weight: ";
        cin>>w;

        adj[x].push_back({w, y});
        adj[y].push_back({w, x});
    }

    int sum = 0;
    vector<pair<int, int> > edges;
    priority_queue< pair<int, pair<int, int>>, vector< pair<int, pair<int, int>> >, greater< pair<int, pair<int, int>> > > pq;
    pq.push({0, {0, -1}});

    while(!pq.empty())
    {
        pair<int, pair<int, int> > it = pq.top();
        pq.pop();
        int wt = it.first;
        int node = it.second.first;

        if(visited[node])
        {
            continue;
        }

        visited[node] = 1;
        sum += wt;
        edges.push_back({node, it.second.second});

        for(int i = 0; i<adj[node].size(); i++)
        {
            int w = adj[node][i].first;
            int n = adj[node][i].second;

            if(!visited[n])
            {
                pq.push({w, {n, node}});
            }
        }
    }

    cout<<"\nMinimum path length of MST is: "<<sum;
    cout<<"\nEdges included are: ";
    for(int i = 1; i<v; i++)
    {
        cout<<"("<<edges[i].first<<","<<edges[i].second<<"), ";
    }
    
    return 0;
}