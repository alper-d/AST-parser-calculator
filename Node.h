/*
 * Node.h
 *
 *  Created on: Oct 6, 2021
 *      Author: alperd
 */

#ifndef NODE_H_
#define NODE_H_

class Node {

public:
	Node(char value);
	Node();
	Node(const Node* nodeToCopy);
	~Node();
	Node *left;
	Node *right;
	char value;
};



#endif /* NODE_H_ */
