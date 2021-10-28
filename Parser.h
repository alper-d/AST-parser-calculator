/*
 * Parser.h
 *
 *  Created on: Oct 6, 2021
 *      Author: alperd
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <stack>
#include <string>
#include "Node.h"

class Parser{
	public:
		Parser();

		bool checkNumber (char c);
		bool checkPrecedence(char c);
		bool checkBinaryOperator(char c);
		Node* parse(std::string &expression);
		void printTree(Node* n);
        int executeOperation(int a, int b, char o);
        int calculate(Node* n);
		void assembleTree();
		void evaluateParanthesis();
	private:
		std::stack<char> operand_stack;
		std::stack<char> operator_stack;
		std::stack<Node> tree_stack;

};


#endif /* PARSER_H_ */
