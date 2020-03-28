// RPN calculator
//Liam Turcotte 
#include <iostream> 
#include <string>
#include <stack> 

using namespace std;
bool is_str_digit(string);  // returns true if input parameter string is and integer (e.g., "127343")
bool is_str_operator(string); // returns true if the input parameter is an operator character (e.g., "+", "*")

class NotEnoughOperands { //exception class 
    public: 
        NotEnoughOperands() {} 
}; 


int main() 
{
    string in;
    stack<string> st;   // stack definition

    cin >> in;

    try {
        if (!is_str_digit(in) && !is_str_operator(in)) {
            throw in; 
        }

        while(in != "q")
        {
            if(is_str_digit(in)){
                st.push(in); 
            }
            else if(is_str_operator(in))
            {   
                if (st.size() == 0) { //calling top() on empty stack is segfault 
                    throw NotEnoughOperands(); 
                }
            
                if (!is_str_digit(st.top())) {
                    throw NotEnoughOperands(); 
                }
                
                int value1 = stoi(st.top()); 
                st.pop(); 

                if (st.size() == 0) { //check size again after pop 
                    throw NotEnoughOperands(); 
                }

                if (!is_str_digit(st.top())) {
                    throw NotEnoughOperands(); 
                }
                int value2 = stoi(st.top()); 
                st.pop(); 
                int value3; 

                switch(in[0])
                {
                    case '+':
                        value3 = value2 + value1;
                        break;

                    case '-':
                        value3 = value2 - value1;
                        break;

                    case '*':
                        value3 = value2 * value1;
                        break;

                    case '/':
                        value3 = value2 / value1;
                        break;

                }

                st.push(to_string(value3)); 

            }
    
            cin >> in;
        }

        if (st.size() != 1) {
            throw st.size(); 
        }
        cout << "The answer is : " << st.top() << endl;
    }

    catch (NotEnoughOperands n) {
        cout << "not enough operands." << endl; 
    } 
    catch (unsigned long size) {
        cout << size << " items on the stack, can't print result." << endl; 
    }
    catch (string in) {
        cout << "\"" << in << "\" is not a valid input." << endl; 
    }

    return 0; 
}

bool is_str_digit(string s)
{
    for (int i = 0; i < s.length(); ++i)
    {
            if(!isdigit(s[i]))
                return false;
    }
    return true;
}
bool is_str_operator(string s)
{
    return (s.length()==1 && (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0]== '/'));
}