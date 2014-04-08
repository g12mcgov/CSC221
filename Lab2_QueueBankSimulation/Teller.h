/*
 * Teller.h
 *
 *  Created on: Feb 16, 2014
 *      Author: grantmcgovern
 */

#ifndef TELLER_H_
#define TELLER_H_

#include <iostream>
#include "Customer.h"
#include "QueueNode.h"
#include "Queue.h"

using namespace std;

class Teller
{
private:
	//bool isOccupied;
	Customer customer;
protected:
	bool free;
public:
	Teller()
	{
		//isOccupied = false;
		free = true;
	}
	bool isFree()
	{
		//return free; - > B C
		if(!free)
		{
			customer.serviceTime--;
			if(customer.serviceTime == 0)
			{
				free = true;
				return true;
			}
			else return false;
		}
		{
			return true;
		}


	}

	void addCustomer(Customer C)
	{
		customer = C;
		free = false;
	}
	void CustMinutePasses()
	{
		if(!free)
		{
			customer.MinutePasses();
		}
	}
	Customer & getCustomer()
	{
		return customer;
	}
	void setAvailability(bool b)
	{
		free = b;
	}
	/*
	void setAvailability(bool b)
	{
		free = b;
	}
	*/
};



#endif /* TELLER_H_ */
