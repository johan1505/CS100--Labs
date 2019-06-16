#include "gtest/gtest.h"
#include "base.hpp"
#include "add.hpp"
#include "op.hpp"
#include "mult.hpp"
#include "div.hpp"
#include "pow.hpp"
#include "sub.hpp"
#include "Decorator.hpp"
#include "Ceiling.hpp"
#include "Floor.hpp"
#include "Abs.hpp"
#include <string>
using namespace std;

TEST(CeilingTest, Ceiling){
    Base* OP = new op(2.3);           // Small positive number
    Base* d1 = new Ceiling(OP);
    EXPECT_EQ(d1->evaluate(), 3.0);

    Base* OP2 = new op(25678.13); //Large positive number
    d1 = new Ceiling(OP2);
    EXPECT_EQ(d1->evaluate(), 25679);

    Base* OP3 = new op(-5.5);     //Small negative number
    d1 = new Ceiling(OP3);
    EXPECT_EQ(d1->evaluate(), -5);

    Base* OP4 = new op(-654321.9);// Large negative number
    d1 = new Ceiling(OP4);
    EXPECT_EQ(d1->evaluate(), -654321);

    Base* sum = new Add(OP, OP2); // 2.3 + 25678.13 = 25680.43 -> 25681
    d1 = new Ceiling(sum);
    EXPECT_EQ(d1->evaluate(), 25681);

    Base* diff = new Sub(OP, OP3); // 2.3 - (-5.5) = 7.8 - > 8
    d1 = new Ceiling(diff);
    EXPECT_EQ(d1->evaluate(), 8);

    Base* mult = new Mult(OP3, OP); // -5.5 * 2.3 = -12.65
    d1 = new Ceiling(mult);
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

TEST(CeilingFloorAbsTest, CeilingFlorrAbs){
    Base* d1 = nullptr;

    // Abs + Ceiling
    d1 = new Abs(new Ceiling(new op(-2.3)));          
    EXPECT_EQ(d1->evaluate(), 3);

    d1 = new Abs(new Ceiling(new Add(new op(4.5), new op(-6.4))));          
    EXPECT_EQ(d1->evaluate(), 1);

    // Abs + Floor
    d1 = new Abs(new Floor(new op(-56.898)));
    EXPECT_EQ(d1->evaluate(), 57);
    
    d1 = new Abs(new Floor(new Sub(new op(20.12), new op(56.4))));          
    EXPECT_EQ(d1->evaluate(), 37);

    // Abs + Ceiling + Floor
    d1 = d1 = new Abs(new Floor(new Sub(new Ceiling(new op(20.12)), new op(56.4))));     
    EXPECT_EQ(d1->evaluate(), 36);
}

int main() {
::testing::InitGoogleTest();
return RUN_ALL_TESTS();
}
