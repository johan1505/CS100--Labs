#ifndef __ABS_HPP__
#define __ABS_HPP__
#include "Decorator.hpp"
#include <math.h>
#include "UnaryIterator.hpp"
#include "visitor.hpp"
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
		Base* get_left(){
	                return this->child;
                }
                Base* get_right(){
                        return nullptr;
                }
		Iterator* create_iterator(){
			return new UnaryIterator(this);
		}
		void accept(CountVisitor* v){
			v->visit_abs();
		}
};
#endif
