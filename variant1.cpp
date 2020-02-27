#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <variant>

int main(int argc, char *argv[])
{
   std::variant<int, double, char> a{42};
   std::variant<double, char, int> b{42};

   std::cout << "a index=" << a.index() << std::endl;
   std::cout << "b index=" << b.index() << std::endl;
   //std::cout << (a==b) << std::endl;

   return 0;
}


