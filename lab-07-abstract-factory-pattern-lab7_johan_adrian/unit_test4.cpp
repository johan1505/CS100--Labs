#include "gtest/gtest.h"
#include "base.hpp"
#include "add.hpp"
#include "op.hpp"
#include "mult.hpp"
#include "div.hpp"
#include "pow.hpp"
#include "sub.hpp"
#include "Decorator.hpp"
#include "Ceil.hpp"
#include "Floor.hpp"
#include "Abs.hpp"
#include "PrecisionOp.hpp"
#include "PrecisionRand.hpp"
#include "rand.hpp"
#include "SciOp.hpp"
#include "SciRand.hpp"
#include "base_factory.hpp"
#include "PrecisionFactory.hpp"
#include "DoubleFactory.hpp"
#include "ScientificFactory.hpp"
#include <string>
using namespace std;


TEST(SciOpTest, SciOp) {
        Base* num1 = new SciOp(34245.663);
        EXPECT_EQ(num1->stringify(), "3.424566e+04");

        Base* num2 = new SciOp(-978.66356);
        EXPECT_EQ(num2->stringify(), "-9.786636e+02");

        Base* num3 = new SciOp(0);
        EXPECT_EQ(num3->stringify(), "0.000000e+00");

        Base* num4 = new op(4.76678);
        Base* num5 = new op(6.456);
        Base* mult = new Mult(num4, num5);
        Base* result = new SciOp(mult->evaluate());
        EXPECT_EQ(result->stringify(), "3.077433e+01");
}

TEST(SciRandTest, SciRand){
	srand(100);
        
	Base* num1  = new SciRand();
        EXPECT_EQ(num1->stringify(), "4.000000e+01");

	Base* num2  = new SciRand();
        EXPECT_EQ(num2->stringify(), "1.000000e+00");

	Base* num3  = new SciRand();
        EXPECT_EQ(num3->stringify(), "7.900000e+01");

	Base* num4  = new SciRand();
        EXPECT_EQ(num4->stringify(), "8.400000e+01");

	Base* num5  = new SciRand();
        EXPECT_EQ(num5->stringify(), "5.600000e+01");        
}

TEST(PrecisionOpTest, PrecisionOp){
	Base* PrecOp = new PrecisionOp(3.45667, 2);
	EXPECT_EQ(PrecOp->stringify(), "3.46");
	
	op* op1 = new PrecisionOp(1.2434555, 4);
	EXPECT_EQ(op1->stringify(), "1.2435");

	Base* PrecOp2 = new PrecisionOp(2.3346, 4);
	EXPECT_EQ(PrecOp2->stringify(), "2.3346");

	op* op2 = new PrecisionOp(1.23, 5);
	EXPECT_EQ(op2->stringify(), "1.23000"); 

	Base* PrecOp3 = new PrecisionOp(-23.5, 9);
	EXPECT_EQ(PrecOp3->stringify(), "-23.500000000");

	op* op3 = new PrecisionOp(0, 2);
	EXPECT_EQ(op3->stringify(), "0.00");

	Base* add = new Add(op1, PrecOp2);
	EXPECT_EQ(add->stringify(), "1.2435 + 2.3346");

	Base* sub = new Sub(op2, PrecOp3);
	EXPECT_EQ(add->stringify(), "1.23000 - -23.500000000");	

	Base* mult = new Mult(op3, op1);
	EXPECT_EQ(add->stringify(), "0.00 * 1.2435");	
}

TEST(PrecisionRandTest, PrecisionRand){
	srand(100);
	Base* PreRand = new PrecisionRand(4);
	EXPECT_EQ(PreRand->stringify(), "40.0000");

	Base* add = new Add(PreRand, new op(2.3346));
	EXPECT_EQ(add->stringify(), "40.0000 + 2.3346");

	PreRand = new PrecisionRand(2);
	EXPECT_EQ(PreRand->stringify(), "1.00");

	Base* sub = new Sub(PreRand, new op(2.3346));
	EXPECT_EQ(sub->stringify(), "1.00 - 2.3346");

	PreRand = new PrecisionRand(6);
	EXPECT_EQ(PreRand->stringify(), "79.000000");

	Base* div = new Div(PreRand, new op(2.3346));
	EXPECT_EQ(div->stringify(), "79.000000 / 2.3346");

	PreRand = new PrecisionRand(10);
	EXPECT_EQ(PreRand->stringify(), "84.0000000000");

	Base* pow = new Pow(PreRand, new op(2));
	EXPECT_EQ(pow->stringify(), "84.0000000000 ** 2");	
}

TEST(PrecisionFactoryTest, PrecisionFactory){
	srand(100);
	PrecisionFactory* PF = new PrecisionFactory(4);
	op* PreOp = PF->createOp(3.56789);
	Rand* PreRand = PF->createRand();
	EXPECT_EQ(PreOp->stringify(), "3.5679");
	EXPECT_EQ(PreRand->stringify(), "40.0000");
	EXPECT_EQ(PreOp->evaluate(), 3.56789);
        EXPECT_EQ(PreRand->evaluate(), 40.00);

	Base* ceiling = new Ceil(PreOp);
	EXPECT_EQ(ceiling->evaluate(), 4);

	PF = new PrecisionFactory(10);
	PreOp = PF->createOp(2.345);
	PreRand = PF->createRand();
	EXPECT_EQ(PreOp->stringify(), "2.3450000000");
	EXPECT_EQ(PreRand->stringify(), "1.0000000000");
	EXPECT_EQ(PreOp->evaluate(), 2.345);
	EXPECT_EQ(PreRand->evaluate(), 1.0);

	Base* floor = new Floor(PreRand);
	EXPECT_EQ(floor->evaluate(), 21;

	PF = new PrecisionFactory(2);
	PreOp = PF->createOp(-3452.14);
	PreRand = PF->createRand();
	EXPECT_EQ(PreOp->stringify(), "-3452.14");
	EXPECT_EQ(PreRand->stringify(), "79.00");
	EXPECT_EQ(PreOp->evaluate(), -3452.14);
        EXPECT_EQ(PreRand->evaluate(), 79.0);

	Base* abs = new Abs(PreOp);
	EXPECT_EQ(abs->evaluate(), 3452.14);

	PF = new PrecisionFactory();
	PreOp = PF->createOp(0);
	PreRand = PF->createRand();
	EXPECT_EQ(PreOp->stringify(), "0");
        EXPECT_EQ(PreRand->stringify(), "84");
	EXPECT_EQ(PreOp->evaluate(), 0);
        EXPECT_EQ(PreRand->evaluate(), 84.0);
}

TEST(DoubleFactoryTest, DoubleFactory){
	srand(100);
	DoubleFactory* DF  = new DoubleFactory();

	op* op1 = DF->createOp(-1.24345);
	Rand* rand1 = DF->createRand();
	EXPECT_EQ(op1->stringify(), "-1.243450");
	EXPECT_EQ(rand1->stringify(), "40.000000");

	op* op2 = DF->createOp(2.3346);
        Rand* rand2 = DF->createRand();
        EXPECT_EQ(op2->stringify(), "2.334600");
        EXPECT_EQ(rand2->stringify(), "1.000000");

	Base* add = new Add(op1, op2);
	EXPECT_EQ(add->stringify(), "-1.243450 + 2.334600");

	op* op3 = DF->createOp(1.23);
	Rand* rand3 = DF->createRand(); 
	EXPECT_EQ(op3->stringify(), "1.230000"); 
	EXPECT_EQ(rand3->stringify(), "79.000000");

	op* op4 = DF->createOp(0.00);
	Rand* rand4 = DF->createRand();
	EXPECT_EQ(op4->stringify(), "0.000000");
	EXPECT_EQ(rand4->stringify(), "84.000000");

	Base* div = new Div(rand3, rand4);
	EXPECT_EQ(add->stringify(), "79.000000 + 84.000000");
}

TEST(ScientificFactoryTest, ScientificFactory){
        srand(100);
        ScientificFactory* SF  = new ScientificFactory();

        op* op1 = SF->createOp(1678.765);
        Rand* rand1 = SF->createRand();
        EXPECT_EQ(op1->stringify(), "1.678765e+03");
        EXPECT_EQ(rand1->stringify(), "4.000000e+01");

	op* op2 = SF->createOp(0.00078543);
        Rand* rand2 = SF->createRand();
        EXPECT_EQ(op2->stringify(), "7.854300e-04");
        EXPECT_EQ(rand2->stringify(), "1.000000e+00");

        op* op3 = SF->createOp(-0.0);
        Rand* rand3 = SF->createRand();
        EXPECT_EQ(op3->stringify(), "-0.000000e+00");
        EXPECT_EQ(rand3->stringify(), "7.900000e+01");

	op* op4 = SF->createOp(456879865);
        Rand* rand4 = SF->createRand();
        EXPECT_EQ(op4->stringify(), "4.568799e+08");
        EXPECT_EQ(rand4->stringify(), "8.400000e+01");
}

int main(){
::testing::InitGoogleTest();
return RUN_ALL_TESTS();
}

