#include "base.hpp"
#include <string>
#include "NullIterator.hpp"
#include "visitor.hpp"
using namespace std;

class InputOpMock: public Base {
    public:
        InputOpMock() { };
        virtual double evaluate() { return 7.5; }
        virtual string stringify() { return "7.500000"; }
	Base* get_left(){ return nullptr; }
        Base* get_right(){ return nullptr;}
	Iterator* create_iterator(){
                return new NullIterator(this);
        }
	void accept(CountVisitor* v){
		v->visit_op();
	}
};
