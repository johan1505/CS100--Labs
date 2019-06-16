#ifndef __INITIAL_COMMAND_HPP__
#define __INITIAL_COMMAND_HPP__
#include "command.hpp"
using namespace std;

class InitialCommand : public Command {
    public:
	InitialCommand(Base* b){this->root = b;}
};

#endif
