#include "../header/VectorContainer.hpp"
#include "../header/base.hpp"
#include "../header/sort.hpp"

void VectorContainer::add_element(Base* element) {
      v.push_back(element); 
      return;
}

void VectorContainer:: print() {
     if (v.size() == 0){
         cout << "Error: vector container is empty" << endl;
         return;
     }
     cout << v.at(0)->stringify();
     for (unsigned i = 1 ; i < v.size(); ++i){
          cout << " " << v.at(i)->stringify();
     }
     return;
 }

void VectorContainer::sort(){
     if (sort_function == nullptr){
         cout << "Error: sort_function not set" << endl;
     }
     else {
         sort_function->sort(this);
     }
     return;
}


void VectorContainer::swap(int i, int j) {
     if (v.size() == 0){
         cout << "Error: vector container is empty" << endl;
         return;
     }
     else if ((i < 0 || i >= v.size()) || (j < 0 || j >= v.size())){
             cout << "Error: parameters out of bounds" << endl;
             return;
     }
     Base* temp = v.at(i);
     v.at(i) = v.at(j);
     v.at(j) = temp;
     return;
}

Base* VectorContainer::at(int i){
      if (v.size() == 0){
          cout << "Error: vector container is empty" << endl;
	  return nullptr;
      }
      else if (i < 0 || i >= v.size()){
              cout << "Error: parameter out of bounds" << endl;
              return nullptr;
      }
      else {
           return v.at(i);
      }
}

int VectorContainer::size() {
    return v.size();
}
