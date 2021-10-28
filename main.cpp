#include <iostream>
#include <iomanip>
#include "Parser.h"
#include "Node.h"
int main(int argc, char *argv[])
{
    Parser *p = new Parser();
    std::string s = "(4 + 5 * (7 - 3)) - 2";
    Node *n = p->parse(s);
    //p->printTree(n);
    std::cout<<"\n";
    std::cout<< p->calculate(n);
    return 0;
}
