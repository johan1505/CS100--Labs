# Command Pattern

> Author: Brian Crites ([@brrcrites](https://github.com/brrcrites))

**You *must* work in a group of two for this lab**

In this lab we will introduce a new main function which will utilize a number of different classes that you have created in previous labs to build a (very) simple calculator application. Note that this lab does not utilize every system that you have developed, but you will likely see ways in which they could be utilized. This calculator will allow the user to do running total calculations (similar to a simple phone calculator) with the additional ability for the user to undo and redo commands that they have input. We will accomplish this by leveraging the command pattern to create a history that we can write to, traverse, and overwrite as necessary, and which will save the state of our calculation every time a new operation is requested.

## The Calculator

For this lab you have been provided with a main function as well as some helper functions in `calculator.cpp` that will parse the user input and execute functions that you have either implemented in previous labs or you will create in this lab. Working with existing code that you have not developed yourself is an essential skill you will need to contribute to real-world codebases, so you should take some time to try and fully undrstand what this code is doing before moving on with this lab. This calculator implements the following commands:

* Exit the program
  * Typing "exit" as a command will exit the program
* Undo a command
  * Typing "undo" will go back to the last command, and can be called until there are no more commands to undo
* Redo a command
  * Typing "redo" will go forward to the next command, and can be called until there are no more commands to redo
* Perform a Calculation
  * Perform a running calculation. This first calculation must start with a single number (ex: `3`) or a random value represented with a question mark (ex: `?`), and after a single number has been input should take an operator followed by a number (ex: `+ 10`) or followed by a question mark (ex: `^ ?`). Note that a space is required between the operator and the operand.

Additionally, it has an initial function which requests that the user specifies what category of operators the user wants to work in and creates the matching factory for use in the rest of the program.

## The Menu Class

The menu class is used as an interface between user input and the commands that are created for keeping track of the calculation. It functions similar to the history system described in class and contains two internal members `vector<Command*> history`, which is used to hold all the commands that have bene run, and `int history_index`, which is used to keep track of our position in history. The menu class must have the following function signature and implement the following functionality to function correctly with the given menu.

```c++
class Menu {
    private:
        int history_index; // Indexes which command was last executed, accounting for undo and redo functions
        std::vector<Command*> history; // Holds all the commands that have been executed until now

    public:
        Menu() {
            // Constructor which initializes the internal members
        }

        std::string execute() {
            // Returns the string converted evaluation of the current command
        }

        std::string stringify() {
            // Returns the stringified version of the current command
        }

        bool initialized() {
            // Returns if the history has an InitialCommand, which is necessary to start the calculation
        }

        void add_command(Command* cmd) {
            // Adds a command to the history (does not execute it), this may require removal of some other commands depending on where history_index is
        }

        Command* get_command() {
            // Returns the command that the history_index is currently referring to
        }

        void undo() {
            // Move back one command (does not execute it) if there is a command to undo
        }

        void redo() {
            // Moves forward one command (does not execute it) if there is a command to redo
        }
};
```

## The Command Class

You will also have to create command classes, which are capable of encapsulating the current state of a calculation. Since we are doing a running calculation, you do not need to worry about accounting for precedence. Instead you can guarantee that the composite tree from the last command will be one child of the new command, and the new value input will be the other child (with the parent of both being determined by the operator that is input by the user).

This means that you will be required to create six concrete command classes (the `Command` base class is provided). You should create each of these classes independently and thoroughly test each one before moving on. It is also a good idea to break each command and its tests into a single commit. You will need to create the following commands:

* `InitialCommand`
* `AddCommand`
* `SubCommand`
* `MultCommand`
* `DivCommand`
* `PowCommand`

The base `Command` class implement three functions for accessing the information in the composite tree represented by the private `Base*` memeber. Because all of the command subclasses will access the same data, these functions are defined in the base class and non-virtual as they do not need to be overridden. Each command subclass is in charge of performing one modification to the composite tree that it represents. The `InitialCommand` class is a special casethat is only created at the beginning of the calculation and represents the lowest `Op` or `Rand` node in the system (depending on what object is passed in). The rest of the classes represent the addition of an operator and an operand (either `Op` or `Rand`) on top of the existing tree, which is represented by an existing command (which is retrieved throught the `Menu` classes `get_command()` function).

* The `InitialCommand` class has the constructor signature `InitialCommand(Base*)`
* The rest of the concrete commmands have the constructor signature `AddCommand(Command*, Base*)`, with the `Add` replaced with the specific class

Since these concrete commands are relatively simple constructional objects that represent the addition of either an operand or an operator and an operand to the calculation depending on what the user inputs, they don't need to override anything except their constructors. Note that one of the first options in the program is to choose what category of `Op` and `Rand` object to use throughout the system, which manifests itslef as the factory that is utilized throughout the program. This is how the `Base*` values are passed to the command objects during their consturction. One additional note is that this program assumes that the traditional double values will be generated by the `BaseFactory` class. If you created a specific `DoubleFactory` class, replace that `BaseFactory` constructor with a `DoubleFactory` constructor instead.

## Submission

To receive credit for this lab you must show an example program to your TA that demonstrates the full functionality of this pattern along with the composite and strategy patterns, and must explain to your TA the structure of both your classes and how they interact. You must also show your TA the tests that you have created for validating your decorator class and its interactions with the other classes.
