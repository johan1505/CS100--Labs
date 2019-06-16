#ifndef __OP_HPP__
#define __OP_HPP__
#include "base.hpp"
#include <string>
#include "NullIterator.hpp"
using namespace std;

class op: public  Base{

 protected:
        double number;
 public:
        op() : number(0) {}
        op(double n) : number(n) {}
        double evaluate(){ return number; }
        string stringify(){ return to_string(number); }
	Base* get_left() { return nullptr; }
	Base* get_right() { return nullptr; }
	Iterator* create_iterator(){
                return new NullIterator(this);
        }
};

#endif 
