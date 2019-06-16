#ifndef __ADD_COMMAND_HPP__
#define __ADD_COMMAND_HPP__
#include "command.hpp"
using namespace std;

class AddCommand : public Command {
    public:
        AddCommand(Command* c, Base* b){this->root = new Add(c->get_root(), b);}
};

#endif
