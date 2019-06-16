#ifndef __MULT_COMMAND_HPP__
#define __MULT_COMMAND_HPP__
#include "command.hpp"
using namespace std;

class MultCommand : public Command {
    public:
        MultCommand(Command* c, Base* b){this->root = new Mult(c->get_root(), b);}
};

#endif
