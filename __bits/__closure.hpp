#pragma once
#include "__oper.hpp"
#include "__simd.hpp"

template <class Oper, typename T> struct UnClosure<Oper, T, _Simd, _Simd> {
  simd<T> &operand;
  simd<T> res;
  simd<bool> pred;
  __mlu_func__ UnClosure(simd<T> &oprand) : operand{oprand} {}

  __mlu_func__ void eval(simd<T> &dst) {
    Oper(dst.get_reg(), operand.get_reg());
  }
};

template <class Oper, typename T> struct BinClosure<Oper, T, _Simd, _Simd> {
  simd<T> &left;
  simd<T> &right;
  simd<T> res;
  simd<bool> pred;
  __mlu_func__ BinClosure(simd<T> &l, simd<T> &r) : left(l), right(r) {}
  __mlu_func__ void eval(simd<T> &dst) {
    Oper()(dst.get_reg(), left.get_reg(), right.get_reg());
  }
};

template <class Oper, typename T> struct BinClosure<Oper, T, _Simd, _Scalar> {
  simd<T> &left;
  T right;
  simd<T> res;
  simd<bool> pred;
  __mlu_func__ BinClosure(simd<T> &l, T r) : left(l), right(r) {}
  __mlu_func__ void eval(simd<T> &dst) {
    Oper()(dst.get_reg(), left.get_reg(), right);
  }
};

template <class Oper, typename T> struct BinClosure<Oper, T, _Scalar, _Simd> {
  T left;
  simd<T> &right;
  simd<T> res;
  simd<bool> pred;
  __mlu_func__ BinClosure(T l, simd<T> &r) : left(l), right(r) {}
  __mlu_func__ void eval(simd<T> &dst) {
    Oper()(dst.get_reg(), left, right.get_reg());
  }
};

// -----------------------------------------------
// Normal Operator
// -----------------------------------------------
template <typename T>
__mlu_func__ BinClosure<__vec_add, T, _Simd, _Simd> operator+(simd<T> &lhs,
                                                              simd<T> &rhs) {
  return BinClosure<__vec_add, T, _Simd, _Simd>(lhs, rhs);
}

template <typename T, typename V>
__mlu_func__ BinClosure<__vec_add, T, _Simd, _Scalar> operator+(simd<T> &lhs,
                                                                V &rhs) {
  return BinClosure<__vec_add, T, _Simd, _Scalar>(lhs, static_cast<T>(rhs));
}

template <typename T, typename V>
BinClosure<__vec_add, T, _Simd, _Scalar> operator+(V &lhs, simd<T> &rhs) {
  return rhs + lhs;
}

template <template <class, typename, class, class> class Clousre, class Oper,
          typename T, class L, class R>
__mlu_func__ BinClosure<__vec_add, T, _Simd, _Simd>
operator+(simd<T> &lhs, Clousre<Oper, T, L, R> &&rhs) {
  rhs.eval(rhs.res);
  return BinClosure<__vec_add, T, _Simd, _Simd>(lhs, rhs.res);
}

template <template <class Oper, typename, class, class> class Clousre,
          class Oper, typename T, class L, class R>
__mlu_func__ BinClosure<__vec_add, T, _Simd, _Simd>
operator+(Clousre<Oper, T, L, R> &&lhs, simd<T> &rhs) {
  lhs.eval(lhs.res);
  return BinClosure<__vec_add, T, _Simd, _Simd>(lhs.res, rhs);
}

template <template <class, typename, class, class> class Clousre, class Oper,
          typename T, class L, class R, typename Scalar>
__mlu_func__ BinClosure<__vec_add, T, _Simd, _Scalar>
operator+(Clousre<Oper, T, L, R> &&lhs, Scalar &&rhs) {
  lhs.eval(lhs.res);
  return BinClosure<__vec_add, T, _Simd, _Scalar>(lhs.res, static_cast<T>(rhs));
}

template <template <class, typename, class, class> class Clousre, class Oper,
          typename T, class L, class R, typename Scalar>
__mlu_func__ BinClosure<__vec_add, T, _Simd, _Scalar>
operator+(Scalar &&lhs, Clousre<Oper, T, L, R> &&rhs) {
  rhs.eval(rhs.res);
  return BinClosure<__vec_add, T, _Simd, _Scalar>(rhs.res, static_cast<T>(lhs));
}

template <template <class, typename, class, class> class ClosureL,
          template <class, typename, class, class> class ClosureR, class Oper1,
          class Oper2, typename T, class LL, class LR, class RL, class RR>
__mlu_func__ BinClosure<__vec_add, T, _Simd, _Simd>
operator+(ClosureL<Oper1, T, LL, LR> &&lhs, ClosureR<Oper2, T, RL, RR> &&rhs) {
  lhs.eval(lhs.res);
  rhs.eval(rhs.res);
  return BinClosure<__vec_add, T, _Simd, _Simd>(lhs.res, rhs.res);
}
