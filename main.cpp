#include <boost/unordered/unordered_flat_map.hpp>
#include <cassert>
#include <string>
#include <iostream>

int main()
{
  boost::unordered_flat_map<int, int> map;
  std::cout << "map size is: " << map.size() << std::endl;
}
