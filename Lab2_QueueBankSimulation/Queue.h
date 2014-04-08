/*
 * Queue2.h
 *
 *  Created on: Feb 16, 2014
 *      Author: grantmcgovern
 */

#ifndef QUEUE2_H_
#define QUEUE2_H_

#include <iostream>
#include "Teller.h"
#include "Queue.h"
#include "Customer.h"
#include "QueueNode.h"

template <typename T>
class Queue
{
private:
	QueueNode<T>*front;	// pointer to front of Queue
	QueueNode<T>*rear; // pointer to rear of Queue
	int count;	// current number of items in Queue										// maximum number of items in Queue
	Queue & operator=(const T & q) {return *this;};
	int QueueCount;

public:
	Queue()
	{
		rear = NULL;
		front = NULL;
		count = 0;
	}

	bool isempty() const
	{
		return front == NULL;
		//return count == 0;
	}
	int queuecount() const
	{
		return count;
	}
	bool enqueue(T &data)  	// add item to end
	{
		QueueNode<T> *add = new QueueNode<T>(data);
		count++;
		QueueCount++;
		if (front == NULL)
		{// if queue is empty,
			front = add;// place item at front
		}
		else
			rear->next = add;				// else place at rear
		rear = add;							// have rear point to new node
		return true;
	}

	bool dequeue(T &data)			// remove item from front
	{
		if(front == NULL)				// front node is empty, queue is empty
			return false;
		data = front->customer;					// set data to first item in queue
		count--;							// decrement item count
		QueueNode<T>* temp = front; 				// save location of first item
		front = front->next; 				// reset front to next item
		delete temp;
		// delete former first item
		if (count == 0)						// if the queue is now empty set rear to point to nothing
			rear = NULL;
		return true;
	}
	void remove(T &d)
	{
		if(front == NULL && rear == NULL)
		{
			//Nothing to put here.
		}
		else if(front == rear)
		{
			QueueNode<T> *temp = front;
			d = temp->customer;
			delete temp;
			front = NULL;
			rear = NULL;
		}
		else
		{
			QueueNode<T> *temp = front;
			d = temp->customer;
			front = front->next;
			delete temp;
		}
	}
	int getLength()
	{
		QueueNode<T> * temp = front;
		int length = 0;
		while(temp != NULL)
		{
			length++;
			temp=temp->next;
		}
		return length;
	}
};


#endif /* QUEUE_H_ */

