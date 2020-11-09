#include <bits/stdc++.h>
#include "token.h"
using namespace std;

#define outputTemVM "temp.vm"

class VM
{
private:
    stack<string> vmStack;
    string ifname, ofname;
    vector<Token> tokens;
    string token;
    void threeAddToVMCode();
    void vmCodeToAssembly();
    int getTypeOfInstruction(vector<Token>&);
    string getVMCode(string);

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
    //vmCodeToAssembly();
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
        cout<<is<<endl;
        vms = getVMCode(is);
        fout << vms;
    }
    fin.close();
    fout.close();
}

void VM::vmCodeToAssembly()
{
    //Rehne de
}

string VM::getVMCode(string s)
{

    // Arithmetic Operations And Assignment Statements

    // 1. Tokenize
    stringstream tokenizer(s);
    tokens.clear();
    while (getline(tokenizer, token, ' '))
    {
        cout << token << endl;
        Token t(token);
        tokens.push_back(t);
    }
    cout<<endl;
    c
    // 2. Match Format of 3 address code
    // Assignment - 0
    // Arithmetic - 1
    int typeOfInstruction = getTypeOfInstruction(tokens);

    // 3. Convert to appropriate VM Code
    string vmcode;
    if (typeOfInstruction == 0)
    {
        // Assignment Operation
        vmcode = "push " + tokens.at(2).name + "\n";
        vmcode += "pop " + tokens.at(0).name + "\n";
    }
    else if (typeOfInstruction == 1)
    {
        // Arithmetic Operation
        vmcode = "push " + tokens.at(2).name + "\n";
        vmcode += "push " + tokens.at(4).name + "\n";
        string opType = tokens.at(3).name;
        if (opType.compare("+") == 0)
        {
            vmcode += "add\n";
        }
        else if (opType.compare("-") == 0)
        {
            vmcode += "sub\n";
        }
        else if (opType.compare("*") == 0)
        {
            vmcode += "mult\n";
        }
        else if (opType.compare("/") == 0)
        {
            vmcode += "div\n";
        }
        vmcode += "pop " + tokens.at(0).name + "\n";
    }
    return vmcode;
}

int VM::getTypeOfInstruction(vector<Token> &v)
{
    if (v.size() == 3)
        return 0;
    else
        return 1;
}