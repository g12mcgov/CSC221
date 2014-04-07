/////////////////////////////////////////////////////
////Includes/////////////////////////////////////////
/////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"
/////////////////////////////////////////////////////
using namespace std;

int precendence(string); //ensures order of operations.
void InFixToPostfix(ifstream& in_file);
double EvaluatePostfix(double first_operand, double second_operand, char*myArray);

int main()
{
////VARS/////////////////////////////////////////////

    string absolutePath;

    cout << endl;
    cout << "Please type in the name of the file you would to open \n";
    cin >> absolutePath;

    ifstream in_file;
    in_file.open(absolutePath.c_str());
    if(!in_file)
    {
        cout << "failed to open input file\n" ;
        return 1 ;
    }
    else
    {
        InFixToPostfix(in_file); //kicks off program
    }

}


void InFixToPostfix(ifstream& in_file)
{
    string infix;
    int right_parentheses =0;
    int left_parentheses =0;
  
    while(getline(in_file, infix))
    {
        char myArray[infix.size()];
        strcpy(myArray, infix.c_str());

        for(int i = 0; i < sizeof(myArray); i++)
        {
            if(myArray[i] == '(')
            {
                right_parentheses++;
            }
            if(myArray[i] == ')')
            {
                left_parentheses++;
            }
        }
        if(right_parentheses!=left_parentheses)
        {
            cout << endl;
            cout << "There is a typo in one of the expressions in your file \n";
            cout << "Please fix it and rerun the program \n";
            exit(1);
        }

        for(int i = 0; i < sizeof(myArray); i++)
        {
            //int number = int(myArray[i]);
            //deferences the pointer and reads each char in the array
            //as an int rather than a character.
            //int number = myArray[i];
            if(isxdigit(myArray[i]) > 0) //function used to check for hexidecimal values (i.e. int's)
            {
                goto exit_out;
            }
            else if(myArray[i] == '(' || myArray[i] == ')' || myArray[i] == '+' || myArray[i] == '-' || myArray[i] == '*' || myArray[i] == '/' || myArray[i] == '\\' || myArray[i] == '\n')
            {
                goto exit_out;
            }
            else if(myArray[i] == char(32)) //checks to see if there is a space
            {
                goto exit_out;
            }
            else
            {
                cout << endl;
                cout << "There is an invalid character in the file\n";
                exit(1);
            }
        exit_out:;
        }

////////Declares a STRING Stack////////////////////////////////
        Stack<string> stack_string;
////////Declares an Int Stack/////////////////////////////////
        Stack<int> stack_int;
//////////////////////////////////////////////////////////////        
        for(int i = 0; i < sizeof(myArray); i++)
        {
            int number = isxdigit(myArray[i]);
            if(number > 0)
            {
                cout << number;
                //outputs the number b/c it is an operand
            }
            if(myArray[i] == '(')
            {
                stack_string.push(myArray[i]);
            }
            if(myArray[i] == ')')
            {
                while(stack_string.peek() != '(')
                {
                    cout << stack_string.peek();
                    stack_string.pop(); //pops to the peek
                }
            stack_string.pop(); // if there is a ), pops to the peek
            }
            if(myArray[i] == "+" || myArray[i] == "-" || myArray[i] == "/" || myArray[i] == "*")
            {
                if(stack_string.empty())
                {
                    stack_string.push(myArray[i]) //if there's nothing on the stack, pushes the current character
                    //goto done;
                    break; //breaks out of the statement 
                }
                int operatorHierarchy = precendence(myArray[i]);
                int stack_top = precendence(stack.peek());
                //must be declared here because i will have been interated through array
                if(operatorHierarchy > stack_top)
                {
                    stack_string.push(myArray[i]);
                }
                else if(operatorHierarchy <= stack_top) //could also be an if
                {
                    dump_out:
                    cout << stack_string.peek();
                    stack_string.pop();

                    int rerunThroughStack =0;
                    rerunThroughStack = precendence(stack_string.peek());
                    if(operatorHierarchy < stack_top)
                    {
                        stack_string.push(myArray[i]);
                        goto done; //could break
                    }
                    if(stack_string.peek() == "(")
                    {
                        stack_string.push(myArray[i]);
goto done;  
                    }
                    if(stack_string.empty())
                    {
                        stack_string.push(myArray[i]);
                        goto done;
                    }
                goto keeptrying;
                }
            }
            done:;
        }
        cout << stack_string.peek() << endl;

//////////Evaluate Section/////////////////////////////

        for(int i = 0; i < sizeof(myArray); i++)
        {
            if(isxdigit(myArray[i]) > 0) //this is a number
            {
                stack_int.push(isxdigit(myArray[i]));
                goto end;
            }
            else if(myArray[i] == '*' || myArray[i] == '+' || myArray[i] == '-' || myArray[i] == '/')
            {
                double first_operand;
                first_operand = stack_int.peek(); //fetches first operand on the stack_int
                stack_int.pop();
                //////////////////
                double second_operand;
                second_operand = stack_int.peek();
                stack_int.pop();
                //////////////////
                double answer;
                answer = EvaluatePostfix(first_operand, second_operand, myArray); //THIS PROBABLY IS NOT RIGHT
                stack_int.push(answer);
            }
        end:;
        }
            int size_of_stack;
            size_of_stack = stack_int.size();
            if(size_of_stack == 1)
            {
                cout << stack_int.peek();
            }
    }
}

double EvaluatePostfix(double first_operand, double second_operand, char* myArray) //might have to pass array as reference
{
    /*
        Cycle through the characters passed in through myArray[i];
    */
    for(int i = 0; i < sizeof(myArray); i++)
    {
        if(myArray[i] == '*')
        {
            double first_answer;
            first_answer = (second_operand * first_operand);
            return first_answer;
        }
        else if(myArray[i] == '/')
        {
            double second_answer;
            second_answer = (second_operand / first_operand);
            return second_answer;
        }
        else if(myArray[i] == '+')
        {
            double third_answer;
            third_answer = (second_operand + first_operand);
            return third_answer;
        }
        else if(myArray[i] == '-')
        {
            double fourth_answer;
            fourth_answer = (second_operand - first_operand);
            return fourth_answer;
        }
        /*
        else
        {
            cout << "There must be an error in your file" <<endl;
            break;
            exit(1);
        }
        */
    }
}


int precendence(string currentoperator)
{
    int precendence;
    if(currentoperator == "*" || currentoperator == "/")
    {
        precendence = 2;
        return precendence;
    }
    //by making it 2, the precendence is dubbed less than +/-
    if(currentoperator == "+" || currentoperator == "-")
    {
        precendence = 1;
        return precendence;
    }
    //by making it 1, the precendence is dubbed greater than */"/"
}

