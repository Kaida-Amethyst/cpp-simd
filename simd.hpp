#define __mlu_func__
#define LIBDEVICE_ATTRIBUTE __mlu_func__ inline

#include "vec_interface.h"
#include <iostream>
#include <utility>

class _Simd;
class _Scalar;
class _Expr;
class _Null;

template <class Oper, typename T, class Meta, class Domin, class RT>
struct UnClosure;

template <class Oper, typename T, class MetaLeft, class MetaRight,
          class DomLeft, class DomRight, class RT>
struct BinClosure;

template <class Closure, typename RT> struct Expr;

template <typename T> struct __VRegTypeT;
template <> struct __VRegTypeT<int> {
  using type = vv_int32;
};
template <> struct __VRegTypeT<int8_t> {
  using type = vv_int8;
};
template <> struct __VRegTypeT<int16_t> {
  using type = vv_int16;
};
template <> struct __VRegTypeT<unsigned> {
  using type = vv_uint32;
};
template <> struct __VRegTypeT<uint8_t> {
  using type = vv_uint8;
};
template <> struct __VRegTypeT<uint16_t> {
  using type = vv_uint16;
};
template <> struct __VRegTypeT<float> {
  using type = vv_float;
};
template <> struct __VRegTypeT<bool> {
  using type = vv_bool;
};

template <typename T> using VRegType = typename __VRegTypeT<T>::type;

#define UNARY_OP(funcname, dtype, stype)                                       \
  LIBDEVICE_ATTRIBUTE void operator()(dtype &dst, stype src) {                 \
    __vv_##funcname(dst, src);                                                 \
  }

#define COMMUTABLE_BINARY_OP(funcname, vtype, stype)                           \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src1, vtype src2) {    \
    __vv_##funcname(dst, src1, src2);                                          \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src1, stype src2) {    \
    __vv_##funcname(dst, src1, src2);                                          \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, stype src1, vtype src2) {    \
    __vv_##funcname(dst, src2, src1);                                          \
  }

struct __vec_neg {
  UNARY_OP(neg, vv_int32, vv_int32);
  UNARY_OP(neg, vv_float, vv_float);
};

struct __vec_add {
  COMMUTABLE_BINARY_OP(add, vv_int32, int);
  COMMUTABLE_BINARY_OP(add, vv_float, float);
};

enum class TypeTag {
  Integral,
  Floating,
  Predicate,
  // Half, Bfloat16, ...
};

template <typename T> struct TypeTraits;
template <> struct TypeTraits<int> {
  static constexpr TypeTag tag = TypeTag::Integral;
};
template <> struct TypeTraits<int8_t> {
  static constexpr TypeTag tag = TypeTag::Integral;
};
template <> struct TypeTraits<int16_t> {
  static constexpr TypeTag tag = TypeTag::Integral;
};
template <> struct TypeTraits<unsigned> {
  static constexpr TypeTag tag = TypeTag::Integral;
};
template <> struct TypeTraits<uint8_t> {
  static constexpr TypeTag tag = TypeTag::Integral;
};
template <> struct TypeTraits<uint16_t> {
  static constexpr TypeTag tag = TypeTag::Integral;
};
template <> struct TypeTraits<float> {
  static constexpr TypeTag tag = TypeTag::Floating;
};
template <> struct TypeTraits<bool> {
  static constexpr TypeTag tag = TypeTag::Predicate;
};

template <typename T, TypeTag tag> struct __simd;

template <typename T> using simd = __simd<T, TypeTraits<T>::tag>;

template <class Oper, typename T, typename RT>
struct UnClosure<Oper, T, _Simd, _Null, RT> {
  simd<T> &operand;

  LIBDEVICE_ATTRIBUTE UnClosure(simd<T> &operand) : operand(operand) {}
  // delete copy constructor
};

template <class Oper, typename T, class Dom, typename RT>
struct UnClosure<Oper, T, _Expr, Dom, RT> {
  Expr<Dom, RT> expr;

  LIBDEVICE_ATTRIBUTE UnClosure(Expr<Dom, RT> expr) : expr(expr) {}
};

template <class Oper, typename T>
struct BinClosure<Oper, T, _Simd, _Simd, _Null, _Null, T> {
  simd<T> &left_operand;
  simd<T> &right_operand;

  LIBDEVICE_ATTRIBUTE BinClosure(simd<T> &left_operand, simd<T> &right_operand)
      : left_operand(left_operand), right_operand(right_operand) {}
  // delete copy constructor
};

template <class Oper, typename T, typename RT>
struct BinClosure<Oper, T, _Simd, _Scalar, _Null, _Null, RT> {
  simd<T> &left_operand;
  T right_operand;

  LIBDEVICE_ATTRIBUTE BinClosure(simd<T> &left_operand, T right_operand)
      : left_operand(left_operand), right_operand(right_operand) {}
};

template <class Oper, typename T, typename RT>
struct BinClosure<Oper, T, _Scalar, _Simd, _Null, _Null, RT> {
  T left_operand;
  simd<T> &right_operand;

  LIBDEVICE_ATTRIBUTE BinClosure(T src1, simd<T> &src2)
      : left_operand(src1), right_operand(src2) {}
  // delete copy constructor
};

template <class Oper, typename T, class Dom, typename RT>
struct BinClosure<Oper, T, _Expr, _Scalar, Dom, _Null, RT> {
  Expr<Dom, RT> left_expr;
  T right_operand;

  LIBDEVICE_ATTRIBUTE BinClosure(Expr<Dom, RT> expr, T src2)
      : left_expr(expr), right_operand(src2) {}
};

template <class Oper, typename T, class Dom, typename RT>
struct BinClosure<Oper, T, _Scalar, _Expr, _Null, Dom, RT> {
  T left_operand;
  Expr<Dom, RT> right_expr;

  LIBDEVICE_ATTRIBUTE BinClosure(T src1, Expr<Dom, RT> expr)
      : right_expr(expr), left_operand(src1) {}
};

template <class Oper, typename T, class Dom, typename RT>
struct BinClosure<Oper, T, _Expr, _Simd, Dom, _Null, RT> {
  Expr<Dom, RT> left_expr;
  simd<T> &right_operand;

  LIBDEVICE_ATTRIBUTE BinClosure(Expr<Dom, RT> expr, simd<T> &src2)
      : left_expr(expr), right_operand(src2) {}
};

template <class Oper, typename T, class Dom, typename RT>
struct BinClosure<Oper, T, _Simd, _Expr, _Null, Dom, RT> {
  simd<T> &left_operand;
  Expr<Dom, RT> right_expr;

  LIBDEVICE_ATTRIBUTE BinClosure(simd<T> &src1, Expr<Dom, RT> expr)
      : left_operand(src1), right_expr(expr) {}
};

template <class Oper, typename T, class DomLeft, class DomRight, typename RT>
struct BinClosure<Oper, T, _Expr, _Expr, DomLeft, DomRight, RT> {
  Expr<DomLeft, RT> left_expr;
  Expr<DomRight, RT> right_expr;

  LIBDEVICE_ATTRIBUTE BinClosure(Expr<DomLeft, RT> expr1,
                                 Expr<DomRight, RT> expr2)
      : left_expr(expr1), right_expr(expr2) {}
};

template <typename T, typename... Others> struct GetFirstT {
  using type = T;
};

template <class Oper, typename T, typename RT>
struct Expr<UnClosure<Oper, T, _Simd, _Null, RT>, RT> {
  using Closure = UnClosure<Oper, T, _Simd, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    Oper()(dst.get_reg(), closure.operand.get_reg());
  }
};

template <class Oper, typename T, typename Dom, typename RT>
struct Expr<UnClosure<Oper, T, _Expr, Dom, RT>, RT> {
  using Closure = UnClosure<Oper, T, _Expr, Dom, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    simd<T> tmp;
    closure.expr.eval(tmp);
    Oper()(dst.get_reg(), tmp.get_reg());
  }
};

template <class Oper, typename T, typename RT>
struct Expr<BinClosure<Oper, T, _Simd, _Simd, _Null, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Simd, _Simd, _Null, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    Oper()(dst.get_reg(), closure.left_operand.get_reg(),
           closure.right_operand.get_reg());
  }
};

template <class Oper, typename T, typename Dom, typename RT>
struct Expr<BinClosure<Oper, T, _Expr, _Simd, Dom, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Expr, _Simd, Dom, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    simd<T> tmp_left;
    closure.left_expr.eval(tmp_left);
    Oper()(dst.get_reg(), tmp_left.get_reg(), closure.right_operand.get_reg());
  }
};

template <class Oper, typename T, typename Dom, typename RT>
struct Expr<BinClosure<Oper, T, _Simd, _Expr, _Null, Dom, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Simd, _Expr, _Null, Dom, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    simd<T> tmp_right;
    closure.right_expr.eval(tmp_right);
    Oper()(dst.get_reg(), closure.left_operand.get_reg(), tmp_right.get_reg());
  }
};

template <class Oper, typename T, class DomLeft, class DomRight, typename RT>
struct Expr<BinClosure<Oper, T, _Expr, _Expr, DomLeft, DomRight, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Expr, _Expr, DomLeft, DomRight, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    simd<T> tmp_left;
    simd<T> tmp_right;
    closure.left_expr.eval(tmp_left);
    closure.right_expr.eval(tmp_right);
    Oper()(dst.get_reg(), tmp_left.get_reg(), tmp_right.get_reg());
  }
};

template <class Oper, typename T, typename RT>
struct Expr<BinClosure<Oper, T, _Simd, _Scalar, _Null, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Simd, _Scalar, _Null, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    Oper()(dst.get_reg(), closure.left_operand.get_reg(),
           closure.right_operand);
  }
};

template <class Oper, typename T, typename Dom, typename RT>
struct Expr<BinClosure<Oper, T, _Expr, _Scalar, Dom, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Expr, _Scalar, Dom, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    simd<T> tmp;
    closure.left_expr.eval(tmp);
    Oper()(dst.get_reg(), tmp.get_reg(), closure.right_operand);
  }
};

template <class Oper, typename T, typename RT>
struct Expr<BinClosure<Oper, T, _Scalar, _Simd, _Null, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Scalar, _Simd, _Null, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    Oper()(dst.get_reg(), closure.left_operand,
           closure.right_operand.get_reg());
  }
};

template <class Oper, typename T, typename Dom, typename RT>
struct Expr<BinClosure<Oper, T, _Scalar, _Expr, _Null, Dom, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Scalar, _Expr, _Null, Dom, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    simd<T> tmp;
    closure.right_expr.eval(tmp);
    Oper()(dst.get_reg(), closure.left_operand, tmp.get_reg());
  }
};

template <typename T, template <typename, TypeTag> class SimdBase>
struct CommonOperation {
  using SimdType = __simd<T, TypeTraits<T>::tag>;

  LIBDEVICE_ATTRIBUTE SimdType &operator=(SimdType &other) {
    __vv_move(static_cast<SimdType &>(*this)->get_reg(), other.get_reg());
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator=(Scalar &&s) {
    __vv_move(static_cast<SimdType &>(*this)->get_reg(), static_cast<T>(s));
    return static_cast<SimdType &>(*this);
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE SimdType &operator=(Expr<Closure, T> &&expr) {
    expr.eval(static_cast<SimdType &>(*this));
  };
  // +=, -=, *=, /=, lnot, neg,

  // load, store
  LIBDEVICE_ATTRIBUTE void load(T *data) {
    __vv_load(static_cast<SimdType &>(*this).get_reg(), data);
  }

  LIBDEVICE_ATTRIBUTE void store(T *data) {
    __vv_store(data, static_cast<SimdType &>(*this).get_reg());
  }
};

template <typename T>
struct __simd<T, TypeTag::Integral> : public CommonOperation<T, __simd> {
  VRegType<T> reg;

  LIBDEVICE_ATTRIBUTE __simd() = default;

  LIBDEVICE_ATTRIBUTE VRegType<T> &get_reg() { return reg; }

  template <typename Scalar> LIBDEVICE_ATTRIBUTE __simd(Scalar &&s) {
    __vv_move(reg, static_cast<T>(s));
  }

  LIBDEVICE_ATTRIBUTE __simd(__simd<T, TypeTag::Integral> &other) {
    __vv_move(reg, other.reg);
  }
};

template <typename T>
struct __simd<T, TypeTag::Floating> : public CommonOperation<T, __simd> {
  VRegType<T> reg;

  LIBDEVICE_ATTRIBUTE __simd() = default;

  LIBDEVICE_ATTRIBUTE VRegType<T> &get_reg() { return reg; }

  template <class Closure> LIBDEVICE_ATTRIBUTE __simd(Expr<Closure, T> &&expr) {
    expr.eval(*this);
  }

  template <typename Scalar> LIBDEVICE_ATTRIBUTE __simd(Scalar &&s) {
    __vv_move(reg, static_cast<T>(s));
  }

  LIBDEVICE_ATTRIBUTE __simd(__simd<T, TypeTag::Floating> &other) {
    __vv_move(reg, other.reg);
  }
};

template <typename T> struct __simd<T, TypeTag::Predicate> {
  VRegType<T> reg;

  LIBDEVICE_ATTRIBUTE __simd() = default;

  LIBDEVICE_ATTRIBUTE VRegType<T> &get_reg() { return reg; }
};

// Operations
template <typename T>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_add, T, _Simd, _Simd, _Null, _Null, T>, T>
    operator+(simd<T> &lhs, simd<T> &rhs) {
  using ClosureType = BinClosure<__vec_add, T, _Simd, _Simd, _Null, _Null, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(lhs, rhs));
}

template <typename T, typename ScalarT>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_add, T, _Simd, _Scalar, _Null, _Null, T>, T>
    operator+(simd<T> &lhs, ScalarT &&rhs) {
  using ClosureType = BinClosure<__vec_add, T, _Simd, _Scalar, _Null, _Null, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(lhs, static_cast<T>(rhs)));
}

template <typename T, typename ScalarT>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_add, T, _Scalar, _Simd, _Null, _Null, T>, T>
    operator+(ScalarT &&lhs, simd<T> &rhs) {
  using ClosureType = BinClosure<__vec_add, T, _Scalar, _Simd, _Null, _Null, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(static_cast<T>(lhs), rhs));
}

template <typename T, class Dom, typename ScalarT>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_add, T, _Expr, _Scalar, Dom, _Null, T>, T>
    operator+(Expr<Dom, T> lhs, ScalarT rhs) {
  using ClosureType = BinClosure<__vec_add, T, _Expr, _Scalar, Dom, _Null, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(lhs, static_cast<T>(rhs)));
}

template <typename T, class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_add, T, _Expr, _Simd, Dom, _Null, T>, T>
    operator+(Expr<Dom, T> lhs, simd<T> &rhs) {
  using ClosureType = BinClosure<__vec_add, T, _Expr, _Simd, Dom, _Null, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(lhs, rhs));
}

template <typename T, class Dom, typename ScalarT>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_add, T, _Scalar, _Expr, _Null, Dom, T>, T>
    operator+(ScalarT lhs, Expr<Dom, T> rhs) {
  using ClosureType = BinClosure<__vec_add, T, _Scalar, _Expr, _Null, Dom, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(static_cast<T>(lhs), rhs));
}

template <typename T, class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_add, T, _Simd, _Expr, _Null, Dom, T>, T>
    operator+(simd<T> &lhs, Expr<Dom, T> rhs) {
  using ClosureType = BinClosure<__vec_add, T, _Simd, _Expr, _Null, Dom, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(lhs, rhs));
}

template <typename T, class DomLeft, class DomRight>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_add, T, _Expr, _Expr, DomLeft, DomRight, T>, T>
    operator+(Expr<DomLeft, T> lhs, Expr<DomRight, T> rhs) {
  using ClosureType =
      BinClosure<__vec_add, T, _Expr, _Expr, DomLeft, DomRight, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(lhs, rhs));
}
