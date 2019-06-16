#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__
#include "base.hpp"
using namespace std;

class Base;
class Iterator {
    protected:
        Base* self_ptr;

    public:
        Iterator(Base* ptr) { this->self_ptr = ptr; }

        /* Sets up the iterator to start at the beginning of traversal */
        virtual void first() = 0;
        
        /* Move onto the next element */
        virtual void next() = 0;
    
        /* Returns if you have finished iterating through all elements */
        virtual bool is_done() = 0;

        /* Return the element the iterator is currently at */
        virtual Base* current() = 0;
};

#endif
