/*
 * Driver.cpp

 *
 *  Created on: Feb 16, 2014
 *      Author: grantmcgovern
 *
 *
 * This program simulates a bank with customers walking in for service and seeing tellers.
 * This program implements a classic Queue style system.
 *
 * DISCLAIMER: MUST BE RUN ON TERMINAL like below.
 *
 * 	- HOW TO RUN: 

 		g++ Driver.cpp -o temp

 		./temp 0.5 10 15 50
 *
 *
 *
 */

////////////////////////////////////////////////////////////////////
///Includes///
////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <cstdlib>
#include "time.h"
#include "Queue.h"
#include "Customer.h"
#include "QueueNode.h"
#include "Teller.h"

using namespace std;

int main(int argc, char *argv[])
{

	srand(time(NULL)); //seeds the random time generator

	if(argc != 5)
	{
		cout << "You must enter at least 5 command line arguments " << endl;
		exit(1);
	}

	/******************Command Line Args-Variables***************************/
	double p = atof(argv[1]);
	int numTellers = atoi(argv[2]); //number of the tellers (M)
	int maxService = atoi(argv[3]);
	int maxClock = atoi(argv[4]); //simulation time (N)

	/******************Local Variables***************************/
	int numberOfCustomers = 0;
	int serv;
	int randProb;
	int totalWait;
	double AverageWaitTime;
	int customerWillBeFinished;
	double maxQLength;
	int counter;
	double AverageQueueLength;
	int wait;
	int individualWaitTime;
	int OtherThanK;
	int a = 10000;

	//Displays to user to double checks to make sure you entered in the arguments correctly
	cout << "------------------------------------------------------------" << endl;
	cout << "These are the arguments that you gave the program: " << endl;
	cout << endl;
	cout << "The p value is: " << p << endl;
	cout << "The number of tellers: " << numTellers << endl;
	cout << "The max service time is: " << maxService << endl;
	cout << "The max clock is: " << maxClock << endl;
	cout << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "\n";

	/******************Declaration of Queue & Vector***************************/
	Queue<Customer> line;
	vector<Teller> teller(numTellers);


	//loop to go through entire clock until the maxClock is reached
	//for(int k = 1; k < maxClock; k++)
	int k = 1;
	while(k != maxClock)
	{
		OtherThanK = k;
		randProb = ((rand() % 100) + 1); //generates a random number seeded with system time
		if(randProb < p*100)
		{
				serv = ((rand() % maxService) + 1); //generates a random number seeded with system time
				Customer customer(OtherThanK, serv); //passes in current time and service time (randomizeD)
				line.enqueue(customer); //pushes a customer onto the Queue.
				cout << "Customer arriving in queue at time: " << OtherThanK << endl;
		}
		customerWillBeFinished = serv + OtherThanK + 1;
		for(int i = 0; i < numTellers; i++)
		{
			if(teller[i].isFree() && (!line.isempty())) //checks to see if a teller is empty
			{
				cout << "Teller " << i << " is now free." << endl;
				Customer frontCustomer; //declares a customer called frontCustomer. This is the customer who is at the front of the Queue.
				line.dequeue(frontCustomer); //pulls off a customer from the Queue.
				wait = OtherThanK - frontCustomer.getArrivalTime();
				numberOfCustomers++; //increases by 1 each time through to keep tracking of the # of Customers.
				totalWait = totalWait + wait;
				cout << "Customer going to teller " << i << " at time " << frontCustomer.getArrivalTime() << endl; //retrieves arrival time
				cout << "This customer had to wait in line for " << wait << " minutes." << endl; //labs() is a function used to determine absolute value
				cout << "This customer will require " << serv << " minutes of service" << endl;
				teller[i].addCustomer(frontCustomer);
				line.remove(frontCustomer); //once cycled through, removes the customer from the Queue.
			}

		}
		cout << endl;
		cout << "Time is: "<< k << endl;
		cout << " \n Number of customers: " << numberOfCustomers << " " << "Total wait so far: " << std::labs(totalWait) << endl; //labs() is a function used to determine absolute value
	k++;
	}
	AverageWaitTime = totalWait/numberOfCustomers;
	cout << "Average wait time is: " << AverageWaitTime << endl;
	maxQLength = line.getLength();
	cout << "The max Queue length is " << maxQLength << endl;
	AverageQueueLength = maxQLength/OtherThanK;
	cout << "The Average Queue Length is " << AverageQueueLength*1000;
}



