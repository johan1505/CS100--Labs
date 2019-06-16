#include <iostream>
#include <vector>
#include <stdlib.h>

#include "../header/command.hpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;

// Helper function to check if a string input is an integer
bool is_integer(const string& s) {
    if(s.empty()) {
        return false ;
    }
    char* p;
    strtol(s.c_str(), &p, 10) ;
    return (*p == 0) ;
}

// Function to initialize the factory for the rest of the program
BaseFactory* generate_factory() {
    cout << "The following operators are available" << endl;
    cout << "\t\"d\": double" << endl;
    cout << "\t\"s\": scientific" << endl;
    cout << "\t\"p\": precision" << endl;
    cout << "Please enter one of the above choices: ";

    string input = "";
    getline(cin, input);

    if(input.substr(0,1) == "d") {
        return new DoubleFactory();
    }
    else if(input.substr(0,1) == "s") {
        return new SciFactory();
    } 
    else if(input.substr(0,1) == "p") {
        return new PrecisionFactory();
    }
    return nullptr;
}

// Function to parse creational inputs and generate the correct command
Command* parse_command_input(Command* lhs, BaseFactory* factory, string in) {
    // Cases where the value after the operator is a number and should create an Op
    if(is_integer(in.substr(2))) {
        int val = atoi((in.substr(2)).c_str());
        switch(in.substr(0,1).c_str()[0]) {
        case '+':
            return new AddCommand(lhs, factory->createOp(val));
            break;
        case '-':
            return new SubCommand(lhs, factory->createOp(val));
            break;
        case '*':
            return new MultCommand(lhs, factory->createOp(val));
            break;
        case '/':
            return new DivCommand(lhs, factory->createOp(val));
            break;
        case '^':
            return new PowCommand(lhs, factory->createOp(val));
            break;
        default:
            return nullptr;
        }
    }
    // Cases where the value after the operator is a question mark and should create a Rand
    else if(in.substr(2,1) == "?") {
        switch(in.substr(0,1).c_str()[0]) {
        case '+':
            return new AddCommand(lhs, factory->createRand());
            break;
        case '-':
            return new SubCommand(lhs, factory->createRand());
            break;
        case '*':
            return new MultCommand(lhs, factory->createRand());
            break;
        case '/':
            return new DivCommand(lhs, factory->createRand());
            break;
        case '^':
            return new PowCommand(lhs, factory->createRand());
            break;
        default:
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

int main() {

    // Initialize the menu class to keep track of operations
    Menu* menu = new Menu();
    string input = "";

    // Initialize the factory so we can create the same type of Op/Rand objects throughout the program
    BaseFactory* factory = generate_factory();
    if(factory == nullptr) {
        cout << "Invalid choice, exiting..." << endl;
        input = "exit";
    }

    while(input != "exit") {
        cout << "Choose a Menu Command: ";
        getline(cin, input);

        if(input == "exit") {
            cout << "Exiting..." << endl;
            break;
        }
        else if(input == "redo") {
            cout << "Redoing command, current command is..." << endl;
            menu->redo();
        }
        else if(input == "undo") {
            cout << "Undoing command, current command is..." << endl;
            menu->undo();
        } else {
            // Calculations must start with a single number, so the first entry is a special case which
            // creates an initial command which is essentially a composite tree with a single node
            if(!menu->initialized()) {
                if(is_integer(input)) {
                    menu->add_command(new InitialCommand(factory->createOp(atoi(input.c_str()))));
                }
                else if(input.substr(0,1) == "?") {
                    menu->add_command(new InitialCommand(factory->createRand()));
                } else {
                    cout << "Invalid Command" << endl;
                }
            // Once the system has been initialized, the rest of the entires should start with an operator
            // and be followed by an operand (seperated by a space), which adds a new operator and operand
            // on top of the tree that has been created previously
            } else {
                Command* cmd = parse_command_input(menu->get_command(), factory, input);
                if(cmd == nullptr) {
                    cout << "Invalid commmand, current command is..." << endl;
                } else {
                    menu->add_command(cmd);
                }
            }
        }

        // After every command is entered we want to print what the most recent good command contains, or
        // print a special "Empty" message when the user call undo enough times to go back to the beginning
        // of the program or when invalid initial commands are entered
        if(!menu->initialized()) {
            cout << "Empty" << endl;
        } else {
            cout << menu->stringify() << " = " << menu->execute() << endl;
        }
    }
    delete menu;
    delete factory;
};

