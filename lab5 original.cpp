#include<iostream>
#include<string>
#include<cmath>
#include<stack>
#include<ctype.h>
#include <typeinfo>

using namespace std;

bool isoperator(char); //Helper method which checks if the input char is an operator
int convertOpToInt (char); //Helper mehtod which converts operators into int so their precdence can be compared
bool isleq(char, char); //Helper method which compare two operators  and return True if first operator has less or equal predence than the right operator
string infix2postfix(string);   //Helper Method which converts an infix notaiton into a postfix notation (lab4)

float evaluate(string y)		//Method which will evaluate a PostfixExpression and return the result
{
    
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
	    else{
	        float x1 = mystack.top();
	        mystack.pop();
	        float x2 = mystack.top();
	        mystack.pop();
	        int x3;
            if (y[i] == '+') x3 = x2+x1;
            if (y[i] == '-') x3 = x2-x1;
            if (y[i] == '*') x3 = x2*x1;
            if (y[i] == '/') x3 = x2/x1;
            if (y[i] == '^') x3 = pow(x2,x1); 
	        mystack.push(x3);
	    }    
	}
	//3. return the value from the top of the stack (i.e. the final answer)	
	return mystack.top();
}

//=============Main funciton ==============
int main()
{
	while(true)
	{
		string x;  						//Infix expression
		cout<<"Enter an Infix Expression: ";
		cin>>x;
	
		if("exit"==x) return 1;

		string y = infix2postfix(x);	//Postfix Expression
		cout << y << endl;
		float ans=evaluate(y);			//evaluate the postfix Expresion
		cout<<x<<"="<<ans<<endl;		//print the final answer
	}
	return EXIT_SUCCESS;
}
//=====================================================================
bool isoperator(char ch)
{
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
		return true;
	else
		return false;

}
//Helper mehtod which converts operators into int so their precdence can be compared
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
