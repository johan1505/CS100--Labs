#ifndef __OP_HPP__
#define __OP_HPP__

#include "base.hpp"
#include <string>
using namespace std;

class op: public  Base{

 protected:
        double number;
 public:
        op() : number(0) {}
        op(double n) : number(n) {}
        double evaluate(){ return number; }
        string stringify(){ return to_string(number); }
};

#endif 
