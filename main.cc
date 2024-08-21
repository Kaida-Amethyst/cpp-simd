#include "simd.hpp"

int main() {
  simd<float> a, b, c, d;
  float *s = nullptr;
  a.load(s);
  b.load(s);
  c.load(s);

  d = a + b + 1.0f;
  d.store(s);
  return 0;
}
