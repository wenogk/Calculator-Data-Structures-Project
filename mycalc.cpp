#include <iostream>
#include <fstream>
#include <stack>
#include <list> 
#include <iterator> 
#include "evaluate.h"

using namespace std;

bool areParanthesisBalanced(string expr);
void showlist(list <string> g);

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
    
    
    file.open(inputFile);
    string line;
    string st;
    string expression;
    list <string> expressionList;
    
    //read from the input file expressions
    while (getline(file, line)) {
        if (line.size() > 0)
            //sanity check could be facilitated through the use of a stack 
            //while reading in and processing each expression.
            st = line.substr(0, line.size() - 2); //to get rid of the " ;" 
            expression = st.substr(4, st.size());
                if(areParanthesisBalanced(expression)){
                    //cout << st << " is balanced" << endl;
                    expressionList.push_back(st);
                }
    }
    file.close();
    showlist(expressionList);
}


//Sanity check function using stack
bool areParanthesisBalanced(string expr) { 
	stack <char> s; 
	char x; 
	// Traversing the Expression 
	for (int i=0; i<expr.length(); i++) { 
	    //If the current character is a starting bracket
		if (expr[i]=='(') { 
		    //push it to stack
			s.push(expr[i]); 
		} 
		//If the current character is a closing bracket
		else if (expr[i]==')'){
		    //pop from stack and check if it is the starting bracket 
		    if (s.top() == '(') s.pop();
		    else return false;
		}
	} 
	//Balanced if no starting bracket left
	return (s.empty()); 
} 

//function for printing the elements in a list 
void showlist(list <string> g){ 
    list <string> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it) 
        cout << *it << endl; 
} 