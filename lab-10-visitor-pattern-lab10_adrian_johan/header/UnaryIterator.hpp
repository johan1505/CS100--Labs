#ifndef __UNARY_ITERATOR_HPP__
#define __UNARY_ITERATOR_HPP__

#include "Iterator.hpp"
using namespace std;


class UnaryIterator : public Iterator {
    protected:
    	Base* parent;

    public:
        UnaryIterator(Base* ptr) : Iterator(ptr){this->parent = ptr;}
        
        void first() { 
            self_ptr = self_ptr->get_left(); 
        }
        
        void next() {
	    if (self_ptr == parent){
		self_ptr = parent->get_left();
	    }
	    if(self_ptr == parent->get_left()) {
		self_ptr = nullptr;
	    }
	}
    
        bool is_done() {
            if (self_ptr) { return false;}
            else { return true; }
        }

        Base* current() { return self_ptr; } 
};

#endif
