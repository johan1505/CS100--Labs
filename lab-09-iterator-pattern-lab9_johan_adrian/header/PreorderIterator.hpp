#ifndef __PREORDER_ITERATOR__
#define __PREORDER_ITERATOR__
#include <stack>
#include "Iterator.hpp"
class PreorderIterator: public Iterator {
     private:
	stack<Iterator*> s;   
     public:
	PreorderIterator(Base* ptr) : Iterator(ptr) {}
     	void first() {
		//First empty the stack
		while (!this->s.empty()){
			s.pop();
		}
		//Second Create an iterator for the Base* that was passed during construction
		Iterator* i = this->self_ptr->create_iterator();
		//Initialize the iterator and push it onto the stack
		i->first();
		this->s.push(i);
	}
	

	void next() {
    	// Create an iterator for the current() of the iterator on the top of the stack
   		Iterator* i = this->s.top()->current()->create_iterator();
         // Initialize the iterator and push it onto the stack. 
	    	if (i){	
			i->first();
			this->s.push(i);
		}	
    	//     As long as the top iterator on the stack is_done, pop it off the stack and then advance whatever iterator is now on top of the stack
    		while (this->s.size() > 0 && this->s.top()->is_done()){
			this->s.pop();
			if (!s.empty()){
				this->s.top()->next();
				//this->s.top()->first();
			}
		}
    	}
	
	bool is_done(){
		return this->s.empty();
	}
	Base* current(){
		if (this->s.size() > 0){
			return this->s.top()->current();
		}
		else {
			return nullptr;
		}
	}
};
#endif
