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
        Token t(token);
        tokens.push_back(t);
    }

    // 2. Match Format of 3 address code
    // Assignment - 0
    // Arithmetic, Logical - 1
    // Labels, Branching - 2
    int typeOfInstruction = getTypeOfInstruction(tokens);

    // 3. Convert to appropriate VM Code
    string vmcode = "";
    if (typeOfInstruction == 0)
    {
        // Assignment Operation
        vmcode = "push " + tokens.at(2).name + "\n";
        vmcode += "pop " + tokens.at(0).name + "\n";
    }
    else if (typeOfInstruction == 1)
    {
        // Arithmetic and Logical Operation
        vmcode = "push " + tokens.at(2).name + "\n";
        vmcode += "push " + tokens.at(4).name + "\n";
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
        vmcode += "pop " + tokens.at(0).name + "\n";
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
            vmcode += "if-goto" + tokens.at(3).name;
            
        vmcode += "\n";
    }
    else if(typeOfInstruction == 3)
    {
        // Function/method definition and return

        if(tokens.at(0).name.compare("function"))
            vmcode += "function " + tokens.at(1).name + " 0\n";

        // Return
        else if(tokens.at(0).name.compare("return"))
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
                vmcode += "push " + tokens.at(1).name + "\n";
                vmcode += "return\n";
            }
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
            vmcode += "call " + tokens.at(1).name + " " + tokens.at(2).name + "\n";
            vmcode += "pop " + tokens.at(0).name + "\n";
        }
    }
    else if(typeOfInstruction == 5)
    {
        // Function/methods parameters
        if(tokens.at(0).name.compare("pushParam") == 0)
            vmcode += "push " + tokens.at(0).name + "\n";
    }
    else if(vmcode.compare("") == 0)
    {
        cout << "ERROR " << endl;
    }
    return vmcode;
}

int VM::getTypeOfInstruction(vector<Token> &v)
{
    //Assignment - 0
    if (v.size() == 3 && v.at(1)=='=')
        return 0;

    //Arithmetic and Logical - 1
    else if (v.size() == 5)
        return 1;

    // Lables and Branches - 2
    // Function/method definition and return - 3
    // Function/method calls - 4
    // Functional Parameters - 5
}