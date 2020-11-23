#include "List.h"
#include <iostream>
#include <string>
#include <algorithm>


int main() {
    List<int> list;

    for (int i=1; i<11; i++)
        list.insertBack(i);

    list.reverseNth(3);

    std::stringstream s;
    list.print(s);

    std::cout << s.str() << std::endl;
    
  return 0;
}
