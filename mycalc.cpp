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
bool isoperator(string str);
void mapEvaluation(string filename);
string evaluate(vector<string>  y);
float eval(float x1, float x2, string sign);
vector<string> tokenize(string x);
int convertOpToInt (string str);
bool isleq(string opA, string opB);
vector<string> infix2postfix(vector<string> x);
vector<string> tokenize(string x);


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

    mapEvaluation(inputFile);
}





//Add calculated variables and values to the map
void mapEvaluation(string filename){
    
    ifstream file;
    map<string, float> variableMap;  
    string afterEquals;
    string variableName;
    int lineNum;
    string line;
    string cleanExpression;
    
    //get number of lines
    file.open(filename);
    while (getline(file, line)) {
        if (line.size() > 0){
            lineNum++;
        }
    }
    file.close();
    
    while(variableMap.size()!=lineNum) {//while not all variables are solved

	    file.open(filename);
	    string lineString;
	
        while (getline(file, line)) {
        
        /*
        evaluation carried on one single expression
        */
        
            variableName = line.substr(0, line.find("=")-1); //variable name
            afterEquals = line.substr(line.find("=")+1, line.size()-1); //expression
            
            cout << "afterEquals" << afterEquals << endl;
            
            cleanExpression = lineOperation(afterEquals);//expression manipulation
            
            
            if(areParanthesisBalanced(cleanExpression)){//sanity check
                cout << cleanExpression << " is balanced" << endl;
            
                //update variables with new values
                if(!variableMap.empty()) {
                    map<string, float>::iterator it = variableMap.begin();
                    while (it != variableMap.end()){
                        cleanExpression  = ReplaceString(cleanExpression, it->first, to_string(it->second));
                        it++;
                    }
                }
                
                //postfix calculation
                if((!isVariablePresent(cleanExpression))&&(isOperatorPresent(cleanExpression))) { 
                    vector<string> v = tokenize(cleanExpression);//tokenize the expression into vector 
                    vector<string> postfix = infix2postfix(v);//postfix expression
                    string result = evaluate(postfix);//result of calculation
                    variableMap.insert(make_pair(variableName, stof(result))); //put (variable,value) to map
                } 
                
                //simple calculation
                else if((!isVariablePresent(cleanExpression))&&(!isOperatorPresent(cleanExpression))) { 
                    variableMap.insert(make_pair(variableName, stof(afterEquals)));
                }    
                
            }
        }
        
        //every line of expression has been visited
        file.close();
	}
	
    //calculation completed
    map <string, float>::iterator it = variableMap.begin();
    while (it != variableMap.end())
    {
        cout<< it->first << " = " << it->second <<endl;
        it++;
    }
}



float eval(float x1, float x2, string sign) { 

    if (sign == "+")//addition
        return x1 + x2;
  
    if (sign == "-")//subtraction
        return x1 - x2;
        
    if (sign == "*")//multiplication
        return x1 * x2;

    if (sign == "/")//division
        return x1 / x2;
        
    if (sign == "%")//integer division
        return static_cast<int>(x1 / x2);
        
    if (sign == "$")//modulus 
        return (int)x1 % (int)x2;
}

//Method which will evaluate a PostfixExpression and return the result
string evaluate(vector<string>  y){

	//1. Create a stack (e.g. of type float) to store the operands
	stack <string> mystack;
	//2. Scan the postfix expression from left to right for every element
	for (int i = 0; i < y.size(); i++){
	//	 a. if the element is an operand push it to the stack
	    if (not isoperator(y[i])){
	        mystack.push(y[i]);
	    }
	    //   b. if the element is an operator pop 2 elements from the stack, 
	    //      apply the operator on it and push the result back to the stack
	    else{
	        float x1 = stof(mystack.top());
	        mystack.pop();
	        float x2 = stof(mystack.top());
	        mystack.pop();
	        int x3;
            
	        mystack.push(to_string(eval(x1,x2,y[i])));
	    }    
	}
	//3. return the value from the top of the stack (i.e. the final answer)	
	return mystack.top();
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
	  	if(isoperator(to_string(value[i]))) { //if a letter is found
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

bool isoperator(string str){
	if( str=="+" || str=="-" || str=="*" || str=="/" || str=="%"|| str=="!"|| str=="@"|| str=="#"|| str=="$")
		return true;
	else
		return false;
}



vector<string> tokenize(string x){

    vector <string> y;
    
    int i=0;
    while(i<x.size()){
        
        if(isdigit(x[i])){//add digits to number
            string number;
            while (isdigit(x[i]) or x[i] == '.' ){
                number += x[i];
                i++;
            }
            y.push_back(number);
        }
        
        else if (isalpha(x[i])){//add letters to variable
            string variable;
            while (isalpha(x[i])){
                variable += x[i];
                i++;
            }
            y.push_back(variable);
        }
        
        else if (x[i] == '-' and isdigit(x[i+1]) and not isdigit(x[i-1]) and x[i-1]!=')' ){//unary minus
            string number;
            cout << "unary minus" << x[i] << endl;
            number += x[i];
            i++;
            while (isdigit(x[i]) or x[i] == '.' ){
                number += x[i];
                i++;
            }
            y.push_back(number);
        }
        
        else if (x[i] == '!'){//++
            string number;
            i++;
            while (isdigit(x[i]) or x[i] == '.'){
                number += x[i];
                i++;
            }
            float f = stof(number) + 1;
            y.push_back(to_string(f));
        }

        else if (x[i] == '@'){//--
            string number;
            i++;
            while (isdigit(x[i]) or x[i] == '.'){
                number += x[i];
                i++;
            }
            float f = stof(number) - 1;
            y.push_back(to_string(f));
        }
        
        else if (x[i] == '#'){//**
            string number;
            i++;
            while (isdigit(x[i]) or x[i] == '.'){
                number += x[i];
                i++;
            }
            float f = pow(stof(number),2);
            y.push_back(to_string(f));
        }
        
        
        else{// (, ), binary operators
            cout << "binary operator" << x[i] << endl;
            y.push_back(string(1, x[i]));
            i++;
        }
        
    }
    
    for(int i=0; i<y.size(); i++){
        cout << y[i] << " ";
    }
    
    return y;
}


vector<string> infix2postfix(vector<string> x){

	stack <string> mystack;
	vector<string> y;

	//1.	Push “(“onto Stack, and add “)” to the end of X.
	x.push_back(")");
	mystack.push("(");

	//2.	Scan X from left to right and repeat Step 3 to 6 for each element of X 
	//until the Stack is empty.
	int i=0;
	while(!mystack.empty())
	{	
		string str = x[i++];
		//3.	If an operand is encountered, add it to Y.
		if (not isoperator(str) and str!="(" and str!=")")
			y.push_back(str);
		//4.	If a left parenthesis is encountered, push it onto Stack.
		else if(str=="(")
			mystack.push(str);
		//5.	If an operator is encountered, then: 
		else if(isoperator(str))
	    {	//a.	Repeatedly pop from Stack and add to Y each operator (on the top of Stack) 
			//which has the same precedence as or higher precedence than operator.
			while (isoperator(mystack.top()) and isleq(str,mystack.top()))
			{
				y.push_back(mystack.top());
				mystack.pop();
			}
			//b.	Add operator to Stack.
			mystack.push(str);
		}
		//.6.	If a right parenthesis is encountered, then: 
		else if(str==")")
		{
			//a.	Repeatedly pop from Stack and add to Y each operator 
			//(on the top of Stack) until a left parenthesis is encountered.
			while(mystack.top()!="(")
			{
				y.push_back(mystack.top());
				mystack.pop();
			}
			//b.	Remove the left Parenthesis.
			mystack.pop();
		}
	}
}

bool isleq(string opA, string opB){
	return (convertOpToInt(opA)<=convertOpToInt(opB));
}
int convertOpToInt (string str){
    if (str=="+" || str=="-") return 1;
    if (str=="*" || str=="/" || str=="%"|| str=="$") return 2;
    if (str=="^") return 3;
    return 0;
}
