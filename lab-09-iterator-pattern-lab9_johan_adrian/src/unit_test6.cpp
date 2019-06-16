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
#include "../header/Trunc.hpp"
#include "../header/Paren.hpp"
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
#include "../header/Iterator.hpp"
#include "../header/NullIterator.hpp"
#include "../header/UnaryIterator.hpp"
#include "../header/BinaryIterator.hpp"
#include "../header/PreorderIterator.hpp"
#include "../header/DummyRoot.hpp"
#include <string>
using namespace std;

TEST(BaseLeftRight, BaseChildTest){
Base* OP = new op(3.4);
EXPECT_EQ(OP->get_left(), nullptr);
EXPECT_EQ(OP->get_right(), nullptr);

Base* RAND = new Rand();
EXPECT_EQ(RAND->get_left(), nullptr);
EXPECT_EQ(RAND->get_right(), nullptr);

Base* ADD = new Add(new op(4.35), new op(4.56));
EXPECT_EQ(ADD->get_left()->evaluate(), 4.35);
EXPECT_EQ(ADD->get_right()->evaluate(), 4.56);

Base* SUB = new Sub(new op(4.35), new op(4.56));
EXPECT_EQ(ADD->get_left()->evaluate(), 4.35);
EXPECT_EQ(ADD->get_right()->evaluate(), 4.56);

Base* MULT = new Mult(new op(4.35), new op(4.56));
EXPECT_EQ(ADD->get_left()->evaluate(), 4.35);
EXPECT_EQ(ADD->get_right()->evaluate(), 4.56);

Base* DIV = new Div(new op(4.35), new op(4.56));
EXPECT_EQ(ADD->get_left()->evaluate(), 4.35);
EXPECT_EQ(ADD->get_right()->evaluate(), 4.56);

Base* POW = new Pow(new op(4.35), new op(4.56));
EXPECT_EQ(POW->get_left()->evaluate(), 4.35);
EXPECT_EQ(POW->get_right()->evaluate(), 4.56);

//Decorators
Base* OP2 = new op(2.3);           // Small positive number
Base* d1 = new Ceil(OP2);
EXPECT_EQ(d1->get_left()->evaluate(), 2.3);
EXPECT_EQ(d1->get_right(), nullptr);

Base* OP3 = new op(25678.13); //Large positive number
Base* d2 = new Floor(OP3);
EXPECT_EQ(d2->get_left()->evaluate(), 25678.13);
EXPECT_EQ(d2->get_right(), nullptr);

Base* OP4 = new op(-5.5);     //Small negative number
Base* d3 = new Abs(OP4);
EXPECT_EQ(d3->get_left()->evaluate(), -5.5);
EXPECT_EQ(d3->get_right(), nullptr);

Base* OP5 = new op(2.3);          
Base* d4 = new Trunc(OP5);
EXPECT_EQ(d4->get_left()->stringify(), "2.300000");
EXPECT_EQ(d4->get_right(), nullptr);

Base* OP6 = new op(8.9);
Base* d5 = new Paren(OP6);
EXPECT_EQ(d5->get_left()->stringify(), "8.900000");
EXPECT_EQ(d5->get_right(), nullptr);
}

TEST(NullIteratorTest, NullIterator){
srand(100);
Base* op1;
Iterator* it;

op1 = new op(156.65);
it = new NullIterator(op1);
it->first();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);

op1 = new Rand();
it = new NullIterator(op1);
it->first();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);

}


TEST(UnaryIteratorTest, UnaryIterator){
Base* op1 = new op(3.21);
Base* op2 = new op(4.56);
Base * d1;
Iterator* it;
Base* sum = new Add(op1, op2); 
d1 = new Ceil(sum);
it = new UnaryIterator(d1);
it->first();
EXPECT_EQ(it->current()->evaluate(), 7.77);
it->next();
EXPECT_EQ(it->current(), nullptr);


d1 = new Floor(sum);
it = new UnaryIterator(d1);
it->first();
EXPECT_EQ(it->current()->evaluate(),7.77);
it->next();
EXPECT_EQ(it->current(), nullptr);


d1 = new Trunc(sum);
it = new UnaryIterator(d1);
it->first();
EXPECT_EQ(it->current()->stringify(), "3.210000 + 4.560000");
it->next();
EXPECT_EQ(it->current(), nullptr);


d1 = new Paren(sum);
it = new UnaryIterator(d1);
it->first();
EXPECT_EQ(it->current()->stringify(), "3.210000 + 4.560000");
it->next();
EXPECT_EQ(it->current(), nullptr);
}


TEST(BinaryIteratorTest, BinaryIterator){
Base* op1 = new op(3.5);
Base* op2 = new op(4.5);
Base * d1;
Iterator* it;

Base* sum = new Add(op1, op2); 
it = new BinaryIterator(sum);
it->first();
EXPECT_EQ(it->current()->evaluate(), 3.5);
EXPECT_EQ(it->is_done(), false); //should be false
it->next();
EXPECT_EQ(it->current()->evaluate(), 4.5);
it->next();
EXPECT_EQ(it->current(), nullptr);


Base* mult = new Mult(op1, op2); 
it = new BinaryIterator(mult);
it->first();
EXPECT_EQ(it->current()->evaluate(), 3.5);
it->next();
EXPECT_EQ(it->current()->evaluate(), 4.5);
EXPECT_EQ(it->is_done(), false);
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true); 


Base* div = new Div(op1, op2); 
it = new BinaryIterator(div);
it->first();
EXPECT_EQ(it->current()->evaluate(), 3.5);
it->next();
EXPECT_EQ(it->is_done(), false);
EXPECT_EQ(it->current()->evaluate(), 4.5);
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);


Base* pow = new Pow(op1, op2); 
it = new BinaryIterator(pow);
it->first();
EXPECT_EQ(it->is_done(), false);
EXPECT_EQ(it->current()->evaluate(), 3.5);
it->next();
EXPECT_EQ(it->current()->evaluate(), 4.5);
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);

Base* sub = new Sub(op1, op2); 
it = new BinaryIterator(sub);
it->first();
EXPECT_EQ(it->is_done(), false);
EXPECT_EQ(it->current()->evaluate(), 3.5);
it->next();
EXPECT_EQ(it->current()->evaluate(), 4.5);
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);

Base* sum2 = new Add(sum, sub);
it = new BinaryIterator(sum2);
it->first();
EXPECT_EQ(it->current()->evaluate(), 8.0);
it->next();
EXPECT_EQ(it->current()->evaluate(), -1.0);
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);


d1 = new Paren(mult);
Base* mult2 = new Mult(sum, d1);
it = new BinaryIterator(mult2);
it->first();
EXPECT_EQ(it->is_done(), false);
EXPECT_EQ(it->current()->stringify(), "3.500000 + 4.500000");
it->next();
EXPECT_EQ(it->current()->stringify(), "(3.500000 * 4.500000)");
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);
}

TEST(PreOrderIteratorTest, PreOrderIterator){
Base* OP1 = new op(2);
Base* OP2 = new op(3);
Base* SUM = new Add(OP1, OP2);
Base* OP3 = new op(-3);
Base* OP4 = new op(-4);
Base* MULT = new Mult(OP3, OP4);
Base* SUB = new Sub(SUM, MULT);
Base* root = new DummyRoot(SUB);
Iterator* it = new PreorderIterator(root);
it->first();
EXPECT_EQ(it->is_done(), false);
EXPECT_EQ(it->current()->stringify(), "2.000000 + 3.000000 - -3.000000 * -4.000000");
it->next();
EXPECT_EQ(it->current()->stringify(), "2.000000 + 3.000000");
it->next();
EXPECT_EQ(it->current()->stringify(), "2.000000");
it->next();
EXPECT_EQ(it->current()->stringify(), "3.000000");
it->next();
EXPECT_EQ(it->current()->stringify(), "-3.000000 * -4.000000");
it->next();
EXPECT_EQ(it->current()->stringify(), "-3.000000");
it->next();
EXPECT_EQ(it->current()->stringify(), "-4.000000");
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);

//Testing the decorators
Base* OP6 = new op(1);
Base* OP7 = new Abs(new op(2));
Base* SUM2 = new Add(OP6,OP7);
Base* root2 = new DummyRoot(SUM2);

Iterator* it2 = new PreorderIterator(root2);
it2->first();
EXPECT_EQ(it2->is_done(), false);
EXPECT_EQ(it2->current()->stringify(), "1.000000 + 2.000000");
it2->next();
EXPECT_EQ(it2->is_done(), false);
EXPECT_EQ(it2->current()->stringify(), "1.000000");
it2->next();
EXPECT_EQ(it2->is_done(), false);
EXPECT_EQ(it2->current()->stringify(), "2.000000");
it2->next();
EXPECT_EQ(it2->is_done(), false);
EXPECT_EQ(it2->current()->stringify(), "2.000000");
it2->next();
EXPECT_EQ(it2->current(), nullptr);
EXPECT_EQ(it2->is_done(), true);
}


TEST(createIteratorTest, createIterator){
srand(100);
Base* op1;
Base* op2;
Iterator* it;

op1 = new op(156.65);
it = op1->create_iterator();
it->first();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);

op1 = new Rand();
it = op1->create_iterator();
it->first();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);



op1 = new op(3.21);
op2 = new op(4.56);
Base* d1;
Base* sum = new Add(op1, op2); 
d1 = new Ceil(sum);
it = d1->create_iterator();
it->first();
EXPECT_EQ(it->current()->evaluate(), 7.77);
it->next();
EXPECT_EQ(it->current(), nullptr);


d1 = new Floor(sum);
it = d1->create_iterator();
it->first();
EXPECT_EQ(it->current()->evaluate(),7.77);
it->next();
EXPECT_EQ(it->current(), nullptr);


op1 = new op(-5.5);   
d1 = new Abs(op1);
it = d1->create_iterator();
it->first();
EXPECT_EQ(it->current()->evaluate(), -5.5);
it->next();
EXPECT_EQ(it->current(), nullptr);


d1 = new Trunc(sum);
it = d1->create_iterator();
it->first();
EXPECT_EQ(it->current()->stringify(), "3.210000 + 4.560000");
it->next();
EXPECT_EQ(it->current(), nullptr);


d1 = new Paren(sum);
it = d1->create_iterator();
it->first();
EXPECT_EQ(it->current()->stringify(), "3.210000 + 4.560000");
it->next();
EXPECT_EQ(it->current(), nullptr);



op1 = new op(3.5);
op2 = new op(4.5);

sum = new Add(op1, op2); 
it = sum->create_iterator();
it->first();
EXPECT_EQ(it->current()->evaluate(), 3.5);
EXPECT_EQ(it->is_done(), false); //should be false
it->next();
EXPECT_EQ(it->current()->evaluate(), 4.5);
it->next();
EXPECT_EQ(it->current(), nullptr);


Base* mult = new Mult(op1, op2); 
it = mult->create_iterator();
it->first();
EXPECT_EQ(it->current()->evaluate(), 3.5);
it->next();
EXPECT_EQ(it->current()->evaluate(), 4.5);
EXPECT_EQ(it->is_done(), false);
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true); 


Base* div = new Div(op1, op2); 
it = div->create_iterator();
it->first();
EXPECT_EQ(it->current()->evaluate(), 3.5);
it->next();
EXPECT_EQ(it->is_done(), false);
EXPECT_EQ(it->current()->evaluate(), 4.5);
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);


Base* pow = new Pow(op1, op2); 
it = pow->create_iterator();
it->first();
EXPECT_EQ(it->is_done(), false);
EXPECT_EQ(it->current()->evaluate(), 3.5);
it->next();
EXPECT_EQ(it->current()->evaluate(), 4.5);
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);


Base* sub = new Sub(op1, op2); 
it = sub->create_iterator();
it->first();
EXPECT_EQ(it->is_done(), false);
EXPECT_EQ(it->current()->evaluate(), 3.5);
it->next();
EXPECT_EQ(it->current()->evaluate(), 4.5);
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);

Base* sum2 = new Add(sum, sub);
it = sum2->create_iterator();
it->first();
EXPECT_EQ(it->current()->evaluate(), 8.0);
it->next();
EXPECT_EQ(it->current()->evaluate(), -1.0);
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);


d1 = new Paren(mult);
Base* mult2 = new Mult(sum, d1);
it = mult2->create_iterator();
it->first();
EXPECT_EQ(it->is_done(), false);
EXPECT_EQ(it->current()->stringify(), "3.500000 + 4.500000");
it->next();
EXPECT_EQ(it->current()->stringify(), "(3.500000 * 4.500000)");
it->next();
EXPECT_EQ(it->current(), nullptr);
EXPECT_EQ(it->is_done(), true);
}

int main(){
::testing::InitGoogleTest();
return RUN_ALL_TESTS();
}
