/*

Grant McGovern 
Dr. Burg 
CSC 221 
28 February 2014

Description:

This program generates 20 random integers between 
1 and 100 and inserts them into a tree node via the
insert function as seen below. 

Disclaimer/How-To-Run:

	(In Terminal (Mac OSX) or Command Line):

		>> g++ Driver.cpp -o temp
		>> ./temp

*/

/****************** Includes ****************/
#include <iostream>
#include "BinaryTree.h"
#include <cstdlib> // for an exit call
#include <stdlib.h>
#include <string>
#include <time.h> 
#include <unistd.h>

using namespace std;

int main()
{
	/********** Local Vars *************/
	int random_store;
	int max_number = 20;
	int user_response;

	/********** Declare Tree *************/
	Tree * tree = new Tree; //declares a tree of integer.

	/********** Seed rand() to system time ****/
	srand(time(NULL)); 

	for(int i = 0; i < max_number; i++)
	{
		random_store = rand() % 100 + 1; //generates random numbers from 1 to 100
		tree->insert(random_store); //inserts the integers up to 20 into the tree.
	}
	usleep(2000000); //sleeps the program for 2 seconds to simulate the digits being added to the tree.
	cout << "Numbers successfully added into the tree." << endl;
	
	cout << "What would you like to do now?" << endl;
	cout << "Press (1) to inorderPrint" << endl;
	cout << "Press (2) to preorderPrint" << endl;
	cout << "Press (3) to postorderPrint" << endl;
	
	cin >> user_response; //takes in the user response;

	if(user_response == 1)
	{
		//perform inorderPrint
		tree->inOrder(tree->root);
		cout << endl;
	}
	else if(user_response == 2)
	{
		//perform preorderPrint
		tree->preOrder(tree->root);
		cout << endl;
	}
	else if(user_response == 3)
	{
		//perform postorderPrint
		tree->postOrder(tree->root);
		cout << endl;
	}
}



