//Main.cpp

/*

Grant McGovern 
Dr. Burg 
CSC 221 - Data Structures & Algorithms Pt. 1
30 April 2014 

*/

#include "Vertex.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <utility>

using namespace std;

void dijkstra(vector<Vertex*> & V, int startNum); //performs the shortest path algorithm 
void printPath(vector<Vertex*> & VP); //prints the path 
void insertionSort(vector<Vertex*> & a); //used to sort the Vector of pointers 

int main()
{
    //// LOCAL VARS ////
    int number_of_Vertices;
    int edges;
    int adjVtex;
    int weight;
    int startNum = 1; //sets the starting number equal to zero, this can be modified here.
    vector<Vertex*> vertices;
    Vertex * new_Vertex;
    ifstream infile;

	///// FILE I/O /////
	infile.open("graph.txt");
    cout << "Opening File..." << endl << endl;
    usleep(1000000);

    if(!infile)
    	cout << "System failed to open infile.";
    else
    	cout << "File successfully opened." << endl << endl;

    infile >> number_of_Vertices; //pulls off first line in the file
    cout << "Total Number of Vertices: " << number_of_Vertices << endl << endl;
    vertices.push_back(NULL); //prevents us from using 0th index
    /*
    Formatted to Write Out Initial Graph Reading as Such:

        V1: V2, 2;  V4, 1
        V2: V4, 3;  V5, 10
        V3: V1, 4;  V6, 5
        V4: V3, 2;  V5, 2;  V6, 8;  V7, 4
        V5: V7, 6
        V6: 
        V7: V6, 1
    
    */
    for(int i = 1; i < number_of_Vertices + 1; i++)
    {	
        new_Vertex = new Vertex(); //dynamically allocates a new Vertex() object each time
    	infile >> edges;
        cout << "\nV" << i << ": ";
        new_Vertex->setVertexNum(i);
        new_Vertex->setNumEdges(edges);
    	for(int n = 1; n <= edges; n++)
    	{
            infile >> adjVtex;
            cout << "V" << adjVtex;
        
    		infile >> weight;
            cout << ", " << weight << "; ";

    		new_Vertex->setAdjacentVertex(adjVtex, weight); //passes in edge and weight information 
    	}
    	vertices.push_back(new_Vertex);
    }
    cout << endl;
    dijkstra(vertices, startNum);
    infile.close();
}

void dijkstra(vector<Vertex*> & V, int startNum)
{
    int maxValue = 9999; //used in the table printing 

    vector<Vertex*> sortedVertices = V;
    sortedVertices[startNum]->setDV(0);
    sortedVertices[startNum]->setVisit(true);
    insertionSort(sortedVertices);

    while(sortedVertices.size() > 1)
    {
        insertionSort(sortedVertices);
        int end = sortedVertices.size()-1;
        Vertex * v = sortedVertices[end]; //creates a pointer to the Vertex object at the tail end of the sorted list
        v->setVisit(true);

        for(int i = 0; i < v->getNumEdges(); i++)
        {
            if(i == 0) 
            {
                cout << endl;
                cout << "Now at V" << v->getVertexNum() << "." << endl;
                cout << "V" << v->getVertexNum() << " has " << v->getNumEdges() << " edges." << endl << endl;
            }

            int dist = v->getAdjacentVertices()[i].getWeight(); // grabs the weight which is really the distance
            int adjV = v->getAdjacentVertices()[i].getAdjVertex(); // grabs the adjacent vertex

            cout << "Now at Adjacent Vertex V" << V[adjV]->getVertexNum() << endl;
            cout << "Distance from V" << V[adjV]->getVertexNum() << " to V" << v->getVertexNum() << " is " << dist << endl << endl;

            if(v->getDV() + dist < V[adjV]->getDV())
            {
                V[adjV]->setDV(v->getDV() + dist); // sets the distance
                cout << "Updating Total Distance of V" << V[adjV]->getVertexNum() << "..." << endl;
                cout << "Distance is now " << v->getDV() + dist << endl << endl;
                V[adjV]->setPV(v->getVertexNum()); //sets the PV to the vertice just visited
            }
        }
        cout << "Removed minimum: " << sortedVertices.back()->getVertexNum() << endl;
        cout << "Setting V" << sortedVertices.back()->getVertexNum() << " visited to TRUE \n" << endl;
        sortedVertices.back()->setVisit(true); //sets the visited column to true, to indicate the vertice has already been visited
        sortedVertices.pop_back(); //pops it off the back of the Vector
 
    ////////////////TABLE PRINTING//////////////////////
        cout<<"\n____________________________________\n";
        cout<< "\n\t\tTABLE\t\t" << endl;
        cout<<"____________________________________\n";
        cout<<"Name:  Visited:\tDV:\tPV:\n";

        for(int i = 1; i<V.size(); i++)
        {
            if(V[i]->getDV() > maxValue)
            {
                if(V[i]->getVisit() == true)
                {
                    cout << "V" << V[i]->getVertexNum();
                    cout << "\tT\tINF\tV";
                    cout << V[i]->getPV() <<endl;
                }
                else
                {
                    cout << "V" << V[i]->getVertexNum();
                    cout << "\tF\tINF\tV";
                    cout << V[i]->getPV() <<endl;
                }
            }
            else
            {
                if(V[i]->getVisit() == true)
                {
                    cout << "V"<< V[i]->getVertexNum();
                    cout << "\tT\t" << V[i]->getDV();
                    cout << "\tV" << V[i]->getPV() <<endl;
                }
                else
                {
                    cout << "V" << V[i]->getVertexNum();
                    cout << "\tF\t" << V[i]->getDV();
                    cout << "\tV" << V[i]->getPV() <<endl;
                }
            }
        }        
    //////////////////////////////////////////////////
    } 
    printPath(V); //prints out the shortest path as calculated in the algorithm
}

void printPath(vector<Vertex*> & V)
{
    cout << "\n\nShortest Path:\n\n"; 
    Vertex * vertexPtr;
    int currentspot;

    for(int k = 1; k < V.size(); k++)
    {
        vertexPtr = V[k];
        currentspot = k;
        cout << " V" << k << " path: ";
        if(currentspot == 1)
        {
            cout << " <-V1"; //takes care of the case of V1 since nothing "technically" leads to it. (path is 0)
        }
        else
        {
            while(currentspot != 1)
            {
                cout << " <-V" << vertexPtr->getPV();
                currentspot = vertexPtr->getPV();
                vertexPtr = V[currentspot];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void insertionSort(vector<Vertex*> & a ) //simple insertionSort method used from last program
{
    for( int p = 2; p < a.size( ); ++p )
    {
        Vertex * tmp = std::move( a[ p ] );

        int j;
        for( j = p; j > 1 && tmp->getDV() > a[ j - 1 ]->getDV(); --j ) //changed this to check if left side is GREATER than to return the list in descending, not ascending order.
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}

bool operator < (const Vertex & v1, const Vertex & v2)
{
    return v1.getDV() > v2.getDV(); //comparison overloading used to sort the Distances. (pays respect to pointers)
}
