#include "../header/SelectionSort.hpp"
#include "../header/container.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

void SelectionSort::sort(Container* container){
      if (container->size() == 0) {
	  cout << "Container is empty" << endl;
          return;
      }
      int i, j, min;
      int size = container->size();
      for (i = 0; i < size - 1; ++i){
           min = i;                 // initialize to subscript of first element
           for (j = i + 1; j < size; j++){   // locate smallest between positions 1 and i. {
                 if (container->at(j)->evaluate() < container->at(min)->evaluate()){
                 	min = j;
		 }
	   }
           container->swap(i,min);
      }
   return; 
}
