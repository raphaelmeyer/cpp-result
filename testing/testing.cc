#include "testing.h"

#include <iostream>
#include <map>
#include <vector>

namespace
{
  using Tests = std::map<std::string, std::vector<TestCase>>;
  Tests & tests() {
    static Tests _tests;
    return _tests;
  }

  void register_test(std::string group, TestCase const & testcase) {
    tests()[group].push_back(testcase);
  }

  bool run_tests() {
    std::size_t passed = 0;
    std::size_t failed = 0;
    for(auto const & testgroup : tests()) {
      std::cout << testgroup.first << "\n";
      for(auto const & testcase : testgroup.second) {
        std::cout << "  RUN  " << testcase.name << "\n";
        try {
          testcase.test();
          std::cout << "    \033[1;32mOK\033[0m\n";
          ++passed;
        } catch(std::exception const & e) {
          std::cout << "    \033[1;31mFAIL\033[0m : " << e.what() << "\n";
          ++failed;
        }
        std::cout << "\n";
      }
    }

    if(failed > 0) {
      std::cout << "\033[1;31mFAILED\033[0m : "
                << failed << " failed (" << passed << " passed)" << "\n";
      return false;
    }

    std::cout << "\033[1;32mPASSED\033[0m : " << passed << " passed\n";
    return true;
  }

} // namespace

TestGroup::TestGroup(std::string group, std::initializer_list<TestCase> const & testcases) {
  for(auto const & testcase : testcases) {
    register_test(group, testcase);
  }
}

int main() {
  if(not run_tests()) {
    return 1;
  }
  return 0;
}
