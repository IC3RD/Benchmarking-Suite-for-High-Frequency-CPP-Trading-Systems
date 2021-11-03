#ifndef CPPDESIGNPATTERNSLOWLATENCY_DEBUG_H
#define CPPDESIGNPATTERNSLOWLATENCY_DEBUG_H

class debug {
// Macro to print things for debugging purposes.
#define DEBUG(x)                         \
  do {                                   \
    std::cout << "> " << x << std::endl; \
  } while (0)
};

#endif  // CPPDESIGNPATTERNSLOWLATENCY_DEBUG_H
