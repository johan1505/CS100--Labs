#ifndef __SCIOP_HPP__
#define __SCIOP_HPP__

#include "base.hpp"
#include "op.hpp"
#include <string>
#include <sstream>
using namespace std;

class SciOp: public op{

 public:
	SciOp() : op(){}
        SciOp(double n) : op(n) {}
	string stringify() {
 		ostringstream os;
 		os << scientific << number;
 		return os.str();
	}
};

#endif
