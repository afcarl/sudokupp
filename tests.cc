#include "tests.h"

#include <stdexcept>

std::string test_name;

void deftest(std::string name) {
  test_name = name;
}

std::string testname() {
  return test_name;
}

void assert(bool pred, std::string desc) {
  if (!pred)
    throw std::logic_error(test_name + " (" + desc + ")");
}
