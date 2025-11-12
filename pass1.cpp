#include<iostream>
#include<unordered_map>
#include<fstream>
#include<sstream>
#include<vector>
#include<unordered_set>

using namespace std;

struct Symbol
{
    string name;
    int address;
};

struct Literal
{
    string name;
    int address;
};


int main()
{
    unordered_map<string, int> imperative = {
        {"STOP", 0},
        {"ADD", 1},
        {"SUB", 2},
        {"MULT", 3},
        {"MOVER", 4},
        {"MOVEM", 5},
        {"COMP", 6},
        {"BC", 7},
        {"DIV", 8},
        {"READ", 9},
        {"PRINT", 10}
    };

    unordered_map<string, int> directives = {
        {"START", 1},
        {"END", 2},
        {"ORIGIN", 3},
        {"EQU", 4},
        {"LTORG", 5}
    };

    unordered_map<string, int> declarative = {
        {"DS", 1},
        {"DC", 2}
    };

    unordered_map<string, int> registers = {
        {"AREG", 1},
        {"BREG", 2},
        {"CREG", 3},
        {"DREG", 4}
    };

    unordered_map<string, int> condCodes = {
        {"LT", 1},
        {"LE", 2},
        {"EQ", 3},
        {"GT", 4},
        {"GE", 5},
        {"ANY", 6}
    };


    fstream fin("input.asm");
    ofstream fout("intermediate.txt");

    if(!fin.is_open())
    {
        cout<<"Error opening the input.asm!"<<endl;
        return 1;
    }


    vector<Symbol> SYMTAB;
    vector<Literal> LITTAB;
    vector<int> POOLTAB = {0};


    string line;
    int LC = 0;

    while(getline(fin, line))
    {
        if(line.empty()) continue;

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while(ss >> token)
        {
            if(token.back() == ' ' || token.back() == ',') token.pop_back();
            tokens.push_back(token);
        }


        if(tokens[0] == "START")
        {
            LC = stoi(tokens[1]);
            fout<<"(AD,1)(C,"<<LC<<")"<<endl;
            continue;
        }

        if(tokens[0] == "LTORG" || tokens[0] == "END")
        {
            if(tokens[0] == "LTORG")
            {
                for(int i = POOLTAB.back(); i<LITTAB.size(); i++)
                {
                    fout<<"(AD,5)"<<"(DL,2)"<<"(C,"<<LITTAB[i].name[2]<<")"<<endl;
                }
            }

            if(tokens[0] == "END")
            {
                fout<<"(AD,2)"<<endl;
            }
            for(int i = POOLTAB.back(); i < LITTAB.size(); i++)
            {
                LITTAB[i].address = LC;
                LC++;
            }

            POOLTAB.push_back(LITTAB.size());
            continue;
        }

        if (tokens[0] == "ORIGIN")
        {
            string expr = tokens[1];
            int newLC = 0;

            size_t pos = expr.find('+');

            if (pos != string::npos)
            {
                string sym = expr.substr(0, pos);
                int offset = stoi(expr.substr(pos + 1));
                for (auto &s : SYMTAB)
                {
                    if (s.name == sym)
                        newLC = s.address + offset;
                }
            } 
            else if ((pos = expr.find('-')) != string::npos)
            {
                string sym = expr.substr(0, pos);
                int offset = stoi(expr.substr(pos + 1));
                for (auto &s : SYMTAB)
                {
                    if (s.name == sym)
                        newLC = s.address - offset;
                }
            } 
            else {
                // direct symbol or constant
                bool found = false;
                for (auto &s : SYMTAB)
                    if (s.name == expr) {
                        newLC = s.address;
                        found = true;
                        break;
                    }
                if (!found)
                    newLC = stoi(expr);
            }

            fout << "(AD," << directives["ORIGIN"] << ")(C," << newLC << ")\n";
            LC = newLC;
            continue;
        }

        if (tokens[1] == "EQU") {
            string sym1 = tokens[0];
            string expr = tokens[2];
            int value = 0;

            // handle forms like LOOP EQU NEXT+1 or LABEL EQU 200
            size_t pos = expr.find('+');

            if (pos != string::npos) {
                string sym = expr.substr(0, pos);
                int offset = stoi(expr.substr(pos + 1));
                for (auto &s : SYMTAB)
                    if (s.name == sym)
                        value = s.address + offset;
            } 
            else if ((pos = expr.find('-')) != string::npos)
            {
                string sym = expr.substr(0, pos);
                int offset = stoi(expr.substr(pos + 1));
                for (auto &s : SYMTAB)
                    if (s.name == sym)
                        value = s.address - offset;
            } 
            else {
                // direct symbol or constant
                bool found = false;
                for (auto &s : SYMTAB)
                    if (s.name == expr) {
                        value = s.address;
                        found = true;
                        break;
                    }
                if (!found)
                    value = stoi(expr);
            }

            // update or insert symbol
            bool exists = false;
            for (auto &s : SYMTAB) {
                if (s.name == sym1) {
                    s.address = value;
                    exists = true;
                    break;
                }
            }
            if (!exists)
                SYMTAB.push_back({sym1, value});

            fout << "(AD," << directives["EQU"] << ") (C," << value << ")\n";
            continue;
        }



        int idx = 0;

        // Label
        if (imperative.find(tokens[0]) == imperative.end() && directives.find(tokens[0]) == directives.end() && declarative.find(tokens[0]) == declarative.end())
        {
            bool exists = false;
            int position = -1;
            for (int i = 0; i<SYMTAB.size(); i++)
            {
                if (SYMTAB[i].name == tokens[0])
                {
                    SYMTAB[i].address = LC;
                    exists = true;
                    position = i+1;
                    break;
                }
            }
            if (!exists)
            {
                SYMTAB.push_back({tokens[0], LC});
                position = SYMTAB.size();
            }

            fout<<"(S,"<<position<<")";
            idx = 1;
        }

        // Declare Statements
        if (declarative.find(tokens[idx]) != declarative.end())
        {
            fout << "(DL," << declarative[tokens[idx]] << ")";

            if (tokens[idx] == "DS")
            {
                fout << "(C," << tokens[idx + 1] << ")"<<endl;
                LC += stoi(tokens[idx + 1]);
            }
            else if (tokens[idx] == "DC")
            {
                fout << "(C," << tokens[idx + 1] << ")"<<endl;
                LC++;
            }
            continue;
        }

        // Imperative Statements
        if (imperative.find(tokens[idx]) != imperative.end()) {
            fout << "(IS," << imperative[tokens[idx]] << ")";
            LC++;

            // Handle registers or operands
            for (size_t i = idx + 1; i < tokens.size(); i++) {
                string op = tokens[i];

                // Register
                if (registers.find(op) != registers.end()) {
                    fout << "(RG," << registers[op] << ")";
                }
                // Condition Codes
                else if (condCodes.find(op) != condCodes.end()) {
                    fout << "(CC," << condCodes[op] << ")";
                }
                // Literal
                else if (op[0] == '=') {
                    bool foundLit = false;
                    for (auto &l : LITTAB)
                    {
                        if (l.name == op)
                            foundLit = true;
                    }
                    if (!foundLit)
                    {
                        LITTAB.push_back({op, -1});
                    }

                    fout << "(L," << LITTAB.size() << ")";
                }
                // Symbol
                else {
                    bool found = false;
                    for (int j = 0; j < SYMTAB.size(); j++) {
                        if (SYMTAB[j].name == op) {
                            fout << "(S," << j + 1 << ")";
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        SYMTAB.push_back({op, -1});
                        fout << "(S," << SYMTAB.size() << ")";
                    }
                }
            }
            fout << "\n";
        }
    }

    cout << "\n--- SYMBOL TABLE ---\n";
    cout << left << setw(10) << "SYMBOL" << setw(10) << "ADDRESS" << endl;
    for (auto &s : SYMTAB)
        cout << left << setw(10) << s.name << setw(10) << s.address << endl;

    cout << "\n--- LITERAL TABLE ---\n";
    cout << left << setw(10) << "LITERAL" << setw(10) << "ADDRESS" << endl;
    for (auto &l : LITTAB)
        cout << left << setw(10) << l.name << setw(10) << l.address << endl;

    cout << "\n--- POOL TABLE ---\n";
    for (auto &p : POOLTAB)
        cout << p << " ";
    cout << endl;



    fin.close();
    fout.close();

    return 0;
}