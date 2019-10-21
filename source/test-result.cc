#include <testing.h>

#include "result.h"

namespace {

using namespace rm;
using namespace std::string_literals;

Feature different_types {
  "Different types for result and error",
  {
    Scenario{"default construction", []{
      Result<int, std::string> result;

      Require(result.is_err(), Equals(true));
      Require(result.err(), Equals(std::string{}));

      Require(result.is_ok(), Equals(false));
    }},

    Scenario{"initialize result by value", []{
      Result<int, std::string> result{42};

      Require(result.is_ok(), Equals(true));
      Require(result.ok(), Equals(42));

      Require(result.is_err(), Equals(false));
    }},

    Scenario{"initialize error by value", []{
      Result<int, std::string> result{"error"s};

      Require(result.is_err(), Equals(true));
      Require(result.err(), Equals("error"s));

      Require(result.is_ok(), Equals(false));
    }},

    Scenario{"initialize result with assignment", []{
      Result<std::string, int> result = "fish"s;

      Require(result.is_ok(), Equals(true));
      Require(result.ok(), Equals("fish"s));
    }},

    Scenario{"initialize error with assignment", []{
      Result<std::string, int> result = 123;

      Require(result.is_err(), Equals(true));
      Require(result.err(), Equals(123));
    }},

    Scenario{"assign result", []{
      Result<std::string, int> result;
      Require(result.is_err(), Equals(true));

      result = "snake"s;

      Require(result.is_ok(), Equals(true));
      Require(result.ok(), Equals("snake"s));
    }},

    Scenario{"assign error", []{
      Result<std::string, int> result;
      Require(result.err(), Equals(int{}));
      result = 23;

      Require(result.is_err(), Equals(true));
      Require(result.err(), Equals(23));
    }},

    Scenario{"copy construction", []{
      Result<int, std::string> const result{1337};
      auto const new_result{result};

      Require(new_result.is_ok(), Equals(true));
      Require(new_result.ok(), Equals(1337));
    }},

    Scenario{"copy or move construction", []{
      auto const new_result{Result<int, std::string>{178}};

      Require(new_result.is_ok(), Equals(true));
      Require(new_result.ok(), Equals(178));
    }},
  }
};

Feature same_type {
  "Same type for result and error",
  {
    Scenario{"default construction", []{
      Result<int, int> const result{};

      Require(result.is_err(), Equals(true));
      Require(result.err(), Equals(int{}));
    }},

    Scenario{"create result with make_ok", []{
      auto const result = make_ok<int, int>(23);

      Require(result.is_ok(), Equals(true));
      Require(result.ok(), Equals(23));
    }},

    Scenario{"create error with make_error", []{
      auto const result = make_err<int, int>(77);

      Require(result.is_err(), Equals(true));
      Require(result.err(), Equals(77));
    }},

    Scenario{"assign result", []{
      Result<int, int> result{};
      Require(result.is_err(), Equals(true));

      result = make_ok<int, int>(178);

      Require(result.is_ok(), Equals(true));
      Require(result.ok(), Equals(178));
    }},

    Scenario{"assign error", []{
      Result<std::string, std::string> result{};
      Require(result.is_err(), Equals(true));

      result = make_err<std::string, std::string>("error"s);

      Require(result.is_err(), Equals(true));
      Require(result.err(), Equals("error"s));
    }},
  }
};

} // namespace
