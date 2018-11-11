#include <iostream>
#include <fstream>
#include <stack>
#include <math.h>

using namespace std; 
  

  
// This function receives a node of the syntax tree 
// and recursively evaluates it 
float eval(float x1, float x2, string sign) { 

    if (sign == "+")//addition
        return x1 + x2;
  
    if (sign == "-" && x1 != NULL)//subtraction
        return x1 - x2;
        
    if (sign == "*")//multiplication
        return x1 * x2;

    if (sign == "/")//division
        return x1 / x2;
        
    if (sign == "%")//integer division
        return static_cast<int>(x1 / x2);
        
    if (sign == "mod")//modulus 
        return (int)x1 % (int)x2;
        
    if (sign == "-" && x1 == NULL)//unary negative
        return 0 - x2;        
        
    if (sign == "++" && x1 == NULL)//unary plus 
        return x2 + 1;
        
    if (sign == "--" && x1 == NULL)//unary minus 
        return x2 - 1;
        
    if (sign == "**" && x1 == NULL)//unary square 
        return pow(2.0, x2);
}
  
//driver function to check the above program 
int main(){ 
    cout << eval(0.0, 2, "**") << endl;
} 
