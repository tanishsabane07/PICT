#include<iostream>
#include<vector>

using namespace std;

class Process
{
public:
    int id;
    bool active;

    Process(int i)
    {
        id = i;
        active = true;
    }
};

class Bully
{
    vector<Process> processes;
    int coordinator;

public:

    Bully(int n)
    {
        for(int i = 1; i<=n; i++)
        {
            processes.push_back(Process(i));
        }
        coordinator = n;
        cout<<"Initial coordinator: "<<coordinator<<endl;
    }

    void failProcess(int id)
    {
        processes[id-1].active = false;
        cout<<"Process "<<id<<" has failed!"<<endl;
        if(id == coordinator) cout<<"Coordinator is down!"<<endl;
    }

    void recoverProcess(int id)
    {
        processes[id-1].active = true;
        cout<<"Process "<<id<<" has recevered!"<<endl;
        startElection(id);
    }

    void startElection(int initiator)
    {
        cout<<"Process "<<initiator<<" starts election!"<<endl;
        bool higherAlive = false;

        for(int i = initiator; i<processes.size(); i++)
        {
            if(processes[i].active)
            {
                cout<<"Process "<<initiator<<"sends election to process"<<processes[i].id<<endl;
                higherAlive = true;
            }
        }

        if(!higherAlive)
        {
            coordinator = initiator;
            cout<<"No higher process alive! Process "<<initiator<<" becomes the Coordinator!"<<endl;
        }
        else
        {
            int maxId = -1;
            for(Process &p : processes)
            {
                if(p.active && p.id > maxId)
                {
                    maxId = p.id;
                }
            }
            coordinator = maxId;
            cout<<"Process "<<coordinator<<" becomes the new Coordinator!"<<endl;
        }

        announceCoordinator();
    }

    void announceCoordinator()
    {
        for(Process &p : processes)
        {
            if(p.active && p.id != coordinator)
            {
                cout<<"Coordinator message sent to process "<<p.id<<endl;
            }
        }
        cout<<endl;
    }

    void printStatus()
    {
        cout<<"Processes Status"<<endl;

        for(Process &p : processes)
        {
            cout<<"Process:"<<p.id<<" Status:"<<(p.active ? "Active" : "Failed")<<endl;
        }
        cout<<"Current coordinator Process: "<<coordinator<<endl<<endl; 
    }
};

int main()
{
    Bully b(5);
    b.printStatus();

    b.failProcess(5);
    b.failProcess(3);

    b.startElection(1);
    b.printStatus();

    b.recoverProcess(5);
    b.printStatus();

    return 0;
}