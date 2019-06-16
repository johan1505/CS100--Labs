#ifndef __FLOOR_HPP__
#define __FLOOR_HPP__
#include "Decorator.hpp"
#include <math.h>
#include "visitor.hpp"
#include "UnaryIterator.hpp"
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
                        v->visit_floor();
        }
};
#endif
