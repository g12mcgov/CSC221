/*

Grant McGovern
Dr. Burg 
CSC 221 
19 March 2014 

*/

/*********************** INCLUDES *******************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "Symbol.h"

using namespace std;

/*********************** FUNCTION HEADERS *******************************/

int nextPrime( int n ); //function declaration to find the next prime number
bool isPrime( int n ); //function to find if number passed in is prime
size_t hasher(const string & key); //declaring hash function here which is being pulled from Driver.cpp

/************************************************************************/

/** THIS ONE HAS TO COME BEFORE THE FOLLOWING TEMPLATE **/
//defining a template for the hash --> this one is a template for a string
template<typename string>
class thehash2 //making a hash2 class to be used in the next hash template
{
public:
    size_t operator()(const string & key) //this is the hash function declaration 
    {
        size_t hashVal = 0; 
        for(char ch : key) //C++11 feature --> goes through the range 
            hashVal = 37 * hashVal + ch; // sets the value of hashVal
        return hashVal;
    }
};

//defining a template for the hash --> this one is a template for a Symbol
template<typename Symbol> //making a hash for thehash2 to be used below in the in the call thehash<HashedObj> 
class thehash
{
public:
    size_t operator()(const Symbol & item) //takes an object of the Symbol class to be hashed by the above template 
    {
        static thehash2<string> hf; // creates a hashed object "hf"
        return hf(item.getData()); //grabs the hashed data from the item via accessor function
    }
};

template<typename HashedObj> //this is the template for the Object to be passed in from Driver.cpp
class HashTable
{
public:
	explicit HashTable(int TABLE_SIZE) //Constructor function for a HashTable, passing in the TABLE_SIZE
	{
		currentSize = 0; //sets int currentSize = 0;
		array.resize(TABLE_SIZE); //resizes the vector based on what ypu pass in 
	}
	void makeEmpty() //makes the HashTable empty
	{
		currentSize = 0;
		for(int i = 0; i < array.size(); i++)
			array[i].info = EMPTY; //see below for enums{} --> this declares EMPTY to be 0
	}
	bool contains(const HashedObj & x) const //searches the HashedObj passed in and returns either true/false if found 
	{
		return isActive(findPos(x)); //either true or false
	}
	bool insert(const HashedObj & x) //here is where a HashedObj is inserted into the HashTable
	{

		//cout << "Still ready to insert " << x.getData() << endl;
		int currentPos = findPos(x); //sets the currentPosition to the hash value generated in findPos(x)
		array[currentPos] = HashEntry(x, ACTIVE); //the vector value AT that SPECIFIC hash is equal to HashEntry(x, ACTIVE) where ACTIVE = 1
		cout << "Inserting: " << x.getData() << " at Index: " << currentPos << endl; //just to print out current index 
		currentSize++; //iterates currentSize
		if(++currentSize > array.size()) //if the table size is greater than the size of the symbol vector... rehash
			rehash();
		/*cout << "Trying to insert at position " << currentPos << endl;
		bool done = false;
		if(isActive(currentPos))
		{
			//cout << "Collision at index " << currentPos << endl;
			int i=currentPos+1;
			//cout << "array.size() = " << array.size() << endl;
			if (i == array.size())
				i = 0;
			while(!done)
			{
				//cout << "Trying index " << i << endl;
				if(i == currentPos)
				{
					done = true;
					rehash();
					//cout << "Rehashing " << endl;
				}
				else if(!isActive(i))
				{
					array[i] = HashEntry(x, ACTIVE);
					done = true;
				}
				else
				{
					i++;
					if(i == array.size())
					{
						i = 0;
					}

				}
			}

		}
		else
		{
			//cout << "inserting " << x.getData() << " at position " << currentPos << endl;
			array[currentPos] = HashEntry(x, ACTIVE);
		}*/
		return true;
	}
	bool remove(const HashedObj & x) //removes a HashedObj from the HashTable
	{
		int currentPos = findPos(x); //returns a hash value and sets equal to currentPos
		if(!isActive(currentPos)) //see isActive() function 
			return false;
		array[currentPos].info = DELETED; //DELETED is equal to 
		return true;
	}

	void print() //function used to print out the contents of the HashTable
	{
		for (int i = 0; i < array.size(); i++)
		{
			cout << "Index " << i << ":  ";
			if (isActive(i)) //if it's active, it prints the Symbol objects 
				cout << array[i] << endl; 
			else
				cout << "empty" << endl; //if its not active, it prints out "empty"

		}
	}

	enum EntryType{ ACTIVE, EMPTY, DELETED }; //this simply sets ACTIVE = 1, EMPTY = 0, and DELETED = -1
private:
	struct HashEntry //declares a HashEntry Struct to handle all the Hashed Objects read in 
	{
		HashedObj element; //sets whatever it comes in as HashedObj equal to the element
		EntryType info; // object of EntryType struct declared here

		HashEntry(const HashedObj & e = HashedObj(), EntryType i = EMPTY) : element(e), info(i) {} //constructer for a HashEntry object 

		friend ostream & operator <<(ostream & os, HashEntry & hashentry) //overloaded the stream operator to print out the HashEntry 
		{
			HashedObj Element = hashentry.element;  
			EntryType Info = hashentry.info;
			os << Element << " : " << Info << endl; 
			return os;
		}
	};

	vector<HashEntry> array; //declares a vector of HashEntry objects called array
	int currentSize; //initizializes currentSize

	bool isActive(int currentPos) const //function to check 
	{
		return array[currentPos].info == ACTIVE; //sets this equal to ACTIVE
	}
	int findPos(const HashedObj & x) const //finds the current position
	{
		int offset = 1; //sets offset equal to 1 
		int currentPos = myhash(x); //the currentPosition is equal to whatever the hashfunction returns 
		if(array[currentPos].info != EMPTY) // this checks for a collision --> if the array is anything but empty, we know a collision has occured.
			cout << "Collision at index: " << currentPos << endl; //simply prints out the index where a collision occured.
		while(array[currentPos].info != EMPTY) 
		{
			//currentPos += offset;
			//offset +=2;
			currentPos++; //iterates currentPos
			if(currentPos >= array.size())
			{
				currentPos -= array.size();
			}
		}
		return currentPos; //returns back the current position if there is not a collision 
	}
	void rehash() //function used to rehash the values 
	{
		cout << "Rehashing" << endl;
		vector<HashEntry> oldArray = array; //the old vector is set equal to the new vector 
		array.resize(nextPrime(2*oldArray.size())); //resizes the table 
		for(int j = 0; j < array.size(); j++)
			array[j].info = EMPTY; //sets the array info equal to 0 (Empty)

		currentSize = 0; //sets currentSize equal to 0
		for(int i = 0; i < oldArray.size(); i++)
			if(oldArray[i].info == ACTIVE) //this checks to see if the oldArray's indeces are active and if so, inserts the elements 
				insert(oldArray[i].element);
	}
	int myhash(const HashedObj & x) const //this takes in an object, puts this object through the hash templates defined above and creates a hashed object named hf
	{
		static thehash<HashedObj> hf;
        return hf( x ) % array.size( ); //mods it by the table size to get appropriate hash
	}
};


//function to simply search for the next prime number
int nextPrime( int n )
{
    if( n % 2 == 0 )
    {
        ++n;
    }
        

    for( ; !isPrime( n ); n += 2 )
    {

    }
        

    return n;
}
//function to simply see if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}
