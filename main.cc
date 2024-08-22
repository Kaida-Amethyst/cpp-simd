#include "simd.hpp"

int main() {
  simd<float> a, b, c, d;
  float t = 5.0;
  float *s = nullptr;
  a.load(s);
  b.load(s);
  c.load(s);
  d.load(s);

  d = a + b + 1.0f;
  d = d + t;
  d.store(s);
  return 0;
}
