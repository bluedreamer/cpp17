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
   Customer(const Customer &c)
      :first(c.first), last(c.last), val(c.val) 
   {
      std::cout << __PRETTY_FUNCTION__ << " OMG, I've been copied\n";
   }
   ~Customer()
   {
      std::cout << __PRETTY_FUNCTION__ << " OMG, I've been destroyed\n";
   }
   const std::string &GetFirst() const { return first; }
   std::string &GetFirst() { return first; }
   const std::string &GetLast() const { return last; }
   std::string &GetLast() { return last; }
   long GetValue() const { return val; }
   long &GetValue() { return val; }
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

template<std::size_t Idx>
//auto get(Customer &c)
decltype(auto) get(Customer &c)
{
   std::cout << __PRETTY_FUNCTION__ << std::endl;
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

template<std::size_t Idx>
//auto get(const Customer &c)
decltype(auto) get(const Customer &c)
{
   std::cout << __PRETTY_FUNCTION__ << std::endl;
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

template<std::size_t Idx>
//auto get(Customer &&c)
decltype(auto) get(Customer &&c)
{
   std::cout << __PRETTY_FUNCTION__ << std::endl;
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

int main(int argc, char *argv[])
{

   Customer c{"Adrian", "Smith", 103};
   auto [f,l,v] = c;
   std::cout << "f/l/v: " << f << ' ' << l << ' ' << v << std::endl;

   auto &[f2, l2, v2] = c;
   //auto &&[f2, l2, v2] = c;
   auto s{std::move(f2)};
   f2 = "Ringo";
   v2+=10;
   std::cout << "f2/l2/v2: " << f2 << ' ' << l2 << ' ' << v2 << std::endl;
   std::cout << "c: " << c.GetFirst() << ' ' << c.GetLast() << ' ' << c.GetValue() << std::endl;
   std::cout << "s: " << s << std::endl;

   return 0;
}
