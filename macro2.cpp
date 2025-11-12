#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>

using namespace std;

struct MacroName
{
    string name;
    int pp;
    int kp;
    int mdtp;
    int kpdtp;
};

int main()
{
    vector<MacroName> MNT = {
        {"INCR_D", 1, 2, 0, 0},
        {"COMPUTE", 2, 1, 4, 2}
    };

    unordered_map<string, vector<string>> PNTAB = {
        {"INCR_D", {"&MEM_VAL", "&INCR_VAL", "&REG"}},
        {"COMPUTE", {"&FIRST", "&SECOND", "&THIRD"}}
    };

    vector<pair<string, string>> KPDTAB = {
        {"&INCR_VAL", ""},
        {"&REG", "AREG"},
        {"&THIRD", "100"}
    };

    vector<vector<string>> MDT = {
        {"MOVER", "(P,2)", "(P,0)"},
        {"ADD", "(P,2)", "(P,1)"},
        {"MOVEM", "(P,2)", "(P,0)"},
        {"MEND"},
        {"MOVEM", "BREG", "(P,2)"},
        {"MOVER", "BREG", "(P,2)"},
        {"ADD", "BREG", "(P,2)"},
        {"MEND"}
    };

    vector<vector<string>> calls = {
        {"INCR_D", "AREA", "&INCR_VAL=3"},
        {"COMPUTE", "AREA", "3"}
    };


    ofstream fout("pass2_output.asm");

    for(auto line : calls)
    {
        bool found = false;
        MacroName currMacro;

        for(int i = 0; i<MNT.size(); i++)
        {
            if(line[0] == MNT[i].name)
            {
                currMacro = MNT[i];
                found = true;
                break;
            }
        }

        if(!found)
        {
            cout<<"Macro "<<line[0]<<"not found!"<<endl;
            continue;
        }


        vector<string> APTAB(currMacro.pp + currMacro.kp);

        // fill postional parameters

        int posIndex = 0;

        for(int i = 1; i<line.size(); i++)
        {
            if(line[i].find('=') == string::npos)
            {
                if (posIndex < currMacro.pp)
                    APTAB[posIndex++] = line[i];
            }
        }

        for(int i = 1; i<line.size(); i++)
        {
            size_t pos = line[i].find('=');
            if (pos != string::npos)
            {
                string pname = line[i].substr(0, pos);
                string pvalue = line[i].substr(pos + 1);

                // Find pname in PNTAB
                for (int j = 0; j < PNTAB[currMacro.name].size(); j++)
                {
                    if (PNTAB[currMacro.name][j] == pname)
                    {
                        APTAB[j] = pvalue;
                        break;
                    }
                }
            }
        }

        // fill defaults from KPDTAB if still empty
        if (currMacro.kp > 0)
        {
            int kpStart = currMacro.kpdtp;
            for (int k = 0; k < currMacro.kp; k++)
            {
                int aptIndex = currMacro.pp + k;
                if (APTAB[aptIndex].empty() && (kpStart + k < KPDTAB.size()))
                {
                    APTAB[aptIndex] = KPDTAB[kpStart + k].second;
                }
            }
        }

        // expand macro calls

        int mdtp = currMacro.mdtp;

        while(mdtp < MDT.size() && MDT[mdtp][0] != "MEND")
        {
            vector<string> lineTokens = MDT[mdtp];
            string expandedLine = "+";

            for(int t = 0; t<lineTokens.size(); t++)
            {
                string tok = lineTokens[t];
                if(tok.find("(P,") != string::npos)
                {
                    int start = tok.find(",") + 1;
                    int end = tok.find(")");

                    int index = stoi(tok.substr(start, end-start));
                    tok = APTAB[index];
                }

                expandedLine += tok + " ";
            }

            fout<<expandedLine<<endl;
            mdtp++;
        }
        fout<<endl;
    }
    
    fout.close();

    return 0;
}