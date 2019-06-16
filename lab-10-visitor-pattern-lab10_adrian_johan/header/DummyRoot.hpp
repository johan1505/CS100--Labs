#ifndef __DUMMY_ROOT__
#define __DUMMY_ROOT__
#include "Decorator.hpp"
#include "visitor.hpp"
#include "UnaryIterator.hpp"
using namespace std;

class Decorator;
class DummyRoot : public Decorator {
	public:
		DummyRoot(): Decorator() {}
		DummyRoot(Base* child){ this->child = child; }
		double evaluate(){
			return child->evaluate();
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
		void accept(CountVisitor* v){}
};
#endif
