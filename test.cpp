#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<stack>
#include<ctype.h>
#include <typeinfo>

using namespace std;
bool isoperator(char ch);

void tokenize(string x){

    vector <string> y;
    
    for(int i=0; i<x.size(); i++){
        cout << x[i] << " ";
    }
    
    int i=0;
    while(i<x.size()){
        
        if(isdigit(x[i])){
            string number;
            while (isdigit(x[i])){
                number += x[i];
                i++;
            }
            //cout << number << endl;
            y.push_back(number);
        }
        
        else if (isalpha(x[i])){
            string variable;
            while (isalpha(x[i])){
                variable += x[i];
                i++;
            }
            //cout << variable << endl;
            y.push_back(variable);
        }
        
        else{
            cout << "hello" << x[i] << endl;
            y.push_back(string(1, x[i]));
            i++;
        }
        
    }
    
    for(int i=0; i<y.size(); i++){
        cout << y[i] << " ";
    }
}

bool isdigit(char ch){
	if( ch=='1' || ch=='2' || ch=='3' || ch=='4' || ch=='5'|| ch=='6'|| ch=='7'|| ch=='8'|| ch=='9'|| ch=='0')
		return true;
	else
		return false;
}

bool isoperator(char ch){
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%'|| ch=='!'|| ch=='@'|| ch=='#'|| ch=='$')
		return true;
	else
		return false;
}

int main(){
    tokenize("3+4-1");
}
