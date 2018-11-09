#include <iostream>
#include <fstream>
#include "evaluate.h"

using namespace std;

int main(int count, char * args[]) {

    string inputFile = "";
    string outputFile = "";
    ifstream file;
    
    //take as parameters names of the input and output textfiles
    for (int i = 1; i < count; i++) {
        if ((string(args[i]) == "-i") && i + 1 < count)
            inputFile = args[i + 1];
        else if ((string(args[i]) == "-o") && i + 1 < count)
            outputFile = args[i + 1];
    }
    //remind user of the way to invocate the application
    if (inputFile == "" || outputFile == "") {
        cout << "Usage ./mycalc -i <inputfile> -o <outputfile>>" << endl;
        return -1;
    }
    //print out names of the input and output textfiles
    cout << "Input file is " << inputFile << endl;
    cout << "Output file is " << outputFile << endl;
    
    //read from the input file expressions
    file.open(inputFile);
    string str;
    string st;
    while (getline(file, str)) {
        if (str.size() > 0)
            st = str.substr(0, str.size() - 1);
            cout << st << endl;
    }
    file.close();
  
}
