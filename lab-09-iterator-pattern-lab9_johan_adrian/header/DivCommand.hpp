#ifndef __DIV_COMMAND_HPP__
#define __DIV_COMMAND_HPP__
#include "command.hpp"
using namespace std;

class DivCommand : public Command {
    public:
        DivCommand(Command* c, Base* b){this->root = new Div(c->get_root(), b);}
};

#endif
