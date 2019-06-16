#include "container.hpp"
#include "sort.hpp"
#include "base.hpp"

void Container::set_sort_function(Sort* sort_function){
                this->sort_function = sort_function;
                return;
} 
