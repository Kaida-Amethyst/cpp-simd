#include "__simd.hpp"

template <typename T> struct UnClosure<T, _Simd, _Simd> {
  const simd<T> &operand;
  simd<T> res;
  using reg_type = typename _Vreg<T>::regtype;
  using op_type = void (*)(reg_type &, reg_type);
  using mask_op_type = void (*)(reg_type &, reg_type, vv_bool);
  using zmask_op_type = void (*)(reg_type &, reg_type, vv_bool);
  using setp_op_type = void (*)(reg_type &, reg_type, reg_type);
  op_type op;
  mask_op_type mop;
  zmask_op_type zop;
  __mlu_func__ UnClosure(const simd<T> &oprand, const op_type &op)
      : operand{oprand}, op{op} {}

  __mlu_func__ void eval(simd<T> &dst) const {
    op(dst.get_reg(), operand.get_reg());
  }
};

template <typename T> struct BinClosure<T, _Simd, _Simd> {
  const simd<T> &left;
  const simd<T> &right;
  simd<T> res;
  using reg_type = typename _Vreg<T>::regtype;
  using op_type = void (*)(reg_type &, reg_type, reg_type);
  using mask_op_type = void (*)(reg_type &, reg_type, reg_type, vv_bool);
  using zmask_op_type = void (*)(reg_type &, reg_type, reg_type, vv_bool);
  op_type op;
  mask_op_type mop;
  zmask_op_type zop;
  __mlu_func__ BinClosure(const simd<T> &l, const simd<T> &r, const op_type &op)
      : left(l), right(r), op(op) {}

  __mlu_func__ void eval(simd<T> &dst) const {
    op(dst.get_reg(), left.get_reg(), right.get_reg());
  }
};

template <typename T> struct BinClosure<T, _Simd, _Literal> {
  const simd<T> &left;
  const T right;
  simd<T> res;
  using reg_type = typename _Vreg<T>::regtype;
  using op_type = void (*)(reg_type &, reg_type, T);
  op_type op;
  __mlu_func__ BinClosure(const simd<T> &l, const T r, const op_type &op)
      : left(l), right(r), op(op) {}

  __mlu_func__ void eval(simd<T> &dst) const {
    op(dst.get_reg(), left.get_reg(), right);
  }
};

template <typename T> struct BinClosure<T, _Literal, _Simd> {
  const T left;
  const simd<T> &right;
  simd<T> res;
  using reg_type = typename _Vreg<T>::regtype;
  using op_type = void (*)(reg_type &, T, reg_type);
  op_type op;
  __mlu_func__ BinClosure(const T l, const simd<T> &r, const op_type &op)
      : left(l), right(r), op(op) {}

  __mlu_func__ void eval(simd<T> &dst) const {
    op(dst.get_reg(), left, right.get_reg());
  }
};

// -----------------------------------------------
template <typename T>
__mlu_func__ BinClosure<T, _Simd, _Simd> operator+(const simd<T> &lhs,
                                                   const simd<T> &rhs) {
  return BinClosure<T, _Simd, _Simd>(lhs, rhs, __vv_add);
}

template <typename T, typename V>
__mlu_func__ BinClosure<T, _Simd, _Literal> operator+(const simd<T> &lhs,
                                                      const V &rhs) {
  return BinClosure<T, _Simd, _Literal>(lhs, static_cast<T>(rhs), __vv_add);
}

template <typename T, typename V>
BinClosure<T, _Simd, _Literal> operator+(const V &lhs, const simd<T> &rhs) {
  return rhs + lhs;
}

template <template <typename, class, class> class Clousre, typename T, class L,
          class R>
__mlu_func__ BinClosure<T, _Simd, _Simd> operator+(const simd<T> &lhs,
                                                   Clousre<T, L, R> &&rhs) {
  rhs.eval(rhs.res);
  return BinClosure<T, _Simd, _Simd>(lhs, rhs.res, __vv_add);
}

template <template <typename, class, class> class Clousre, typename T, class L,
          class R>
__mlu_func__ BinClosure<T, _Simd, _Simd> operator+(Clousre<T, L, R> &&lhs,
                                                   const simd<T> &rhs) {
  lhs.eval(lhs.res);
  return BinClosure<T, _Simd, _Simd>(lhs.res, rhs, __vv_add);
}

template <template <typename, class, class> class Clousre, typename T, class L,
          class R, typename Liter>
__mlu_func__ BinClosure<T, _Simd, _Literal> operator+(Clousre<T, L, R> &&lhs,
                                                      const Liter &rhs) {
  lhs.eval(lhs.res);
  return BinClosure<T, _Simd, _Literal>(lhs.res, static_cast<T>(rhs), __vv_add);
}

template <template <typename, class, class> class Clousre, typename T, class L,
          class R, typename Liter>
__mlu_func__ BinClosure<T, _Simd, _Literal> operator+(const Liter &lhs,
                                                      Clousre<T, L, R> &&rhs) {
  rhs.eval(rhs.res);
  return BinClosure<T, _Simd, _Literal>(rhs.res, static_cast<T>(lhs), __vv_add);
}

template <template <typename, class, class> class ClosureL,
          template <typename, class, class> class ClosureR, typename T,
          class LL, class LR, class RL, class RR>
__mlu_func__ BinClosure<T, _Simd, _Simd> operator+(ClosureL<T, LL, LR> &&lhs,
                                                   ClosureR<T, RL, RR> &&rhs) {
  lhs.eval(lhs.res);
  rhs.eval(rhs.res);
  return BinClosure<T, _Simd, _Simd>(lhs.res, rhs.res, __vv_add);
}
