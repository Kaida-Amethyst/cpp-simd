#include "simd.hpp"

// int main() {
//   simd<float> a, b, c;
//   float t = 5.0;
//   float s[] = {1, 2, 3};
//   a.load(s);
//   b.load(s);
//
//   c = (2 + a) + (a + t);
//   c.store(s);
//
//   simd<float> d = a + c;
//   return 0;
// }

#include <iostream>

template <typename T> void print() {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

struct __fma {
  LIBDEVICE_ATTRIBUTE void operator()(simd<float> &dst, simd<float> &a,
                                      simd<float> &b, simd<float> &c) {
    std::cout << "fma " << dst.reg.regNum << " " << a.reg.regNum << " "
              << b.reg.regNum << " " << c.reg.regNum << std::endl;
  }
  // LIBDEVICE_ATTRIBUTE void operator()(vv_float &dst, vv_float a, vv_float b,
  //                                     vv_float c) {
  //   std::cout << "fma " << dst.regNum << " " << a.regNum << " " << b.regNum
  //             << " " << c.regNum << std::endl;
  // }
};

template <typename... Args>
Expr<FuncClosure<__fma, float, Args...>, float> fma(Args &&...args) {
  using ClosureType = FuncClosure<__fma, float, Args...>;
  using ExprType = Expr<ClosureType, float>;
  return ExprType(ClosureType(std::forward<Args>(args)...));
}

int main() {
  simd<float> a, b, c;
  simd<float> d = fma(a + b, b, c);
  return 0;
}
