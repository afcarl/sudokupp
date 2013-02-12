#include "tests.h"

void test(bool (*func)(void), std::string name) {
  if (!func()) {
    std::cout << "Test failed: " << name << std::endl;
  }
}
