# Visitor Pattern

> Author: Brian Crites ([@brrcrites](https://github.com/brrcrites))

**You *must* work in a group of two for this lab**

## The Visitor Class

In this lab you will create a visitor pattern which, when paired with your `PreorderIterator` class from the previous lab will be used to count the number of each type of element within an expression. To do this, you will need to create a single `CountVisitor` class which can be paired with a `PreorderIterator` to visit each node in an expression tree and count them. The below code is truncated, and the full code has been provided in visitor.hpp.

```c++
class CountVisitor {
    private:
        // Composite Pattern Tracking Members
        int ops;
        int rands;
        ...
        int sub;
        int pow;
       
        // Decorator Pattern Tracking Members
        int ceil;
        int floor;
        ...
        int trunc;
        int paren;

    public:
        CountVisitor();

        // Composite Pattern Visit Functions
        void visit_op();
        int op_count();
        void visit_rand();
        int rand_count();
        ...
        void visit_sub();
        int sub_count();
        void visit_pow();
        int pow_count();

        // Decorator Pattern Visit Functions
        void visit_ceil();
        int ceil_count();
        void visit_floor();
        int floor_count();
        ...
        void visit_trunc();
        int trunc_count();
        void visit_paren();
        int paren_count();
};
```

There is one function for visiting each type of node in the expression tree, and another for retrieving the count of the node types that have been visited. 

## Modifying the Expression Tree Elements

In addition to completing the functionality for the above visitor class, you will also need to modify all the classes that can exist in an expression tree to allow for the `CountVisitor` to access them. You should add the function `void accept(CountVisitor*)` to the necessary classes which will then call the appropriate function within the `CountVisitor`.

## Submission

To receive credit for this lab you must show an example program to your TA that demonstrates the full functionality of this pattern, including any interactions with other patterns. You must also show your TA the tests that you have created for validating that your classes are functioning correctly.

