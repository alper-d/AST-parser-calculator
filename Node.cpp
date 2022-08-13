/*
 * Node.cpp
 *
 *  Created on: Oct 6, 2021
 *      Author: alperd
 */

#include "Node.h"
#include <string>


Node::Node(){
	Node* left=nullptr;
	Node* right=nullptr;
	char value = '\0' ;
}

Node::Node(char c){
	Node* left = nullptr;
	Node* right = nullptr;
	char value = c ;
}
Node::Node(const Node* nodeToCopy){
    left = nodeToCopy->left;
    right = nodeToCopy->right;
    value = nodeToCopy->value;
}
Node::~Node(){

}

