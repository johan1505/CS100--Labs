#include "c-echo.h"

#include "gtest/gtest.h"

TEST(EchoTest, HelloWorld) {
    char* test_val[3]; test_val[0] = "./c-echo"; test_val[1] = "hello"; test_val[2] = "world";
    EXPECT_EQ("hello world", echo(3,test_val));
}

TEST(EchoTest, EmptyString) {
    char* test_val[1]; test_val[0] = "./c-echo";
    EXPECT_EQ("", echo(1,test_val));
}


TEST(EchoTest, Numbers) {
   char* test_val[4]; test_val[0] = "./c-echo"; test_val[1] = "0000"; test_val[2] = "0001"; test_val[3] = "0010";
   EXPECT_EQ("0000 0001 0010", echo(4, test_val));
}

TEST(EchoTest, BlankSpaces) {
    char* test_val[3]; test_val[0] = "./c-echo"; test_val[1] = " "; test_val[2] = " ";
    EXPECT_EQ("   ", echo(3,test_val));
}

TEST(EchoTest, SinglesNumbers) {
    char* test_val[5]; test_val[0] = "./c-echo"; test_val[1] = "0"; test_val[2] = "1"; test_val[3] = "2"; test_val[4] = " ";
    EXPECT_EQ("0 1 2  ", echo(5,test_val));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
