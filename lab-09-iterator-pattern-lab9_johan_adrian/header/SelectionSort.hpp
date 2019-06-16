#ifndef __SELECTION_SORT_HPP__
#define __SELECTION_SORT_HPP__
#include "sort.hpp"
#include "container.hpp"
using namespace std;

class Sort;
class Container;
class SelectionSort: public Sort {
    public:
       void sort(Container* container);
};
#endif
