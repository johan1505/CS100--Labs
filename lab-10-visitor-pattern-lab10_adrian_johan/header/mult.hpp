#ifndef __MULT_HPP__
#define __MULT_HPP__
#include "base.hpp"
#include <string>
#include "visitor.hpp"
#include "BinaryIterator.hpp"
using namespace std;

class BinaryIterator;
class Mult : public Base {
        private:
         Base* Base1;
         Base* Base2;

        public:
       // Constructor
               Mult(): Base1(0), Base2(0) {}
               Mult(Base* userBase1) : Base1(userBase1), Base2(0) {}
               Mult(Base* userBase1, Base* userBase2) : Base1(userBase1), Base2(userBase2) {}
   
               double evaluate(){
                   if(!Base1 && !Base2){ return 1.0; }
                   else if(Base1 && !Base2){ return Base1->evaluate(); }
                   else{ return Base1->evaluate() *  Base2->evaluate(); }
               }
        
               string stringify(){
                   if(!Base1 && !Base2) { return to_string(1.0) + " * " +  to_string(1.0); }
                   else if(Base1 && !Base2) { return Base1->stringify() + " * " + to_string(1.0); }
                   else { return Base1->stringify() +  " * " +  Base2->stringify(); }
 		}
		
		Base* get_left(){
	                if (Base1) {
        	                return Base1;
              		}
                	else {
                      	 	 return nullptr;
               		 }
       		 }
		Base* get_right(){
               		if(Base2){
                        	return Base2;
               		}
                	else {
                        	return nullptr;
                	}
        	}
		Iterator* create_iterator(){
        	        return new BinaryIterator(this);
	        }
		void accept(CountVisitor* v){
        	        v->visit_mult();
	        }
};                                                                                                                                         
#endif
