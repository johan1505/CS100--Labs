#ifndef __CEILING_HPP__
#define __CEILING_HPP__
#include "Decorator.hpp"
#include <math.h>

using namespace std;
class Decorator;
class Ceil: public Decorator {
	public:
		Ceil(): Decorator(){}
		Ceil(Base* child){
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
