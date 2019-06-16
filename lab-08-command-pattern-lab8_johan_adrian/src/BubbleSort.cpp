#include "../header/BubbleSort.hpp"
#include "../header/container.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

void BubbleSort::sort(Container* container){
      if (container->size() == 0) {
          cout << "Container is empty" << endl;
          return;
      }
      int i, j;

      for (i = 0; i < (container->size() - 1);  i++) {
           for (j = 0; (j < container->size() - i - 1); j++) {
		if(container->at(j)->evaluate() > container->at(j + 1)->evaluate()) {
			container->swap(j, j + 1);
		}
           }
      }	 	     

   return;
}

