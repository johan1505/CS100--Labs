#ifndef __DECORATOR_HPP__
#define __DECORATOR_HPP__
#include "Base.hpp"

class Base;
class Decorator: public Base{
    protected:
        Base* child;
    public:
        Decorator(): child(nullptr){}
        virtual double evaluate() = 0;
        virtual std::string stringify() = 0;
};
#endif