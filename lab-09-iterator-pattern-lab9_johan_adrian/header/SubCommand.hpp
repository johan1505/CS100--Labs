#ifndef __SUB_COMMAND_HPP__
#define __SUB_COMMAND_HPP__
#include "command.hpp"
using namespace std;

class SubCommand : public Command {
    public:
        SubCommand(Command* c, Base* b){this->root = new Sub(c->get_root(), b);}
};

#endif
