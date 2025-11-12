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

    int complete = 0, time = 0;

    while(complete != n)
    {
        int shortest = -1;
        int minRT = INT_MAX;
        for(int i = 0; i<n; i++)
        {
            if(p[i].at <= time && p[i].rt > 0 && p[i].rt < minRT)
            {
                minRT = p[i].rt;
                shortest = i;
            }
        }
        if(shortest == -1) {
            time++;
            continue;
        }

        p[shortest].rt--;
        time++;

        if(p[shortest].rt == 0)
        {
            complete++;
            p[shortest].ct = time;
        }
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &x : p) {
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
        cout << x.pid << "\t" << x.at << "\t" << x.bt << "\t"<< x.ct << "\t" << x.tat << "\t" << x.wt << endl;

    }
}