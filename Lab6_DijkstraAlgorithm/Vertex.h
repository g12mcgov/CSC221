//Vertex.h

/*

Grant McGovern 
Dr. Burg 
CSC 221 - Data Structures & Algorithms Pt. 1
30 April 2014 

*/

#include "Edge.h"
#include <vector>
#include <climits>
#include <fstream>
#include <utility>

using namespace std;

class Vertex
{
	private:
		int vertex_number; 
		bool visited;
		vector<Edge> adjacentVertices; 
		int dv; 
		int previousVertice; 
		Vertex * vertex;
		int numEdges;
	public:
		Vertex()
		{
			dv = INT_MAX;
			visited = false;
		}
		
		/* OVERLOADING */
		friend bool operator < (const Vertex & v1, const Vertex & v2);
		friend ostream & operator <<(ostream & outstream, Vertex *vtex) //overloaded to work with Vertex pointers
		{
			outstream << vtex->getVertexNum() << endl;
			outstream << vtex->getVisit() << endl;
			vector<Edge> edges = vtex->getAdjacentVertices();
			for(int i = 0; i < edges.size(); i++)
			{
				outstream << edges[i].getAdjVertex() << endl;
				outstream << edges[i].getWeight() << endl;
			}
			return outstream;
		}
		///////////////////
		void setVisit(bool Known)
		{
			visited = Known;
		}
		bool getVisit()
		{
			return visited;
		}
		void setVertexNum(int VertexNum)
		{
			vertex_number = VertexNum;
		}
		int getVertexNum()
		{
			return vertex_number;
		}
		int getDV() const 
		{
			return dv;
		}
		int setDV(int Dv)
		{
			dv = Dv;
		}
		int setNumEdges(int NumEDGES)
		{
			numEdges = NumEDGES;
		}
		int getNumEdges()
		{
			return numEdges;
		}
		int setPV(int Pv)
		{
			previousVertice = Pv;
		}
		int getPV()
		{
			return previousVertice;
		}
		vector<Edge> & getAdjacentVertices()
		{
			return adjacentVertices;
		}
		void setAdjacentVertex(int AdjacentVertex, int Weight) //sets the adjacent vertex
		{
			Edge edge;
			edge.setWeight(Weight);
			edge.setAdjVertex(AdjacentVertex);
			adjacentVertices.push_back(edge);
		}
};