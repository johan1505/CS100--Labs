#ifndef __PRECISION_FACTORY_HPP__
#define __PRECISION_FACTORY_HPP__
#include "base_factory.hpp"
#include "PrecisionOp.hpp"
#include "PrecisionRand.hpp"

class PrecisionFactory: public BaseFactory {
        private:
                int precision;
        public:
                PrecisionFactory(): BaseFactory(){this->precision = 0;}
                PrecisionFactory(int precision) : BaseFactory() {this->precision = precision;}
                op* createOp(double value) {return new PrecisionOp(value, precision);}
                Rand* createRand() {return new PrecisionRand(precision);}
};
#endif

