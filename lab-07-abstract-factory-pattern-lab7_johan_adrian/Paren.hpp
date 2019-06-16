#ifndef __PAREN_HPP__
#define __PAREN_HPP__
#include "Decorator.hpp"
#include <string>
using namespace std;

class Decorator;
class Paren: public Decorator {
    public:
        Paren(): Decorator(){}
        Paren(Base* child){
            this->child = child;
        }
        double evaluate()
        {
            return child->evaluate();
        }
        string stringify(){
            return "(" + (child->stringify()) + ")";
        }
};
#endif
