#include <iostream>
#include <string> 
#include <fstream>
#include <stack> 
#include <map> 
#include<cmath>
#include<ctype.h>
using namespace std;



bool debugMode=true;
bool isoperator(char); //Helper method which checks if the input char is an operator

int evaluate(string y)		//Method which will evaluate a PostfixExpression and return the result
{	
	stack <float> stackA;
	int length = y.size(); 
	for(int i = 0; i < length; i++) {
		if(isoperator(y[i])) {
			float first=stackA.top();
			stackA.pop();
			float second=stackA.top();
			stackA.pop();
			float result;
			//cout<< "res: " << first << endl;
			 if(y[i]=='+') {
			 	result = first + second;
			 }
			 if(y[i]=='-') {
			 	result = second - first;
			 }
			 if(y[i]=='*') {
			 	result = first * second;
			 }
			 if(y[i]=='/') {
			 	result = second / first;
			 }
			 if(y[i]=='^') {
			 	result = pow(second,first);
			 }
			 if(y[i]=='$') {
			 	result = result; //make it find the mod 
			 }
			 stackA.push(result);
		} else {
			//cout<<"PUSHING: " << y[i] <<endl;

			stackA.push(y[i]);
		}
	}
	return int(stackA.top());
	//1. Create a stack (e.g. of type float) to store the operands
	//2. Scan the postfix expression from left to right for every element
	//	 a. if the element is an operand push it to the stack
	//   b. if the element is an operator pop 2 elements from the stack, 
	//      apply the operator on it and push the result back to the stack
	//3. return the value from the top of the stack (i.e. the final answer)	
}

bool isoperator(char ch)
{
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
		return true;
	else
		return false;

}
bool isVariablePresent(string value) { //method to check if there are any other variables used in an individual variable declaration
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

bool isOperatorPresent(string value) { //method to check if there are any operators used in an individual variable declaration
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




string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) { //GOT THIS REPLACESTRING METHOD FROM THE INTERNET LOL
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}
int main(int count, char * args[]) {
	if(debugMode) cout <<"**********DEBUG MODE IS ON,IT JUST PRINTS WHAT IT DOES WHICH MAKES IT EASIER TO UNDERSTAND, TO SWITCH OFF SET debugMode variable to false in file******"<<endl;
	string filename="filex.txt";
	ifstream infile;
	ifstream lineNum;
	map<string, int> variableMap;  
	lineNum.open(filename);
	int lines=0;
	string str1;
  while (getline(lineNum, str1)) { 
  	lines++;
  }
  if(debugMode) cout<<"-------------"<< lines << " lines of vars in text file -------------"<<endl;
  lineNum.close();
  while(variableMap.size()!=lines) {
		infile.open(filename);
		  string lineString;
	  while (getline(infile, lineString)) {
	  	string str=lineString;
	   string variableName = str.substr(0, str.find("=")-1); // - 1 to remove that space before the =
	   int varSize = str.size(); 
	   string afterEquals= str.substr(str.find("=")+1,varSize);
	   afterEquals = ReplaceString(afterEquals,";","");
	   afterEquals = ReplaceString(afterEquals," ","");
	   afterEquals = ReplaceString(afterEquals,"mod","$"); //some of the textfiles use a "mod" operator so I'm just using $ for it to make it easier to differentiate variables from operators
	   if(debugMode) cout<<variableName<<"="<<afterEquals<<endl;
	   //REPLACE LINE WITH VARS FROM MAP
		map<string, int>::iterator it = variableMap.begin();
		if(debugMode) cout<<"----- Gonna iterate through map and find and replace all keys with values, in " << variableName <<" ----"<<endl;
	while (it != variableMap.end())
	{
		if(debugMode) cout<< "replacing " << it->first << " with " << to_string(it->second) << " in " <<variableName<<"="<<afterEquals<<endl; 
		afterEquals  = ReplaceString(afterEquals, it->first, to_string(it->second));
		if(debugMode) cout<<"Result of replacement: " <<variableName<<"="<<afterEquals<<endl;
		it++;
	}
	if(debugMode) cout << "---- End map iteration ----" <<endl;
		//END REPLACE LINE WITH VARS
	  if((!isVariablePresent(afterEquals))&&(isOperatorPresent(afterEquals))) { //no variables in expression but expression has operations 
	  //	cout << variableName << " has no other vars in it, so can add to map" <<endl;
	  	if(debugMode) cout<< "Inserting and calculating" << variableName << " = " << afterEquals << " into map (99 cus "<< variableName <<" requires calculation and evaluate() method not implemented to actually calculate lol)"<<endl;
	   //if (debugMode) {cout<< "Insertion and Calculation occuring: " << afterEquals << "=" << to_string(evaluate(afterEquals)) <<endl;}
	   variableMap.insert(make_pair(variableName, 99)); //change 99 to evaluate(afterEquals) when evaluate() function is implemented

	} else if((!isVariablePresent(afterEquals))&&(!isOperatorPresent(afterEquals))) { //no variables in expression and no operations, just number
		if(debugMode) cout<< "Inserting" << variableName << " = " << afterEquals <<" into map (direct value cus variable has no operation required, is just a number)"<<endl;
		
		variableMap.insert(make_pair(variableName, stoi(afterEquals)));
	}
	   //cout << "variableName: " << variableName <<endl;
	  }
	  
	  infile.close();
	    //REPLACE LINE WITH VARS FROM MAP
		
		map<string, int>::iterator it = variableMap.begin();
		if(debugMode) cout<<"-----------"<<endl;
	while (it != variableMap.end())
	{
		cout<< it->first << " = " << it->second <<endl;
		it++;
	}
		//END REPLACE LINE WITH VARS
}
	
  return EXIT_SUCCESS;

	}





int convertOpToInt (char ch)
{
    if (ch=='+' || ch=='-') return 1;
    if (ch=='*' || ch=='/') return 2;
    if (ch=='^') return 3;
    return 0;
}

//Helper method which compare two operators and return True if first operator
//has less or equal predence than the right operator
bool isleq(char opA, char opB)
{
	return (convertOpToInt(opA)<=convertOpToInt(opB));
}

// Helper Method which converts an Infix Notaiton to a postfix notation
string infix2postfix(string x)
{
	stack <char> mystack;
	string y="";

	//1.	Push “(“onto Stack, and add “)” to the end of X.
	x=x+')';
	mystack.push('(');

	//2.	Scan X from left to right and repeat Step 3 to 6 for each element of X 
	//until the Stack is empty.3.	If an operand 

	int i=0;
	while(!mystack.empty())
	{	
		char ch = x[i++];
		//3.	If an operand is encountered, add it to Y.
		if (isalnum(ch))
			y=y+ch;
		//4.	If a left parenthesis is encountered, push it onto Stack.
		else if(ch=='(')
			mystack.push(ch);
		//5.	If an operator is encountered, then: 
		else if(isoperator(ch))
		{	//a.	Repeatedly pop from Stack and add to Y each operator (on the top of Stack) 
			//which has the same precedence as or higher precedence than operator.
			while (isoperator(mystack.top()) and isleq(ch,mystack.top()))
			{
				y=y+mystack.top();
				mystack.pop();
			}
			//b.	Add operator to Stack.
			mystack.push(ch);
		}
		//.6.	If a right parenthesis is encountered, then: 
		else if(ch==')')
		{
			//a.	Repeatedly pop from Stack and add to Y each operator 
			//(on the top of Stack) until a left parenthesis is encountered.
			while(mystack.top()!='(')
			{
				y+=mystack.top();
				mystack.pop();
			}
			//b.	Remove the left Parenthesis.
			mystack.pop();
		}
	}
	return y;
}