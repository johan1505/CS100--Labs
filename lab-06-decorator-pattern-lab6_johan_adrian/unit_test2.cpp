#include "base.hpp"
#include "add.hpp"
#include "gtest/gtest.h"
#include "op.hpp"
#include "InputOpMock.hpp"
#include "mult.hpp"
#include "div.hpp"
#include "pow.hpp"
#include "sub.hpp"
#include "container.hpp"
#include "VectorContainer.hpp"
#include "ListContainer.hpp"
#include "SelectionSort.hpp"
#include "BubbleSort.hpp"
#include <string>
using namespace std;

//*******************************************JOHAN**************************************************

//Testing VectorContainer
TEST(VectorContainerTestSet, vectorContainer) {
    // Setup the elements under test
    op* eight = new op(8);
    op* four  = new op(4);
    Add* TreeA = new Add(eight, four); // 12
    Sub* TreeB = new Sub(eight, four); // 4 
    Mult* TreeC = new Mult(eight, four); // 32
    Div* TreeD = new Div(eight, four); // 2 
    Pow* TreeE = new Pow(eight, four); // 4096
    VectorContainer* test_container = new VectorContainer();
    string output;
   
   EXPECT_EQ(test_container->size(), 0);

   //Testing at() with empty vector
   testing::internal::CaptureStdout(); //captures any output from the function below
   EXPECT_EQ(test_container->at(4), nullptr);
   output = testing::internal::GetCapturedStdout(); // get the captured output and set it to a string variable
   EXPECT_EQ(output, "Error: vector container is empty\n"); // compared the output

   //Testing swap() with empty vector
   testing::internal::CaptureStdout();
   test_container->swap(0,1);
   output = testing::internal::GetCapturedStdout();
   EXPECT_EQ(output, "Error: vector container is empty\n"); 

   //Testing print() with empty vector
 
   testing::internal::CaptureStdout();
   test_container->print();
   output = testing::internal::GetCapturedStdout();
   EXPECT_EQ(output, "Error: vector container is empty\n");

    //Testing add_element, at, and evaluate functions
    test_container->add_element(eight);
    test_container->add_element(four);
    test_container->add_element(TreeA);
    test_container->add_element(TreeB);
    test_container->add_element(TreeC);
    test_container->add_element(TreeD);
    test_container->add_element(TreeE);

    //Assert that the container has at least a single element otherwise we are likely to cause a segfault when accessing
    ASSERT_EQ(test_container->size(), 7);
    EXPECT_EQ(test_container->at(0)->evaluate(), 8);
    EXPECT_EQ(test_container->at(1)->evaluate(), 4);
    EXPECT_EQ(test_container->at(2)->evaluate(), 12);
    EXPECT_EQ(test_container->at(3)->evaluate(), 4);
    EXPECT_EQ(test_container->at(4)->evaluate(), 32);
    EXPECT_EQ(test_container->at(5)->evaluate(), 2);
    EXPECT_EQ(test_container->at(6)->evaluate(), 4096);

    //Testing out of bound cases
    testing::internal::CaptureStdout();
    test_container->swap(1,7); 
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error: parameters out of bounds\n");

    testing::internal::CaptureStdout();
    Base* temp = test_container->at(100);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error: parameter out of bounds\n");   
 
    //Testing swap function
    test_container->swap(1,1); //swapping the same element
    EXPECT_EQ(test_container->at(1)->evaluate(), 4);
    test_container->swap(0,6); //swapping the first and last element
    EXPECT_EQ(test_container->at(0)->evaluate(), 4096);
    EXPECT_EQ(test_container->at(6)->evaluate(), 8); 

   //Testing print function
   testing::internal::CaptureStdout();
   test_container->print();
   output = testing::internal::GetCapturedStdout(); 
   EXPECT_EQ(output, "8.000000 ** 4.000000 4.000000 8.000000 + 4.000000 8.000000 - 4.000000 8.000000 * 4.000000 8.000000 / 4.000000 8.000000");
}

TEST(SelectionSortTest, SelectionSort_VectorContainer){
    string output;
    op* seven = new op(7);
    op* four = new op(4);
    Mult* TreeA = new Mult(seven, four);

    op* three = new op(3);
    op* two = new op(2);
    Add* TreeB = new Add(three, two);

    op* ten = new op(10);
    op* six = new op(6);
    Sub* TreeC = new Sub(ten, six);
    
    op* eight = new op(8);
    op* sixteen = new op(16);
    Div* TreeD = new Div(sixteen, eight);

    op* nine = new op(9);
    Pow* TreeE = new Pow(two,nine);
    VectorContainer* container = new VectorContainer();

    //Testing sorting an empty container
    VectorContainer* emptyContainer = new VectorContainer();
    emptyContainer->set_sort_function(new SelectionSort());
    testing::internal::CaptureStdout();
    emptyContainer->sort();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Container is empty\n");

    //Adding elements to the container
    container->add_element(TreeA);
    container->add_element(TreeB);
    container->add_element(TreeC);
    container->add_element(TreeD);
    container->add_element(TreeE);

    ASSERT_EQ(container->size(), 5);
    EXPECT_EQ(container->at(0)->evaluate(), 28);
    EXPECT_EQ(container->at(1)->evaluate(), 5);
    EXPECT_EQ(container->at(2)->evaluate(), 4);
    EXPECT_EQ(container->at(3)->evaluate(), 2);
    EXPECT_EQ(container->at(4)->evaluate(), 512);

    //Testing sort with sort_function not set
    testing::internal::CaptureStdout();
    container->sort();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error: sort_function not set\n");

    //Testing sorting algorithm
    container->set_sort_function(new SelectionSort());
    container->sort();
    ASSERT_EQ(container->size(), 5);
    EXPECT_EQ(container->at(0)->evaluate(), 2);
    EXPECT_EQ(container->at(1)->evaluate(), 4);
    EXPECT_EQ(container->at(2)->evaluate(), 5); 
    EXPECT_EQ(container->at(3)->evaluate(), 28);
    EXPECT_EQ(container->at(4)->evaluate(), 512);
}

TEST(BubbleSortTest, BubbleSort_VectorContainer){
    string output;
    op* seven = new op(7);
    op* four  = new op(4) ;
    Mult* TreeA = new Mult(seven, four);

    op* three = new op(3);
    op* two = new op(2);
    Add* TreeB = new Add(three, two);

    op* ten = new op(10);
    op* six = new op(6);
    Sub* TreeC = new Sub(ten, six);

    op* eight = new op(8);
    op* sixteen = new op(16);
    Div* TreeD = new Div(sixteen, eight);

    op* nine = new op(9);
    Pow* TreeE = new Pow(two,nine);
    VectorContainer* container = new VectorContainer();

    // Testing sorting an empty container
    VectorContainer* emptyContainer = new VectorContainer();
    emptyContainer->set_sort_function(new BubbleSort());
    testing::internal::CaptureStdout();
    emptyContainer->sort();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Container is empty\n");
  
   //Adding elements to the container
    container->add_element(TreeA);
    container->add_element(TreeB);
    container->add_element(TreeC);
    container->add_element(TreeD);
    container->add_element(TreeE);

    ASSERT_EQ(container->size(), 5);
    EXPECT_EQ(container->at(0)->evaluate(), 28);
    EXPECT_EQ(container->at(1)->evaluate(), 5);
    EXPECT_EQ(container->at(2)->evaluate(), 4);
    EXPECT_EQ(container->at(3)->evaluate(), 2);
    EXPECT_EQ(container->at(4)->evaluate(), 512);

    //Testing sort with sort_function not set
    testing::internal::CaptureStdout();
    container->sort();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error: sort_function not set\n");
    
    //Testing sorting algorithm
    container->set_sort_function(new BubbleSort());
    container->sort();
    ASSERT_EQ(container->size(), 5);
    EXPECT_EQ(container->at(0)->evaluate(), 2);
    EXPECT_EQ(container->at(1)->evaluate(), 4);
    EXPECT_EQ(container->at(2)->evaluate(), 5);
    EXPECT_EQ(container->at(3)->evaluate(), 28);
    EXPECT_EQ(container->at(4)->evaluate(), 512);
}

//*************************************************ADRIAN***************************************


TEST(ListContainerTestSet, ListContainer) {
    //Setup the elements under test
    op* eight = new op(8);
    op* four  = new op(4);
    Add* TreeA = new Add(eight, four);  //12
    Sub* TreeB = new Sub(eight, four);  //4
    Mult* TreeC = new Mult(eight, four);  //32
    Div* TreeD = new Div(eight, four);  //2
    Pow* TreeE = new Pow(eight, four);  //4096
    ListContainer* test_container = new ListContainer();
    string output;

   EXPECT_EQ(test_container->size(), 0);

   //Testing at() with empty vector
   testing::internal::CaptureStdout(); //captures any output from the function below
   EXPECT_EQ(test_container->at(4), nullptr);
   output = testing::internal::GetCapturedStdout();  //get the captured output and set it to a string variable
   EXPECT_EQ(output, "Error: list container is empty\n");  //compared the output

   //Testing swap() with empty vector
   testing::internal::CaptureStdout();
   test_container->swap(0,1);
   output = testing::internal::GetCapturedStdout();
   EXPECT_EQ(output, "Error: list container is empty\n");

   //Testing print() with empty vector

   testing::internal::CaptureStdout();
   test_container->print();
   output = testing::internal::GetCapturedStdout();
   EXPECT_EQ(output, "Error: list container is empty\n");

    //Testing add_element, at, and evaluate functions
    test_container->add_element(eight);
    test_container->add_element(four);
    test_container->add_element(TreeA);
    test_container->add_element(TreeB);
    test_container->add_element(TreeC);
    test_container->add_element(TreeD);
    test_container->add_element(TreeE);

    //assert that the container has at least a single element otherwise we are likely to cause a segfault when accessing
    ASSERT_EQ(test_container->size(), 7);
    EXPECT_EQ(test_container->at(0)->evaluate(), 8); //change back to 8
    EXPECT_EQ(test_container->at(1)->evaluate(), 4);
    EXPECT_EQ(test_container->at(2)->evaluate(), 12);
    EXPECT_EQ(test_container->at(3)->evaluate(), 4);
    EXPECT_EQ(test_container->at(4)->evaluate(), 32);
    EXPECT_EQ(test_container->at(5)->evaluate(), 2);
    EXPECT_EQ(test_container->at(6)->evaluate(), 4096); // change back to 4096

    //Testing out of bound cases
    testing::internal::CaptureStdout();
    test_container->swap(1,7);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error: parameters out of bounds\n");

    testing::internal::CaptureStdout();
    Base* temp = test_container->at(100);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error: parameter out of bounds\n");

    //Testing swap function
    test_container->swap(1,1); //swapping the same element
    EXPECT_EQ(test_container->at(1)->evaluate(), 4); 
    test_container->swap(0,6); //swapping the first and last element
    EXPECT_EQ(test_container->at(0)->evaluate(), 4096);
    EXPECT_EQ(test_container->at(6)->evaluate(), 8);

   //Testing print function
   testing::internal::CaptureStdout();
   test_container->print();
   output = testing::internal::GetCapturedStdout();
   EXPECT_EQ(output, "8.000000 ** 4.000000 4.000000 8.000000 + 4.000000 8.000000 - 4.000000 8.000000 * 4.000000 8.000000 / 4.000000 8.000000");
}

TEST(SelectionSortTest, SelectionSort_ListContainer){
    string output;
    op* seven = new op(7);
    op* four = new op(4);
    Mult* TreeA = new Mult(seven, four);

    op* three = new op(3);
    op* two = new op(2);
    Add* TreeB = new Add(three, two);

    op* ten = new op(10);
    op* six = new op(6);
    Sub* TreeC = new Sub(ten, six);

    op* eight = new op(8);
    op* sixteen = new op(16);
    Div* TreeD = new Div(sixteen, eight);

    op* nine = new op(9);
    Pow* TreeE = new Pow(two,nine);
    ListContainer* container = new ListContainer();

    //Testing sorting an empty container
    ListContainer* emptyContainer = new ListContainer();
    emptyContainer->set_sort_function(new SelectionSort());
    testing::internal::CaptureStdout();
    emptyContainer->sort();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Container is empty\n");
    
    //Adding elements to the container
    container->add_element(TreeA);
    container->add_element(TreeB);
    container->add_element(TreeC);
    container->add_element(TreeD);
    container->add_element(TreeE);
    
    ASSERT_EQ(container->size(), 5);
    EXPECT_EQ(container->at(0)->evaluate(), 28);
    EXPECT_EQ(container->at(1)->evaluate(), 5);
    EXPECT_EQ(container->at(2)->evaluate(), 4);
    EXPECT_EQ(container->at(3)->evaluate(), 2);
    EXPECT_EQ(container->at(4)->evaluate(), 512);
    
    //Testing sort with sort_function not set
    testing::internal::CaptureStdout();
    container->sort();
    output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "Error: sort_function not set\n");

    //Testing sorting algorithm
    container->set_sort_function(new SelectionSort());
    container->sort();
    ASSERT_EQ(container->size(), 5);
    EXPECT_EQ(container->at(0)->evaluate(), 2);
    EXPECT_EQ(container->at(1)->evaluate(), 4);
    EXPECT_EQ(container->at(2)->evaluate(), 5);
    EXPECT_EQ(container->at(3)->evaluate(), 28);
    EXPECT_EQ(container->at(4)->evaluate(), 512);
}

TEST(BubbleSortTest, BubbleSort_ListContainer){
    op* seven = new op(7);
    op* four = new op(4);
    Mult* TreeA = new Mult(seven, four);

    op* three = new op(3);
    op* two = new op(2);
    Add* TreeB = new Add(three, two);

    op* ten = new op(10);
    op* six = new op(6);
    Sub* TreeC = new Sub(ten, six);

    op* eight = new op(8);
    op* sixteen = new op(16);
    Div* TreeD = new Div(sixteen, eight);

    op* nine = new op(9);
    Pow* TreeE = new Pow(two,nine);
    ListContainer* container = new ListContainer();

    container->add_element(TreeA);
    container->add_element(TreeB);
    container->add_element(TreeC);
    container->add_element(TreeD);
    container->add_element(TreeE);

    ASSERT_EQ(container->size(), 5);
    EXPECT_EQ(container->at(0)->evaluate(), 28);
    EXPECT_EQ(container->at(1)->evaluate(), 5);
    EXPECT_EQ(container->at(2)->evaluate(), 4);
    EXPECT_EQ(container->at(3)->evaluate(), 2);
    EXPECT_EQ(container->at(4)->evaluate(), 512);

    container->set_sort_function(new BubbleSort());
    container->sort();

    ASSERT_EQ(container->size(), 5);
    EXPECT_EQ(container->at(0)->evaluate(), 2);
    EXPECT_EQ(container->at(1)->evaluate(), 4);
    EXPECT_EQ(container->at(2)->evaluate(), 5);
    EXPECT_EQ(container->at(3)->evaluate(), 28);
    EXPECT_EQ(container->at(4)->evaluate(), 512);
} 


int main() {
::testing::InitGoogleTest();
return RUN_ALL_TESTS();
}
