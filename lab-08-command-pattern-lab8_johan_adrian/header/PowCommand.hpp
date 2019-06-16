#ifndef __POW_COMMAND_HPP__
#define __POW_COMMAND_HPP__
#include "command.hpp"
using namespace std;

class PowCommand : public Command {
    public:
        PowCommand(Command* c, Base* b){this->root = new Pow(c->get_root(), b);}
};

#endif
