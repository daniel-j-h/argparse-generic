#include <cstdint>

#include <string>
#include <iostream>
#include <stdexcept>

#include <boost/fusion/include/adapted.hpp>
#include <boost/fusion/include/io.hpp>

#include "generic.hpp"


// Provide your datatype and adapt it for introspecting member attributes
namespace Datatype {

  struct Request {
    std::string host;
    std::int32_t port;
  };

  // Deriving Show
  using boost::fusion::operator<<;
}

BOOST_FUSION_ADAPT_STRUCT(Datatype::Request, host, port)


// Let the compiler generate an simple argument parser for it
int main(int argc, char** argv) try {
  using namespace Datatype;
  using namespace Generic;

  const auto req = get<Request>(argc, argv, "Make Query");

  if (req)
    std::cout << req << std::endl;

} catch (const std::exception& e) {
  std::cerr << "Error: " << e.what() << std::endl;
}
