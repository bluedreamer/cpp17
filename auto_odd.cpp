#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <typeinfo>

int main(int argc, char *argv[])
{
   int a{42};
   auto b{42};
   auto c = {42};
   auto d{42,43,44};

   std::cout << "a=" << typeid(a).name() << std::endl;
   std::cout << "b=" << typeid(b).name() << std::endl;
   std::cout << "c=" << typeid(c).name() << std::endl;
   std::cout << "d=" << typeid(d).name() << std::endl;
   return 0;
}


