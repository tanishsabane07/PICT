#include<iostream>
using namespace std;

class Hash
{
    int arr1[10];
    int arr2[10];
    int cnt;

public:
    Hash()
    {
        cnt = 0;
        for(int i = 0; i < 10; i++)
        {
            arr1[i] = -1;
            arr2[i] = -1;
        }
    }

    void insert();
    void show();
};

void Hash::insert()
{
    if(cnt == 10)
    {
        cout<<"\nHash Table already Full!\n";
        return;
    }
    int newEle;
    cout<<"\nEnter new entry to be inserted: ";
    cin >> newEle;

    int hash_value = newEle % 10;

    if(arr1[hash_value] == -1)
    {
        arr1[hash_value] = newEle;
        cout<<"Element placed successfully!\n";
        cnt++;
    }
    else
    {
        for(int i = 1; i<10; i++)
        {
            int probe_ind = (hash_value + i) % 10;
            if(arr1[probe_ind] == -1)
            {
                arr1[probe_ind] = newEle;
                cout<<"Element placed successfully!\n";
                cnt++;
                break;
            }
        }
    }

    if(arr2[hash_value] == -1)
    {
        arr2[hash_value] = newEle;
        cout<<"Element placed successfully!\n";
    }
    else
    {
        int val_move;

        if(arr2[hash_value] % 10 == hash_value)
        {
            val_move = newEle;
        }
        else
        {
            val_move = arr2[hash_value];
            arr2[hash_value] = newEle;
        }

        for(int i = 1; i<10; i++)
        {
            int probe_ind = (hash_value + i) % 10;
            if(arr2[probe_ind] == -1)
            {
                arr2[probe_ind] = val_move;
                cout<<"Element placed successfully!\n";
                break;
            }
        }
    }
}

void Hash::show()
{
    cout<<"\nHash Table w/o Replacement\t\tHash Table with Replacement\n";
    for(int i = 0; i<10; i++)
    {
        cout<<i<<":"<<"  "<<arr1[i]<<"\t\t\t\t\t\t"<<arr2[i]<<endl;
    }
}

int main()
{
    Hash h;
    h.insert();
    h.insert();
    h.insert();
    h.insert();
    h.insert();
    h.insert();
    h.insert();
    h.insert();
    h.insert();
    h.insert();
    h.insert();

    h.show();

    return 0;
}