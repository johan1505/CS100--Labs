#ifndef __CEILING_HPP__
#define __CEILING_HPP__
#include "Decorator.hpp"
#include "UnaryIterator.hpp"
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
