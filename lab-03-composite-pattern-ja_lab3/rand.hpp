#ifndef __RAND_HPP__
#define __RAND_HPP__

#include "base.hpp"
#include <string>
using namespace std;

class Rand: public  Base{

 private:
        double number;
 public:
        op() : number(rand() % 100) {}
        double evaluate(){ return number; }
        string stringify(){ return to_string(number); }
};

#endif 
