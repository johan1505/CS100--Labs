#ifndef __TRUNC_HPP__
#define __TRUNC_HPP__
#include "Decorator.hpp"
#include <string>
using namespace std;

class Decorator;
class Trunc: public Decorator {
    public:
        Trunc(): Decorator(){}
        Trunc(Base* child){
            this->child = child;
        }
        double evaluate()
        {
            return child->evaluate();
        }
        string stringify(){
            return to_string(child->evaluate());
        }
};
#endif
