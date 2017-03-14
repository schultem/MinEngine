#include <string>
#include <sstream>
#include <memory>

namespace patch
{
  template < typename T > std::string to_string( const T& n )
  {
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
  }

  template<typename T, typename... Args> std::unique_ptr<T> make_unique(Args&&... args) 
  {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
}