//Edge.h

/*

Grant McGovern 
Dr. Burg 
CSC 221 - Data Structures & Algorithms Pt. 1
30 April 2014 

*/

#include <iostream>
#include <cstdlib>
#include <utility>

class Edge
{
	private:
		int adjVertex; 
		int weight;
	public:
		Edge()
		{
			adjVertex = 0;
			weight = 0;
		}
		void setWeight(int Weight)
		{
			weight = Weight;
		}
		int getWeight()
		{
			return weight;
		}
		void setAdjVertex(int adjacent)
		{
			adjVertex = adjacent;
		}
		int getAdjVertex()
		{
			return adjVertex;
		}
};