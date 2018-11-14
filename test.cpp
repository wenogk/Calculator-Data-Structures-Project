#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<stack>
#include<ctype.h>
#include <typeinfo>

using namespace std;
bool isoperator(char ch);
vector<string> tokenize(string x);
vector<string> infix2postfix(vector<string> &x);
bool isleq(string opA, string opB);
int convertOpToInt (string str);
bool isoperator(string str);
string evaluate(vector<string>  &y);
float eval(float x1, float x2, string sign);
string lineOperation(string afterEquals);
string ReplaceString(string subject, const string& search, const string& replace);


vector<string> tokenize(string x){

    vector <string> y;
    cout << "start of tokenization" << x << endl;
    
    int i=0;
    while(i<x.size()){
    
         if(i == 0 and x[i] == '-' and (isdigit(x[i+1]) or x[i+1]=='(') ){//unary minus
                //cout << i << " unary minus " << x[i] << endl;
                y.push_back("^");
                i++;
        }   
        
         if (x[i] == '-' and (isdigit(x[i+1]) or x[i+1]=='(') and (not isdigit(x[i-1])) and x[i-1]!=')' ){ //(4-2)-(-1)
                    //cout << i << " unary minus " << x[i] << endl;
                    y.push_back("^");
                    i++;
        }
        
        else if (isdigit(x[i])){//add digits to number
            string number;
            while (isdigit(x[i]) or x[i] == '.' ){
                number += x[i];
                i++;
            }
            //cout << "number is " << number << endl;
            y.push_back(number);
        }
        
        else if (isalpha(x[i])){//add letters to variable
            string variable;
            while (isalpha(x[i])){
                variable += x[i];
                i++;
            }
            //cout << "variable is " << variable << endl;
            y.push_back(variable);
        }
        
        else {// (, ), binary operators
            //cout << "binary operator" << x[i] << endl;
            y.push_back(string(1, x[i]));
            i++;
        }
    }    
    
    for(int i=0; i<y.size(); i++){
        //cout << y[i] << " ";
    }
    cout << endl;
    return y;
}


string lineOperation(string afterEquals){

    afterEquals = ReplaceString(afterEquals,";",""); //get rid of ;
    afterEquals = ReplaceString(afterEquals," ",""); //get rid of space
    afterEquals = ReplaceString(afterEquals,"++","!"); //replace ++ with !
    afterEquals = ReplaceString(afterEquals,"--","@"); //replace -- with @ 5+++4
    afterEquals = ReplaceString(afterEquals,"**","#"); //replace ** with #
    afterEquals = ReplaceString(afterEquals,"mod","$"); //replace mod with $ 
    return afterEquals;
}


vector<string> infix2postfix(vector<string> &x){

	stack <string> mystack;
	vector<string> y;
	
	cout << "post fix begins" << endl;

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
		if (not isoperator(str) and str!="(" and str!=")"){
		    //cout << "push operand to vector: " << str << endl;
			y.push_back(str);
		}
		//4.	If a left parenthesis is encountered, push it onto Stack.
		else if(str=="("){
		    //cout << "push ( to vector: " << str << endl;
			mystack.push(str);
		}
		//5.	If an operator is encountered, then: 
		else if(isoperator(str))
	    {	//a.	Repeatedly pop from Stack and add to Y each operator (on the top of Stack) 
			//which has the same precedence as or higher precedence than operator.
			while (isoperator(mystack.top()) and isleq(str,mystack.top()))
			{
			    //cout << "push operator to vector: " << mystack.top() << endl;
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
			    //cout << "push ) to vector: "  << mystack.top() << endl;
				y.push_back(mystack.top());
				mystack.pop();
			}
			//b.	Remove the left Parenthesis.
			mystack.pop();
		}
	}
	
	cout << "in post fix" << endl;
	for (int i=0; i<y.size(); i++){
        cout << y[i] << " ";
    }
    cout << endl;
    return y;
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

bool isoperator(string str){
	if( str=="+" || str=="-" || str=="*" || str=="/" || str=="%"|| str=="!"|| str=="@"|| str=="#"|| str=="$"||str=="^")
		return true;
	else
		return false;
}


string evaluate(vector<string>  &y){

	//1. Create a stack (e.g. of type float) to store the operands
	stack <string> mystack;
	//2. Scan the postfix expression from left to right for every element
	for (int i = 0; i < y.size(); i++){
	//	 a. if the element is an operand push it to the stack
	    if (not isoperator(y[i])){
	        mystack.push(y[i]);
	    }
	    else if(y[i]=="^"){
	        float num = stof(mystack.top())*-1;
	        mystack.pop();
	        mystack.push(to_string(num));
	    }
	    else if(y[i]=="@"){
	        float num = stof(mystack.top())-1;
	        mystack.pop();
	        mystack.push(to_string(num));
	    }
	    else if(y[i]=="#"){
	        float num = pow(stof(mystack.top()), 2);
	        mystack.pop();
	        mystack.push(to_string(num));
	    }
	    else if(y[i]=="!"){
	        float num = stof(mystack.top())+1;
	        mystack.pop();
	        mystack.push(to_string(num));
	    }
	    //   b. if the element is an operator pop 2 elements from the stack, 
	    //      apply the operator on it and push the result back to the stack
	    else{
	        float x1 = stof(mystack.top());
	        mystack.pop();
	        float x2 = stof(mystack.top());
	        mystack.pop();
	        float x3 = eval(x2,x1,y[i]);
	        mystack.push(to_string(x3));
	        cout << x2 << " " << x1 << " "<< y[i] << " =  " << x3 << endl;
	    }    
	}
	//3. return the value from the top of the stack (i.e. the final answer)	
	return mystack.top();
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


string ReplaceString(string subject, const string& search, const string& replace) { 
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}


int main(){

    string clean = lineOperation("-(5+4)+6");//(-(6+5)-8)
    vector<string> v = tokenize(clean);
    
    cout << " Tokenize in main" << endl;
    for (int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
    
    vector<string> post = infix2postfix(v);
    
    cout << " Postfix in main" << endl;
    for (int i=0; i<post.size(); i++){
        cout << post[i] << " ";
    }
    cout << endl;
    
    string result = evaluate(post);//result of calculation
    
    cout << "result of calculation " << result << endl;
    
}


