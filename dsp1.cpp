#include <iostream>
#include <string> 
#include <fstream>
#include <stack> 
#include <map> 
#include<cmath>
#include<ctype.h>
#include<math.h>
using namespace std;

bool debugMode=true;
bool isoperator(char); //Helper method which checks if the input char is an operator
float eval(float x1, float x2, string sign) { 

    return 0.0;
}
class node 
{ 
public: 
    string info; 
    node *left, *right; 
    node(string x) 
    { 
        info = x; 
    } 
}; 
// Utility function to return the integer value 
// of a given string 
int toInt(string s) 
{ 
    int num = 0; 
    for (int i=0; i<s.length();  i++) 
        num = num*10 + (int(s[i])-48); 
    return num; 
} 
// This function receives a node of the syntax tree 
// and recursively evaluates it 
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
			//y=y+ " ";
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
bool isDoubleOperatorPresent(string y) {
return (y.find("++")!= std::string::npos)||(y.find("--")!= std::string::npos);
}
string doubleOperatorHandler(string input) {
	string y=input;
	while((y.find("++")!= std::string::npos)||(y.find("--")!= std::string::npos)) {
		if(debugMode) {cout<<"------DOUBLE OPERATOR HANDLER-----"<<endl;}
	for (int i = 0; i < y.length(); i++){
	//	 4+++6
		if((isoperator(y[i]))&&(isoperator(y[i+1]))&&(isdigit(y[i+2]))&&(y[i]==y[i+1])) {

				string number;
				for (int j = i+2; j < y.length(); j++){
					if(isdigit(y[j])) {
					number = number + to_string(y[j]-48);
				} else {
					break;
				}
				}
				cout<<"NUMBER IS:"<<number<<endl;
			if(y[i]=='+') {
				string search = "++" + number;
				int ans = stoi(number)+1;
				string result = to_string(ans);
				if(debugMode) cout<<"Finding:"<<search<<" and replacing with:"<<result<<" in the string:"<<y<<endl;
				y=ReplaceString(y,search,result);
				break;
			}
			if(y[i]=='-') {
				string search = "--" + number;
				int ans = stoi(number)-1;
				string result = to_string(ans);
				y=ReplaceString(y,search,result);
			}
		}
	}
}
return y;
}
int evaluate(string y)		//Method which will evaluate a infix and return the result
{
	string infix = y;
	y = infix2postfix(y);
    cout <<  "EVALUATING:"<<y<<" from infix expression:"<<infix<<endl;
	//1. Create a stack (e.g. of type float) to store the operands
	stack <float> mystack;
	//2. Scan the postfix expression from left to right for every element

	for (int i = 0; i < y.length(); i++){
	//	 a. if the element is an operand push it to the stack
		if (isdigit(y[i])){
	        mystack.push(int(y[i]) - 48);
	    }
	    //   b. if the element is an operator pop 2 elements from the stack, 
	    //      apply the operator on it and push the result back to the stack
	    else {
	        float x1 = mystack.top();
	        mystack.pop();
	        float x2 = mystack.top();
	        mystack.pop();
	        int x3;
            if (y[i] == '+')//addition
        return x1 + x2;
  
    if (y[i] == '-')//subtraction
        return x1 - x2;
        
    if (y[i] == '*')//multiplication
        return x1 * x2;

    if (y[i] == '/')//division
        return x1 / x2;
        
    if (y[i] == '%')//integer division
        return static_cast<int>(x1 / x2);
        
    if (y[i] == '$')//modulus 
        return (int)x1 % (int)x2;
        
	    }    
	}
	//3. return the value from the top of the stack (i.e. the final answer)	
	return mystack.top();
}

/*
int evaluate(string y)		//Method which will evaluate a PostfixExpression and return the result
{

	
	node root,t1,t2;
	string postfix = infix2postfix(y);
	int size = postfix.size();
	stack<node> st; 
	for (int i=0; i<size; i++) 
    { 

    	if (!isoperator(postfix[i])) 
        { 
            root = new node(postfix[i]); 
            st.push(t); 
        } 
        else {
        	 node root2 = new node(postfix[i]);

        }
    }
    //if (debugMode) { cout <<"Evaluating: "<< y<<endl;}
	//1. Create a stack (e.g. of type float) to store the operands
	return 99;
	
}*/



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
		  if(!variableMap.empty()) {
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
		  }
		//END REPLACE LINE WITH VARS
		  if((!isVariablePresent(afterEquals))&&(isDoubleOperatorPresent(afterEquals))) {
		  	afterEquals = doubleOperatorHandler(afterEquals);
		  }
	  if((!isVariablePresent(afterEquals))&&(isOperatorPresent(afterEquals))) { //no variables in expression but expression has operations 
	  //	cout << variableName << " has no other vars in it, so can add to map" <<endl;
	  	//if(debugMode) cout<< "Inserting and calculating" << variableName << " = " << afterEquals << " into map (99 cus "<< variableName <<" requires calculation and evaluate() method not implemented to actually calculate lol)"<<endl;
	  // if (debugMode) {cout<< "Insertion and Calculation occuring: " << afterEquals << "=" << to_string(evaluate(afterEquals)) <<endl;}
	  	
	   variableMap.insert(make_pair(variableName, evaluate(afterEquals))); //change 99 to evaluate(afterEquals) when evaluate() function is implemented

	} else if((!isVariablePresent(afterEquals))&&(!isOperatorPresent(afterEquals))) { //no variables in expression and no operations, just number
		if(debugMode) cout<< "Inserting" << variableName << " = " << afterEquals <<" into map (direct value cus variable has no operation required, is just a number)"<<endl;
		//afterEquals = doubleOperatorHandler(afterEquals);
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
	//cout<<"TEST CALCULATION: "<< evaluate(infix2postfix("(6)+(4)")<< endl;
  return EXIT_SUCCESS;

	}





// Helper Method which converts an Infix Notaiton to a postfix notation
