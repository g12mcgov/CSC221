/*

Grant McGovern
Dr. Burg 
CSC 221 
19 March 2014 

*/

/*********************** INCLUDES *******************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <map>
#include <cstdlib>
#include <cmath>
#include <iterator>
#include "SeparateChaining.h"

using namespace std;

int TABLE_SIZE;  // Hope you don't mind, but set TABLE_SIZE as the one global so the hasher() function at the bottom could use it
                // without having to pass it in as an argument. 


/*********************** FUNCTION HEADERS *******************************/

size_t hasher(const string & key); //hash function, defined at the bottom

/************************************************************************/

int main()
{
    ///////// Declares a Symbol Object /////////
	Symbol symb_temp;

    ///////// Declares a Vector of Symbol Objects /////////
	vector<Symbol> symbols;

    ///////// Variables for File I/O ///////////
	string read_in_string;
    int read_in_int;

    //////////////////////////////////////////////////////////

	ifstream file; //declares an ifstream file to read in data from textfile
    file.open("symbols.txt");
    
    cout << "Opening file..." << endl << endl;
    
    usleep(1000000); //simulates a short delay while opening file
    
    if(!file)
    {
    	cout << "System could not open file." << endl;
    }
    else
    {
    	cout << "File opened successfully." << endl << endl;
    }

    while(file >> read_in_string) //while there are still lines to read in, put these lines into read_in_string
    {
        symb_temp.setData(read_in_string); //set the data member "data" of the Symbol class to read_in_string
        file >> read_in_int; //while there are still lines to read in, put these lines into read_in_int
        symb_temp.setType(read_in_int); //set the data member "type" of the Symbol class to read_in_string
        symbols.push_back(symb_temp); //finally, put these objects into the vector of Symbol objects
    }


    cout << "What would you like the table size to be?" << endl;
    cout << "Please consider making the size of the table a prime number (hash tables work best with prime #'s) " << endl;
    cin >> TABLE_SIZE;

    HashTable<Symbol> hashtable(TABLE_SIZE); //creates a HashTable of the size passed in
    cout << endl;

    for(int j = 0; j < symbols.size(); j++)
    {
    	symb_temp.setData(symbols[j].getData()); //sets data of symbol object to the current data returned by getData()
        cout << symb_temp.getData() << endl; 

        symb_temp.setType(symbols[j].getType()); //sets type of symbol object to the current data returned by getType()
        cout << symb_temp.getType() << endl;

        cout << endl;

        hashtable.insert(symb_temp); //inserts the symbol objects into the hashTable()
    }
    hashtable.print(); //calls the print() function to print out the HashTable
}

size_t hasher(const string & key) //Hash Function which takes in a string
{
	size_t hashVal = 0;

	for(char ch : key)
	{
		hashVal = 37 * hashVal + ch;
	}
	return labs(hashVal % TABLE_SIZE); //labs is used to find absolute value of long int 
}








