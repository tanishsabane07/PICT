// Design suitable data structures and implement pass-1 of two pass macro processor

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
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
    fstream fin("macro_input.asm");

    if(!fin.is_open())
    {
        cout<<"File macro_input.asm can't be opened!"<<endl;
    }

    string line;
    bool prevMacro = false;

    vector<MacroName> MNT;
    vector<vector<string>> MDT;
    vector<pair<string, string>> KPDTAB;
    unordered_map<string, vector<string>> PNTAB;
    
    string curr_name = "";

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

    
        if(tokens[0] == "MACRO")
        {
            prevMacro = true;
            continue;
        }
        else if(prevMacro)
        {
            string mname = tokens[0];
            curr_name = mname;
            int pp = 0, kp = 0;
            int mdtp = MDT.size();
            int kpdtp = KPDTAB.size();

            for(int i = 1; i<tokens.size(); i++)
            {
                size_t pos = tokens[i].find('=');
                if(pos != string::npos)
                {
                    kp++;
                    string para = tokens[i].substr(0, pos);
                    string value = tokens[i].substr(pos+1);

                    PNTAB[mname].push_back(para);
                    KPDTAB.push_back({para, value});
                }
                else
                {
                    pp++;
                    PNTAB[mname].push_back(tokens[i]);
                }
            }

            MNT.push_back({mname, pp, kp, mdtp, kpdtp});

            prevMacro = false;
            continue;
        }
        else
        {
            for(int i = 0; i<tokens.size(); i++)
            {
                for(int j = 0; j < PNTAB[curr_name].size(); j++)
                {
                    if(tokens[i] == PNTAB[curr_name][j])
                    {
                        tokens[i] = "(P,"+to_string(j)+")";
                        break;
                    }
                }
            }

            MDT.push_back(tokens);
        }
    }

    fin.close();

    cout<<"--------------MNT---------------"<<endl;
    cout<<"#NAME\t#PP\t#KP\t#MDTP\t#KPDTP"<<endl;
    for(int i = 0; i<MNT.size(); i++)
    {
        cout<<MNT[i].name<<"\t"<<MNT[i].pp<<"\t"<<MNT[i].kp<<"\t"<<MNT[i].mdtp<<"\t"<<MNT[i].kpdtp<<endl;
    }

    cout<<"\n--------------PNTAB---------------"<<endl;
    for(auto i = PNTAB.begin(); i != PNTAB.end(); i++)
    {
        cout<<i->first<<endl;
        cout<<"----------"<<endl;
        for(int j = 0; j<i->second.size(); j++)
        {
            cout<<i->second[j]<<endl;
        }
        cout<<endl;
    }

    cout<<"--------------KPDTAB---------------"<<endl;
    cout<<"NAME\t\tValue"<<endl;

    for(int i = 0; i<KPDTAB.size(); i++)
    {
        cout<<KPDTAB[i].first<<"\t\t"<<KPDTAB[i].second<<endl;
    }

    cout<<"\n--------------MDT---------------"<<endl<<endl;

    for(int i = 0; i<MDT.size(); i++)
    {
        for(int j = 0; j<MDT[i].size(); j++)
        {
            cout<<MDT[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}