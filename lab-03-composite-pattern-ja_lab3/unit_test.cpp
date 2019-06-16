// Here we are going to put all of our unit test cases. This is pretty much the test.cpp file from lab2.
//
#include "base.hpp"
#include "add.hpp"
#include "mocks.hpp"
#include "gtest/gtest.h"
#include "op.hpp"
#include "InputOpMock.hpp"
#include "mult.hpp"
#include "div.hpp"
#include "pow.hpp"
#include "sub.hpp"

//****************JOHAN'S TESTS***************************

//TESTING OP CLASS
TEST(Optest, operand) {
    Base* opTest = new op(3);
    EXPECT_EQ(3, opTest->evaluate());
    EXPECT_EQ("3.000000", opTest->stringify()); 
    Base* opTest2 = new op();
    EXPECT_EQ(0, opTest2->evaluate());
    EXPECT_EQ("0.000000", opTest2->stringify());
    Base* opTest3 = new op('a');
    EXPECT_EQ(97, opTest3->evaluate());
    EXPECT_EQ("97.000000", opTest3->stringify());
}

//TESTING RAND CLASS USING THE MOCK
TEST(Randtest, runningMock1) {
    Base* testMock = new InputOpMock();
    EXPECT_EQ(7.5, testMock->evaluate());
    EXPECT_EQ("7.500000", testMock->stringify());
}


//*****************ADRIAN'S TESTS*************************

//TESTING ADD CLASS
TEST(AddTest, addition) {
	//two operands
	op* op1 = new op(7);
	op* op2  = new op(7);
	Add* add1 = new Add(op1, op2);
	EXPECT_EQ(add1->evaluate(), 14.0);
	EXPECT_EQ(add1->stringify(), "7.000000 + 7.000000");
	
	//one operand
        op* op3  = new op(5.3);
        Add* add2 = new Add(op3);
        EXPECT_EQ(add2->evaluate(), 5.3);
        EXPECT_EQ(add2->stringify(), "5.300000 + 0.000000");
	
	//no operands 
        Add* add3 = new Add();
        EXPECT_EQ(add3->evaluate(), 0.0);
        EXPECT_EQ(add3->stringify(), "0.000000 + 0.000000");

} 

//TESTING THE SUB CLASS
TEST(SubTest, subtraction) {
        op* op1 = new op(6);
        op* op2  = new op(4);
        Sub* sub1 = new Sub(op1, op2);
        EXPECT_EQ(sub1->evaluate(), 2.0);
        EXPECT_EQ(sub1->stringify(), "6.000000 - 4.000000");

        op* op3  = new op(2334.3);
        Sub* sub2 = new Sub(op3);
        EXPECT_EQ(sub2->evaluate(), 2334.3);
        EXPECT_EQ(sub2->stringify(), "2334.300000 - 0.000000");

        Sub* sub3 = new Sub();
        EXPECT_EQ(sub3->evaluate(), 0.0);
        EXPECT_EQ(sub3->stringify(), "0.000000 - 0.000000");

}

//TESTING THE POWER CLASS
TEST(PowTest, power) {
        op* op1 = new op(2);
        op* op2  = new op(5);
        Pow* pow1 = new Pow(op1, op2);
        EXPECT_EQ(pow1->evaluate(), 32.0);
        EXPECT_EQ(pow1->stringify(), "2.000000 ** 5.000000");

        op* op3  = new op(5.3);
        Pow* pow2 = new Pow(op3);
        EXPECT_EQ(pow2->evaluate(), 5.3);
        EXPECT_EQ(pow2->stringify(), "5.300000 ** 1.000000");

        Pow* pow3 = new Pow();
        EXPECT_EQ(pow3->evaluate(), 1.0);
        EXPECT_EQ(pow3->stringify(), "0.000000 ** 0.000000");

}


//TESTING MULT CLASS
TEST(MultTest, multiplication){
	//TESTING WITH 2 PARAMETERS
	Base* OP1 = new op(7.5);
	Base* OP2 = new op(7.5);
	Mult* mult1 = new Mult(OP1, OP2);
	EXPECT_EQ(mult1->evaluate(), 56.25);
	EXPECT_EQ(mult1->stringify(), "7.500000 * 7.500000");
	
	//TESTING WITH 1 PARAMETERS
	Mult* mult2 = new Mult(OP1);
	EXPECT_EQ(mult2->evaluate(), 7.5);
        EXPECT_EQ(mult2->stringify(), "7.500000 * 1.000000");
	
	//TESTING WITH NO PARAMETERS
	Mult* mult3 = new Mult();
	EXPECT_EQ(mult3->evaluate(), 1.0);
        EXPECT_EQ(mult3->stringify(), "1.000000 * 1.000000");

	//TESTING WITH ZEROS, NEGATIVE NUMBERS
	Base* OP3 = new op(0.0);
	Base* OP4 = new op(-30.0);
	Base* OP5 = new op(-20.0);

	Mult* mult4 = new Mult(OP3, OP4);
	EXPECT_EQ(mult4->evaluate(), 0.0);
	EXPECT_EQ(mult4->stringify(), "0.000000 * -30.000000");

	Mult* mult5 = new Mult(OP4, OP5);
	EXPECT_EQ(mult5->evaluate(), 600.0);
	EXPECT_EQ(mult5->stringify(), "-30.000000 * -20.000000");
}

//TESTING DIV CLASS
TEST(DivTest, division){
	//MOCKS
	Base* OP1 = new op(7.5);
	Base* OP2 = new op(7.5);

	//TESTING WITH 2 PARAMETERS
	Div*  div1  = new Div(OP1, OP2);
	EXPECT_EQ(div1->evaluate(), 1.00);
	EXPECT_EQ(div1->stringify(), "7.500000 / 7.500000");
		
	//TESTING WITH 1 PARAMETER
	Div* div2 = new Div(OP1);
	EXPECT_EQ(div2->evaluate(), 7.5 );
	EXPECT_EQ(div2->stringify(), "7.500000 / 1.000000");
	
	//TESTING WITH NO PARAMETERS
      	Div* div3 = new Div();
	EXPECT_EQ(div3->evaluate(), 1.0);
	EXPECT_EQ(div3->stringify(), "1.000000 / 1.000000"); 

	// TESTING ZEROS, NEGATIVE NUMBERS
	Base* OP3 = new op(0.0);
        Base* OP4 = new op(-30.0);
        Base* OP5 = new op(-20.0);

        Div* div4 = new Div(OP3, OP4);
        EXPECT_EQ(div4->evaluate(), 0.0);
        EXPECT_EQ(div4->stringify(), "0.000000 / -30.000000");

        Div* div5 = new Div(OP4, OP5);
        EXPECT_EQ(div5->evaluate(), 1.5);
        EXPECT_EQ(div5->stringify(), "-30.000000 / -20.000000");

	Div* div6 = new Div(OP4, OP3);
	EXPECT_EQ(div6->evaluate(), -1.0); // -30.0 / 0.0
	EXPECT_EQ(div6->stringify(), "Undefined");
}

TEST(CombinedOperationTests, combination){

//OPERATION TESTED: 5 - 2.3 x 2^3 + 4 / 7.5
//EXPECTED RESULT: -12.866667
/*      Base* OP_5 = new op(5);
        Base* OP_2_3 = new op(2.3);
	Base* OP_2 = new op(2);
        Base* OP_3 = new op(3);
	Base* OP_4 = new op(4);
        Base* OP_7_5 = new InputOpMock();      // "Rand object" 

	Base* POW  = new Pow(OP_2, OP_3);      // 2 ^ 3    = 8 
	Base* DIV  = new Div(OP_4, OP_7_5);    // 4 / 7.5  = 0.533333
	Base* MULT = new Mult(OP_2_3, POW);    // 2.3 * 8  = 18.4
	Base* SUB  = new Sub(OP_5, MULT);      // 5 - 18.4 = -13.4
	Base* ADD = new Add(SUB, DIV);         // -13.4 + 0.533333 = -12.866667 --  FINAL RESULT

	EXPECT_EQ(ADD->evaluate(), -12.8667);
	EXPECT_EQ(ADD->stringify(), "5.000000 - 2.300000 * 2.000000 ** 3.000000 + 4.000000 / 7.500000"); // MAY NOT PASS
*/
//OPERATION TESTED: 5 - 2 * 4 ^ 2 +  9 / 3
//EXPECTED RESULT: -24
	Base* OP_5 = new op(5);
        Base* OP_2 = new op(2);
        Base* OP_3 = new op(3);
        Base* OP_4 = new op(4);
        Base* OP_9 = new op(9);

	Base* POW = new Pow(OP_4, OP_2);
	Base* DIV = new Div(OP_9, OP_3);
	Base* MULT = new Mult(OP_2, POW);
	Base* SUB = new Sub(OP_5, MULT);
	Base* ADD = new Add(SUB, DIV);

        EXPECT_EQ(ADD->evaluate(), -24.0);
        EXPECT_EQ(ADD->stringify(), "5.000000 - 2.000000 * 4.000000 ** 2.000000 + 9.000000 / 3.000000"); 

}

int main() {
::testing::InitGoogleTest();
return RUN_ALL_TESTS();
}
