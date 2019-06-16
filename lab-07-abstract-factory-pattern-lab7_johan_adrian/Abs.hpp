#ifndef __ABS_HPP__
#define __ABS_HPP__
#include "Decorator.hpp"
#include <math.h>
using namespace std;

class Decorator;
class Abs: public Decorator {
	public:
		Abs(): Decorator(){}
	    Abs(Base* child){
            this->child = child;
        }
		double evaluate()
		{
			return abs(child->evaluate());
		}
        string stringify(){
            return child->stringify();
        }
};
#endif