#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Process
{
    int pid;
    int at;
    int bt;
    int rt;
    int priority;
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
        cout << "Enter AT, BT, Priority for P" << i + 1 << ": ";
        p[i].pid = i + 1;
        cin >> p[i].at >> p[i].bt >> p[i].priority;
        p[i].rt = p[i].bt;
    }

    int complete = 0, time = 0;

    while(complete < n)
    {
        int idx = -1;
        int bestPriority = INT_MAX;

        for(int i = 0; i<n; i++)
        {
            if(p[i].at <= time && p[i].rt > 0 && p[i].priority < bestPriority)
            {
                bestPriority = p[i].priority;
                idx = i;
            }
        }

        if(idx == -1)
        {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].rt = 0;
        complete++;
    }

    cout << "\nPID\tAT\tBT\tPri\tCT\tTAT\tWT\n";
    for (auto &x : p) {
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
        cout << x.pid << "\t" << x.at << "\t" << x.bt << "\t" << x.priority<< "\t" << x.ct << "\t" << x.tat << "\t" << x.wt << endl;
    }

    return 0;
}