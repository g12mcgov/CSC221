/*
 * Customer.h
 *
 *  Created on: Feb 16, 2014
 *      Author: grantmcgovern
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <iostream>
#include "QueueNode.h"
#include "Queue.h"
#include "Teller.h"
#include <cstdlib>

using namespace std;

class Customer
{

public:
	int serviceTime;
	int arrivalTime;
	Customer()
	{
		serviceTime = 0;
		arrivalTime = 0;
	}

	Customer(int arrival, int maxService)
	{
		arrivalTime = arrival;
		serviceTime = maxService;
	}

	int getServiceTime()
	{
		return serviceTime;
	}
	bool isDone()
	{
		serviceTime--;
		return serviceTime <= 0;
	}

	int getArrivalTime()
	{
		return arrivalTime;
	}
	void MinutePasses()
	{
		serviceTime--;
	}
};

#endif /* CUSTOMER_H_ */
