#ifndef __SCIRAND_HPP__
#define __SCIRAND_HPP__

#include "base.hpp"
#include "rand.hpp"
#include <string>
#include <sstream>
using namespace std;

class SciRand: public Rand{

 public:
        SciRand(): Rand(){}
        string stringify() {
                ostringstream os;
                os << scientific << number;
                return os.str();
        }
};

#endif
