#ifndef STACK_H
#define STACK_H
/////////////////////////////////////////////////////
////Includes/////////////////////////////////////////
/////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <stdio.h>
/////////////////////////////////////////////////////
using namespace std;

/*-------------------------------------------------------------------------------------------------------------*/
class stack;

class Stack
{
private:
	class stackListNode	// Struct linked list
		{
		public:
			int data;
			stackListNode *next;
		private:
			//Nothing to declare-->placeholder since class 
			//sets data members to private initially
		};

	stackListNode *top;

public:
	/////////////////////////////////////////////////
	//Constructor Function//////////////////////////
	Stack() {top = NULL;}

		/////////////////////////////////////////////////
		//Rest of functions defined inline for simplicity

		void push(char token)	// Push token onto the stack and create new node for top of stack
			{
				stackListNode *newNode = new stackListNode;
				newNode-> data = token;
				newNode-> next = top;
				top = newNode;
			}

		int pop()
			{
				if(empty())
				{
					cout << "Stack is empty!\n" << endl;
					return NULL;				
				}

				stackListNode *temp = top;
				top = temp-> next;
			}
			
		int peek()
			{
				if(empty())
				{
					cout << "Stack is empty!\n" << endl;
					return NULL;				
				}

				return top->data;
			}

		int empty()
			{
				return top == NULL;
			}
};

#endif	


