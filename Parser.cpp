/*
 * Parser.cpp
 *
 *  Created on: Oct 6, 2021
 *      Author: alperd
 */

#include "Parser.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <stdexcept>


Parser::Parser(){
	std::stack<char> operand_stack;
	std::stack<char> operator_stack;
	std::stack<Node*> tree_stack;
}

bool Parser::checkNumber (char c){
	return (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9');
}
bool Parser::checkPrecedence(char c){
	return (c == '*' || c == '/');
}
bool Parser::checkBinaryOperator(char c){
	return (c == '*' || c == '/'|| c == '+'|| c == '-');
}
void Parser::assembleTree(){
	Node* n;
	char temp;
	while (!operator_stack.empty()){
		n = new Node();
		temp = operand_stack.top();
		operand_stack.pop();

		if (temp == '#'){
			n->right = new Node(tree_stack.top());
			tree_stack.pop();
		}else if (checkNumber(temp)){
			n->right = new Node();
			n->right->value = temp;
		}
		n->value = operator_stack.top();
		operator_stack.pop();
		temp = operand_stack.top();
		operand_stack.pop();
		if (temp == '#'){
			n->left = new Node(tree_stack.top());
			tree_stack.pop();

		}else if (checkNumber(temp)){
			n->left = new Node();
			n->left->value = temp;
		}

		operand_stack.push('#');
		tree_stack.push(*n);
	}
}

void Parser::evaluateParanthesis(){
	Node* n;
	char temp;
	while (operator_stack.top() != '('){
		n = new Node();
		temp = operand_stack.top();
		operand_stack.pop();
		if (temp == '#'){
			n->right = new Node(tree_stack.top());
			tree_stack.pop();
		}else if (checkNumber(temp)){
			n->right = new Node();
			n->right->value = temp;
		}
		n->value = operator_stack.top();
		operator_stack.pop();
		temp = operand_stack.top();
		operand_stack.pop();
		if (temp == '#'){
			n->left = new Node(tree_stack.top());
			tree_stack.pop();
		}else if (checkNumber(temp)){
			n->left = new Node();
			n->left->value = temp;
		}
		operand_stack.push('#');
		tree_stack.push(*n);
	}
	operator_stack.top();
	operator_stack.pop();
}

Node* Parser::parse(std::string &s ){
		//std::string s = "1+1(3+3)";
		char temp;
		int lastInsertionType = 1;
		int parentheses = 0;
		Node* n;
		for (auto it = s.cbegin() ; it != s.cend(); ++it) {
			if(!checkNumber(*it) && !checkBinaryOperator(*it) && *it != '(' && *it != ')' && *it != ' '){
                throw std::invalid_argument( "" );
			}
			if (checkNumber(*it)){
                if(lastInsertionType == 0){
                    throw std::invalid_argument( "" );
                }else{
                    lastInsertionType = 0;
                }
                operand_stack.push(*it);
				while(!operator_stack.empty() && checkPrecedence(operator_stack.top())){
					n = new Node();
					n->right = new Node();
					n->right->value = operand_stack.top();
					operand_stack.pop();
					n->value = operator_stack.top();
                    operator_stack.pop();
					temp = operand_stack.top();
                    operand_stack.pop();
					if (temp == '#'){
						n->left = new Node(tree_stack.top());
                        tree_stack.pop();
					}else if (checkNumber(temp)){
						n->left = new Node();
						n->left->value = temp;
					}
					operand_stack.push('#');
					tree_stack.push(*n);
				}
			} else if (Parser::checkBinaryOperator(*it) || *it == '('){
				operator_stack.push(*it);
				if (lastInsertionType ==1){
                    if(*it != '('){
                        throw std::invalid_argument( "" );
                    }
                    else{
                        parentheses++;
                    }
				}
				else{
                    if(*it == '('){
                       throw std::invalid_argument( "" );
                    }
                    lastInsertionType = 1;
				}
			} else if(*it == ')') {
			    if (parentheses == 0){
                   throw std::invalid_argument( "" );
			    }
				evaluateParanthesis();
				parentheses--;
				while(!operator_stack.empty() && checkPrecedence(operator_stack.top())) {
					n = new Node();
					temp = operand_stack.top();
                    operand_stack.pop();
					if (temp == '#'){
						n->right = new Node(tree_stack.top());
                        tree_stack.pop();
					}else if (checkNumber(temp)){
						n->right = new Node(temp);
					}
					n->value = operator_stack.top();
                    operator_stack.pop();
					temp = operand_stack.top();
                    operand_stack.pop();
					if (temp == '#'){
						n->left = new Node(tree_stack.top());
                        tree_stack.pop();
					}else if (checkNumber(temp)){
						n->left = new Node();
						n->left->value = temp;
					}
					operand_stack.push('#');
					tree_stack.push(*n);
				}
			}
		}
        if(parentheses >0){
            throw std::invalid_argument( "" );
        }
		//buraya
		this->assembleTree();
		return &(tree_stack.top());

	}
void Parser::printTree(Node *n){
	if (!checkBinaryOperator(n->value)){
		std::cout<< n->value << "/";
		return;
	}
	Parser::printTree(n->left);
    std::cout<< n->value << "\\";
	Parser::printTree(n->right);
    //cout<< n->value;
	return;
}
int Parser::executeOperation(int operand1, int operand2, char o){

    if(o == '*'){
        return  operand1 * operand2;
    }else if(o == '/'){
        return  operand1 / operand2;
    }else if(o == '+'){
        return  operand1 + operand2;
    }else if(o == '-'){
        return  operand1 - operand2;
    }
}
int Parser::calculate(Node *n){
	if (checkNumber(n->value)){
        int result = (n->value) - '0';
		return result;
	}
	int o1 = Parser::calculate(n->left);
	int o2 = Parser::calculate(n->right);
	return executeOperation(o1, o2, n->value);

}
