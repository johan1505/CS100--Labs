# Iterator Pattern

> Author: Brian Crites ([@brrcrites](https://github.com/brrcrites))

**You *must* work in a group of two for this lab**

In this you will implement an Iterator pattern which is capable of accessing each element of the expression tree you created in previous labs independently. It should be compatible with every type of element that has been previously developed for use in your expression tree including operators, operands, and decorator modifiers. 

## Modification of Expression Tree Classes

In the previous labs there was no requirement that the children of the expression tree be accessible externally. These objects were typically given their children during construction, and the ability to access them and modify them later was not necessary. While there are a number of different ways to implement the iterator and collection interaction (making it a friend class, modifying encapsulation, etc.) in this exercise we will extend the interface of the `Base` class to create "standard" accessor functions that can be used by the iterators we are going to create. Add the following pure virtual functions to your `Base` class.

```c++
    virtual Base* get_left() = 0;
    virtual Base* get_right() = 0;
```

You will then need to create implementations for these functions in all the classes that inherit from this `Base` class and make up the possible nodes in your expression tree. Subclasses with two children will return the appropriate child for each function call, subclasses with one child will return that child in the `get_left()` function and return a `nullptr` when `get_right()` is called, and subclasses with no children will return a `nullptr` for both functions.

## The Iterator Interface

All iterators that we create (for iterating over the expression tree classes or otherwise) will follow the same interface. Use the following as the interface defining class for the rest of the iterators that you create in this lab.

```c++
class Iterator {
    protected:
        Base* self_ptr;

    public:
        Iterator(Base* ptr) { this->self_ptr = ptr; }

        /* Sets up the iterator to start at the beginning of traversal */
        virtual void first() = 0;
        
        /* Move onto the next element */
        virtual void next() = 0;
    
        /* Returns if you have finished iterating through all elements */
        virtual bool is_done() = 0;

        /* Return the element the iterator is currently at */
        virtual Base* current() = 0;
};
```

If we were creating a base class for all iterators in a large system, we would likely leave off the protected data member and any non-default constructors since there would be unlikely to be any data that was consistent across all classes in a large system. However, because we are only creating iterators for the expression tree classes in this course we can save oursevles some coding by adding these additional features to the interface defining class.

## The Composite Iterators

In order to be able to iterate over the various objects that might be included in an expression tree we need to create three distinct iterators, each of which implements the interface from the class above.

* `BinaryIterator`: will be used to iterate over expression tree classes with two children. This means it's `first` will initialize to the left child, and its `next` will cycle from left child, to right child, then to nothing.
* `UnaryIterator`: will be used to iterate over expression tree classes with one child. This means it's `first` will initialize to the only child, and its `next` will cycle from the only child to nothing.
* `NullIterator`: will be used to iterate over expression tree classes with no children. In this special case the `is_done()` function will always return `true` and the `current()` function will always return `nullptr`. The `first()` and `next()` functions don't do anything.

## Iterator Creation in Expression Tree Classes

The above iterators are capable of traversing every type of expression tree class that has been developed so far. In order to allow a client to request the iterator from the expression tree class, rather than having it try and guess whic one to use, you'll need to extend the `Base` class with the following function.

```c++
    virtual Iterator* create_iterator() = 0;
```

You will then need to override this function in all classes which inherit from `Base` (which represents all the expression tree classes). By overriding this function in all the subclasses of `Base` you are tieing that particular for of iteration to that particular class, and its expected that the client will always perform an iteration over an element in an express tree by asking the particular element for an iterator directly. This is helpful in our system, as the accessors we added to the `Base` class earlier return `nullptr` in many cases, and having to constantly screen for the return of these `nullptr` would be annoying.

**Note:** depending on your particular implementation the addition of the `Iterator` class into your `Base` class derivatives may create a new circular dependency. If you find that after the additions you have compilation errors because of unknown classes, this is likely the issue and you should take the same steps you did in previous labs to remedy them.

## The Preorder Iterator

Finally, you will need to create an iterator capable of traversing each of the expression tree objects. In this case you will be creating an iterator capable of performing a preorder traversal named `PreorderIterator`, which there are some details about in the lecture slides. The `PreorderIterator` has an additional `stack<Iterator*>` internal data member which is used to keep track of the expression tree traversal. The rest of the `PreorderIterator` fucntions should be implemented as follows.

```c++
void PreorderIterator::first() {
    // Empty the stack (just in case we had something leftover from another run). Create
    // an iterator for the Base* that was passed into the PreorderIterator constructor.
    // Initialize that iterator and push it onto the stack.
}

void PreorderIterator::next() {
    // Create an iterator for the current() of the iterator on the top of the stack
    // Initialize the iterator and push it onto the stack. As long as the top iterator 
    // on the stack is_done, pop it off the stack and then advance whatever iterator is
    // now on top of the stack
}

bool PreorderIterator::is_done() {
    // Return true if there are no more elements on the stack to iterate
}

Base* PreorderIterator::current() {
    // Return the current for the top iterator in the stack
}
```

**Note:** the method above ignores the node used to initialize the traversal when iterating. Because of this, you should create a dummy root node above the intended root node to allow for a full traversal. This dummy root node is equivalent to a base decorator object which simply passes through the `evaluate()` and `stringify()` functions, so if you implemented that class previously you can use it here.

## Submission

To receive credit for this lab you must show an example program to your TA that demonstrates the full functionality of this pattern, including any interactions with other patterns. You must also show your TA the tests that you have created for validating that your classes are functioning correctly.

