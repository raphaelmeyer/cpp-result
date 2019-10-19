#include <testing.h>

#include "result.h"

namespace {

using namespace rm;

Feature feature{
  "Different types for result and error",
  {
    Scenario{"default construction", []{
      Result<int, std::string> result;

      Require(result.is_err(), Equals(true));
      Require(result.err(), Equals(std::string{}));

      Require(result.is_ok(), Equals(false));
    }},
  }
};

} // namespace
