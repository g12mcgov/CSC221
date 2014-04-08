/*

Grant McGovern
Dr. Burg 
CSC 221 
19 March 2014 

*/



#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

/*********************** INCLUDES *******************************/

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include "Symbol.h"
#include <iterator>

using namespace std;

/*********************** FUNCTION HEADERS *******************************/

int nextPrime( int n ); //function declaration to find the next prime number
bool isPrime( int n ); //function to find if number passed in is prime

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
        return hf(item.getData()); //grabs the hashed data which in our case is the string from the item via accessor function
    }
};


template <typename HashedObj> //this is the template for the Object to be passed in from Driver.cpp
class HashTable
{
  public:
    explicit HashTable(int size) //constructor function for a HashTable, passing in the TABLE_SIZE
    { 
        currentSize = 0;
        theLists.resize(size); // this sets the size of the theLists to TABLE_SIZE, the value passed in.
    }

    bool contains( const HashedObj & x ) const
    {
        auto & whichList = theLists[ myhash( x ) ]; //using a C++11 feature, sets whichList equal to the list containing the hashed HashedObj x
        return find( begin( whichList ), end( whichList ), x ) != end( whichList ); //Using a predefined find( ) function, returns true/false if x is found
    }

    void makeEmpty( ) //function to make the HashTable empty
    {
        for( auto & thisList : theLists ) // uses C++11 feature of using auto to iterate through the range in theLists
            thisList.clear( ); //clears the list using a predefined list function, clear()
    }

    bool insert( const HashedObj & x ) //this function inserts for the left side 
    {
        auto & whichList = theLists[myhash( x )]; // like above, using a C++11 feature, sets whichList equal to the list containing the hashed HashedObj x

        if( find( begin( whichList ), end( whichList ), x ) != end( whichList) ) //prevents duplicate insertions by going through list and seeing if x is already there.
            return false;
        if(whichList.size() > 0) //If this condition is true, we know there already exists an object at that point in the list so it MUST BE A COLLISION
        {
            cout << "Collision Occured. " << endl;
        }
        whichList.push_back( x ); //if there is no collision, simply add that object into the list 

        if( ++currentSize > theLists.size()) //if the currentSize of the list (iterated) is greater than the size of the list, we must rehash to make a new HashTable
        {
            rehash(); //creates a new HashTable
            cout << "\n New Table Created" << endl;
        }
        return true;
    }
    
    bool insert( HashedObj && x ) //this function inserts for the right side as indicated by &&
    {
        auto & whichList = theLists[ myhash( x ) ]; // like above, using a C++11 feature, sets whichList equal to the list containing the hashed HashedObj x    
        if( find( begin( whichList ), end( whichList ), x ) != end( whichList ) ) //prevents duplicate insertions by going through list and seeing if x is already there.
            return false;
        if(whichList.size() > 0) //If this condition is true, we know there already exists an object at that point in the list so it MUST BE A COLLISION
        {
            cout << "Collision Occured. " << endl;
        }
        whichList.push_back( std::move( x ) ); //if there is no collision, simply add that object into the list 

        if( ++currentSize > theLists.size()) //if the currentSize of the list (iterated) is greater than the size of the list, we must rehash to make a new HashTable
        {
            rehash( ); //creates a new HashTable
            cout << "\n New Table Created" << endl;
        }
        return true;
    }

    bool remove( const HashedObj & x )
    {
        auto & whichList = theLists[ myhash( x ) ]; //using a C++11 feature, sets whichList equal to the list containing the hashed HashedObj x

        auto itr = find( begin( whichList ), end( whichList ), x ); // auto is used because the iterator can now be for any type and this returns iterator itr pointing to where x exists

        if( itr == end( whichList ) ) // if the iterator is equal to the end of the list, it will return false because we know the object isn't there to remove.
        {
            return false;
        }
        
        whichList.erase( itr ); // if the iterator itr finds the HashedObj x, then it removes it.
        --currentSize; // de-increments currentSize since an object has been removed.
        return true;
    }

    void print() //function used to print out the contents of the HashTable
    {
        for(int i = 0; i < theLists.size(); ++i) // first loops through the vector theLists
        {
            typename list<HashedObj>::iterator listItr; //then creates an iterator for the list to loop through list. NOTE: MUST INCLUDE "typename" to work!!!! Took me forever to figure this out.
            for(listItr = theLists[i].begin(); listItr != theLists[i].end(); ++listItr) //using the iterator, goes through the list
                cout << *listItr << endl; //since an iterator is merely a placeholder, this prints out the objects at that place at which the iterator currently is.
        }
    }

  private: 
     vector<list<HashedObj>> theLists; //declares a vector of lists of HashedObj --- pretty cool
     int currentSize;

     void rehash( ) //function to rehash 
     {
         vector<list<HashedObj>> oldLists = theLists; //makes a vector of lists of HashedObj's called oldLists and is set equal to previously declared theLists

         theLists.resize( nextPrime( 2 * theLists.size( ) ) ); // Creates a new table which is twice the size 
         for( auto & thisList : theLists ) // uses C++11 feature of using auto to iterate through the range in theLists
             thisList.clear( ); //clears the list

         currentSize = 0; // sets currentSize equal to 0
         for( auto & thisList : oldLists ) // uses C++11 feature of using auto to iterate through the range in oldLists
             for( auto & x : thisList ) // uses C++11 feature of using auto to iterate through the range in theLists
                 insert( std::move( x ) ); // Copies the old table into the new table
     }

    size_t myhash( const HashedObj & x ) const //this takes in an object, puts this object through the hash templates defined above and creates a hashed object named hf
    {
         static thehash<HashedObj> hf;
         return hf( x ) % theLists.size( ); //mods it by the table size to get appropriate hash
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


#endif