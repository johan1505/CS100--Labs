#include "gtest/gtest.h"
#include "../header/base.hpp"
#include "../header/add.hpp"
#include "../header/op.hpp"
#include "../header/mult.hpp"
#include "../header/div.hpp"
#include "../header/pow.hpp"
#include "../header/sub.hpp"
#include "../header/Decorator.hpp"
#include "../header/Ceil.hpp"
#include "../header/Floor.hpp"
#include "../header/Abs.hpp"
#include "../header/PrecisionOp.hpp"
#include "../header/PrecisionRand.hpp"
#include "../header/rand.hpp"
#include "../header/SciOp.hpp"
#include "../header/SciRand.hpp"
#include "../header/base_factory.hpp"
#include "../header/PrecisionFactory.hpp"
#include "../header/DoubleFactory.hpp"
#include "../header/ScientificFactory.hpp"
#include "../header/command.hpp"
#include "../header/Menu.hpp"
#include "../header/InitialCommand.hpp"
#include "../header/PowCommand.hpp"
#include "../header/SubCommand.hpp"
#include "../header/AddCommand.hpp"
#include "../header/DivCommand.hpp"
#include "../header/MultCommand.hpp"
#include <string>
using namespace std;

TEST(AddCommandTest, AddCommand) {
srand(100);
PrecisionFactory* PF = new PrecisionFactory(3);
DoubleFactory* DF = new DoubleFactory();
ScientificFactory* SF = new ScientificFactory();

Command* c = nullptr;
Base* b = nullptr;
Command* d = nullptr;

c = new InitialCommand(DF->createOp(2.34));
b = DF->createOp(3.21);
d = new AddCommand(c, b);
EXPECT_EQ(d->execute(), 5.55);
EXPECT_EQ(d->stringify(), "2.340000 + 3.210000");

c = new InitialCommand(PF->createOp(2.34));
b = PF->createOp(2.34);
d = new AddCommand(c, b);
EXPECT_EQ(d->execute(), 4.68);
EXPECT_EQ(d->stringify(), "2.340 + 2.340");

c = new InitialCommand(SF->createOp(12.3456));
b = SF->createOp(0.0);
d = new AddCommand(c, b);
EXPECT_EQ(d->execute(), 12.3456);
EXPECT_EQ(d->stringify(), "1.234560e+01 + 0.000000e+00");

c = new InitialCommand(DF->createOp(9.34434));
b = DF->createOp(4.0);
d = new AddCommand(c, b);
EXPECT_EQ(d->execute(), 13.34434);
EXPECT_EQ(d->stringify(), "9.344340 + 4.000000");

//inputting an add command
b = DF->createOp(7.1);
Command* e = new AddCommand(d, b);
EXPECT_EQ(e->execute(), 20.44434);
EXPECT_EQ(e->stringify(), "9.344340 + 4.000000 + 7.100000");

}

TEST(DivCommandTest, DivCommand){
srand(100);
PrecisionFactory* PF = new PrecisionFactory(3);
DoubleFactory* DF = new DoubleFactory();
ScientificFactory* SF = new ScientificFactory();

Command* c = nullptr;
Base* b = nullptr;
Command* d = nullptr;

c = new InitialCommand(DF->createOp(7.0));
b = DF->createOp(2.0);
d = new DivCommand(c, b);
EXPECT_EQ(d->execute(), 3.500000);
EXPECT_EQ(d->stringify(), "7.000000 / 2.000000");

c = new InitialCommand(PF->createOp(2.34));
b = PF->createOp(2.34);
d = new DivCommand(c, b);
EXPECT_EQ(d->execute(), 1);
EXPECT_EQ(d->stringify(), "2.340 / 2.340");

c = new InitialCommand(SF->createOp(12.3456));
b = SF->createOp(0.0);
d = new DivCommand(c, b);
EXPECT_EQ(d->execute(), -1); //denotes error
EXPECT_EQ(d->stringify(), "Undefined");

c = new InitialCommand(DF->createOp(12.5));
b = DF->createOp(5.0);
d = new DivCommand(c, b);
EXPECT_EQ(d->execute(), 2.5);
EXPECT_EQ(d->stringify(), "12.500000 / 5.000000");

//inputting an div command
b = DF->createOp(2.5);
Command* e = new DivCommand(d, b);
EXPECT_EQ(e->execute(), 1.0);
EXPECT_EQ(e->stringify(), "12.500000 / 5.000000 / 2.500000");

}


TEST(MultCommandTest, MultCommand){
srand(100);
PrecisionFactory* PF = new PrecisionFactory(3);
DoubleFactory* DF = new DoubleFactory();
ScientificFactory* SF = new ScientificFactory();

Command* c = nullptr;
Base* b = nullptr;
Command* d = nullptr;

c = new InitialCommand(DF->createOp(7.0));
b = DF->createOp(2.0);
d = new MultCommand(c, b);
EXPECT_EQ(d->execute(), 14.000000);
EXPECT_EQ(d->stringify(), "7.000000 * 2.000000");

c = new InitialCommand(PF->createOp(2));
b = PF->createOp(2.3);
d = new MultCommand(c, b);
EXPECT_EQ(d->execute(), 4.6);
EXPECT_EQ(d->stringify(), "2.000 * 2.300");

c = new InitialCommand(SF->createOp(12.3456));
b = SF->createOp(0.0);
d = new MultCommand(c, b);
EXPECT_EQ(d->execute(), 0); //denotes error
EXPECT_EQ(d->stringify(), "1.234560e+01 * 0.000000e+00");

c = new InitialCommand(DF->createOp(12.5));
b = DF->createOp(5.0);
d = new MultCommand(c, b);
EXPECT_EQ(d->execute(), 62.5);
EXPECT_EQ(d->stringify(), "12.500000 * 5.000000");

//inputting a Mult command
b = DF->createOp(2.5);
Command* e = new MultCommand(d, b);
EXPECT_EQ(e->execute(), 156.25);
EXPECT_EQ(e->stringify(), "12.500000 * 5.000000 * 2.500000");
}


TEST(PowCommandTest, PowCommand){
srand(100);
PrecisionFactory* PF = new PrecisionFactory(3);
DoubleFactory* DF = new DoubleFactory();
ScientificFactory* SF = new ScientificFactory();

Command* c = nullptr;
Base* b = nullptr;
Command* d = nullptr;

c = new InitialCommand(DF->createOp(7.0));
b = DF->createOp(2.0);
d = new PowCommand(c, b);
EXPECT_EQ(d->execute(), 49);
EXPECT_EQ(d->stringify(), "7.000000 ** 2.000000");

c = new InitialCommand(PF->createOp(12));
b = PF->createOp(5);
d = new PowCommand(c, b);
EXPECT_EQ(d->execute(), 248832.000);
EXPECT_EQ(d->stringify(), "12.000 ** 5.000");

c = new InitialCommand(SF->createOp(12.3456));
b = SF->createOp(0.0);
d = new PowCommand(c, b);
EXPECT_EQ(d->execute(), 1); //denotes error
EXPECT_EQ(d->stringify(), "1.234560e+01 ** 0.000000e+00");

c = new InitialCommand(DF->createOp(22));
b = DF->createOp(1);
d = new PowCommand(c, b);
EXPECT_EQ(d->execute(), 22);
EXPECT_EQ(d->stringify(), "22.000000 ** 1.000000");

b = DF->createOp(2);
Command* e = new PowCommand(d, b);
EXPECT_EQ(e->execute(), 484);
EXPECT_EQ(e->stringify(), "22.000000 ** 1.000000 ** 2.000000");
}

TEST(SubCommandTest, SubCommand){
srand(100);
PrecisionFactory* PF = new PrecisionFactory(3);
DoubleFactory* DF = new DoubleFactory();
ScientificFactory* SF = new ScientificFactory();

Command* c = nullptr;
Base* b = nullptr;
Command* d = nullptr;

c = new InitialCommand(DF->createOp(7.0));
b = DF->createOp(2.0);
d = new SubCommand(c, b);
EXPECT_EQ(d->execute(), 5.000000);
EXPECT_EQ(d->stringify(), "7.000000 - 2.000000");

c = new InitialCommand(PF->createOp(12));
b = PF->createOp(10);
d = new SubCommand(c, b);
EXPECT_EQ(d->execute(), 2.000);
EXPECT_EQ(d->stringify(), "12.000 - 10.000");

c = new InitialCommand(SF->createOp(12.3456));
b = SF->createOp(0.0);
d = new SubCommand(c, b);
EXPECT_EQ(d->execute(), 12.3456); //denotes error
EXPECT_EQ(d->stringify(), "1.234560e+01 - 0.000000e+00");

c = new InitialCommand(DF->createOp(12.5));
b = DF->createOp(5.0);
d = new SubCommand(c, b);
EXPECT_EQ(d->execute(), 7.5);
EXPECT_EQ(d->stringify(), "12.500000 - 5.000000");

//inputting an add command
b = DF->createOp(2.5);
Command* e = new SubCommand(d, b);
EXPECT_EQ(e->execute(), 5.0);
EXPECT_EQ(e->stringify(), "12.500000 - 5.000000 - 2.500000");
}


TEST(InitialCommandTes,InitialCommand){
srand(100);
//Factories
PrecisionFactory* PF = new PrecisionFactory(3);
DoubleFactory* DF = new DoubleFactory();
ScientificFactory* SF = new ScientificFactory();

Command* c = nullptr;

//Testing InitialCommand with PrecisionFactory
c = new InitialCommand(PF->createOp(2.34));
EXPECT_EQ(c->execute(), 2.340);
EXPECT_EQ(c->stringify(), "2.340");

c = new InitialCommand(PF->createRand());
EXPECT_EQ(c->execute(), 40.000);
EXPECT_EQ(c->stringify(), "40.000");

//Testing InitialCommand with DoubleFactory
c = new InitialCommand(DF->createOp(5.678));
EXPECT_EQ(c->execute(), 5.678);
EXPECT_EQ(c->stringify(), "5.678000");

c = new InitialCommand(DF->createRand());
EXPECT_EQ(c->execute(), 1.000);
EXPECT_EQ(c->stringify(), "1.000000");


//Testing InitialCommand with ScientificFactory
c = new InitialCommand(SF->createOp(-978.66356));
EXPECT_EQ(c->execute(), -978.66356);
EXPECT_EQ(c->stringify(), "-9.786636e+02");

c = new InitialCommand(SF->createRand());
EXPECT_EQ(c->execute(), 79);
EXPECT_EQ(c->stringify(), "7.900000e+01");
}

TEST(MenuTest, Menu){
srand(100); 
//Factories used to initlize the Command for the menu
PrecisionFactory* PF = new PrecisionFactory(4);
DoubleFactory* DF = new DoubleFactory();
ScientificFactory* SF = new ScientificFactory();

Menu* M = new Menu();
EXPECT_EQ(M->initialized(), false);// Test if Menu has been initialized
EXPECT_EQ(M->execute(), "");
EXPECT_EQ(M->stringify(), "");

Command* I = new InitialCommand(DF->createOp(3.45)); // Initialize the menu
M->add_command(I); 
EXPECT_EQ(M->initialized(), true); // history: 3.45
EXPECT_EQ(M->execute(), "3.450000");
EXPECT_EQ(M->stringify(), "3.450000");

Command* Add = new AddCommand(I, PF->createOp(3.12));
M->add_command(Add);
EXPECT_EQ(M->initialized(), true); // history: 3.45 -> (3.45 + 3.1200)
EXPECT_EQ(M->execute(), "6.570000");
EXPECT_EQ(M->stringify(), "3.450000 + 3.1200");
M->undo(); // Undo the command just done
EXPECT_EQ(M->execute(), "3.450000"); // index pointing at pos 0
M->undo(); // Attempting to undo the las comand
EXPECT_EQ(M->execute(), "3.450000"); // History still pointing at the first command
M->redo();// Redo the AddCommand
EXPECT_EQ(M->execute(), "6.570000"); // History still pinting at the last command
M->redo();
EXPECT_EQ(M->execute(), "6.570000");

Command* Sub = new SubCommand(Add, SF->createRand());
M->add_command(Sub);
EXPECT_EQ(M->initialized(), true); // history: 3.45 -> (3.45 + 3.1200) -> ((3.45 + 3.1200) - 4.000000e+01"
EXPECT_EQ(M->execute(), "-33.430000");
EXPECT_EQ(M->stringify(), "3.450000 + 3.1200 - 4.000000e+01");
M->undo(); // Undo the command just done
EXPECT_EQ(M->execute(), "6.570000"); // index pointing at pos 1

Command* Mult = new MultCommand (Sub, DF->createOp(2)); //Creating a new Mult Command
M->add_command(Mult); // Adding that new command to the history, note at this point the index was not pointing to the last element in the vector, so all the elements after the index should have been erased
EXPECT_EQ(M->execute(), "-66.860000"); // History  now points at the last element in the history vector. All of the elements that were after the previous index were deleted.
EXPECT_EQ(M->stringify(), "3.450000 + 3.1200 - 4.000000e+01 * 2.000000"); //history: 3.45 -> (3.45 + 3.1200) -> (3.450000 + 3.1200 - 4.000000e+01 * 2.000000)
M->redo();
EXPECT_EQ(M->execute(), "-66.860000"); // History index still points at the same element in the history vector since there is nothing to redo
EXPECT_EQ(M->stringify(), "3.450000 + 3.1200 - 4.000000e+01 * 2.000000");

Command* Div = new DivCommand (Mult, PF->createRand());// Creating a new Div Command
M->add_command(Div);// Adding the new command to the history; index now points to this element
EXPECT_EQ(M->execute(), "-66.860000");
EXPECT_EQ(M->stringify(), "3.450000 + 3.1200 - 4.000000e+01 * 2.000000 / 1.0000"); //history: 3.45 -> (3.45 + 3.1200) -> (3.450000 + 3.1200 - 4.000000e+01 * 2.000000) -> (3.450000 + 3.1200 - 4.000000e+01 * 2.000000 / 1.0000)

M->undo(); //history: 3.45 -> (3.45 + 3.1200) -> (3.450000 + 3.1200 - 4.000000e+01 * 2.000000) 
M->undo(); //history: 3.45 -> (3.45 + 3.1200)
M->undo(); //history: 3.45
M->undo();// history: 3.45// Note index stilll points at the only element in the vecvtor since there is nothing to undo

EXPECT_EQ(M->execute(), "3.450000");
EXPECT_EQ(M->stringify(), "3.450000");

Command* Pow = new PowCommand(Div, DF->createOp(2));
M->add_command(Pow);// Adding the new pow command to the history, index now points to this element. Note all the posible redos were deleted
EXPECT_EQ(M->execute(), "4470.259600"); 
EXPECT_EQ(M->stringify(), "3.450000 + 3.1200 - 4.000000e+01 * 2.000000 / 1.0000 ** 2.000000"); // history: 3.45 ->  (3.450000 + 3.1200 - 4.000000e+01 * 2.000000 / 1.0000 ** 2.000000)
M->execute();
M->redo();
EXPECT_EQ(M->execute(), "4470.259600"); // The index still points at the same element in the vector since there is nothing to redo
}

int main(){
::testing::InitGoogleTest();
return RUN_ALL_TESTS();
}
