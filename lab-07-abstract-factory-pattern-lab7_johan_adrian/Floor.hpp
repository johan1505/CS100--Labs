#ifndef __FLOOR_HPP__
#define __FLOOR_HPP__
#include "Decorator.hpp"
#include <math.h>
using namespace std;

class Decorator;
class Floor: public Decorator {
	public:
		Floor(): Decorator(){}
		Floor(Base* child){
            this->child = child;
        }
		double evaluate()
		{
			return floor(child->evaluate());
		}
        string stringify(){
            return child->stringify();
        }
};
#endif
