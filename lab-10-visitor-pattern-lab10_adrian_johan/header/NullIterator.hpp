#ifndef __NULL_ITERATOR_HPP__
#define __NULL_ITERATOR_HPP__

#include "Iterator.hpp"
using namespace std;

class NullIterator : public Iterator {

    public:
        NullIterator(Base* ptr) : Iterator(ptr) {  }
        
        void first() { }
        
        void next() { }
    
        bool is_done() { return true; }

        Base* current() { return nullptr; } 
};

#endif
