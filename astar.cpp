#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<cmath>
using namespace std;

class Node
{
public:
    vector<vector<int>> state;
    int x0, y0;
    int g, h;
    string path;

    int f() const
    {
        return g+h;
    }

    bool operator >(const Node &other) const
    {
        return f() > other.f();
    }
};

vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, -1, 1};
vector<char> dir = {'U', 'D', 'L', 'R'};

int heuristic(vector<vector<int>> &state)
{
    int dist = 0;

    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(state[i][j] != 0)
            {
                int targetX = (state[i][j]-1) / 3;
                int targetY = (state[i][j]-1) % 3;

                dist += abs(targetX - i) + abs(targetY - j);
            }
        }
    }

    return dist;
}

string serialize(vector<vector<int>> &state)
{
    string s = "";

    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++) s += to_string(state[i][j]);
    }

    return s;
}

void printState(vector<vector<int>> &state)
{
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            cout<<state[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void solvePuzzle(vector<vector<int>> &start)
{
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<string> visited;

    int startX, startY;

    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(start[i][j] == 0)
            {
                startX = i;
                startY = j;
                break;
            }
        }
    }

    Node initial = {
        start,
        startX, startY,
        0, heuristic(start),
        ""
    };

    pq.push(initial);

    while(!pq.empty())
    {
        Node curr = pq.top();
        pq.pop();

        string key = serialize(curr.state);

        if(visited.count(key)) continue;

        visited.insert(key);

        if(curr.state == goal)
        {
            cout<<"Goal Reached!!\n";
            cout<<"Path: "<<curr.path<<endl;
            return;
        }

        for(int i = 0; i<4; i++)
        {
            int newX = curr.x0 + dx[i];
            int newY = curr.y0 + dy[i];

            if(newX >= 0 && newX < 3 && newY >= 0 && newY < 3)
            {
                Node child = curr;

                swap(child.state[curr.x0][curr.y0], child.state[newX][newY]);

                child.x0 = newX;
                child.y0 = newY;

                child.g = curr.g + 1;
                child.h = heuristic(child.state);

                child.path += dir[i];

                pq.push(child);
            }
        }
    }
    cout << "No Solution Found!" << endl;
}

int main()
{
    vector<vector<int>> start = {
        {0, 1, 3},
        {4, 2, 6},
        {7, 5, 8}
    };

    printState(start);

    solvePuzzle(start);

    return 0;
}
