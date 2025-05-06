#include<iostream>
#include<fstream>
using namespace std;

const int TABLE_SIZE = 10;

class Student
{
    int roll;
    string name;
    int div;

public:
    Student()
    {
        roll = -1;
        name = "";
        div = -1;
    }

    int hash(int key)
    {
        return key % TABLE_SIZE;
    }
    void display()
    {
        if(roll != -1)
        {
            cout << "\n" << roll << "\t" << name << "\t"<<div << endl;
        }
        else
        {
            cout<<endl;
        }
    }
    void getDetails();
    void insertRecord(fstream &);
    void displayAll(fstream &);
    void deleteRecord(fstream &f);
};

void Student::getDetails()
{
    cout<<"Enter Roll: ";
    cin>>roll;
    cin.ignore();
    cout<<"Enter name: ";
    getline(cin, name);
    cout<<"Enter division: ";
    cin>>div;
}

void Student::insertRecord(fstream &f)
{
    Student s;
    s.getDetails();

    int pos = hash(s.roll);

    f.seekg(pos*sizeof(Student),ios::beg);

    Student temp;
    f.read((char*)&temp, sizeof(Student));

    if(temp.roll == -1)
    {
        f.seekp(pos*sizeof(Student),ios::beg);
        f.write((char*)&s,sizeof(Student));
        cout<<"Record Successfully inserted at position:"<<pos<<endl;
    }
    else
    {
        cout<<"Record already exists!\n";
    }
}

void Student::displayAll(fstream &f)
{
    Student s;
    f.seekg(0, ios::beg);
    cout<<"Roll\tName\tDivision";
    for(int i = 0; i<TABLE_SIZE; i++)
    {
        f.read((char*)&s, sizeof(Student));
        s.display();
    }
}

void Student::deleteRecord(fstream &f)
{
    int key;
    cout<<"Enter roll to be deleted: ";
    cin>>key;

    int pos = hash(key);
    f.seekg(pos*sizeof(Student), ios::beg);

    Student s;
    f.read((char*)&s, sizeof(Student));

    if(s.roll == key)
    {
        Student empty;

        f.seekp(pos*sizeof(Student), ios::beg);
        f.write((char*)&empty, sizeof(Student));
        cout<<"Entry deleted successfully!\n";
    }
    else
    {
        cout<<"Record not fould!\n";
    }
}

int main()
{
    fstream f;
    f.open("students.txt", ios::in | ios::out | ios::binary);

    if(f.is_open())
    {
        Student *p;
        Student s;
        f.seekp(0, ios::beg);
        for(int i = 0; i<TABLE_SIZE; i++)
        {
            f.write((char*)&s, sizeof(Student));
        }

        int n = 10;
        while(n)
        {
            cout<<"Enter 1:Insert 2:Display file 3:Delete 0:Stop :- ";
            cin>>n;

            if(n == 1)
            {
                p->insertRecord(f);
            }
            else if(n == 2)
            {
                p->displayAll(f);
            }
            else if(n == 3)
            {
                p->deleteRecord(f);
            }
            else if(n == 0)
            {

            }
            else
            {
                cout<<"Enter correct option!\n";
            }
        }
    }
    else
    {
        cout<<"Unable to open the file!\n";
    }
}