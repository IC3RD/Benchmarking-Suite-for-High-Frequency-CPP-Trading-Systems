#pragma once

class debug {
// Macro to print things for debugging purposes.
#define DEBUG(x)                         \
  do {                                   \
    std::cout << "> " << x << std::endl; \
  } while (0)
};
