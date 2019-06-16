#ifndef __CEILING_HPP__
#define __CEILING_HPP__
#include "Decorator.hpp"
#include <math.h>

using namespace std;
class Decorator;
class Ceiling: public Decorator {
	public:
		Ceiling(): Decorator(){}
		Ceiling(Base* child){
            this->child = child;
        }
		double evaluate()
		{
			return ceil(child->evaluate());
		}
        string stringify(){
            return child->stringify();
        }
};
#endif