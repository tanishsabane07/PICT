// Implement all the functions of a dictionary (ADT) using open
// hashing technique: separate chaining using linked list Data: Set of
// (key, value) pairs, Keys are mapped to values, Keys must be
// comparable, and Keys must be unique. Standard Operations: Insert
// (key, value), Find(key), Delete(key)

#include<iostream>
using namespace std;

struct ListNode
{
    int data;
    string value;
    ListNode *next;
};

class Chain
{
    ListNode* arr[10];

public:

    Chain()
    {
        for(int i = 0; i<10; i++)
        {
            arr[i] = NULL;
        }
    }

    void insert();
    void find();
    void delet();
    void display();
};

void Chain::insert()
{
    int key;
    string val;
    cout<<"\nEnter a key(int) and a value(string) to be inserted: ";
    cin>>key>>val;

    int hash_value = key % 10;

    ListNode *temp = arr[hash_value];
    ListNode *end = temp;

    if(!temp)
    {
        ListNode *newNode  = new ListNode;
        newNode->data = key;
        newNode->value = val;
        newNode->next = NULL;
        arr[hash_value] = newNode;
        cout<<"Key added successfully!\n";
        return;
    }

    while(temp)
    {
        if(temp->data == key)
        {
            cout<<"Key already present!\n";
            return;
        }
        end = temp;
        temp = temp->next;
    }
    ListNode *newNode = new ListNode;
    newNode->data = key;
    newNode->value = val;
    newNode->next = NULL;
    end->next = newNode;
    cout<<"Key added successfully!\n";
}

void Chain::find()
{
    int key;
    cout<<"\nEnter a key to be found: ";
    cin>>key;

    int hash_value = key % 10;
    ListNode *temp = arr[hash_value];
    while(temp)
    {
        if(temp->data == key)
        {
            cout<<"Key found!(Key : Value) :-  "<<temp->data<<":"<<temp->value<<endl;
            return;
        }
        temp = temp->next;
    }
    cout<<"Key not found!\n";
}

void Chain::delet()
{
    int key;
    cout << "Enter key to be deleted: ";
    cin >> key;

    int hash_value = key % 10;

    ListNode *temp = arr[hash_value];
    ListNode *prev = NULL;

    while (temp)
    {
        if (temp->data == key)
        {
            if (prev == NULL)
            {
                arr[hash_value] = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Key deleted successfully!\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Key not found!\n";
}


void Chain::display()
{
    cout << "\nHash Table:\n";
    for (int i = 0; i < 10; i++)
    {
        cout << i << ": ";
        ListNode *temp = arr[i];
        while (temp)
        {
            cout << "(" << temp->data << ", " << temp->value << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}


int main()
{
    Chain c;

    int n = 10;

    while(n)
    {
        cout<<"\nEnter 1:Insert 2:Find 3:Delete 0:Stop :-  ";
        cin>>n;
        if(n == 1)
        {
            c.insert();
            c.display();
        }
        else if(n == 2)
        {
            c.find();
        }
        else if(n == 3)
        {
            c.delet();
            c.display();
        }
        else if(n == 0)
        {
            break;
        }
        else
        {
            cout<<"Enter correct option!\n";
        }
    }

    return 0;
}