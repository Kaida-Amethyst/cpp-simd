#define __mlu_func__
#include "vec_interface.h"
#include <iostream>

#define LIBDEVICE_ATTRIBUTE __mlu_func__ inline
//-------------------------------------------
// Utils
// ------------------------------------------
#include <cstdint>
#include <utility>

template <typename... Args> struct Tuple;

template <typename Head, typename... Tail> struct Tuple<Head, Tail...> {
  Head head;
  Tuple<Tail...> tails;

  LIBDEVICE_ATTRIBUTE Tuple(Head &&h, Tail &&...t)
      : head(std::forward<Head>(h)), tails(std::forward<Tail>(t)...) {}
};

template <> struct Tuple<> {
  LIBDEVICE_ATTRIBUTE Tuple() {}
};

// Tuple Size
template <typename Tuple> struct TupleSizeV;

template <template <typename...> class Meta, typename... Args>
struct TupleSizeV<Meta<Args...>> {
  static constexpr std::size_t value = sizeof...(Args);
};

template <typename TypeList> struct FrontT;
template <typename TypeList> struct PopFrontT;
template <typename NewType, typename TypeList> struct PushFrontT;
template <template <typename...> class Meta, typename Head, typename... Tail>
struct FrontT<Meta<Head, Tail...>> {
  using type = Head;
};
template <typename TypeList> using Front = typename FrontT<TypeList>::type;
template <template <typename...> class Meta, typename Head, typename... Tail>
struct PopFrontT<Meta<Head, Tail...>> {
  using type = Tuple<Tail...>;
};
template <typename TypeList>
using PopFront = typename PopFrontT<TypeList>::type;

template <template <typename...> class Meta, typename NewType,
          typename... Types>
struct PushFrontT<NewType, Meta<Types...>> {
  using type = Tuple<NewType, Types...>;
};

template <typename NewType, typename TypeList>
using PushFront = typename PushFrontT<NewType, TypeList>::type;

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

// FuncArg can be Simd, Scalar, Expr
template <class Oper, typename RT, class... FuncArgs> struct FuncClosure;

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

template <typename T> struct __vec_neg;
template <typename T> struct __vec_not;
template <typename T> struct __vec_lnot;
template <typename T> struct __vec_add;
template <typename T> struct __vec_mul;
template <typename T> struct __vec_sub;
template <typename T> struct __vec_div;
template <typename T> struct __vec_rem;
template <typename T> struct __vec_and;
template <typename T> struct __vec_or;
template <typename T> struct __vec_xor;
template <typename T> struct __vec_sl;
template <typename T> struct __vec_sr;
template <typename T> struct __vec_land;
template <typename T> struct __vec_lor;
template <typename T> struct __vec_lxor;
template <typename T> struct __vec_eq;
template <typename T> struct __vec_ne;
template <typename T> struct __vec_gt;
template <typename T> struct __vec_lt;
template <typename T> struct __vec_ge;
template <typename T> struct __vec_le;

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

/***********************************************************
 * Closure
 ***********************************************************/

/***********************************************************
 * UnClosure
 ***********************************************************/
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

/***********************************************************
 * BinClosure
 ***********************************************************/

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

/***********************************************************
 * FuncClosure
 ***********************************************************/

template <class Oper, typename RT, class... FuncArgs> struct FuncClosure {
  Tuple<FuncArgs...> args;

  LIBDEVICE_ATTRIBUTE FuncClosure(FuncArgs &&...args)
      : args(std::forward<FuncArgs>(args)...) {}
};

/***********************************************************
 * Expr
 ***********************************************************/
template <class Oper, typename T, typename RT>
struct Expr<UnClosure<Oper, T, _Simd, _Null, RT>, RT> {
  using Closure = UnClosure<Oper, T, _Simd, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) { Oper()(dst, closure.operand); }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    Oper()(dst, closure.operand);
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
    Oper()(dst, tmp);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp;
    closure.expr.eval(tmp);
    Oper()(dst, tmp);
  }
};

template <class Oper, typename T, typename RT>
struct Expr<BinClosure<Oper, T, _Simd, _Simd, _Null, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Simd, _Simd, _Null, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    Oper()(dst, closure.left_operand, closure.right_operand);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    Oper()(dst, closure.left_operand, closure.right_operand);
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
    Oper()(dst, tmp_left, closure.right_operand);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp_left;
    closure.left_expr.eval(tmp_left);
    Oper()(dst, tmp_left, closure.right_operand);
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
    Oper()(dst, closure.left_operand, tmp_right);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp_right;
    closure.right_expr.eval(tmp_right);
    Oper()(dst, closure.left_operand, tmp_right);
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
    Oper()(dst, dst, tmp_right);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp_right;
    closure.left_expr.eval(dst);
    closure.right_expr.eval(tmp_right);
    Oper()(dst, dst, tmp_right, mask);
  }
};

template <class Oper, typename T, typename RT>
struct Expr<BinClosure<Oper, T, _Simd, _Scalar, _Null, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Simd, _Scalar, _Null, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    Oper()(dst, closure.left_operand, closure.right_operand);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    Oper()(dst, closure.left_operand, closure.right_operand, mask);
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
    Oper()(dst, tmp, closure.right_operand);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp;
    closure.left_expr.eval(tmp);
    Oper()(dst, tmp, closure.right_operand, mask);
  }
};

template <class Oper, typename T, typename RT>
struct Expr<BinClosure<Oper, T, _Scalar, _Simd, _Null, _Null, RT>, RT> {
  using Closure = BinClosure<Oper, T, _Scalar, _Simd, _Null, _Null, RT>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    Oper()(dst, closure.left_operand, closure.right_operand);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    Oper()(dst, closure.left_operand, closure.right_operand, mask);
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
    Oper()(dst, closure.left_operand, tmp);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst, simd<bool> &mask) {
    simd<RT> tmp;
    closure.right_expr.eval(tmp);
    Oper()(dst, closure.left_operand, tmp);
  }
};
// transform Type
// simd<T>& -> simd<T>&
// scalar& -> scalar&
// scalar -> scalar
// Note, for: Expr<Dom, RT> -> simd<RT>
template <class T> struct TransformType {
  using type = T;
};

template <class Dom, typename RT> struct TransformType<Expr<Dom, RT>> {
  using type = simd<RT>;
};

// For Tuple<Args...>
template <typename T> struct is_expr {
  constexpr static bool value = false;
};

template <class Closure, typename RT> struct is_expr<Expr<Closure, RT>> {
  constexpr static bool value = true;
};

template <typename A1, typename... Args> struct FuncArgsTuple {
  A1 head;
  FuncArgsTuple<Args...> tails;

  // // if s1 could eval(a1)
  template <typename S1, typename... SArgs>
  LIBDEVICE_ATTRIBUTE FuncArgsTuple(Tuple<S1, SArgs...> &oriFuncArgs)
      : head(oriFuncArgs.head), tails(oriFuncArgs.tails) {}
};

template <typename T> struct FuncArgsTuple<T> {
  T head;

  template <typename S1>
  LIBDEVICE_ATTRIBUTE FuncArgsTuple(Tuple<S1> &oriFuncArgs)
      : head(oriFuncArgs.head) {}
};

template <typename NewType, typename TypeList>
struct PushFrontFromFuncArgsTupleT;

template <typename NewType, typename... Types>
struct PushFrontFromFuncArgsTupleT<NewType, FuncArgsTuple<Types...>> {
  using type = FuncArgsTuple<NewType, Types...>;
};

template <typename NewType>
struct PushFrontFromFuncArgsTupleT<NewType, Tuple<>> {
  using type = FuncArgsTuple<NewType>;
};

template <typename Head, typename... Tails>
struct TransformType<Tuple<Head, Tails...>> {
  using TransHead = typename TransformType<Head>::type;
  using TransTails = typename TransformType<Tuple<Tails...>>::type;
  using type =
      typename PushFrontFromFuncArgsTupleT<TransHead, TransTails>::type;
};

template <std::size_t N> struct GetTupleElement {
  template <template <typename...> class Meta, typename Head, typename... Tail>
  LIBDEVICE_ATTRIBUTE static auto &get(Meta<Head, Tail...> &t) {
    return GetTupleElement<N - 1>::get(t.tails);
  }

  template <typename Head, typename... Tail>
  LIBDEVICE_ATTRIBUTE static auto &getFuncArg(FuncArgsTuple<Head, Tail...> &t) {
    return GetTupleElement<N - 1>::getFuncArg(t.tails);
  }
};

template <> struct GetTupleElement<0> {
  template <template <typename...> class Meta, typename Head, typename... Tail>
  LIBDEVICE_ATTRIBUTE static auto &get(Meta<Head, Tail...> &t) {
    return t.head;
  }

  template <typename HeadT, typename... TailT>
  LIBDEVICE_ATTRIBUTE static auto &
  getFuncArg(FuncArgsTuple<HeadT, TailT...> &t) {
    return t.head;
  }
};

template <std::size_t N, template <typename...> class Meta, typename... Args>
LIBDEVICE_ATTRIBUTE auto &get(Meta<Args...> &t) {
  return GetTupleElement<N>::get(t);
}

template <std::size_t N, template <typename...> class Meta, typename... Args>
LIBDEVICE_ATTRIBUTE auto &getFuncArg(Meta<Args...> &t) {
  return GetTupleElement<N>::getFuncArg(t);
}

// apply function
template <typename F, typename RT, typename Tuple, std::size_t... I>
LIBDEVICE_ATTRIBUTE constexpr decltype(auto)
eval_func_impl(F &&f, simd<RT> &dst, Tuple &&args, std::index_sequence<I...>) {
  return std::forward<F>(f)(dst, getFuncArg<I>(std::forward<Tuple>(args))...);
}

template <class Oper, typename RT, class... FuncArgs>
struct Expr<FuncClosure<Oper, RT, FuncArgs...>, RT> {
  using Closure = FuncClosure<Oper, RT, FuncArgs...>;
  Closure closure;

  LIBDEVICE_ATTRIBUTE Expr(Closure closure) : closure(closure) {}

  LIBDEVICE_ATTRIBUTE void eval(simd<RT> &dst) {
    using TmpVarType = typename TransformType<Tuple<FuncArgs...>>::type;
    TmpVarType tmpVar(closure.args);
    eval_func_impl(Oper(), dst, tmpVar,
                   std::make_index_sequence<TupleSizeV<TmpVarType>::value>{});
  }
};

template <typename T, template <typename, TypeTag> class SimdBase>
struct CommonOperation {
  using SimdType = __simd<T, TypeTraits<T>::tag>;

  LIBDEVICE_ATTRIBUTE SimdType &operator=(SimdType &other) {
    __vv_move(static_cast<SimdType &>(*this).reg, other.reg);
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator=(Scalar &&s) {
    __vv_move(static_cast<SimdType &>(*this).reg, static_cast<T>(s));
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
    __vv_add(static_cast<SimdType &>(*this).reg, other.reg);
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator+=(Scalar &&s) {
    __vv_add(static_cast<SimdType &>(*this).reg, static_cast<T>(s));
    return static_cast<SimdType &>(*this);
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE SimdType &operator+=(Expr<Closure, T> &&expr) {
    SimdType tmp;
    expr.eval(tmp);
    __vv_add(static_cast<SimdType &>(*this).reg,
             static_cast<SimdType &>(*this).reg, tmp.reg);
  };
  /***********************************************************
   * operator-=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE SimdType &operator-=(SimdType &other) {
    __vv_sub(static_cast<SimdType &>(*this).reg, other.reg);
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator-=(Scalar &&s) {
    __vv_sub(static_cast<SimdType &>(*this).reg, static_cast<T>(s));
    return static_cast<SimdType &>(*this);
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE SimdType &operator-=(Expr<Closure, T> &&expr) {
    SimdType tmp;
    expr.eval(tmp);
    __vv_sub(static_cast<SimdType &>(*this).reg,
             static_cast<SimdType &>(*this).reg, tmp.reg);
  };
  /***********************************************************
   * operator*=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE SimdType &operator*=(SimdType &other) {
    __vv_mul(static_cast<SimdType &>(*this).reg, other.reg);
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator*=(Scalar &&s) {
    __vv_mul(static_cast<SimdType &>(*this).reg, static_cast<T>(s));
    return static_cast<SimdType &>(*this);
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE SimdType &operator*=(Expr<Closure, T> &&expr) {
    SimdType tmp;
    expr.eval(tmp);
    __vv_mul(static_cast<SimdType &>(*this).reg,
             static_cast<SimdType &>(*this).reg, tmp.reg);
  };
  /***********************************************************
   * operator/=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE SimdType &operator/=(SimdType &other) {
    __vv_div(static_cast<SimdType &>(*this).reg, other.reg);
    return static_cast<SimdType &>(*this);
  }

  template <typename Scalar>
  LIBDEVICE_ATTRIBUTE SimdType &operator/=(Scalar &&s) {
    __vv_div(static_cast<SimdType &>(*this).reg, static_cast<T>(s));
    return static_cast<SimdType &>(*this);
  };

  template <typename Closure>
  LIBDEVICE_ATTRIBUTE SimdType &operator/=(Expr<Closure, T> &&expr) {
    SimdType tmp;
    expr.eval(tmp);
    __vv_div(static_cast<SimdType &>(*this).reg,
             static_cast<SimdType &>(*this).reg, tmp.reg);
  };
  /***********************************************************
   * operator++
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE void operator++() {
    __vv_add(static_cast<SimdType &>(*this).reg,
             static_cast<SimdType &>(*this).reg, (T)1);
  }
  LIBDEVICE_ATTRIBUTE void operator++(int) {
    __vv_add(static_cast<SimdType &>(*this).reg,
             static_cast<SimdType &>(*this).reg, (T)1);
  }
  /***********************************************************
   * operator--
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE SimdType &operator--() {
    __vv_sub(static_cast<SimdType &>(*this).reg,
             static_cast<SimdType &>(*this).reg, (T)1);
    return static_cast<SimdType &>(*this);
  }
  LIBDEVICE_ATTRIBUTE SimdType &operator--(int) {
    __vv_sub(static_cast<SimdType &>(*this).reg,
             static_cast<SimdType &>(*this).reg, (T)1);
    return static_cast<SimdType &>(*this);
  }

  // load, store
  LIBDEVICE_ATTRIBUTE void load(T *data) {
    __vv_load(static_cast<SimdType &>(*this).reg, data);
  }

  LIBDEVICE_ATTRIBUTE void store(T *data) {
    __vv_store(data, static_cast<SimdType &>(*this).reg);
  }
};

template <typename T>
struct __simd<T, TypeTag::Integral> : public CommonOperation<T, __simd> {
  VRegType<T> reg;

  LIBDEVICE_ATTRIBUTE __simd() = default;

  template <typename Scalar> LIBDEVICE_ATTRIBUTE __simd(Scalar &&s) {
    __vv_move(reg, static_cast<T>(s));
  }

  template <class Closure> LIBDEVICE_ATTRIBUTE __simd(Expr<Closure, T> &&expr) {
    expr.eval(*this);
  }

  template <class Closure> LIBDEVICE_ATTRIBUTE __simd(Expr<Closure, T> &expr) {
    expr.eval(*this);
  }

  LIBDEVICE_ATTRIBUTE __simd(__simd<T, TypeTag::Integral> &other) {
    __vv_move(reg, other.reg);
  }
  /***********************************************************
   * operator&=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE __simd &operator&=(__simd &other) {
    __vv_and(reg, other.reg);
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
    __vv_div(reg, reg, tmp.reg);
  };
  /***********************************************************
   * operator|=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE __simd &operator|=(__simd &other) {
    __vv_or(reg, other.reg);
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
    __vv_or(reg, reg, tmp.reg);
  };
  /***********************************************************
   * operator^=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE __simd &operator^=(__simd &other) {
    __vv_xor(reg, other.reg);
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
    __vv_xor(reg, reg, tmp.reg);
  };
  /***********************************************************
   * operator<<=
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE __simd &operator<<=(__simd &other) {
    __vv_sll(reg, other.reg);
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
    __vv_sll(reg, reg, tmp.reg);
  };
  /***********************************************************
   * operator>>=
   ***********************************************************/
// #pragma push_macro("LIBDEVICE_ATTRIBUTE")
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
  LIBDEVICE_ATTRIBUTE __simd &operator>>=(__simd &other) {
    if constexpr (std::is_signed<T>::value)
      __vv_sra(reg, other.reg);
    else
      __vv_srl(reg, other.reg);
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
      __vv_sra(reg, tmp.reg);
    else
      __vv_srl(reg, tmp.reg);
  };
#pragma clang diagnostic pop
  /***********************************************************
   * operator-
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_neg<T>, T, _Simd, _Null, T>, T>
  operator-() {
    using ClosureType = UnClosure<__vec_neg<T>, T, _Simd, _Null, T>;
    using ExprType = Expr<ClosureType, T>;
    return ExprType(ClosureType(static_cast<__simd &>(*this)));
  }
  /***********************************************************
   * operator~
   ***********************************************************/
  LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_not<T>, T, _Simd, _Null, T>, T>
  operator~() {
    using ClosureType = UnClosure<__vec_not<T>, T, _Simd, _Null, T>;
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

  template <class Closure> LIBDEVICE_ATTRIBUTE __simd(Expr<Closure, T> &&expr) {
    expr.eval(*this);
  }

  template <class Closure> LIBDEVICE_ATTRIBUTE __simd(Expr<Closure, T> &expr) {
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

  LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_not<T>, T, _Simd, _Null, bool>, bool>
  operator!() {
    using ClosureType = UnClosure<__vec_not<T>, T, _Simd, _Null, bool>;
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
BINARY_OPERATIRON_DEFINE(+, __vec_add<T>);
BINARY_OPERATIRON_DEFINE(-, __vec_sub<T>);
BINARY_OPERATIRON_DEFINE(*, __vec_mul<T>);
BINARY_OPERATIRON_DEFINE(/, __vec_div<T>);
// BINARY_OPERATIRON_DEFINE(%, __vec_rem<T>);
BINARY_OPERATIRON_DEFINE(&, __vec_and<T>);
BINARY_OPERATIRON_DEFINE(|, __vec_or<T>);
BINARY_OPERATIRON_DEFINE(^, __vec_xor<T>);
// BINARY_OPERATIRON_DEFINE(&&, __vec_land<T>);
// BINARY_OPERATIRON_DEFINE(||, __vec_lor<T>);
BINARY_OPERATIRON_DEFINE(>>, __vec_sl<T>);
BINARY_OPERATIRON_DEFINE(<<, __vec_sr<T>);

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

RELATION_OPERATIRON_DEFINE(==, __vec_eq<T>);
RELATION_OPERATIRON_DEFINE(!=, __vec_ne<T>);
RELATION_OPERATIRON_DEFINE(>, __vec_gt<T>);
RELATION_OPERATIRON_DEFINE(<, __vec_lt<T>);
RELATION_OPERATIRON_DEFINE(>=, __vec_ge<T>);
RELATION_OPERATIRON_DEFINE(<=, __vec_le<T>);

LIBDEVICE_ATTRIBUTE
Expr<BinClosure<__vec_and<bool>, bool, _Simd, _Simd, _Null, _Null, bool>, bool>
operator&&(simd<bool> &lhs, simd<bool> &rhs) {
  using ClosureType =
      BinClosure<__vec_and<bool>, bool, _Simd, _Simd, _Null, _Null, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_and<bool>, bool, _Expr, _Simd, Dom, _Null, bool>,
         bool>
    operator&&(Expr<Dom, bool> lhs, simd<bool> &rhs) {
  using ClosureType =
      BinClosure<__vec_and<bool>, bool, _Expr, _Simd, Dom, _Null, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_and<bool>, bool, _Simd, _Expr, _Null, Dom, bool>,
         bool>
    operator&&(simd<bool> &lhs, Expr<Dom, bool> rhs) {
  using ClosureType =
      BinClosure<__vec_and<bool>, bool, _Simd, _Expr, _Null, Dom, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class DomLeft, class DomRight>
LIBDEVICE_ATTRIBUTE Expr<
    BinClosure<__vec_and<bool>, bool, _Expr, _Expr, DomLeft, DomRight, bool>,
    bool>
operator&&(Expr<DomLeft, bool> lhs, Expr<DomRight, bool> rhs) {
  using ClosureType =
      BinClosure<__vec_and<bool>, bool, _Expr, _Expr, DomLeft, DomRight, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

LIBDEVICE_ATTRIBUTE
Expr<BinClosure<__vec_or<bool>, bool, _Simd, _Simd, _Null, _Null, bool>, bool>
operator||(simd<bool> &lhs, simd<bool> &rhs) {
  using ClosureType =
      BinClosure<__vec_or<bool>, bool, _Simd, _Simd, _Null, _Null, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_or<bool>, bool, _Expr, _Simd, Dom, _Null, bool>, bool>
    operator||(Expr<Dom, bool> lhs, simd<bool> &rhs) {
  using ClosureType =
      BinClosure<__vec_or<bool>, bool, _Expr, _Simd, Dom, _Null, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<BinClosure<__vec_or<bool>, bool, _Simd, _Expr, _Null, Dom, bool>, bool>
    operator||(simd<bool> &lhs, Expr<Dom, bool> rhs) {
  using ClosureType =
      BinClosure<__vec_or<bool>, bool, _Simd, _Expr, _Null, Dom, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

template <class DomLeft, class DomRight>
LIBDEVICE_ATTRIBUTE Expr<
    BinClosure<__vec_or<bool>, bool, _Expr, _Expr, DomLeft, DomRight, bool>,
    bool>
operator||(Expr<DomLeft, bool> lhs, Expr<DomRight, bool> rhs) {
  using ClosureType =
      BinClosure<__vec_or<bool>, bool, _Expr, _Expr, DomLeft, DomRight, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(lhs, rhs));
}

/***********************************************************
 * Unary Operations: +, -, ~, !
 ***********************************************************/
template <typename T>
LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_neg<T>, T, _Simd, _Null, T>, T>
operator-(simd<T> &operand) {
  using ClosureType = UnClosure<__vec_neg<T>, T, _Simd, _Null, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(operand));
}
template <typename T, class Dom>
LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_neg<T>, T, _Expr, Dom, T>, T>
operator-(Expr<Dom, T> operand) {
  using ClosureType = UnClosure<__vec_neg<T>, T, _Expr, Dom, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(operand));
}
template <typename T>
LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_not<T>, T, _Simd, _Null, T>, T>
operator~(simd<T> &operand) {
  using ClosureType = UnClosure<__vec_not<T>, T, _Simd, _Null, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(operand));
}
template <typename T, class Dom>
LIBDEVICE_ATTRIBUTE Expr<UnClosure<__vec_not<T>, T, _Expr, Dom, T>, T>
operator~(Expr<Dom, T> operand) {
  using ClosureType = UnClosure<__vec_not<T>, T, _Expr, Dom, T>;
  using ExprType = Expr<ClosureType, T>;
  return ExprType(ClosureType(operand));
}
template <typename Clos, typename RT>
LIBDEVICE_ATTRIBUTE Expr<Clos, RT> operator+(Expr<Clos, RT> operand) {
  return operand;
}

template <class Dom>
LIBDEVICE_ATTRIBUTE
    Expr<UnClosure<__vec_not<bool>, bool, _Expr, Dom, bool>, bool>
    operator!(Expr<Dom, bool> operand) {
  using ClosureType = UnClosure<__vec_not<bool>, bool, _Expr, Dom, bool>;
  using ExprType = Expr<ClosureType, bool>;
  return ExprType(ClosureType(operand));
}

// Oper Definations
#define UNARY_OP(vv_funcname)                                                  \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src) {            \
    vv_funcname(dst.reg, src.reg);                                             \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src,              \
                                      simd<bool> &mask) {                      \
    vv_funcname##_m(dst.reg, src.reg, mask.reg);                               \
  }

#define COMMUTABLE_OP(vv_funcname)                                             \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src1,             \
                                      simd<T> &src2) {                         \
    vv_funcname(dst.reg, src1.reg, src2.reg);                                  \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src1, T src2) {   \
    vv_funcname(dst.reg, src1.reg, src2);                                      \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, T src1, simd<T> &src2) {   \
    vv_funcname(dst.reg, src2.reg, src1);                                      \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src1,             \
                                      simd<T> &src2, simd<bool> &mask) {       \
    vv_funcname##_m(dst.reg, src1.reg, src2.reg, mask.reg);                    \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src1, T src2,     \
                                      simd<bool> &mask) {                      \
    vv_funcname##_m(dst.reg, src1.reg, src2, mask.reg);                        \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, T src1, simd<T> &src2,     \
                                      simd<bool> &mask) {                      \
    vv_funcname##_m(dst.reg, src2.reg, src1, mask.reg);                        \
  }

#define UNCOMMUTABLE_OP(vv_funcname)                                           \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src1,             \
                                      simd<T> &src2) {                         \
    vv_funcname(dst.reg, src1.reg, src2.reg);                                  \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src1, T src2) {   \
    vv_funcname(dst.reg, src1.reg, src2);                                      \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, T src1, simd<T> &src2) {   \
    vv_funcname(dst.reg, src1, src2.reg);                                      \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src1,             \
                                      simd<T> &src2, simd<bool> &mask) {       \
    vv_funcname##_m(dst.reg, src1.reg, src2.reg, mask.reg);                    \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src1, T src2,     \
                                      simd<bool> &mask) {                      \
    vv_funcname##_m(dst.reg, src1.reg, src2, mask.reg);                        \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, T src1, simd<T> &src2,     \
                                      simd<bool> &mask) {                      \
    vv_funcname##_m(dst.reg, src1, src2.reg, mask.reg);                        \
  }

#define RELATION_OP(vv_funcname, vv_revfuncname)                               \
  LIBDEVICE_ATTRIBUTE void operator()(simd<bool> &dst, simd<T> &src1,          \
                                      simd<T> &src2) {                         \
    vv_funcname(dst, src1, src2);                                              \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<bool> &dst, simd<T> &src1,          \
                                      T src2) {                                \
    vv_funcname(dst, src1, src2);                                              \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<bool> &dst, T src1,                 \
                                      simd<T> &src2) {                         \
    vv_revfuncname(dst, src2, src1);                                           \
  }

#define SHIFTING_OP(vv_funcname)                                               \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src,              \
                                      simd<T> &shift) {                        \
    vv_funcname(dst.reg, src.reg, shift.reg);                                  \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src, T shift) {   \
    vv_funcname(dst.reg, src.reg, shift);                                      \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src,              \
                                      simd<T> &shift, simd<bool> &mask) {      \
    vv_funcname(dst.reg, src.reg, shift.reg, mask.reg);                        \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(simd<T> &dst, simd<T> &src, T shift,     \
                                      simd<bool> &mask) {                      \
    vv_funcname(dst.reg, src.reg, shift, mask.reg);                            \
  }

template <typename T> struct __vec_neg {
  UNARY_OP(__vv_neg)
};

template <typename T> struct __vec_not {
  UNARY_OP(__vv_not)
};

template <typename T> struct __vec_add {
  COMMUTABLE_OP(__vv_add)
};

template <typename T> struct __vec_mul {
  COMMUTABLE_OP(__vv_mul)
};

template <typename T> struct __vec_sub {
  UNCOMMUTABLE_OP(__vv_sub)
};

template <typename T> struct __vec_div {
  UNCOMMUTABLE_OP(__vv_div)
};

template <typename T> struct __vec_and {
  COMMUTABLE_OP(__vv_and)
};

template <typename T> struct __vec_or {
  COMMUTABLE_OP(__vv_or)
};

template <typename T> struct __vec_xor {
  COMMUTABLE_OP(__vv_xor)
};

template <typename T> struct __vec_sl {
  SHIFTING_OP(__vv_sll)
};

enum class SignTag { Signed, Unsigned };

template <typename T, SignTag signtag> struct __vec_sr_impl;

template <typename T> struct getSignTag {
  static constexpr SignTag value =
      std::is_signed<T>::value ? SignTag::Signed : SignTag::Unsigned;
};

template <typename T> struct __vec_sr_impl<T, SignTag::Unsigned> {
  SHIFTING_OP(__vv_srl)
};

template <typename T> struct __vec_sr_impl<T, SignTag::Signed> {
  SHIFTING_OP(__vv_sra)
};

template <typename T>
struct __vec_sr : public __vec_sr_impl<T, getSignTag<T>::value> {};

template <typename T> struct __vec_eq {
  RELATION_OP(__vv_eq, __vv_eq)
};

template <typename T> struct __vec_ne {
  RELATION_OP(__vv_ne, __vv_ne)
};

template <typename T> struct __vec_gt {
  RELATION_OP(__vv_gt, __vv_lt)
};

template <typename T> struct __vec_lt {
  RELATION_OP(__vv_lt, __vv_gt)
};

template <typename T> struct __vec_ge {
  RELATION_OP(__vv_ge, __vv_le)
};

template <typename T> struct __vec_le {
  RELATION_OP(__vv_le, __vv_ge)
};
