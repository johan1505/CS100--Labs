#ifndef __PRECISION_RAND_HPP__
#define __PRECISION_RAND_HPP__
#include "base.hpp"
#include "rand.hpp"
#include <iomanip>
#include <sstream>


class Rand;
class PrecisionRand : public Rand{
	private:
		int precision;
       public:
                PrecisionRand(): Rand(){this->precision = 0;}
                PrecisionRand(int precision): Rand() {this->precision = precision;}
                string stringify(){
			ostringstream oss;
			oss << fixed << setprecision(precision) << number;
			return oss.str();
                }
};
#endif
