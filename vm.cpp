#include<bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    if(argc!=3 && argc !=2) {
        cout << "Error..." << endl;
    }  
    string inputFileName,outputFileName;
    if(argc==3) {
        inputFileName = argv[1];
        outputFileName = argv[2];
    } 
    else {
        inputFileName = argv[1];
        outputFileName = "a.m";
    }
    cout << inputFileName << endl;
    cout << outputFileName << endl;
    
    ifstream infile;
    infile.open(inputFileName);

}