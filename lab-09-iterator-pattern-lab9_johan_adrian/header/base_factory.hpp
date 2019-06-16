#ifndef __BASE_FACTORY_HPP__
#define __BASE_FACTORY_HPP__

class BaseFactory {
    public:
        /* Constructor */
        BaseFactory() {}

        /* Pure Virtual Production Function */
        virtual op* createOp(double value) = 0;
        virtual Rand* createRand() = 0;
};

#endif //__BASE_FACTORY_HPP__
