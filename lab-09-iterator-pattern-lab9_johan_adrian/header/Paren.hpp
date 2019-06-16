#ifndef __PAREN_HPP__
#define __PAREN_HPP__
#include "Decorator.hpp"
#include "UnaryIterator.hpp"
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
	Base* get_left(){
                   return this->child;
        }
        Base* get_right(){
                    return nullptr;
        }
	Iterator* create_iterator(){
                        return new UnaryIterator(this); 
        }
};
#endif
