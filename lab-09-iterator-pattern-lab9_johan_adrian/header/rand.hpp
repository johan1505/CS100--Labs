#ifndef __RAND_HPP__
#define __RAND_HPP__
#include "base.hpp"
#include <string>
#include <stdlib.h>
#include "NullIterator.hpp"
using namespace std;

class Rand: public  Base{
 protected:
        double number;
 public:
        Rand() : number(rand() % 100) {}
        double evaluate(){ return number; }
        string stringify(){ return to_string(number);}; 
	Base* get_left(){ return nullptr; }
        Base* get_right(){ return nullptr; }
	Iterator* create_iterator(){
                return new NullIterator(this);
        }
};
#endif
