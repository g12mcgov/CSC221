/*
 * QueueNode.h
 *
 *  Created on: Feb 16, 2014
 *      Author: grantmcgovern
 */

#ifndef QUEUENODE_H_
#define QUEUENODE_H_

#include <iostream>
#include "Queue.h"
#include "Customer.h"

using namespace std;

class Customer;
template<class T>
class Queue;

template<class T>
class QueueNode
{
private:
	T customer;
	QueueNode *next;

public:
	QueueNode(const T &C)
	{
		customer = C;
		next = NULL;
	}
	friend class Queue<T>;
	friend class Customer;
};

#endif /* QUEUENODE_H_ */
