#ifndef __VECTOR_CONTAINTER__
#define __VECTOR_CONTAINER__

#include "sort.hpp"
#include "base.hpp"
#include "container.hpp"
#include <vector>
#include <iostream>
using namespace std;

class Sort;
class Base;
class VectorContainer : public Container {
	private:
	  vector<Base*> v;
	public:
	  void add_element(Base* element);
	  void print();
	  void sort();
	  void swap(int i, int j);
	  Base* at(int i);
	  int size();
};
#endif
