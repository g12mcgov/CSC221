Grant McGovern 
Dr. Burg 
CSC 221 
April 8, 2014

This is simply a program used to represent the different times/computational complexity of insertion algorithms into a heap.

It works by taking in a vector of random numbers between 1 and 100 (seeded from system clock) and then inserts them into the heap via the following methods: 
	
	- insertionSort()
	- heapSort()
	- mergeSort()
	- quickSort()

Each of these methods takes in the entire vector, rather than simply the elements. It then sorts the vector and returns the time elapsed. 

For best/most obvious results, choose a vector size of greater than 1,000. 

HOW TO RUN:

        On UNIX Based Machine (Mac OSX / Linux) Terminal or Console:


                >> g++ -std=c++0x Driver.cpp -o temp
                >> ./temp


        NOTE: the "-std=c++0x" is to indicate C++11 features 
