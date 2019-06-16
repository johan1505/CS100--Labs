#include "../header/container.hpp"
#include "../header/sort.hpp"
#include "../header/base.hpp"

void Container::set_sort_function(Sort* sort_function){
                this->sort_function = sort_function;
                return;
} 
