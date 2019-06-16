#ifndef __BUBBLE_SORT_HPP__
#define __BUBBLE_SORT_HPP__
#include "sort.hpp"
#include "container.hpp"
using namespace std;

class Sort;
class Container;
class BubbleSort : public Sort {
    public:
       void sort(Container* container);
};
#endif
