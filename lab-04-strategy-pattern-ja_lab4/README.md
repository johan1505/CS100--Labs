# Strategy Pattern

> Author: Jimmy Tran, Brian Crites ([@brrcrites](https://github.com/brrcrites))

In this lab you will create a strategy pattern for sorting a collection of expression trees by their `evaluate()` value, which you will pair with a different containers to see how strategies can be paired different clients through an interface to create an easily extendable system. This lab requires a completed composite pattern from the previous lab, so you should begin by copying you or your partners code from the previous assignment into your new repo, making sure it compiles correctly, and running your tests to make sure everything is still functioning correctly.

## Container Classes

You will start this lab by creating two expression tree containers: one that uses a vector to hold your trees (class `VectorContainer`) and one that uses a standard list (class `ListContainer`). Each of these container classes should be able to hold any amount of different expressions each of which can be of any size. You will implement them both as subclasses of the following `Container` abstract base class, which has been provided to you in container.h. You should create each one independently, creating tests for them using the google test framework before moving on. Each container should be it’s own commit with a proper commit message. Optionally you can create each one as a branch and merge it in once it has been completed.

```c++
class Container {
    protected:
        Sort* sort_function;

    public:
        /* Constructors */
        Container() : sort_function(nullptr) { };
        Container(Sort* function) : sort_function(function) { };

        /* Non Virtual Functions */
        void set_sort_function(Sort* sort_function); // set the type of sorting algorithm

        /* Pure Virtual Functions */
        // push the top pointer of the tree into container
        virtual void add_element(Base* element) = 0;
        // iterate through trees and output the expressions (use stringify())
        virtual void print() = 0;
        // calls on the previously set sorting-algorithm. Checks if sort_function is not
        // null, throw exception if otherwise
        virtual void sort() = 0;

        /* Functions Needed to Sort */
        //switch tree locations
        virtual void swap(int i, int j) = 0;
        // get top ptr of tree at index i
        virtual Base* at(int i) = 0;
        // return container size
        virtual int size() = 0;
};
```

Notice that our Container abstract base class does not have any actual STL containers because it leaves the impelementation details of the container to the subclasses. You **must use the homogeneous interface above for your sort functions, and you are only allowed to manipulate the containers through this interface, not directly**. This will allow you to extend and change the underlying functionality without having to change anything that interfaces with it.

## Sorting Classes

In addition to the containers you will also create two sort functions capable of sorting your containers, one that uses the [selection sort](https://www.mathbits.com/MathBits/CompSci/Arrays/Selection.htm) algorithm and one that uses the [bubble sort](https://www.mathbits.com/MathBits/CompSci/Arrays/Bubble.htm) algorithm (you may adapt this code when writing your sort functions). They should both be implemented as subclasses of the `Sort` base class below which has been provided. You should create each one independently, creating tests for them using the google test framework before moving on. Each sort class should be it's own commit with it’s own proper commit message. When creating tests for these sort classes, make sure you test them with each of the containers you developed previously, and with a number of different expression trees.

```c++
class Sort {
    public:
        /* Constructors */
        Sort();

        /* Pure Virtual Functions */
        virtual void sort(Container* container) = 0;
};
```

**Note:** your container class requires a reference to your sorting class and vice-versa, a situation known as a circular dependency. Due to the way the C++ compiler works, resolving circular dependencies will require you to use [forward declarations](http://www.umich.edu/~eecs381/handouts/IncompleteDeclarations.pdf) and compile your classes as object files by seperating the class declarations (header) from the class definitions (source) and adding the source files to your CMakeLists.txt. 

You must test all the combinations of containers and sorting objects together using googletest. The following code serves as a basic test for using the SelectionSort class to sort a VectorContainer, but you should create a full test suite for each class and the appropriate class combinations.

## Unit Testing

For this lab you are not required to mocks for the different classes, you can instead use the composite classes from your previous lab directly. Because your sort objects are paired with a container, you will also need build and test your container classes before you can build and test your sort classes. Make sure to test all the functions of the container class (except the sort functions) before moving on to developing the sorting classes. The unit tests for the container class may look something like this:

```c++
TEST(VectorContainerTestSet, SwapTest) {
    // Setup the elements under test
    Op* seven = new Op(7);
    VectorContainer* test_container = new VectorContainer();

    // Exercise some functionality of hte test elements
    test_container->add_element(seven);

    // Assert that the container has at least a single element
    // otherwise we are likely to cause a segfault when accessing
    ASSERT_EQ(test_container->size(), 1);
    EXPECT_EQ(test_container->at(0)->evaluate(), 7);
}
```

Testing the sorting classes will require combining them with a container class and testing the combination, since the sort function utilizes the container interface to perform its actions. We could develop special mocks using the container interface that simulates a container and has additional functionality for reporting the sorting classes effectively (number of swap function calls for instanace) but for this lab you can simply use the containers directly.

```c++
TEST(SortTestSet, SelectionSortTest) {
    Op* seven = new Op(7);
    Op* four = new Op(4);
    Mult* TreeA = new Mult(seven, four);

    Op* three = new Op(3);
    Op* two = new Op(2);
    Add* TreeB = new Add(three, two);

    Op* ten = new Op(10);
    Ope* six = new Op(6);
    Sub* TreeC = new Sub(ten, six);

    VectorContainer* container = new VectorContainer();
    container->add_element(TreeA);
    container->add_element(TreeB);
    container->add_element(TreeC);

    ASSERT_EQ(container->size(), 3);
    EXPECT_EQ(container->at(0)->evaluate(), 28);
    EXPECT_EQ(container->at(1)->evaluate(), 5);
    EXPECT_EQ(container->at(2)->evaluate(), 4);

    container->set_sort_function(new SelectionSort());
    container->sort();

    ASSERT_EQ(container->size(), 3);
    EXPECT_EQ(container->at(0)->evaluate(), 4);
    EXPECT_EQ(container->at(1)->evaluate(), 5);
    EXPECT_EQ(container->at(2)->evaluate(), 28);
}
```

## Submission

To receive credit for this lab you must show an example program to your TA that demonstrates the full functionality of this pattern, including any interactions with other patterns. You must also show your TA the tests that you have created for validating that your classes are functioning correctly.
