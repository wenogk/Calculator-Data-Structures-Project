#include <iostream>
#include <fstream>
#include <stack>
#include "evaluate.h"

using namespace std;

bool areParanthesisBalanced(string expr);

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
    string line;
    string st;
    string expression;
    while (getline(file, line)) {
        if (line.size() > 0)
            //sanity check could be facilitated through the use of a stack 
            //while reading in and processing each expression.
            st = line.substr(0, line.size() - 2); //to get rid of the " ;" 
            expression = st.substr(4, st.size());
                if(areParanthesisBalanced(expression)){
                    cout << st << " is balanced" << endl;
                }
    }
    file.close();
  
}



//Sanity check function using stack
bool areParanthesisBalanced(string expr) { 
	stack <char> s; 
	char x; 
	// Traversing the Expression 
	for (int i=0; i<expr.length(); i++) { 
		if (expr[i]=='(') { 
			// Push the element in the stack 
			s.push(expr[i]); 
		} 
		else if (expr[i]==')'){
		    if (s.top() == '(') s.pop();
		    else return false;
		}
	} 
	return (s.empty()); 
} 

