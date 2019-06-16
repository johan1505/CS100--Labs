#ifndef __DOUBLE_FACTORY_HPP__
#define __DOUBLE_FACTORY_HPP__
#include "base_factory.hpp"
#include "op.hpp"
#include "rand.hpp"

class DoubleFactory: public BaseFactory {
        public:
                DoubleFactory(): BaseFactory(){}
                op* createOp(double value) {return new op(value);}
                Rand* createRand() {return new Rand();}
};
#endif
