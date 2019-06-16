#ifndef __MENU_HPP__
#define __MENU_HPP__
#include "../header/command.hpp"
#include <string>
#include <vector>

class Menu {
    private:
        int history_index; // Indexes which command was last executed, accounting for undo and redo functions
        std::vector<Command*> history; // Holds all the commands that have been executed until now

    public:
       Menu() {
            // Constructor which initializes the internal members
            // The vector shouldn't be needed to initialize
            //Should the index be initialized to 0 or -1?
            this->history_index = -1;
       }

       std::string execute() {
        // Returns the string converted evaluation of the current command
          if (this->history_index > -1){
		return std::to_string(this->history.at(this->history_index)->execute());
	  }
	  else {
		return "";
	  }
       }

       std::string stringify() {
        // Returns the stringified version of the current command
        // If the index is > -1 then we can access the element in the vector at pos index and return its stringify version, otherwise return an empty string
	 	return this->history_index > -1 ? this->history.at(this->history_index)->stringify() : "";
       }
       
       bool initialized() {
        // Returns if the history has an InitialCommand, which is necessary to start the calculation
       		return this->history_index > -1;
       }
      
       void add_command(Command* cmd) {
        // Adds a command to the history (does not execute it), this may require removal of some other commands depending on where history_index is
        	if(this->history_index == -1){ // if the index is -1 that means the vector is empty so just pushback the new command and set the index to 0
			history.push_back(cmd);
			this->history_index = 0;
		}
		else if (this->history_index == this->history.size() - 1){// if the index is the pos of the last element of the vector then pushback the new commands and increase the index
			history.push_back(cmd);
			++this->history_index;
		}
		else {  // else the index is not at the begging nor the back of the vector so it must be somewhere in the middle. This means we have to erase all Commands that are positined after the position of the index and then push_back the new command                                                                                
			this->history.erase(this->history.begin() +  this->history_index + 1, this->history.end());	
		      	this->history.push_back(cmd);
			++this->history_index;
		}
       }
   
       Command* get_command() {
       // Returns the command that the history_index is currently referring to
		return this->history_index > -1 ? history.at(this->history_index) : NULL;
       }
    
       void undo() {
        // Move back one command (does not execute it) if there is a command to undo
        	if (this->history_index > 0){ // If the index is greater than 0 then it is possible to undo otherwise is not
			--this->history_index;
		}
       }
 
       void redo() {
       // Moves forward one command (does not execute it) if there is a command to redo
       		if (this->history_index == -1 || this->history_index == this->history.size() - 1){ //If the index is -1 then there is nothing in history so it's not possible to redo, just return
			return;
		}
		else if (this->history_index < this->history.size() - 1){ // if the index is less than the size of the vector - 1 then it means that there are commands to redo
			++this->history_index;		
		}
       } 
};
#endif
