#ifndef __PRECISION_OP_HPP__
#define __PRECISION_OP_HPP__
#include "base.hpp"
#include "op.hpp"
#include <iomanip>
#include <sstream>
#include <stdlib.h>
class op;
class PrecisionOp : public op{
	private:
		int precision;
       public:
                PrecisionOp(): op(){this->precision = 0;}
                PrecisionOp(double number, int precision): op(number) {this->precision = precision;}
                string stringify(){
			ostringstream oss;
			oss << fixed << setprecision(precision) << number;
			return oss.str();
                }
};
#endif

