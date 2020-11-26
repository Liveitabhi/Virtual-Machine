#include <bits/stdc++.h>
#include "token.h"
using namespace std;

#define outputTemVM "temp.vm"

class VM
{
private:
    // stack<string> vmStack;
    string ifname, ofname;
    vector<Token> tokens;
    string token;
    stack<vector<string>> localVars;
    stack<vector<string>> args;
    void threeAddToVMCode();
    void vmCodeToAssembly();
    int get3acTypeOfInstruction(vector<Token>&);
    int getVMTypeOfInstruction(vector<Token>&);
    string getVMCode(string);
    string getAssemblyCode(string);
    string getSegmentPos(Token&);

public:
    VM(string, string);
    void convertToAssembly();
};

VM::VM(string inputFileName, string outputFileName)
{
    ifname = inputFileName;
    ofname = outputFileName;
}

void VM::convertToAssembly()
{
    threeAddToVMCode();
    vmCodeToAssembly();
}

void VM::threeAddToVMCode()
{
    ifstream fin;
    ofstream fout;
    fin.open(ifname);
    fout.open(outputTemVM);
    string is, vms;
    while (getline(fin, is))
    {
        vms = getVMCode(is);
        fout << vms;
    }
    fin.close();
    fout.close();
}

void VM::vmCodeToAssembly()
{
    ifstream fin;
    ofstream fout;
    fin.open(outputTemVM);
    fout.open(ofname);
    string is, arm;
    while (getline(fin, is))
    {
        arm = getAssemblyCode(is);
        fout << arm;
    }
    fin.close();
    fout.close();
}

string VM::getVMCode(string s)
{
    string segmentPos;
    // Arithmetic Operations And Assignment Statements

    // 1. Tokenize
    stringstream tokenizer(s);
    tokens.clear();
    while (getline(tokenizer, token, ' '))
    {
        Token t(token);
        tokens.push_back(t);
    }

    // 2. Match Format of 3 address code
    // Assignment - 0
    // Arithmetic, Logical - 1
    // Labels, Branching - 2
    // Function/method definition and return - 3
    // Function/methods call - 4
    // Function/methods parameters - 5
    // New Line - 6
    
    int typeOfInstruction = get3acTypeOfInstruction(tokens);
    cout<<s<<" "<<typeOfInstruction<<endl;
    // 3. Convert to appropriate VM Code
    string vmcode = "";
    if (typeOfInstruction == 0)
    {
        // Assignment Operation
        segmentPos = getSegmentPos(tokens.at(2));
        vmcode = "push " + segmentPos + "\n";
        segmentPos = getSegmentPos(tokens.at(0));
        vmcode += "pop " + segmentPos + "\n";
    }
    else if (typeOfInstruction == 1)
    {
        // Arithmetic and Logical Operation
        segmentPos = getSegmentPos(tokens.at(2));
        vmcode = "push " + segmentPos + "\n";
        segmentPos = getSegmentPos(tokens.at(4));
        vmcode += "push " + segmentPos + "\n";

        string opType = tokens.at(3).name;
        if (opType.compare("+") == 0)
            vmcode += "add\n";
        else if (opType.compare("-") == 0)
            vmcode += "sub\n";
        else if (opType.compare("==") == 0)
            vmcode += "eq\n";
        else if (opType.compare("<") == 0)
            vmcode += "lt\n";
        else if (opType.compare("&&") == 0)
            vmcode += "and\n";
        else if (opType.compare("||") == 0)
            vmcode += "or\n";

        segmentPos = getSegmentPos(tokens.at(0));
        vmcode += "pop " + segmentPos + "\n";
    }
    else if(typeOfInstruction == 2)
    {
        // Labels and Branches
        
        // Label
        if(tokens.at(1).name.compare(":") == 0)
            vmcode += "label " + tokens.at(0).name;

        // Unconditional jump
        else if(tokens.at(0).name.compare("goto") == 0)
            vmcode += "goto " + tokens.at(1).name;

        // Conditional jump
        else if(tokens.at(2).name.compare("goto") == 0)
        {
            segmentPos = getSegmentPos(tokens.at(1));
            vmcode += "push " + segmentPos + "\n";
            vmcode += "if-goto " + tokens.at(3).name;
        }
            
        vmcode += "\n";
    }
    else if(typeOfInstruction == 3)
    {
        // Function/method definition and return
        if(tokens.at(0).name.compare("function")==0)
        {
            vector<string> v;
            localVars.push(v);
            for(int i=3; i<tokens.size(); i++)
                v.push_back(tokens.at(i).name);
            args.push(v);

            vmcode += "function " + tokens.at(1).name + " " + tokens.at(2).name + "\n";

        }

        // Return
        else if(tokens.at(0).name.compare("return")==0)
        {

            // Void function
            if(tokens.size()==1)
            {
                vmcode += "push NULL\n";
                vmcode += "return\n";
            }

            // Non-void function
            else if(tokens.size()==2)
            {
                segmentPos = getSegmentPos(tokens.at(1));
                vmcode += "push " + segmentPos + "\n";
                vmcode += "return\n";
            }

            localVars.pop();
            args.pop();
        }
        
    }
    else if(typeOfInstruction == 4)
    {
        // Function/methods call

        //Void call
        if(tokens.at(0).name.compare("call") == 0)
            vmcode += "call " + tokens.at(1).name + " " + tokens.at(2).name + "\n";

        //Non-void call
        else if(tokens.at(2).name.compare("call") == 0)
        {
            vmcode += "call " + tokens.at(3).name + " " + tokens.at(4).name + "\n";
            segmentPos = getSegmentPos(tokens.at(0));
            vmcode += "pop " + segmentPos + "\n";
        }
    }
    else if(typeOfInstruction == 5)
    {
        // Function/methods parameters
        if(tokens.at(0).name.compare("pushParam") == 0)
        {
            segmentPos = getSegmentPos(tokens.at(1));
            vmcode += "push " + segmentPos + "\n";
        }
    }
    else if(typeOfInstruction == 6)
    {
        // cout << "ERROR " << endl;
        vmcode += "\n";
    }
    return vmcode;
}

int VM::get3acTypeOfInstruction(vector<Token> &v)
{
    //New line
    if(v.empty())
        return 6;

    //Assignment - 0
    if (v.size() == 3 && v.at(1).name.compare("=")==0)
        return 0;

    //Arithmetic and Logical - 1
    else if (v.size() == 5 && v.at(1).name.compare("=")==0 && v.at(2).name.compare("call")!=0)
        return 1;

    // Function/method definition and return - 3
    else if(v.at(0).name.compare("function") == 0 || v.at(0).name.compare("return") == 0)
        return 3;

    // Lables and Branches - 2
    else if(v.at(1).name.compare(":") == 0 || tokens.at(0).name.compare("goto") == 0 || tokens.at(0).name.compare("If") == 0)
        return 2;

    // Function/method calls - 4
    else if(v.at(0).name.compare("call") == 0 || v.at(1).name.compare("=") == 0)
        return 4;

    // Functional Parameters - 5
    else
        return 5;
}

string VM::getSegmentPos(Token &t)
{
    string s = "";
    
    if(t.name.at(0)=='_')
    {
        s += "temp " + t.name.substr(2);
        return s;
    }

    if(t.name.at(0)=='\'' || t.name.at(0)=='\"' || isdigit(t.name.at(0)))
    {
        s += "constant " + t.name;
        return s;
    }

    vector <string> v = args.top();
    auto it = find(v.begin(), v.end(), t.name);
    if(it!=v.end())
    {
        s += "argument " + to_string(it-v.begin());
        return s;
    }

    v = localVars.top();
    it = find(v.begin(), v.end(), t.name);
    if(it!=v.end())
    {
        s += "local " + to_string(it-v.begin());
        return s;
    }

    s += "local " + to_string(localVars.top().size());
    localVars.top().push_back(t.name);
    return s;
}

string VM:: getAssemblyCode(string s)
{
    // 1. Tokenize
    stringstream tokenizer(s);
    tokens.clear();
    while (getline(tokenizer, token, ' '))
    {
        Token t(token);
        tokens.push_back(t);
    }
    return "";
}

int VM::getVMTypeOfInstruction(vector<Token> &v)
{
    return 0;
}