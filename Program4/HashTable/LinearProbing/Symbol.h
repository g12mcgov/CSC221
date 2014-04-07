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
	friend ostream & operator <<(ostream & outstream, Symbol & symbol) //overloaded to print out the the HashTable
	{
		int num = symbol.getType();
		string name = symbol.getData();
		outstream << name << " : " << num << endl;
		return outstream;
	}
};
