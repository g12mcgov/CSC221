/*

Grant McGovern
Dr. Burg 
CSC 221 
19 March 2014 

*/

/*********************** INCLUDES *******************************/

#include <iostream>

using namespace std;

class Symbol
{
private:
	int type;
	string data;
public:
	const string & getData() const
	{
		return data;
	}
	int getType() 
	{
		return type;
	}
	void setType(int Type)
	{	
		type = Type;
	}
	void setData(string Data)
	{
		data = Data;
	}
	bool operator== (const Symbol & rhs) const
	{
		return getData() == rhs.getData();
	}
	bool operator!= (const Symbol & rhs) const
	{
		return !(*this == rhs);
	}
	friend ostream & operator <<(ostream & os, const Symbol & symbol) // overloads the stream operator "<<" to print out the HashTable
	{
		int num = symbol.type;
		string name = symbol.data;
		os << name << " : " << num << "\n";
		return os;
	}
};
