#ifndef __RAND_HPP__
#define __RAND_HPP__

#include "base.hpp"
#include <string>
#include <stdlib.h>
using namespace std;
class Rand: public  Base{

 protected:
        double number;
 public:
        Rand() : number(rand() % 100) {}
        double evaluate(){ return number; }
        string stringify(){ return to_string(number); }
};
#endif
