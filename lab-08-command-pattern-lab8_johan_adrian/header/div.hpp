#ifndef __DIV_HPP__
#define __DIV_HPP__
#include "base.hpp"
#include <string>
using namespace std;

class Div : public Base {
        private:
         Base* Base1;
         Base* Base2;

	public:
       // Constructor
         Div(): Base1(0), Base2(0) {}
         Div(Base* userBase1) : Base1(userBase1), Base2(0) {}
         Div(Base* userBase1, Base* userBase2) : Base1(userBase1), Base2(userBase2) {}

	 double evaluate(){
             if(!Base1 && !Base2){ 
		return 1.0;
	     } 
             else if(Base1 && !Base2){
		 return Base1->evaluate();
	     } 
             else {
		if(Base2->evaluate() == 0){
		   return -1; // -1 signifies an eror. User attempted to divide base1/0 which is not defined.
		}
		else {
		    return Base1->evaluate() /  Base2->evaluate();
	        }
            }
         }
	 
	 string stringify(){
             if(!Base1 && !Base2) {
		 return to_string(1.0) + " / " +  to_string(1.0);
	     }
             else if(Base1 && !Base2) {
		 return Base1->stringify() + " / " + to_string(1.0);
	     }
             else {
		if(Base2->evaluate() == 0) {
		   return "Undefined";
		}
		else {
		 return Base1->stringify() +  " / " +  Base2->stringify();
	        }
             }		
 	 }
};                                                                                                                                               
#endif
