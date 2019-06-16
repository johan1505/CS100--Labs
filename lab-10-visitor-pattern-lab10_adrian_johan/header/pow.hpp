#ifndef __POW_HPP__
#define __POW_HPP__
#include "base.hpp"
#include <math.h>
#include "BinaryIterator.hpp"
#include "visitor.hpp"
using namespace std;

class BinaryIterator;
class Pow : public Base {
        private:
         Base* Base1;
         Base* Base2;
        public:
        //Constructor
         Pow(Base* userBase1, Base* userBase2) {
                this->Base1 = userBase1;
                this->Base2 = userBase2;
        }

         Pow(Base* userBase1) {
                this->Base1 = userBase1;
                this->Base2 = 0;
        }

         Pow() {
                this->Base1 = 0;
                this->Base2 = 0;
        }

        //Functions
        double evaluate() {
                if (Base1 && Base2) { return pow(Base1->evaluate(), Base2->evaluate());}
                else if (Base1 && !Base2) { return Base1->evaluate(); }
                else { return 1.0; } //zero to the zero is one
        }
        string stringify() {
                if (Base1 && Base2) { return Base1->stringify() +  " ** " +  Base2->stringify();}
                else if (Base1 && !Base2) { return Base1->stringify() + " ** " + to_string(1.0);}
                else { return to_string(0.0) + " ** " + to_string(0.0); }
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
                v->visit_pow();
        }
};

#endif
