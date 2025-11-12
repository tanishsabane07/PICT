#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

struct Process
{
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival and Burst time for P" << i << ": ";
        p[i].pid = i;
        cin >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;
    }

    int tq;
    cout<<"Enter time quantum: ";
    cin>>tq;

    queue<int> q;
    vector<bool> inQ(n, false);
    int complete = 0, time = 0;

    while(complete < n)
    {
        for(int i = 0; i<n; i++)
        {
            if(!inQ[i] && p[i].at <= time && p[i].rt > 0)
            {
                q.push(i);
                inQ[i] = true;
            }
        }

        if(q.empty())
        {
            time++;
            continue;
        }

        int i = q.front();
        q.pop();

        int exec = min(tq, p[i].rt);
        p[i].rt -= exec;
        time += exec;

        // Check for new arrivals while CPU was busy
        for (int j = 0; j < n; j++) {
            if (!inQ[j] && p[j].at <= time && p[j].rt > 0) {
                q.push(j);
                inQ[j] = true;
            }
        }

        if(p[i].rt > 0)
        {
            q.push(i);
        }
        else{
            p[i].ct = time;
            complete++;
        }
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &x : p)
    {
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
        cout << x.pid << "\t" << x.at << "\t" << x.bt << "\t" << x.ct << "\t" << x.tat << "\t" << x.wt << endl;
    }

    return 0;
}