#include "__simd.hpp"

template <typename T> struct UnClosure<T, _Simd, _Simd> {
  const simd<T> &operand;
  simd<T> res;
  simd<bool> pred;
  using reg_type = typename _Vreg<T>::regtype;
  using op_type = void (*)(reg_type &, reg_type);
  using mask_op_type = void (*)(reg_type &, reg_type, vv_bool);
  using zmask_op_type = void (*)(reg_type &, reg_type, vv_bool);
  using setp_op_type = void (*)(reg_type &, reg_type, reg_type);
  op_type op;
  mask_op_type mop;
  zmask_op_type zop;
  __mlu_func__ UnClosure(const simd<T> &oprand, const op_type &op,
                         const mask_op_type &mop, const zmask_op_type &zop)
      : operand{oprand}, op{op}, mop(mop), zop(zop) {}

  __mlu_func__ void eval(simd<T> &dst) const {
    op(dst.get_reg(), operand.get_reg());
  }
  __mlu_func__ void meval(simd<T> &dst, simd<bool> &p) const {
    mop(dst.get_reg(), operand.get_reg(), p.get_reg());
  }
  __mlu_func__ void zeval(simd<T> &dst, simd<bool> &p) const {
    zop(dst.get_reg(), operand.get_reg(), p.get_reg());
  }
};

template <typename T> struct BinClosure<T, _Simd, _Simd> {
  const simd<T> &left;
  const simd<T> &right;
  simd<T> res;
  simd<bool> pred;
  using reg_type = typename _Vreg<T>::regtype;
  using op_type = void (*)(reg_type &, reg_type, reg_type);
  using mask_op_type = void (*)(reg_type &, reg_type, reg_type, vv_bool);
  using zmask_op_type = void (*)(reg_type &, reg_type, reg_type, vv_bool);
  using setp_op_type = void (*)(vv_bool &, reg_type, reg_type);
  op_type op;
  mask_op_type mop;
  zmask_op_type zop;
  setp_op_type sop;
  __mlu_func__ BinClosure(const simd<T> &l, const simd<T> &r, const op_type &op,
                          const mask_op_type &mop, const zmask_op_type &zop,
                          const setp_op_type &sop)
      : left(l), right(r), op(op), mop(mop), zop(zop), sop(sop) {}

  __mlu_func__ void eval(simd<T> &dst) const {
    op(dst.get_reg(), left.get_reg(), right.get_reg());
  }

  __mlu_func__ void meval(simd<T> &dst, simd<bool> &p) const {
    mop(dst.get_reg(), left.get_reg(), right.get_reg(), p.get_reg());
  }

  __mlu_func__ void zeval(simd<T> &dst, simd<bool> &p) const {
    zop(dst.get_reg(), left.get_reg(), right.get_reg(), p.get_reg());
  }

  __mlu_func__ void setp_eval(simd<bool> &dst) const {
    if constexpr (sop == nullptr) {
      eval(res);
      __vv_setp_ne(pred.get_reg(), res.get_reg(), T(0));
    } else {
      sop(pred.get_reg(), right.get_reg(), left);
    }
  }
};

template <typename T> struct BinClosure<T, _Simd, _Scalar> {
  const simd<T> &left;
  const T right;
  simd<T> res;
  simd<bool> pred;
  using reg_type = typename _Vreg<T>::regtype;
  using op_type = void (*)(reg_type &, reg_type, T);
  using mask_op_type = void (*)(reg_type &, reg_type, T, vv_bool);
  using zmask_op_type = void (*)(reg_type &, reg_type, T, vv_bool);
  using setp_op_type = void (*)(vv_bool &, reg_type, T);
  op_type op;
  mask_op_type mop;
  zmask_op_type zop;
  setp_op_type sop;
  __mlu_func__ BinClosure(const simd<T> &l, const T r, const op_type &op,
                          const mask_op_type &mop, const zmask_op_type &zop,
                          const setp_op_type &sop)
      : left(l), right(r), op(op), mop(mop), zop(zop), sop(sop) {}

  __mlu_func__ void eval(simd<T> &dst) const {
    op(dst.get_reg(), left.get_reg(), right);
  }

  __mlu_func__ void meval(simd<T> &dst, simd<bool> &p) const {
    mop(dst.get_reg(), left.get_reg(), right, p.get_reg());
  }

  __mlu_func__ void zeval(simd<T> &dst, simd<bool> &p) const {
    mop(dst.get_reg(), left.get_reg(), right, p.get_reg());
  }

  __mlu_func__ void setp_eval(simd<bool> &dst) const {
    if constexpr (sop == nullptr) {
      eval(res);
      __vv_setp_ne(pred.get_reg(), res.get_reg(), T(0));
    } else {
      sop(pred.get_reg(), right.get_reg(), left);
    }
  }
};

template <typename T> struct BinClosure<T, _Scalar, _Simd> {
  const T left;
  const simd<T> &right;
  simd<T> res;
  simd<bool> pred;
  using reg_type = typename _Vreg<T>::regtype;
  using op_type = void (*)(reg_type &, T, reg_type);
  using mask_op_type = void (*)(reg_type &, T, reg_type, vv_bool);
  using zmask_op_type = void (*)(reg_type &, T, reg_type, vv_bool);
  using setp_op_type = void (*)(vv_bool &, reg_type, T);
  op_type op;
  mask_op_type mop;
  zmask_op_type zop;
  setp_op_type sop;
  __mlu_func__ BinClosure(const T l, const simd<T> &r, const op_type &op,
                          const mask_op_type &mop, const zmask_op_type &zop,
                          const setp_op_type &sop)
      : left(l), right(r), op(op), mop(mop), zop(zop), sop(sop) {}

  __mlu_func__ void eval(simd<T> &dst) const {
    op(dst.get_reg(), left, right.get_reg());
  }

  __mlu_func__ void meval(simd<T> &dst, simd<bool> &p) const {
    mop(dst.get_reg(), left, right.get_reg(), p.get_reg());
  }

  __mlu_func__ void zeval(simd<T> &dst, simd<bool> &p) const {
    zop(dst.get_reg(), left, right.get_reg(), p.get_reg());
  }

  __mlu_func__ void setp_eval(simd<bool> &dst) const {
    if constexpr (sop == nullptr) {
      eval(res);
      __vv_setp_ne(pred.get_reg(), res.get_reg(), T(0));
    } else {
      sop(pred.get_reg(), right.get_reg(), left);
    }
  }
};

// -----------------------------------------------
// Normal Operator
// -----------------------------------------------
template <typename T>
__mlu_func__ BinClosure<T, _Simd, _Simd> operator+(const simd<T> &lhs,
                                                   const simd<T> &rhs) {
  return BinClosure<T, _Simd, _Simd>(lhs, rhs, __vv_add, __vv_add_m, __vv_add_z,
                                     nullptr);
}

template <typename T, typename V>
__mlu_func__ BinClosure<T, _Simd, _Scalar> operator+(const simd<T> &lhs,
                                                     const V &rhs) {
  return BinClosure<T, _Simd, _Scalar>(lhs, static_cast<T>(rhs), __vv_add,
                                       __vv_add_m, __vv_add_z, nullptr);
}

template <typename T, typename V>
BinClosure<T, _Simd, _Scalar> operator+(const V &lhs, const simd<T> &rhs) {
  return rhs + lhs;
}

template <template <typename, class, class> class Clousre, typename T, class L,
          class R>
__mlu_func__ BinClosure<T, _Simd, _Simd> operator+(const simd<T> &lhs,
                                                   Clousre<T, L, R> &&rhs) {
  rhs.eval(rhs.res);
  return BinClosure<T, _Simd, _Simd>(lhs, rhs.res, __vv_add, __vv_add_m,
                                     __vv_add_z, nullptr);
}

template <template <typename, class, class> class Clousre, typename T, class L,
          class R>
__mlu_func__ BinClosure<T, _Simd, _Simd> operator+(Clousre<T, L, R> &&lhs,
                                                   const simd<T> &rhs) {
  lhs.eval(lhs.res);
  return BinClosure<T, _Simd, _Simd>(lhs.res, rhs, __vv_add, __vv_add_m,
                                     __vv_add_z, nullptr);
}

template <template <typename, class, class> class Clousre, typename T, class L,
          class R, typename Liter>
__mlu_func__ BinClosure<T, _Simd, _Scalar> operator+(Clousre<T, L, R> &&lhs,
                                                     const Liter &rhs) {
  lhs.eval(lhs.res);
  return BinClosure<T, _Simd, _Scalar>(lhs.res, static_cast<T>(rhs), __vv_add,
                                       __vv_add_m, __vv_add_z, nullptr);
}

template <template <typename, class, class> class Clousre, typename T, class L,
          class R, typename Liter>
__mlu_func__ BinClosure<T, _Simd, _Scalar> operator+(const Liter &lhs,
                                                     Clousre<T, L, R> &&rhs) {
  rhs.eval(rhs.res);
  return BinClosure<T, _Simd, _Scalar>(rhs.res, static_cast<T>(lhs), __vv_add,
                                       __vv_add_m, __vv_add_z, nullptr);
}

template <template <typename, class, class> class ClosureL,
          template <typename, class, class> class ClosureR, typename T,
          class LL, class LR, class RL, class RR>
__mlu_func__ BinClosure<T, _Simd, _Simd> operator+(ClosureL<T, LL, LR> &&lhs,
                                                   ClosureR<T, RL, RR> &&rhs) {
  lhs.eval(lhs.res);
  rhs.eval(rhs.res);
  return BinClosure<T, _Simd, _Simd>(lhs.res, rhs.res, __vv_add, __vv_add_m,
                                     __vv_add_z, nullptr);
}
