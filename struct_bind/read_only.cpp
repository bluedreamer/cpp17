#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <utility>

class Customer
{
public:
   Customer(std::string f, std::string l, long v)
      :first(std::move(f)), last(std::move(l)), val(v) {}
   std::string GetFirst() const { return first; }
   std::string GetLast() const { return last; }
   long GetValue() const { return val; }
private:
   std::string first;
   std::string last;
   long val{0};
};

template<>
struct std::tuple_size<Customer>
{
   static constexpr int value = 3; // 3 attribs on customer
};

template<>
struct std::tuple_element<2, Customer>
{
   using type = long;
};

template<std::size_t Idx>
struct std::tuple_element<Idx, Customer>
{
   using type = std::string;
};

//#define ALTVER
#ifndef ALTVER
template<std::size_t>
auto get(const Customer &c);

template<>
auto get<0>(const Customer &c)
{
   return c.GetFirst();
}
template<>
auto get<1>(const Customer &c)
{
   return c.GetLast();
}
template<>
auto get<2>(const Customer &c)
{
   return c.GetValue();
}

#else
// Alt def of get<>
template<std::size_t Idx>
auto get(const Customer &c)
{
   static_assert(Idx < std::tuple_size<Customer>::value);
   //static_assert(Idx < 3);
   if constexpr (Idx == 0)
   {
      return c.GetFirst();
   }
   else if constexpr (Idx == 1)
   {
      return c.GetLast();
   }
   else
   {
      return c.GetValue();
   }
}
#endif

int main(int argc, char *argv[])
{
   Customer c{"Adrian", "Smith", 103};

   auto [f,l,v] = c;

   std::cout << "f/l/v: " << f << ' ' << l << ' ' << v << std::endl;
   auto s{std::move(f)};
   l = "Waters";
   v+=10;
   std::cout << "f/l/v: " << f << ' ' << l << ' ' << v << std::endl;
   std::cout << "c: " << c.GetFirst() << ' ' << c.GetLast() << ' ' << c.GetValue() << std::endl;
   std::cout << "s: " << s << std::endl;
   return 0;
}


