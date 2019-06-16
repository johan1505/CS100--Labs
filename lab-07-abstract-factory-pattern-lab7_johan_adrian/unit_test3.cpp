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
#include "Trunc.hpp"
#include "Paren.hpp"
#include <string>
using namespace std;

TEST(CeilTest, Ceil){
    Base* OP = new op(2.3);           // Small positive number
    Base* d1 = new Ceil(OP);
    EXPECT_EQ(d1->evaluate(), 3.0);

    Base* OP2 = new op(25678.13); //Large positive number
    d1 = new Ceil(OP2);
    EXPECT_EQ(d1->evaluate(), 25679);

    Base* OP3 = new op(-5.5);     //Small negative number
    d1 = new Ceil(OP3);
    EXPECT_EQ(d1->evaluate(), -5);

    Base* OP4 = new op(-654321.9);// Large negative number
    d1 = new Ceil(OP4);
    EXPECT_EQ(d1->evaluate(), -654321);

    Base* sum = new Add(OP, OP2); // 2.3 + 25678.13 = 25680.43 -> 25681
    d1 = new Ceil(sum);
    EXPECT_EQ(d1->evaluate(), 25681);

    Base* diff = new Sub(OP, OP3); // 2.3 - (-5.5) = 7.8 - > 8
    d1 = new Ceil(diff);
    EXPECT_EQ(d1->evaluate(), 8);

    Base* mult = new Mult(OP3, OP); // -5.5 * 2.3 = -12.65
    d1 = new Ceil(mult);
    EXPECT_EQ(d1->evaluate(), -12);
}

TEST(FloorTest, Floor){
    Base* OP = new op(2.3);           // Small positive number
    Base* d1 = new Floor(OP);
    EXPECT_EQ(d1->evaluate(), 2.0);

    Base* OP2 = new op(25678.13); //Large positive number
    d1 = new Floor(OP2);
    EXPECT_EQ(d1->evaluate(), 25678);

    Base* OP3 = new op(-5.5);     //Small negative number
    d1 = new Floor(OP3);
    EXPECT_EQ(d1->evaluate(), -6);

    Base* OP4 = new op(-654321.9);// Large negative number
    d1 = new Floor(OP4);
    EXPECT_EQ(d1->evaluate(), -654322);

    Base* sum = new Add(OP, OP2); // 2.3 + 25678.13 = 25680.43 -> 25680
    d1 = new Floor(sum);
    EXPECT_EQ(d1->evaluate(), 25680);

    Base* diff = new Sub(OP, OP3); // 2.3 - (-5.5) = 7.8 - > 7
    d1 = new Floor(diff);
    EXPECT_EQ(d1->evaluate(), 7);

    Base* mult = new Mult(OP3, OP); // -5.5 * 2.3 = -12.65
    d1 = new Floor(mult);
    EXPECT_EQ(d1->evaluate(), -13);
}

TEST(AbsTest, Abs){
    Base* OP = new op(2.3);           // Small positive number
    Base* d1 = new Abs(OP);
    EXPECT_EQ(d1->evaluate(), 2.3);

    Base* OP2 = new op(25678.13); //Large positive number
    d1 = new Abs(OP2);
    EXPECT_EQ(d1->evaluate(), 25678.13);

    Base* OP3 = new op(-5.5);     //Small negative number
    d1 = new Abs(OP3);
    EXPECT_EQ(d1->evaluate(), 5.5);

    Base* OP4 = new op(-654321.9);// Large negative number
    d1 = new Abs(OP4);
    EXPECT_EQ(d1->evaluate(), 654321.9);

    Base* sum = new Add(OP, OP2); // 2.3 + 25678.13 = 25680.43
    d1 = new Abs(sum);
    EXPECT_EQ(d1->evaluate(), 25680.43);

    Base* diff = new Sub(OP, OP3); // 2.3 - (-5.5) = 7.8
    d1 = new Abs(diff);
    EXPECT_EQ(d1->evaluate(), 7.8);

    Base* mult = new Mult(new op(-4.0), new op(3.0)); // -4 * 3 = -12
    d1 = new Abs(mult);
    EXPECT_EQ(d1->evaluate(), 12);

    Base* div = new Div(new op(32.0), new op(-8.0));  // 32 / -8 = -4
    d1 = new Abs(div);
    EXPECT_EQ(d1->evaluate(), 4);
}

TEST(CeilFloorAbsTest, CeilFlorrAbs){
    Base* d1 = nullptr;

    // Abs + Ceil
    d1 = new Abs(new Ceil(new op(-2.3)));          
    EXPECT_EQ(d1->evaluate(), 2);

    d1 = new Abs(new Ceil(new Add(new op(4.5), new op(-6.4))));          
    EXPECT_EQ(d1->evaluate(), 1);

    // Abs + Floor
    d1 = new Abs(new Floor(new op(-56.898)));
    EXPECT_EQ(d1->evaluate(), 57);
    
    d1 = new Abs(new Floor(new Sub(new op(20.12), new op(56.4))));          
    EXPECT_EQ(d1->evaluate(), 37);

    // Ceiling + Floor
    d1 = new Floor(new Mult(new Ceil(new op(4.5)), new op(7.5)));
    EXPECT_EQ(d1->evaluate(), 37);

    d1 = new Ceil(new Sub(new Floor(new op(8.9)), new op(3.7)));
    EXPECT_EQ(d1->evaluate(), 5);
	
    // Abs + Ceiling + Floor
    d1 = new Abs(new Floor(new Sub(new Ceil(new op(20.12)), new op(56.4))));        EXPECT_EQ(d1->evaluate(), 36);

    d1 = new Abs(new Ceil(new Div(new Floor(new op(1.9)), new op(2.0))));
    EXPECT_EQ(d1->evaluate(), 1);
    
}

TEST(TruncTest, Truncate){
    Base* OP1 = new op(2.3);          
    Base* d1 = new Trunc(OP1);
    EXPECT_EQ(d1->stringify(), "2.300000");

    Base* OP2 = new op(14.9);
    Base* sum = new Add(OP1, OP2); // 2.3 + 14.9 = 17.2
    d1 = new Trunc(sum);
    EXPECT_EQ(d1->stringify(), "17.200000");

    Base* OP3 = new op(-5.5);
    Base* diff = new Sub(OP1, OP3); // 2.3 - (-5.5) = 7.8 - > 8.8
    d1 = new Trunc(diff);
    EXPECT_EQ(d1->stringify(), "7.800000");

    Base* mult = new Mult(OP1, d1); // 17.2 
    EXPECT_EQ(mult->stringify(), "2.300000 * 7.800000");
}

TEST(ParenTest, Parentheses){
    Base* OP1 = new op(2.3);
    Base* d1 = new Paren(OP1);
    EXPECT_EQ(d1->stringify(), "(2.300000)");

    Base* OP2 = new op(14.9);
    Base* sum = new Add(OP1, OP2); // 2.3 + 14.9 = 17.2
    d1 = new Paren(sum);
    EXPECT_EQ(d1->stringify(), "(2.300000 + 14.900000)");

    Base* OP3 = new op(-5.5);
    Base* parenOP3 = new Paren(OP3);
    Base* diff = new Sub(OP1, parenOP3); // 2.3 - (-5.5) = 7.8 - > 8.8
    d1 = new Paren(diff);
    EXPECT_EQ(d1->stringify(), "(2.300000 - (-5.500000))");

    Base* mult = new Mult(OP1, d1); // 17.2
    EXPECT_EQ(mult->stringify(), "2.300000 * (2.300000 - (-5.500000))");
}

TEST(CombinationTest, Trunc){
    Base* OP1 = new op(2.3);         
    EXPECT_EQ(OP1->stringify(), "2.300000");

    Base* OP2 = new op(14.9);
    Base* sum = new Add(OP1, OP2); // 2 + 15 = 17
    Base* d1 = new Trunc(sum);
    EXPECT_EQ(d1->stringify(), "17.200000");

    Base* OP3 = new op(5.5);
    Base* diff = new Sub(OP1, OP3); // 2.3 - 5.5 = -3.5
    Base* d2 = new Paren(diff);
    EXPECT_EQ(d2->stringify(), "(2.300000 - 5.500000)");

    Base* mult = new Mult(d1, d2); // 17.2 
    EXPECT_EQ(mult->stringify(), "17.200000 * (2.300000 - 5.500000)");
}	

int main() {
::testing::InitGoogleTest();
return RUN_ALL_TESTS();
}
