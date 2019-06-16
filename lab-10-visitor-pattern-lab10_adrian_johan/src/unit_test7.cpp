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
#include "../header/visitor.hpp"
#include <string>
using namespace std;

TEST(VisitorTest, Visitor) {
	srand(100);
	Base* OP1 = new op(2);
	Base* OP2 = new op(10);
	Base* OP3 = new op(8);
	Base* OP4 = new op(5);
	Base* RAND1 = new Rand();
	Base* RAND2 = new Rand();
	Base* TRUNC = new Trunc(OP1);
	Base* FLOOR = new Floor(RAND1);
	Base* SUB = new Sub(TRUNC, FLOOR);
	Base* MULT = new Mult(OP2, RAND2);
	Base* POW = new Pow(OP3, OP4);
	Base* CEIL = new Ceil(POW);
	Base* PAREN = new Paren(MULT);
	Base* DIV = new Div(PAREN, CEIL);
	Base* ADD = new Add(SUB, DIV);
	Base* ABS = new Abs(ADD);

	Base* root = new DummyRoot(ABS);
	Iterator* it = new PreorderIterator(root);
	CountVisitor* v = new CountVisitor();

	for (it->first(); !(it->is_done()); it->next()) {
		it->current()->accept(v);
	}

	EXPECT_EQ(v->op_count(), 4);
	EXPECT_EQ(v->rand_count(), 2);
	EXPECT_EQ(v->mult_count(), 1);
	EXPECT_EQ(v->div_count(), 1);
	EXPECT_EQ(v->add_count(), 1);
	EXPECT_EQ(v->sub_count(), 1);
	EXPECT_EQ(v->pow_count(), 1);
	EXPECT_EQ(v->ceil_count(), 1);
	EXPECT_EQ(v->floor_count(), 1);
	EXPECT_EQ(v->abs_count(), 1);
	EXPECT_EQ(v->trunc_count(), 1);
	EXPECT_EQ(v->paren_count(), 1);
}

int main(){
::testing::InitGoogleTest();
return RUN_ALL_TESTS();
}
