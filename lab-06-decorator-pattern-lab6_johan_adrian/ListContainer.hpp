#ifndef __LISTCONTAINER_HPP__
#define __LISTCONTAINER_HPP__

#include "container.hpp"
#include "sort.hpp"
#include "base.hpp"
#include <list>
#include <iterator>
#include <iostream>

using namespace std;


class Sort;
class Base;

class ListContainer: public Container {
	private:
		list<Base*> list1;
	public: 
        void add_element(Base* element);
	void print();
        void sort();
        void swap(int i, int j);
	Base* at(int i);
        int size();
};

#endif
