// Department maintains a student information. The file contains roll
// number, name, division and address. Allow user to add, delete
// information of student. Display information of particular student. If
// record of student does not exist an appropriate message is displayed. If
// it is, then the system displays the student details. Use Sequential File
// to maintain the data. =====ADD | SEARCH | DELETE=====

#include<iostream>
#include<fstream>
using namespace std;

struct Student
{
    int roll;
    string name;
    string div;
    string address;
};

class File
{
    Student student;
    public:

    void add();
    void display();
    void delet();
};

void File::add()
{
    fstream f;

    cout<<"Enter roll: ";
    cin>>student.roll;
    cin.ignore();
    cout<<"Enter name: ";
    getline(cin, student.name);
    cout<<"Enter division: ";
    cin>>student.div;
    cin.ignore();
    cout<<"Enter address: ";
    getline(cin, student.address);

    f.open("records.txt", ios::app);

    if(f.is_open())
    {
        f<<student.roll<<","<<student.name<<","<<student.div<<","<<student.address<<endl;
        f.close();
        cout<<"Student added successfully!\n";
    }
    else
    {
        cout<<"Unable to open the file!\n";
    }}

void File::display()
{
    int rollno;
    cout<<"Enter roll to be searched: ";
    cin>>rollno;
    cin.ignore();

    Student s;

    ifstream inFile("records.txt");

    if(inFile.is_open())
    {
        string line;
        bool found = false;

        while(getline(inFile, line))
        {
            size_t pos = line.find(",");
            int roll = stoi(line.substr(0, pos));

            if(roll == rollno)
            {
                found  = true;
                cout<<"Roll No: "<<roll<<endl;

                line = line.substr(pos+1);
                pos = line.find(",");
                cout<<"Name: "<<line.substr(0, pos)<<endl;

                line = line.substr(pos+1);
                pos = line.find(",");
                cout<<"Division: "<<line.substr(0, pos)<<endl;

                line = line.substr(pos+1);
                cout<<"Address: "<<line.substr(pos+1)<<endl;
                break;
            }
        }
        inFile.close();

        if(!found)
        {
            cout<<"Entry not found!\n";
        }
    }
    else
    {
        cout<<"Could not open the file!\n";
    }
}

void File::delet()
{
    int rollno;
    cout<<"Enter a Roll No to delete: ";
    cin>>rollno;

    ifstream ifile("records.txt");
    ofstream ofile("temp.txt");

    if(ofile.is_open() && ifile.is_open())
    {
        bool found = false;
        string line;

        while(getline(ifile, line))
        {
            size_t pos = line.find(",");
            int rol = stoi(line.substr(0, pos));

            if(rol == rollno)
            {
                found = true;
            }
            else
            {
                ofile<<line<<endl;
            }
        }

        ifile.close();
        ofile.close();
        remove("records.txt");
        rename("temp.txt", "records.txt");

        if(found)
        {
            cout<<"Student deleted!\n";
        }
        else
        {
            cout<<"Student not found!\n";
        }
    }

}

int main()
{
    File fi;

    int n = 10;

    while(n)
    {
        cout<<"Enter 0:Add 1:Search 2:Delete 3:Stop :- ";
        cin>>n;

        if(n == 0)
        {
            fi.add();
        }
        else if(n == 1)
        {
            fi.display();
        }
        else if(n == 2)
        {
            fi.delet();
        }
        else
        {
            cout<<"Please enter correct option!\n";
        }
    }

    return 0;
}