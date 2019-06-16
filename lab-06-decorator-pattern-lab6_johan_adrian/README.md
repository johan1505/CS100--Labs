# Decorator Pattern

> Author: Jimmy Tran, Brian Crites ([@brrcrites](https://github.com/brrcrites))

**You *must* work in a group of two for this lab**

In this lab you will be extending the system that you have created in your Composite and Strategy Pattern labs. In this lab you will use the decorator pattern to modify both the `evaluate()` and `stringify()` functions you've previously implemented in your expression tree. For example, you may want to round the results of an expression (or the results of the subset of an expression) so you may create an expression like the following:
```
ceil(3 + 7 * 4 - 2)
```
This expression would be represented with the following tree, with the top most node being a decorator:

![Equation tree for Decorator Pattern](https://github.com/cs100/lab05-decoratorPattern/blob/master/images/decorator.png)

You can see how the ceiling function simply modifies the return of the statement, and that the return value at the top would be the ceiling of the equation below which it should transparently enclose. You will be in charge of building four separate decorator classes, three of which modify the `evaluate()` function and one which modifies the `stringify()` function. 

## Evaluate Modifying Decorators

* Ceiling (`Ceil` class): performs the `ceil()` function on whatever composite it encloses and returns that value.
* Floor (`Floor` class): performs the `floor()` function on whatever composite it encloses and returns that value.
* Absolute value (`Abs` class): performs the `abs()` function on whatever compsite it encloses and returns that value.

## Stringify Modifying Decorators

* Truncate (`Trunc` class): shortens the expression tree so that whatever compsite it encloses will report its `evaluation()` value as its `stringify()` return rather than the full expression. Ex: The tree `5+Trunc(7-4)` would `stringify()` to `5+3` if called on the root node.
* Parenthesies (`Paren` class): adds parenthesies before and after whatever composite it encloses. Ex: the tree `5+Paren(7-4)` would `stringify()` to `5+(7-4)` if called on the root node.

In order to make this system extensible (and save yourself from writing some code) you must create a decorator base class that all of the above classes inherit from. To implement the functionality of the evaluate modifying decorators you may employ the cmath library (`math.h`).

## Unit Testing

It is important that you not only test the decorator classes in combination with the composite pattern classes that you have previously developed but also that you test that the decorator objects can are capable of working with each other as composability is an important aspect of the pattern. All the decorators should be able to not only enclose every composite pattern class but should also be able to enclose each other and in any combination.

## Submission

To receive credit for this lab you must show an example program to your TA that demonstrates the full functionality of this pattern, including any interactions with other patterns. You must also show your TA the tests that you have created for validating that your classes are functioning correctly.
