#include <math.h>

double squareRoot(const double n) {
  double b = sqrt(n);
  if (b != b) {  // nan check
    return -1.0;
  } else {
    return sqrt(n);
  }
}
