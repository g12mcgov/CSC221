/*
 * BinaryTree.h
 *
 *  Created on: Feb 26, 2014
 *      Author: grantmcgovern
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_
////////////////Includes////////////////
#include <iostream>

using namespace std;

class Node
{
private:
	Node * left;
	Node * right;
	int key;
public:
	Node()
	{
		key =- 1;
		left = NULL;
		right = NULL;
	}
	void setElement(int theElement)
	{
		key = theElement;
	}
	void setLeft(Node * theLeft)
	{
		left = theLeft;
	}
	void setRight(Node * theRight)
	{
		right = theRight;
	}
	int element(){return key;};
	Node* Left(){return left;};
	Node* Right(){return right;};
};

//NOTE: The insert function has been overloaded to work with multiple agruments.
class Tree
{
public:
	Node* root;

	Tree()
	{
		root = NULL;
	}
	~Tree()
	{
		freeNode(root);
	} //delete function
	Node* Root()
	{
		return root;
	}
	void insert(int key)
	{
		if(root == NULL)
		{
			//cout << "Adding a root node ..." << key << endl;
			Node* n = new Node();
			n->setElement(key);
			root = n;
		}
		else
		{
			//cout << "Adding a root node ..." << key << endl;
			insert(key, root);
		}

	}
	void inOrder(Node* n)
	{
		if(n)
		{
			inOrder(n->Left());
			cout << n->element() << " ";
			inOrder(n->Right());
		}
	}
	void preOrder(Node* n)
	{
		if(n)
		{
			cout << n->element() << " ";
			preOrder(n->Left());
			preOrder(n->Right());
		}
	}
	void postOrder(Node* n)
	{
		if(n)
		{
			postOrder(n->Left());
			postOrder(n->Right());
			cout << n->element() << " ";
		}
	}
private:
	void insert(int key, Node* part)
	{
		if(key <= part->element())
		{
			if(part->Left() != NULL)
			{
				insert(key, part->Left());
			}
			else
			{
				Node* n = new Node();
				n->setElement(key);
				part->setLeft(n);
			}
		}
		else
		{
			if(part->Right() != NULL)
			{
				insert(key, part->Right());
			}
			else
			{
				Node* n = new Node();
				n->setElement(key);
				part->setRight(n);
			}
		}
	}
	void freeNode(Node* part)
	{
		if(part != NULL)
		{
			freeNode(part->Left());
			freeNode(part->Right());
			delete part;
		}
	}

};

#endif /* BINARYTREE_H_ */
