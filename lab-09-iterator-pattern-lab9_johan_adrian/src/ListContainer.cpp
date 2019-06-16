#include "../header/ListContainer.hpp"
#include <algorithm>


void ListContainer::add_element(Base* element) {
	list1.push_back(element);
}


void ListContainer::print() {
        if (this->size() == 0) {
		cout << "Error: list container is empty" << endl;
	}
	else {
     		cout << this->at(0)->stringify();
     		for (unsigned i = 1 ; i < list1.size(); ++i){
          		cout << " " << this->at(i)->stringify();
		}
     	}
}

void ListContainer::sort() {
        if (sort_function == nullptr) {
                cout << "Error: sort_function not set" << endl;
	}
        else {
                sort_function->sort(this);
	}
}


void ListContainer::swap(int i, int j) {
	if (this->size() == 0){
        	cout << "Error: list container is empty" << endl;
    	}
        else if (i >= this->size() || j >= this->size() || i < 0 || j < 0) {
             cout << "Error: parameters out of bounds" << endl;
        }
        else {
		list<Base*>::iterator it_i = list1.begin();
		list<Base*>::iterator it_j = list1.begin();
		Base* temp;

		advance(it_i, i);
		advance(it_j, j);
		
		temp = *it_i;
		*it_i = *it_j;
		*it_j = temp;

			
	}
}

Base* ListContainer::at(int i) {
     	if (this->size()  == 0){
       		cout << "Error: list container is empty" << endl;
        	return nullptr;
     	}
	else if (i >= this->size() || i < 0) {
             cout << "Error: parameter out of bounds" << endl;
	     return nullptr;
        }
	else {
		Base* i_pointer = nullptr;
		
		list<Base*>::iterator it = list1.begin();
		advance(it, i);

		return *it;
	}

}


int ListContainer::size() {
	return list1.size();
}


		
