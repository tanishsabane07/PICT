#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Process
{
    int pid;
    int at;
    int bt;
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
    }

    sort(p.begin(), p.end(), [](Process a, Process b){return a.at < b.at;});

    int time = 0;

    for(int i = 0; i<p.size(); i++)
    {
        time = max(time, p[i].at) + p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    cout<<"PID\tAT\tBT\tCT\tTAT\tWT\n";
    
    for(int i = 0; i<p.size(); i++)
    {
        cout<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<endl;
    }

    return 0;
}