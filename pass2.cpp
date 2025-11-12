#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
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
    // ✅ Example tables (replace with file input if needed)
    vector<Symbol> SYMTAB = {{"X", 210}, {"NEXT", 204}};
    vector<Literal> LITTAB = {{"='5'", 205}, {"='2'", 206}};

    ifstream fin("intermediate.txt");
    ofstream fout("machine_code.txt");

    if (!fin.is_open())
    {
        cout << "❌ Error opening intermediate.txt!" << endl;
        return 1;
    }

    string line;
    int LC = 0;

    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        // Trim spaces and tabs from the line
        line.erase(remove_if(line.begin(), line.end(),
                     [](unsigned char c){ return isspace(c); }),
           line.end());

        size_t pos;

        // 🔹 START (AD,1)
        if ((pos = line.find("(AD,1)")) != string::npos)
        {
            pos = line.find("(C,");
            if (pos != string::npos)
            {
                size_t end = line.find(')', pos);
                string s = line.substr(pos + 3, end - (pos + 3));
                LC = stoi(s);
            }
            continue;
        }

        // --- ORIGIN (set LC directly) ---
        if ((pos = line.find("(AD,3)")) != string::npos) {
            pos = line.find("(C,");
            if (pos != string::npos) {
                size_t end = line.find(')', pos);
                string val = line.substr(pos + 3, end - (pos + 3));
                LC = stoi(val);
                // For debugging
                cout << "LC reset by ORIGIN → " << LC << endl;
            }
            continue;
        }


        // 🔹 Handle END and LTORG
        if (line.find("(AD,2)") != string::npos) {
            break; // END means stop
        }
        if (line.find("(AD,5)") != string::npos) {
            // Generate machine code for LTORG literals
            size_t pos = line.find("(C,");
            if (pos != string::npos) {
                size_t end = line.find(')', pos);
                string val = line.substr(pos + 3, end - (pos + 3));
                int valInt = stoi(val);
                fout << setw(3) << LC << "  "
                    << "00 00 "
                    << setw(3) << setfill('0') << valInt << endl;
                setfill(' ');
                LC++;
            }
            continue;
        }

        // --- Declarative (DL) — DC / DS
        if (line.find("(DL,") != string::npos) {
            size_t posDL = line.find("(DL,");
            size_t endDL = line.find(')', posDL);
            string dlType = line.substr(posDL + 4, endDL - (posDL + 4)); // get "1" or "2"

            pos = line.find("(C,");
            if (pos != string::npos) {
                size_t end = line.find(')', pos);
                string val = line.substr(pos + 3, end - (pos + 3));
                int valInt = stoi(val);

                fout << setw(3) << LC << "  "
                    << "00 00 "
                    << setw(3) << setfill('0') << valInt << endl;
                setfill(' ');

                // DS should reserve space; DC just one constant
                if (dlType == "1") {  // DS
                    LC += valInt;     // Reserve that many locations
                } else {
                    LC++;             // DC occupies one location
                }
            }
            continue;
        }


        // 🔹 Imperative Statements (IS)
        if (line.find("(IS,") != string::npos)
        {
            // Extract opcode
            pos = line.find("(IS,");
            size_t end = line.find(')', pos);
            string opcodeStr = line.substr(pos + 4, end - (pos + 4));

            // Extract register
            string reg = "00";
            pos = line.find("(RG,");
            if (pos != string::npos)
            {
                end = line.find(')', pos);
                reg = line.substr(pos + 4, end - (pos + 4));
            }

            // Extract operand correctly, considering symbol at start too
            // Extract operand (symbol or literal)
            int addr = 0;
            size_t posS = line.rfind("(S,");  // rfind = last occurrence
            size_t posL = line.rfind("(L,");

            if (posL != string::npos && (posS == string::npos || posL > posS)) {
                int index = stoi(line.substr(posL + 3, line.find(')', posL) - (posL + 3)));
                addr = LITTAB[index - 1].address;
            } 
            else if (posS != string::npos) {
                int index = stoi(line.substr(posS + 3, line.find(')', posS) - (posS + 3)));
                addr = SYMTAB[index - 1].address;
            }


            // Output machine instruction
            fout << setw(3) << LC << "  "
                 << setw(2) << setfill('0') << opcodeStr << " "
                 << setw(2) << reg << " "
                 << setw(3) << addr << endl;
            setfill(' ');
            LC++;
        }
    }

    cout << "✅ Machine code generated successfully → machine_code.txt\n";
    fin.close();
    fout.close();
    return 0;
}
