#include <iostream>
#include <fstream>
#include <string> 
#include <stack>
#include <vector>
#include <list> 
#include <iterator> 
#include <map> 
#include <cmath>
#include <ctype.h>
#include <typeinfo>
#include "evaluate.h"

using namespace std;

bool areParanthesisBalanced(string expr);
string lineOperation(string afterEquals);
bool isVariablePresent(string value);
bool isOperatorPresent(string value);
string ReplaceString(string subject, const string& search, const string& replace);
bool isoperator(char ch);
void mapEvaluation(string** A, int lineNum);


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

    string line;
    string str;
    string variableName;
    string afterEquals;
    string cleanExpression;
    int lineNum = 0;
    //vector<vector<string> > expressionVector;
    
    file.open(inputFile);
    while (getline(file, line)) {
        if (line.size() > 0){
            lineNum ++;	//number of expressions  
        }
    }
    file.close();
    
    file.open(inputFile);
    string A[lineNum][2];
    for(int i=0; i<lineNum; i++) {//read from the input file expressions
    
        getline(file, line);
        if (line.size() > 0){
            str = line.substr(0, line.size()-1); //read each line  
            variableName = str.substr(0, str.find("=")-1); //variable name
	        afterEquals = str.substr(str.find("=")+1, str.size()); //expression
	        cleanExpression = lineOperation(afterEquals);
            

            if(areParanthesisBalanced(cleanExpression)){//sanity check
                cout << cleanExpression << " is balanced" << endl;
                A[i][0] = variableName;//add variable name to the array
                A[i][1] = cleanExpression;//add expression to the array         
            }
        }
    }
    file.close();
    mapEvaluation(A, lineNum);
}





//Add calculated variables and values to the map
void mapEvaluation(string** A, int lineNum){
    
    map<string, float> variableMap;  
    string afterEquals;
    string variableName;
        
    while(variableMap.size()!=lineNum) {
    
        for(int i=0; i<lineNum; i++){
            cout << A[i][1] << endl;
            /*
            afterEquals = A[i][1];
            variableName = A[i][0];
            
            //replace all variables with their values from map
            if(!variableMap.empty()) {
                map<string, float>::iterator it = variableMap.begin();
                while (it != variableMap.end()){
                    afterEquals  = ReplaceString(afterEquals, it->first, to_string(it->second));
                    it++;
                }
            }
        
            //insert calculated results to the map
            if((!isVariablePresent(afterEquals))&&(isOperatorPresent(afterEquals))) { //only operator, no variable
                variableMap.insert(make_pair(variableName, 99)); //change 99 to evaluate(afterEquals)
            } 
            else if((!isVariablePresent(afterEquals))&&(!isOperatorPresent(afterEquals))){ //no operator or variable
                variableMap.insert(make_pair(variableName, stoi(afterEquals)));
            }*/
        }
    }
    
    //print out results when all calculations are done
    map<string, float>::iterator it = variableMap.begin();
    while (it != variableMap.end()){
        cout<< it->first << " = " << it->second <<endl;
        it++;
    }
}




/*




BELOW ARE HELPER FUNCTIONS




*/



//Cleaning work on the expressions
string lineOperation(string afterEquals){

    afterEquals = ReplaceString(afterEquals,";",""); //get rid of ;
	afterEquals = ReplaceString(afterEquals," ",""); //get rid of space
	afterEquals = ReplaceString(afterEquals,"++","!"); //replace ++ with !
	afterEquals = ReplaceString(afterEquals,"--","@"); //replace -- with @
	afterEquals = ReplaceString(afterEquals,"**","#"); //replace ** with #
	afterEquals = ReplaceString(afterEquals,"mod","$"); //replace mod with $ 
	return afterEquals;
}

//Sanity check function using stack
bool areParanthesisBalanced(string expr) { 
	stack <char> s; 
	char x; 
	// Traversing the Expression 
	for (int i=0; i<expr.length(); i++) { 
		if (expr[i]=='(') { //If the current character is a starting bracket
			s.push(expr[i]); //push it to stack
		} 
		//If the current character is a closing bracket
		else if (expr[i]==')'){
		    if (s.top() == '(') s.pop();//pop from stack and check if it is the starting bracket 
		    else return false;
		}
	} 
	//Balanced if no starting bracket left
	return (s.empty()); 
} 

bool isVariablePresent(string value){ //method to check if there are any other variables used in an individual variable declaration
	//the string input value would be the part after the equals for every variable declaration statement
	int valueSize = value.size();  // size of the input string
	bool hasAlphabetLetter=false;
	for (int i = 0; i < valueSize; i++) {  //iterate over ever character of input string
	  	if(isalpha(value[i])) { //if a letter is found
	  		hasAlphabetLetter=true;
	  		break; //break as if even a single letter is found that means there is a variable so it has to be true
	  	} 
	  }
	  return hasAlphabetLetter;
}

bool isOperatorPresent(string value){ //method to check if there are any operators used in an individual variable declaration
	//the string input value would be the part after the equals for every variable declaration statement
	int valueSize = value.size();  // size of the input string
	bool hasOperator=false;
	for (int i = 0; i < valueSize; i++) {  //iterate over ever character of input string
	  	if(isoperator(value[i])) { //if a letter is found
	  		hasOperator=true;
	  		break; //break as if one letter is found that means there is a variable so it has to be true
	  	} 
	  }
	  return hasOperator;
}

//String replacement 
string ReplaceString(string subject, const string& search, const string& replace) { 
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

bool isoperator(char ch){
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%'|| ch=='!'|| ch=='@'|| ch=='#'|| ch=='$')
		return true;
	else
		return false;
}
