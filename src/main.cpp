#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/hash2/hash_append.hpp>
#include <boost/hash2/siphash.hpp>
#include <cassert>
#include <string>
#include <iostream>
#include <ctime>

struct sip_hash
{
  std::uint64_t seed_;

  sip_hash( std::uint64_t seed ) : seed_{ seed } {}

  template<class T>
  std::size_t operator()( T const& t ) const noexcept
  {
    boost::hash2::siphash_64 h( seed_ );
    boost::hash2::hash_append( h, {}, t );
    return boost::hash2::get_integral_result<std::size_t, boost::hash2::siphash_64>( h );
  }
};

int main()
{
  sip_hash h( time( nullptr ) );
  boost::unordered_flat_map<int, int, sip_hash> map( 0, h );
  map.insert( std::pair( 1234, 4321 ) );
  std::cout << "map size is: " << map.size() << std::endl;
}
