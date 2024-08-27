#include "simd.hpp"

int main() {
  simd<float> a, b, c;
  float t = 5.0;
  float s[] = {1, 2, 3};
  a.load(s);
  b.load(s);

  c = (2 + a) + (a + t);
  c.store(s);

  simd<float> d = a + c;
  return 0;
}
