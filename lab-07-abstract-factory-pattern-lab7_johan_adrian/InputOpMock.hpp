
#include "base.hpp"
#include <string>
using namespace std;

class InputOpMock: public Base {
    public:
        InputOpMock() { };
        virtual double evaluate() { return 7.5; }
        virtual string stringify() { return "7.500000"; }
};
