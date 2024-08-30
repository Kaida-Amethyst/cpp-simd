#define __mlu_func__
#include "vec_interface.h"

#define LIBDEVICE_ATTRIBUTE __mlu_func__ inline
//-------------------------------------------
// Utils
// ------------------------------------------
#include <cstdint>
#include <utility>

// ------------------------------------------------------------

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

struct __vec_neg;
struct __vec_not;
struct __vec_lnot;
struct __vec_add;
struct __vec_mul;
struct __vec_sub;
struct __vec_div;
struct __vec_rem;
struct __vec_and;
struct __vec_or;
struct __vec_xor;
struct __vec_sl;
struct __vec_sr;
struct __vec_land;
struct __vec_lor;
struct __vec_lxor;
struct __vec_eq;
struct __vec_ne;
struct __vec_gt;
struct __vec_lt;
struct __vec_ge;
struct __vec_le;

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

template <typename T, TypeTag tag> struct __simd_with_mask;
template <typename T, TypeTag tag> struct __simd_with_zeromask;

template <typename T> using simd = __simd<T, TypeTraits<T>::tag>;

template <typename T>
using simd_with_mask = __simd_with_mask<T, TypeTraits<T>::tag>;

template <typename T>
using simd_with_zeromask = __simd_with_zeromask<T, TypeTraits<T>::tag>;

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

template <class Oper, typename T, typename RT>
struct BinClosure<Oper, T, _Simd, _Simd, _Null, _Null, RT> {
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

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    Oper()(dst.get_reg(), closure.operand.get_reg());
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    Oper()(dst.get_reg(), closure.operand.get_reg());
  }
};

template <class Oper, typename T, typename Dom, typename RT>
struct Expr<UnClosure<Oper, T, _Expr, Dom, RT>, RT> {
  using Closure = UnClosure<Oper, T, _Expr, Dom, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    simd<RT> tmp;
    closure.expr.eval(tmp);
    Oper()(dst.get_reg(), tmp.get_reg());
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp;
    closure.expr.eval(tmp);
    Oper()(dst.get_reg(), tmp.get_reg());
  }
};

template <class Oper, typename T, typename RT>
struct Expr<BinClosure<Oper, T, _Simd, _Simd, _Null, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Simd, _Simd, _Null, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    Oper()(dst.get_reg(), closure.left_operand.get_reg(),
           closure.right_operand.get_reg());
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    Oper()(dst.get_reg(), closure.left_operand.get_reg(),
           closure.right_operand.get_reg());
  }
};

template <class Oper, typename T, typename Dom, typename RT>
struct Expr<BinClosure<Oper, T, _Expr, _Simd, Dom, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Expr, _Simd, Dom, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    simd<RT> tmp_left;
    closure.left_expr.eval(tmp_left);
    Oper()(dst.get_reg(), tmp_left.get_reg(), closure.right_operand.get_reg());
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp_left;
    closure.left_expr.eval(tmp_left);
    Oper()(dst.get_reg(), tmp_left.get_reg(), closure.right_operand.get_reg());
  }
};

template <class Oper, typename T, typename Dom, typename RT>
struct Expr<BinClosure<Oper, T, _Simd, _Expr, _Null, Dom, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Simd, _Expr, _Null, Dom, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    simd<RT> tmp_right;
    closure.right_expr.eval(tmp_right);
    Oper()(dst.get_reg(), closure.left_operand.get_reg(), tmp_right.get_reg());
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp_right;
    closure.right_expr.eval(tmp_right);
    Oper()(dst.get_reg(), closure.left_operand.get_reg(), tmp_right.get_reg());
  }
};

template <class Oper, typename T, class DomLeft, class DomRight, typename RT>
struct Expr<BinClosure<Oper, T, _Expr, _Expr, DomLeft, DomRight, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Expr, _Expr, DomLeft, DomRight, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    simd<RT> tmp_right;
    closure.left_expr.eval(dst);
    closure.right_expr.eval(tmp_right);
    Oper()(dst.get_reg(), dst.get_reg(), tmp_right.get_reg());
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp_right;
    closure.left_expr.eval(dst);
    closure.right_expr.eval(tmp_right);
    Oper()(dst.get_reg(), dst.get_reg(), tmp_right.get_reg(), mask);
  }
};

template <class Oper, typename T, typename RT>
struct Expr<BinClosure<Oper, T, _Simd, _Scalar, _Null, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Simd, _Scalar, _Null, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    Oper()(dst.get_reg(), closure.left_operand.get_reg(),
           closure.right_operand);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    Oper()(dst.get_reg(), closure.left_operand.get_reg(), closure.right_operand,
           mask);
  }
};

template <class Oper, typename T, typename Dom, typename RT>
struct Expr<BinClosure<Oper, T, _Expr, _Scalar, Dom, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Expr, _Scalar, Dom, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    simd<RT> tmp;
    closure.left_expr.eval(tmp);
    Oper()(dst.get_reg(), tmp.get_reg(), closure.right_operand);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp;
    closure.left_expr.eval(tmp);
    Oper()(dst.get_reg(), tmp.get_reg(), closure.right_operand, mask);
  }
};

template <class Oper, typename T, typename RT>
struct Expr<BinClosure<Oper, T, _Scalar, _Simd, _Null, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Scalar, _Simd, _Null, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    Oper()(dst.get_reg(), closure.left_operand,
           closure.right_operand.get_reg());
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    Oper()(dst.get_reg(), closure.left_operand, closure.right_operand.get_reg(),
           mask);
  }
};

template <class Oper, typename T, typename Dom, typename RT>
struct Expr<BinClosure<Oper, T, _Scalar, _Expr, _Null, Dom, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Scalar, _Expr, _Null, Dom, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    simd<RT> tmp;
    closure.right_expr.eval(tmp);
    Oper()(dst.get_reg(), closure.left_operand, tmp.get_reg());
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp;
    closure.right_expr.eval(tmp);
    Oper()(dst.get_reg(), closure.left_operand, tmp.get_reg());
  }
};

template <typename T, template <typename, TypeTag> class SimdBase>
struct CommonOperation {
  using SimdType = __simd<T, TypeTraits<T>::tag>;

  LIBDEVICE_ATTRIBUTE SimdType &operator=(SimdType &other) {
    __vv_move(static_cast<SimdType &>(*this).get_reg(), other.get_reg());
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator=(Scalar &&s) {
    __vv_move(static_cast<SimdType &>(*this).get_reg(), static_cast<T>(s));
    return static_cast<SimdType &>(*this);
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE SimdType &operator=(Expr<Closure, T> &&expr) {
    expr.eval(static_cast<SimdType &>(*this));
  };
  // +=, -=, *=, /=, lnot, neg,
  /***********************************************************
   * operator+=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE SimdType &operator+=(SimdType &other) {
    __vv_add(static_cast<SimdType &>(*this).get_reg(), other.get_reg());
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator+=(Scalar &&s) {
    __vv_add(static_cast<SimdType &>(*this).get_reg(), static_cast<T>(s));
    return static_cast<SimdType &>(*this);
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE SimdType &operator+=(Expr<Closure, T> &&expr) {
    SimdType tmp;
    expr.eval(tmp);
    __vv_add(static_cast<SimdType &>(*this).get_reg(),
             static_cast<SimdType &>(*this).get_reg(), tmp.get_reg());
  };
  /***********************************************************
   * operator-=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE SimdType &operator-=(SimdType &other) {
    __vv_sub(static_cast<SimdType &>(*this).get_reg(), other.get_reg());
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator-=(Scalar &&s) {
    __vv_sub(static_cast<SimdType &>(*this).get_reg(), static_cast<T>(s));
    return static_cast<SimdType &>(*this);
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE SimdType &operator-=(Expr<Closure, T> &&expr) {
    SimdType tmp;
    expr.eval(tmp);
    __vv_sub(static_cast<SimdType &>(*this).get_reg(),
             static_cast<SimdType &>(*this).get_reg(), tmp.get_reg());
  };
  /***********************************************************
   * operator*=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE SimdType &operator*=(SimdType &other) {
    __vv_mul(static_cast<SimdType &>(*this).get_reg(), other.get_reg());
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator*=(Scalar &&s) {
    __vv_mul(static_cast<SimdType &>(*this).get_reg(), static_cast<T>(s));
    return static_cast<SimdType &>(*this);
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE SimdType &operator*=(Expr<Closure, T> &&expr) {
    SimdType tmp;
    expr.eval(tmp);
    __vv_mul(static_cast<SimdType &>(*this).get_reg(),
             static_cast<SimdType &>(*this).get_reg(), tmp.get_reg());
  };
  /***********************************************************
   * operator/=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE SimdType &operator/=(SimdType &other) {
    __vv_div(static_cast<SimdType &>(*this).get_reg(), other.get_reg());
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator/=(Scalar &&s) {
    __vv_div(static_cast<SimdType &>(*this).get_reg(), static_cast<T>(s));
    return static_cast<SimdType &>(*this);
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE SimdType &operator/=(Expr<Closure, T> &&expr) {
    SimdType tmp;
    expr.eval(tmp);
    __vv_div(static_cast<SimdType &>(*this).get_reg(),
             static_cast<SimdType &>(*this).get_reg(), tmp.get_reg());
  };
  /***********************************************************
   * operator++
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE void operator++() {
    __vv_add(static_cast<SimdType &>(*this).get_reg(),
             static_cast<SimdType &>(*this).get_reg(), (T)1);
  }
  LIBDEVICE_ATTRIBUTE void operator++(int) {
    __vv_add(static_cast<SimdType &>(*this).get_reg(),
             static_cast<SimdType &>(*this).get_reg(), (T)1);
  }
  /***********************************************************
   * operator--
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE SimdType &operator--() {
    __vv_sub(static_cast<SimdType &>(*this).get_reg(),
             static_cast<SimdType &>(*this).get_reg(), (T)1);
    return static_cast<SimdType &>(*this);
  }
  LIBDEVICE_ATTRIBUTE SimdType &operator--(int) {
    __vv_sub(static_cast<SimdType &>(*this).get_reg(),
             static_cast<SimdType &>(*this).get_reg(), (T)1);
    return static_cast<SimdType &>(*this);
  }

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
  /***********************************************************
   * operator&=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE __simd &operator&=(__simd &other) {
    __vv_and(reg, other.get_reg());
    return *this;
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE __simd &operator&=(Scalar &&s) {
    __vv_div(reg, static_cast<T>(s));
    return *this;
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE __simd &operator&=(Expr<Closure, T> &&expr) {
    __simd tmp;
    expr.eval(tmp);
    __vv_div(reg, reg, tmp.get_reg());
  };
  /***********************************************************
   * operator|=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE __simd &operator|=(__simd &other) {
    __vv_or(reg, other.get_reg());
    return *this;
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE __simd &operator|=(Scalar &&s) {
    __vv_or(reg, static_cast<T>(s));
    return *this;
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE __simd &operator|=(Expr<Closure, T> &&expr) {
    __simd tmp;
    expr.eval(tmp);
    __vv_or(reg, reg, tmp.get_reg());
  };
  /***********************************************************
   * operator^=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE __simd &operator^=(__simd &other) {
    __vv_xor(reg, other.get_reg());
    return *this;
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE __simd &operator^=(Scalar &&s) {
    __vv_xor(reg, static_cast<T>(s));
    return *this;
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE __simd &operator^=(Expr<Closure, T> &&expr) {
    __simd tmp;
    expr.eval(tmp);
    __vv_xor(reg, reg, tmp.get_reg());
  };
  /***********************************************************
   * operator<<=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE __simd &operator<<=(__simd &other) {
    __vv_sll(reg, other.get_reg());
    return *this;
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE __simd &operator<<=(Scalar &&s) {
    __vv_sll(reg, static_cast<T>(s));
    return *this;
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE __simd &operator<<=(Expr<Closure, T> &&expr) {
    __simd tmp;
    expr.eval(tmp);
    __vv_sll(reg, reg, tmp.get_reg());
  };
  /***********************************************************
   * operator>>=
   ***********************************************************/
// #pragma push_macro("LIBDEVICE_ATTRIBUTE")
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
  LIBDEVICE_ATTRIBUTE __simd &operator>>=(__simd &other) {
    if constexpr (std::is_signed<T>::value)
      __vv_sra(reg, other.get_reg());
    else
      __vv_srl(reg, other.get_reg());
    return *this;
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE __simd &operator>>=(Scalar &&s) {
    if constexpr (std::is_signed<T>::value)
      __vv_sra(reg, static_cast<T>(s));
    else
      __vv_srl(reg, static_cast<T>(s));
    return *this;
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE __simd &operator>>=(Expr<Closure, T> &&expr) {
    __simd tmp;
    expr.eval(tmp);
    if constexpr (std::is_signed<T>::value)
      __vv_sra(reg, tmp.get_reg());
    else
      __vv_srl(reg, tmp.get_reg());
  };
#pragma clang diagnostic pop
  /***********************************************************
   * operator-
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_neg, T, _Simd, _Null, T>, T>
  operator-() {
    using ClosureType = UnClosure<__vec_neg, T, _Simd, _Null, T>;
    using ExprType = Expr<ClosureType, T>;
    return ExprType(ClosureType(static_cast<__simd &>(*this)));
  }
  /***********************************************************
   * operator~
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_not, T, _Simd, _Null, T>, T>
  operator~() {
    using ClosureType = UnClosure<__vec_not, T, _Simd, _Null, T>;
    using ExprType = Expr<ClosureType, T>;
    return ExprType(ClosureType(static_cast<__simd &>(*this)));
  }
  /***********************************************************
   * operator+
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE __simd &operator+() { return *this; }
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

  LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_not, T, _Simd, _Null, bool>, bool>
  operator!() {
    using ClosureType = UnClosure<__vec_not, T, _Simd, _Null, bool>;
    using ExprType = Expr<ClosureType, bool>;
    return ExprType(ClosureType(static_cast<__simd &>(*this)));
  }

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE __simd(Expr<Closure, bool> &&expr) {
    expr.eval(*this);
  }

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE __simd &operator=(Expr<Closure, bool> &&expr) {
    expr.eval(*this);
  }
};

template <typename T> struct __simd_with_mask<T, TypeTag::Integral> {
  VRegType<T> reg;
  vv_bool mask;

  LIBDEVICE_ATTRIBUTE __simd_with_mask() = delete;

  LIBDEVICE_ATTRIBUTE __simd_with_mask(simd<bool> &pred, simd<T> &dst)
      : reg(dst.reg), mask(pred.reg) {}

  LIBDEVICE_ATTRIBUTE VRegType<T> &get_reg() { return reg; }

  LIBDEVICE_ATTRIBUTE VRegType<bool> &get_mask() { return mask; }

  LIBDEVICE_ATTRIBUTE
  __simd_with_mask(simd<T> &other) { __vv_move_m(reg, other.reg, mask); }
};

template <typename T> struct __simd_with_zeromask<T, TypeTag::Integral> {
  VRegType<T> &reg;
  vv_bool &mask;

  LIBDEVICE_ATTRIBUTE __simd_with_zeromask() = delete;

  LIBDEVICE_ATTRIBUTE __simd_with_zeromask(simd<bool> &pred, simd<T> &dst)
      : reg(dst.reg), mask(pred.reg) {}

  LIBDEVICE_ATTRIBUTE VRegType<T> &get_reg() { return reg; }

  LIBDEVICE_ATTRIBUTE VRegType<bool> &get_mask() { return mask; }
};

// ----------------------------
template <typename T>
LIBDEVICE_ATTRIBUTE simd_with_mask<T> where(const simd<bool> &pred,
                                            simd<T> &dst) {
  return simd_with_mask<T>(pred, dst);
}

template <typename T>
LIBDEVICE_ATTRIBUTE simd_with_mask<T> whereM(const simd<bool> &pred,
                                             simd<T> &dst) {
  return simd_with_mask<T>(pred, dst);
}

template <typename T>
LIBDEVICE_ATTRIBUTE simd_with_zeromask<T> whereZ(const simd<bool> &pred,
                                                 simd<T> &dst) {
  return simd_with_zeromask<T>(pred, dst);
}

/***********************************************************
 * Operations
 ***********************************************************/
/***********************************************************
 * Binary Operations: +, -, *, /, %, &, |, ^, &&, ||, >>, <<
 ***********************************************************/
#define BINARY_OPERATIRON_DEFINE(sym, vec_fun)                                 \
  template <typename T>                                                        \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<vec_fun, T, _Simd, _Simd, _Null, _Null, T>, T>           \
      operator sym(simd<T> &lhs, simd<T> &rhs) {                               \
    using ClosureType = BinClosure<vec_fun, T, _Simd, _Simd, _Null, _Null, T>; \
    using ExprType = Expr<ClosureType, T>;                                     \
    return ExprType(ClosureType(lhs, rhs));                                    \
  }                                                                            \
  template <typename T, typename ScalarT>                                      \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<vec_fun, T, _Simd, _Scalar, _Null, _Null, T>, T>         \
      operator sym(simd<T> &lhs, ScalarT && rhs) {                             \
    using ClosureType =                                                        \
        BinClosure<vec_fun, T, _Simd, _Scalar, _Null, _Null, T>;               \
    using ExprType = Expr<ClosureType, T>;                                     \
    return ExprType(ClosureType(lhs, static_cast<T>(rhs)));                    \
  }                                                                            \
  template <typename T, typename ScalarT>                                      \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<vec_fun, T, _Scalar, _Simd, _Null, _Null, T>, T>         \
      operator sym(ScalarT && lhs, simd<T> &rhs) {                             \
    using ClosureType =                                                        \
        BinClosure<vec_fun, T, _Scalar, _Simd, _Null, _Null, T>;               \
    using ExprType = Expr<ClosureType, T>;                                     \
    return ExprType(ClosureType(static_cast<T>(lhs), rhs));                    \
  }                                                                            \
  template <typename T, class Dom, typename ScalarT>                           \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<vec_fun, T, _Expr, _Scalar, Dom, _Null, T>, T>           \
      operator sym(Expr<Dom, T> lhs, ScalarT rhs) {                            \
    using ClosureType = BinClosure<vec_fun, T, _Expr, _Scalar, Dom, _Null, T>; \
    using ExprType = Expr<ClosureType, T>;                                     \
    return ExprType(ClosureType(lhs, static_cast<T>(rhs)));                    \
  }                                                                            \
  template <typename T, class Dom>                                             \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<vec_fun, T, _Expr, _Simd, Dom, _Null, T>, T>             \
      operator sym(Expr<Dom, T> lhs, simd<T> &rhs) {                           \
    using ClosureType = BinClosure<vec_fun, T, _Expr, _Simd, Dom, _Null, T>;   \
    using ExprType = Expr<ClosureType, T>;                                     \
    return ExprType(ClosureType(lhs, rhs));                                    \
  }                                                                            \
  template <typename T, class Dom, typename ScalarT>                           \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<vec_fun, T, _Scalar, _Expr, _Null, Dom, T>, T>           \
      operator sym(ScalarT lhs, Expr<Dom, T> rhs) {                            \
    using ClosureType = BinClosure<vec_fun, T, _Scalar, _Expr, _Null, Dom, T>; \
    using ExprType = Expr<ClosureType, T>;                                     \
    return ExprType(ClosureType(static_cast<T>(lhs), rhs));                    \
  }                                                                            \
  template <typename T, class Dom>                                             \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<vec_fun, T, _Simd, _Expr, _Null, Dom, T>, T>             \
      operator sym(simd<T> &lhs, Expr<Dom, T> rhs) {                           \
    using ClosureType = BinClosure<vec_fun, T, _Simd, _Expr, _Null, Dom, T>;   \
    using ExprType = Expr<ClosureType, T>;                                     \
    return ExprType(ClosureType(lhs, rhs));                                    \
  }                                                                            \
  template <typename T, class DomLeft, class DomRight>                         \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<vec_fun, T, _Expr, _Expr, DomLeft, DomRight, T>, T>      \
      operator sym(Expr<DomLeft, T> lhs, Expr<DomRight, T> rhs) {              \
    using ClosureType =                                                        \
        BinClosure<vec_fun, T, _Expr, _Expr, DomLeft, DomRight, T>;            \
    using ExprType = Expr<ClosureType, T>;                                     \
    return ExprType(ClosureType(lhs, rhs));                                    \
  }

//--------
BINARY_OPERATIRON_DEFINE(+, __vec_add);
BINARY_OPERATIRON_DEFINE(-, __vec_sub);
BINARY_OPERATIRON_DEFINE(*, __vec_mul);
BINARY_OPERATIRON_DEFINE(/, __vec_div);
// BINARY_OPERATIRON_DEFINE(%, __vec_rem);
BINARY_OPERATIRON_DEFINE(&, __vec_and);
BINARY_OPERATIRON_DEFINE(|, __vec_or);
BINARY_OPERATIRON_DEFINE(^, __vec_xor);
// BINARY_OPERATIRON_DEFINE(&&, __vec_land);
// BINARY_OPERATIRON_DEFINE(||, __vec_lor);
BINARY_OPERATIRON_DEFINE(>>, __vec_sl);
BINARY_OPERATIRON_DEFINE(<<, __vec_sr);

/***********************************************************
 * Comparison Operations: ==, !=, <, >, <=, >=
 ***********************************************************/

#define RELATION_OPERATIRON_DEFINE(sym, relation_fun)                          \
  template <typename T>                                                        \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<relation_fun, T, _Simd, _Simd, _Null, _Null, bool>,      \
           bool> operator sym(simd<T> &lhs, simd<T> &rhs) {                    \
    using ClosureType =                                                        \
        BinClosure<relation_fun, T, _Simd, _Simd, _Null, _Null, bool>;         \
    using ExprType = Expr<ClosureType, bool>;                                  \
    return ExprType(ClosureType(lhs, rhs));                                    \
  }                                                                            \
  template <typename T, typename ScalarT>                                      \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<relation_fun, T, _Simd, _Scalar, _Null, _Null, bool>,    \
           bool> operator sym(simd<T> &lhs, ScalarT && rhs) {                  \
    using ClosureType =                                                        \
        BinClosure<relation_fun, T, _Simd, _Scalar, _Null, _Null, bool>;       \
    using ExprType = Expr<ClosureType, bool>;                                  \
    return ExprType(ClosureType(lhs, static_cast<T>(rhs)));                    \
  }                                                                            \
  template <typename T, typename ScalarT>                                      \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<relation_fun, T, _Scalar, _Simd, _Null, _Null, bool>,    \
           bool> operator sym(ScalarT && lhs, simd<T> &rhs) {                  \
    using ClosureType =                                                        \
        BinClosure<relation_fun, T, _Scalar, _Simd, _Null, _Null, bool>;       \
    using ExprType = Expr<ClosureType, bool>;                                  \
    return ExprType(ClosureType(static_cast<T>(lhs), rhs));                    \
  }                                                                            \
  template <typename T, class Dom, typename ScalarT>                           \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<relation_fun, T, _Expr, _Scalar, Dom, _Null, bool>,      \
           bool> operator sym(Expr<Dom, T> lhs, ScalarT rhs) {                 \
    using ClosureType =                                                        \
        BinClosure<relation_fun, T, _Expr, _Scalar, Dom, _Null, bool>;         \
    using ExprType = Expr<ClosureType, bool>;                                  \
    return ExprType(ClosureType(lhs, static_cast<T>(rhs)));                    \
  }                                                                            \
  template <typename T, class Dom>                                             \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<relation_fun, T, _Expr, _Simd, Dom, _Null, bool>, bool>  \
      operator sym(Expr<Dom, T> lhs, simd<T> &rhs) {                           \
    using ClosureType =                                                        \
        BinClosure<relation_fun, T, _Expr, _Simd, Dom, _Null, bool>;           \
    using ExprType = Expr<ClosureType, bool>;                                  \
    return ExprType(ClosureType(lhs, rhs));                                    \
  }                                                                            \
  template <typename T, class Dom, typename ScalarT>                           \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<relation_fun, T, _Scalar, _Expr, _Null, Dom, bool>,      \
           bool> operator sym(ScalarT lhs, Expr<Dom, T> rhs) {                 \
    using ClosureType =                                                        \
        BinClosure<relation_fun, T, _Scalar, _Expr, _Null, Dom, bool>;         \
    using ExprType = Expr<ClosureType, T>;                                     \
    return ExprType(ClosureType(static_cast<T>(lhs), rhs));                    \
  }                                                                            \
  template <typename T, class Dom>                                             \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<relation_fun, T, _Simd, _Expr, _Null, Dom, bool>, bool>  \
      operator sym(simd<T> &lhs, Expr<Dom, T> rhs) {                           \
    using ClosureType =                                                        \
        BinClosure<relation_fun, T, _Simd, _Expr, _Null, Dom, bool>;           \
    using ExprType = Expr<ClosureType, bool>;                                  \
    return ExprType(ClosureType(lhs, rhs));                                    \
  }                                                                            \
  template <typename T, class DomLeft, class DomRight>                         \
  LIBDEVICE_ATTRIBUTE                                                          \
      Expr<BinClosure<relation_fun, T, _Expr, _Expr, DomLeft, DomRight, bool>, \
           bool> operator sym(Expr<DomLeft, T> lhs, Expr<DomRight, T> rhs) {   \
    using ClosureType =                                                        \
        BinClosure<relation_fun, T, _Expr, _Expr, DomLeft, DomRight, bool>;    \
    using ExprType = Expr<ClosureType, bool>;                                  \
    return ExprType(ClosureType(lhs, rhs));                                    \
  }

RELATION_OPERATIRON_DEFINE(==, __vec_eq);
RELATION_OPERATIRON_DEFINE(!=, __vec_ne);
RELATION_OPERATIRON_DEFINE(>, __vec_gt);
RELATION_OPERATIRON_DEFINE(<, __vec_lt);
RELATION_OPERATIRON_DEFINE(>=, __vec_ge);
RELATION_OPERATIRON_DEFINE(<=, __vec_le);

LIBDEVICE_ATTRIBUTE
Expr<BinClosure<__vec_and, bool, _Simd, _Simd, _Null, _Null, bool>, bool>
operator&&(simd<bool> &lhs, simd<bool> &rhs) {
  using ClosureType =
      BinClosure<__vec_and, bool, _Simd, _Simd, _Null, _Null, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_and, bool, _Expr, _Simd, Dom, _Null, bool>, bool>
    operator&&(Expr<Dom, bool> lhs, simd<bool> &rhs) {
  using ClosureType =
      BinClosure<__vec_and, bool, _Expr, _Simd, Dom, _Null, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_and, bool, _Simd, _Expr, _Null, Dom, bool>, bool>
    operator&&(simd<bool> &lhs, Expr<Dom, bool> rhs) {
  using ClosureType =
      BinClosure<__vec_and, bool, _Simd, _Expr, _Null, Dom, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class DomLeft, class DomRight>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_and, bool, _Expr, _Expr, DomLeft, DomRight, bool>,
         bool>
    operator&&(Expr<DomLeft, bool> lhs, Expr<DomRight, bool> rhs) {
  using ClosureType =
      BinClosure<__vec_and, bool, _Expr, _Expr, DomLeft, DomRight, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

LIBDEVICE_ATTRIBUTE
Expr<BinClosure<__vec_or, bool, _Simd, _Simd, _Null, _Null, bool>, bool>
operator||(simd<bool> &lhs, simd<bool> &rhs) {
  using ClosureType =
      BinClosure<__vec_or, bool, _Simd, _Simd, _Null, _Null, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_or, bool, _Expr, _Simd, Dom, _Null, bool>, bool>
    operator||(Expr<Dom, bool> lhs, simd<bool> &rhs) {
  using ClosureType =
      BinClosure<__vec_or, bool, _Expr, _Simd, Dom, _Null, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_or, bool, _Simd, _Expr, _Null, Dom, bool>, bool>
    operator||(simd<bool> &lhs, Expr<Dom, bool> rhs) {
  using ClosureType =
      BinClosure<__vec_or, bool, _Simd, _Expr, _Null, Dom, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class DomLeft, class DomRight>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_or, bool, _Expr, _Expr, DomLeft, DomRight, bool>,
         bool>
    operator||(Expr<DomLeft, bool> lhs, Expr<DomRight, bool> rhs) {
  using ClosureType =
      BinClosure<__vec_or, bool, _Expr, _Expr, DomLeft, DomRight, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

/***********************************************************
 * Unary Operations: +, -, ~, !
 ***********************************************************/
template <typename T>
LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_neg, T, _Simd, _Null, T>, T>
operator-(simd<T> &operand) {
  using ClosureType = UnClosure<__vec_neg, T, _Simd, _Null, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(operand));
}
template <typename T, class Dom>
LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_neg, T, _Expr, Dom, T>, T>
operator-(Expr<Dom, T> operand) {
  using ClosureType = UnClosure<__vec_neg, T, _Expr, Dom, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(operand));
}
template <typename T>
LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_not, T, _Simd, _Null, T>, T>
operator~(simd<T> &operand) {
  using ClosureType = UnClosure<__vec_not, T, _Simd, _Null, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(operand));
}
template <typename T, class Dom>
LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_not, T, _Expr, Dom, T>, T>
operator~(Expr<Dom, T> operand) {
  using ClosureType = UnClosure<__vec_not, T, _Expr, Dom, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(operand));
}
template <typename Clos, typename RT>
LIBDEVICE_ATTRIBUTE Expr<Clos, RT> operator+(Expr<Clos, RT> operand) {
  return operand;
}

template <class Dom>
LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_not, bool, _Expr, Dom, bool>, bool>
operator!(Expr<Dom, bool> operand) {
  using ClosureType = UnClosure<__vec_not, bool, _Expr, Dom, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(operand));
}

// Oper Definations

#define UNARY_OP(funcname, vtype)                                              \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src) {                 \
    __vv_##funcname(dst, src);                                                 \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src, vv_bool p) {      \
    __vv_##funcname##_m(dst, src, p);                                          \
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

#define UNCOMMUTABLE_BINARY_OP(funcname, vtype, stype)                         \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src1, vtype src2) {    \
    __vv_##funcname(dst, src1, src2);                                          \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src1, stype src2) {    \
    __vv_##funcname(dst, src1, src2);                                          \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, stype src1, vtype src2) {    \
    __vv_##funcname(dst, src1, src2);                                          \
  }

#define NO_SCALAR_LEFT_OP(funcname, vtype, stype)                              \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src1, vtype src2) {    \
    __vv_##funcname(dst, src1, src2);                                          \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src1, stype src2) {    \
    __vv_##funcname(dst, src1, src2);                                          \
  }

#define RELATION_OP_SETP(funcname, revfuncname, vtype, stype)                  \
  LIBDEVICE_ATTRIBUTE void operator()(vv_bool &dst, vtype src1, vtype src2) {  \
    __vv_setp_##funcname(dst, src1, src2);                                     \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(vv_bool &dst, vtype src1, stype src2) {  \
    __vv_setp_##funcname(dst, src1, src2);                                     \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(vv_bool &dst, stype src1, vtype src2) {  \
    __vv_setp_##revfuncname(dst, src2, src1);                                  \
  }

struct __vec_neg {
  UNARY_OP(neg, vv_float);
  UNARY_OP(neg, vv_int32);
  UNARY_OP(neg, vv_int8);
  UNARY_OP(neg, vv_int16);
};

struct __vec_not {
  UNARY_OP(not, vv_int32);
  UNARY_OP(not, vv_int8);
  UNARY_OP(not, vv_int16);
  UNARY_OP(not, vv_uint32);
  UNARY_OP(not, vv_uint8);
  UNARY_OP(not, vv_uint16);
  // UNARY_OP(not, vv_bool);
};

struct __vec_add {
  COMMUTABLE_BINARY_OP(add, vv_float, float);
  COMMUTABLE_BINARY_OP(add, vv_int32, int);
  COMMUTABLE_BINARY_OP(add, vv_int8, int8_t);
  COMMUTABLE_BINARY_OP(add, vv_int16, int16_t);
  COMMUTABLE_BINARY_OP(add, vv_uint32, uint32_t);
  COMMUTABLE_BINARY_OP(add, vv_uint8, uint8_t);
  COMMUTABLE_BINARY_OP(add, vv_uint16, uint16_t);
};

struct __vec_mul {
  COMMUTABLE_BINARY_OP(mul, vv_float, float);
  COMMUTABLE_BINARY_OP(mul, vv_int32, int);
  COMMUTABLE_BINARY_OP(mul, vv_int8, int8_t);
  COMMUTABLE_BINARY_OP(mul, vv_int16, int16_t);
  COMMUTABLE_BINARY_OP(mul, vv_uint32, uint32_t);
  COMMUTABLE_BINARY_OP(mul, vv_uint8, uint8_t);
  COMMUTABLE_BINARY_OP(mul, vv_uint16, uint16_t);
};

struct __vec_sub {
  UNCOMMUTABLE_BINARY_OP(sub, vv_float, float);
  UNCOMMUTABLE_BINARY_OP(sub, vv_int32, int);
  UNCOMMUTABLE_BINARY_OP(sub, vv_int8, int8_t);
  UNCOMMUTABLE_BINARY_OP(sub, vv_int16, int16_t);
  UNCOMMUTABLE_BINARY_OP(sub, vv_uint32, uint32_t);
  UNCOMMUTABLE_BINARY_OP(sub, vv_uint8, uint8_t);
  UNCOMMUTABLE_BINARY_OP(sub, vv_uint16, uint16_t);
};

struct __vec_div {
  UNCOMMUTABLE_BINARY_OP(div, vv_float, float);
  UNCOMMUTABLE_BINARY_OP(div, vv_int32, int);
  // UNCOMMUTABLE_BINARY_OP(div, vv_int8, int8_t);
  UNCOMMUTABLE_BINARY_OP(div, vv_int16, int16_t);
  UNCOMMUTABLE_BINARY_OP(div, vv_uint32, uint32_t);
  // UNCOMMUTABLE_BINARY_OP(div, vv_uint8, uint8_t);
  UNCOMMUTABLE_BINARY_OP(div, vv_uint16, uint16_t);
};

struct __vec_and {
  COMMUTABLE_BINARY_OP(and, vv_int32, int);
  COMMUTABLE_BINARY_OP(and, vv_int8, int8_t);
  COMMUTABLE_BINARY_OP(and, vv_int16, int16_t);
  COMMUTABLE_BINARY_OP(and, vv_uint32, uint32_t);
  COMMUTABLE_BINARY_OP(and, vv_uint8, uint8_t);
  COMMUTABLE_BINARY_OP(and, vv_uint16, uint16_t);
};

struct __vec_or {
  COMMUTABLE_BINARY_OP(or, vv_int32, int);
  COMMUTABLE_BINARY_OP(or, vv_int8, int8_t);
  COMMUTABLE_BINARY_OP(or, vv_int16, int16_t);
  COMMUTABLE_BINARY_OP(or, vv_uint32, uint32_t);
  COMMUTABLE_BINARY_OP(or, vv_uint8, uint8_t);
  COMMUTABLE_BINARY_OP(or, vv_uint16, uint16_t);
};

struct __vec_xor {
  COMMUTABLE_BINARY_OP(xor, vv_int32, int);
  COMMUTABLE_BINARY_OP(xor, vv_int8, int8_t);
  COMMUTABLE_BINARY_OP(xor, vv_int16, int16_t);
  COMMUTABLE_BINARY_OP(xor, vv_uint32, uint32_t);
  COMMUTABLE_BINARY_OP(xor, vv_uint8, uint8_t);
  COMMUTABLE_BINARY_OP(xor, vv_uint16, uint16_t);
};
struct __vec_sl {
  NO_SCALAR_LEFT_OP(sll, vv_int32, int);
  NO_SCALAR_LEFT_OP(sll, vv_int8, int8_t);
  NO_SCALAR_LEFT_OP(sll, vv_int16, int16_t);
  NO_SCALAR_LEFT_OP(sll, vv_uint32, uint32_t);
  NO_SCALAR_LEFT_OP(sll, vv_uint8, uint8_t);
  NO_SCALAR_LEFT_OP(sll, vv_uint16, uint16_t);
};

struct __vec_sr {
  NO_SCALAR_LEFT_OP(srl, vv_uint32, uint32_t);
  NO_SCALAR_LEFT_OP(srl, vv_uint8, uint8_t);
  NO_SCALAR_LEFT_OP(srl, vv_uint16, uint16_t);
  NO_SCALAR_LEFT_OP(sra, vv_int32, int);
  NO_SCALAR_LEFT_OP(sra, vv_int8, int8_t);
  NO_SCALAR_LEFT_OP(sra, vv_int16, int16_t);
};

struct __vec_eq {
  RELATION_OP_SETP(eq, eq, vv_float, float);
  RELATION_OP_SETP(eq, eq, vv_int32, int);
  RELATION_OP_SETP(eq, eq, vv_int8, int8_t);
  RELATION_OP_SETP(eq, eq, vv_int16, int16_t);
  RELATION_OP_SETP(eq, eq, vv_uint32, uint32_t);
  RELATION_OP_SETP(eq, eq, vv_uint8, uint8_t);
  RELATION_OP_SETP(eq, eq, vv_uint16, uint16_t);
};

struct __vec_ne {
  RELATION_OP_SETP(ne, ne, vv_float, float);
  RELATION_OP_SETP(ne, ne, vv_int32, int);
  RELATION_OP_SETP(ne, ne, vv_int8, int8_t);
  RELATION_OP_SETP(ne, ne, vv_int16, int16_t);
  RELATION_OP_SETP(ne, ne, vv_uint32, uint32_t);
  RELATION_OP_SETP(ne, ne, vv_uint8, uint8_t);
  RELATION_OP_SETP(ne, ne, vv_uint16, uint16_t);
};

struct __vec_gt {
  RELATION_OP_SETP(gt, lt, vv_float, float);
  RELATION_OP_SETP(gt, lt, vv_int32, int);
  RELATION_OP_SETP(gt, lt, vv_int8, int8_t);
  RELATION_OP_SETP(gt, lt, vv_int16, int16_t);
  RELATION_OP_SETP(gt, lt, vv_uint32, uint32_t);
  RELATION_OP_SETP(gt, lt, vv_uint8, uint8_t);
  RELATION_OP_SETP(gt, lt, vv_uint16, uint16_t);
};

struct __vec_lt {
  RELATION_OP_SETP(lt, gt, vv_float, float);
  RELATION_OP_SETP(lt, gt, vv_int32, int);
  RELATION_OP_SETP(lt, gt, vv_int8, int8_t);
  RELATION_OP_SETP(lt, gt, vv_int16, int16_t);
  RELATION_OP_SETP(lt, gt, vv_uint32, uint32_t);
  RELATION_OP_SETP(lt, gt, vv_uint8, uint8_t);
  RELATION_OP_SETP(lt, gt, vv_uint16, uint16_t);
};

struct __vec_ge {
  RELATION_OP_SETP(ge, le, vv_float, float);
  RELATION_OP_SETP(ge, le, vv_int32, int);
  RELATION_OP_SETP(ge, le, vv_int8, int8_t);
  RELATION_OP_SETP(ge, le, vv_int16, int16_t);
  RELATION_OP_SETP(ge, le, vv_uint32, uint32_t);
  RELATION_OP_SETP(ge, le, vv_uint8, uint8_t);
  RELATION_OP_SETP(ge, le, vv_uint16, uint16_t);
};

struct __vec_le {
  RELATION_OP_SETP(le, ge, vv_float, float);
  RELATION_OP_SETP(le, ge, vv_int32, int);
  RELATION_OP_SETP(le, ge, vv_int8, int8_t);
  RELATION_OP_SETP(le, ge, vv_int16, int16_t);
  RELATION_OP_SETP(le, ge, vv_uint32, uint32_t);
  RELATION_OP_SETP(le, ge, vv_uint8, uint8_t);
  RELATION_OP_SETP(le, ge, vv_uint16, uint16_t);
};
