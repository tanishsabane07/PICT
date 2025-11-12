#include <iostream>
#include <vector>
using namespace std;

struct Block
{
    int size;
    bool allocated;
};

void display(vector<int> &processes, vector<int> &allocation)
{
    cout << "\nProcess No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < processes.size(); i++)
    {
        cout << i + 1 << "\t\t" << processes[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1; // block numbers are 1-based
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

// ---------------- FIRST FIT ----------------
void firstFit(vector<Block> blocks, vector<int> &processes)
{
    vector<int> allocation(processes.size(), -1);

    for (int i = 0; i < processes.size(); i++)
    {
        for (int j = 0; j < blocks.size(); j++)
        {
            if (!blocks[j].allocated && blocks[j].size >= processes[i])
            {
                allocation[i] = j;
                blocks[j].allocated = true;
                break;
            }
        }
    }

    cout << "\n--- First Fit Allocation ---";
    display(processes, allocation);
}

// ---------------- BEST FIT ----------------
void bestFit(vector<Block> blocks, vector<int> &processes)
{
    vector<int> allocation(processes.size(), -1);

    for (int i = 0; i < processes.size(); i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < blocks.size(); j++)
        {
            if (!blocks[j].allocated && blocks[j].size >= processes[i])
            {
                if (bestIdx == -1 || blocks[j].size < blocks[bestIdx].size)
                    bestIdx = j;
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blocks[bestIdx].allocated = true;
        }
    }

    cout << "\n--- Best Fit Allocation ---";
    display(processes, allocation);
}

// ---------------- WORST FIT ----------------
void worstFit(vector<Block> blocks, vector<int> &processes)
{
    vector<int> allocation(processes.size(), -1);

    for (int i = 0; i < processes.size(); i++)
    {
        int worstIdx = -1;
        for (int j = 0; j < blocks.size(); j++)
        {
            if (!blocks[j].allocated && blocks[j].size >= processes[i])
            {
                if (worstIdx == -1 || blocks[j].size > blocks[worstIdx].size)
                    worstIdx = j;
            }
        }
        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            blocks[worstIdx].allocated = true;
        }
    }

    cout << "\n--- Worst Fit Allocation ---";
    display(processes, allocation);
}

// ---------------- NEXT FIT ----------------
void nextFit(vector<Block> blocks, vector<int> &processes)
{
    vector<int> allocation(processes.size(), -1);
    int lastPos = 0;

    for (int i = 0; i < processes.size(); i++)
    {
        int count = 0;
        while (count < blocks.size())
        {
            int j = (lastPos + count) % blocks.size();
            if (!blocks[j].allocated && blocks[j].size >= processes[i])
            {
                allocation[i] = j;
                blocks[j].allocated = true;
                lastPos = j;
                break;
            }
            count++;
        }
    }

    cout << "\n--- Next Fit Allocation ---";
    display(processes, allocation);
}

// ---------------- MAIN ----------------
int main()
{
    int blocks_cnt, processes_cnt;

    cout << "Enter number of blocks: ";
    cin >> blocks_cnt;

    vector<Block> blocks(blocks_cnt);
    cout << "Enter the size of each block: ";
    for (int i = 0; i < blocks_cnt; i++)
    {
        cin >> blocks[i].size;
        blocks[i].allocated = false;
    }

    cout << "Enter number of processes: ";
    cin >> processes_cnt;

    vector<int> processes(processes_cnt);
    cout << "Enter the size of each process: ";
    for (int i = 0; i < processes_cnt; i++)
        cin >> processes[i];

    firstFit(blocks, processes);
    bestFit(blocks, processes);
    worstFit(blocks, processes);
    nextFit(blocks, processes);

    return 0;
}
