Grant McGovern 
Dr. Burg 
CSC 221 - Data Structures & Algorithms Pt. 1
30 April 2014 

~ Lab 6 - Dijkstra's Algorithm ~

PURPOSE:

	- The purpose of this lab is to implement Dijkstra's algorithm in an effort to solve the shortest path (or commonly known as the Traveling Salesman problem) for a given graph. This particular graph (as provided by Dr. Burg) is a graph containing 7 vertices (the first number read in from the textfile). 

HOW-IT-WORKS:

	- The program first reads in the graph information from an external text file and constructs the graph via vector of pointers to Vertex objects (vertices). It then applies Dijkstra's algorithm to this vector, and prints out a table indicating the visited vertices, the distance between them, and the previous vertices. The program then prints out the shortest path. 

TO-RUN:

	Using G++:
	
		(Make sure graph.txt is in the same directory)

		On UNIX Based Machine (Mac OSX / Linux) Terminal or Console:


			>> g++ -std=c++0x Driver.cpp -o temp
			>> ./temp


		NOTE: the "-std=c++0x" is to indicate C++11 features are enabled. 
		NOTE: WE NEED THIS SINCE WE ARE USING STD::MOVE OPERATIONS (which are a C++11 feature)
