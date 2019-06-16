#ifndef __SCIENTIFIC_FACTORY_HPP__
#define __SCIENTIFIC_FACTORY_HPP__
#include "base_factory.hpp"
#include "SciOp.hpp"
#include "SciRand.hpp"

class ScientificFactory: public BaseFactory {
        public:
                ScientificFactory(): BaseFactory(){}
                op* createOp(double value) {return new SciOp(value);}
                Rand* createRand() {return new SciRand();}
};
#endif
