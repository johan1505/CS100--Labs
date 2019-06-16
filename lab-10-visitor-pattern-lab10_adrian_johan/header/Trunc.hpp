#ifndef __TRUNC_HPP__
#define __TRUNC_HPP__
#include "Decorator.hpp"
#include <string>
#include "visitor.hpp"
#include "UnaryIterator.hpp"
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
		v->visit_trunc();
	}
};
#endif
