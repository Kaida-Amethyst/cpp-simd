#define __mlu_func__
#include "vec_interface.h"

#define LIBDEVICE_ATTRIBUTE __mlu_func__ inline
//-------------------------------------------
// Utils
// ------------------------------------------
#include <cstdint>
#include <utility>

struct false_type {
  static constexpr bool value = false;
};

struct true_type {
  static constexpr bool value = true;
};

template <bool Cond, typename T1, typename T2> struct ConditionalT;
template <typename T1, typename T2> struct ConditionalT<true, T1, T2> {
  using type = T1;
};
template <typename T1, typename T2> struct ConditionalT<false, T1, T2> {
  using type = T2;
};
template <bool Cond, typename T1, typename T2>
using Conditional = typename ConditionalT<Cond, T1, T2>::type;

template <typename T1, typename T2> struct IsSameT {
  static constexpr bool value = false;
};

template <typename T> struct IsSameT<T, T> {
  static constexpr bool value = true;
};

template <typename... Types> struct TypeList;
template <typename List> struct FrontT;
template <typename Head, typename... Tail>
struct FrontT<TypeList<Head, Tail...>> {
  using type = Head;
};

template <typename List> using Front = typename FrontT<List>::type;
template <typename List> struct PopFrontT;
template <typename Head, typename... Tail>
struct PopFrontT<TypeList<Head, Tail...>> {
  using type = TypeList<Tail...>;
};
template <typename List> using PopFront = typename PopFrontT<List>::type;

template <typename T, typename List> struct MatchIfT;

template <typename T, typename... Types>
struct MatchIfT<T, TypeList<Types...>> {
  using first = Front<TypeList<Types...>>;
  using rest = PopFront<TypeList<Types...>>;
  using result_type = Conditional<IsSameT<T, first>::value, true_type,
                                  typename MatchIfT<T, rest>::result_type>;
};

template <typename T> struct MatchIfT<T, TypeList<>> {
  using result_type = false_type;
};

template <bool> struct EnableMatchIfT;
template <> struct EnableMatchIfT<true> {
  using type = true_type;
};

template <typename T, typename... Types> struct MatchIfLT {
  using result_type = typename MatchIfT<T, TypeList<Types...>>::result_type;
  using type = typename EnableMatchIfT<result_type::value>::type;
};

template <typename T, typename... Types>
using MatchIf = typename MatchIfLT<T, Types...>::type;

// -----------------------------------------------------

template <int N> struct UType;
template <> struct UType<1> {
  using type = uint8_t;
};
template <> struct UType<2> {
  using type = uint16_t;
};
template <> struct UType<4> {
  using type = uint32_t;
};

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

#define UNARY_OP(funcname, vtype)                                              \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src) {                 \
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

#define SHIFT_OP(funcname, vtype, stype)                                       \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src1, vtype src2) {    \
    __vv_##funcname(dst, src1, src2);                                          \
  }                                                                            \
  LIBDEVICE_ATTRIBUTE void operator()(vtype &dst, vtype src1, stype src2) {    \
    __vv_##funcname(dst, src1, src2);                                          \
  }

#define RELATION_OP_SETP(funcname, vtype)                                      \
  LIBDEVICE_ATTRIBUTE void operator()(vv_bool &dst, vtype src1, vtype src2) {  \
    __vv_setp_##funcname(dst, src1, src2);                                     \
  }

struct __vec_neg {
  UNARY_OP(neg, vv_float);
  UNARY_OP(neg, vv_int32);
  UNARY_OP(neg, vv_int8);
  UNARY_OP(neg, vv_int16);
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
  SHIFT_OP(sll, vv_int32, int);
  SHIFT_OP(sll, vv_int8, int8_t);
  SHIFT_OP(sll, vv_int16, int16_t);
  SHIFT_OP(sll, vv_uint32, uint32_t);
  SHIFT_OP(sll, vv_uint8, uint8_t);
  SHIFT_OP(sll, vv_uint16, uint16_t);
};

struct __vec_sr {
  SHIFT_OP(srl, vv_uint32, uint32_t);
  SHIFT_OP(srl, vv_uint8, uint8_t);
  SHIFT_OP(srl, vv_uint16, uint16_t);
  SHIFT_OP(sra, vv_int32, int);
  SHIFT_OP(sra, vv_int8, int8_t);
  SHIFT_OP(sra, vv_int16, int16_t);
};

struct __vec_land {
  COMMUTABLE_BINARY_OP(land, vv_int32, int);
  COMMUTABLE_BINARY_OP(land, vv_int8, int8_t);
  COMMUTABLE_BINARY_OP(land, vv_int16, int16_t);
  COMMUTABLE_BINARY_OP(land, vv_uint32, uint32_t);
  COMMUTABLE_BINARY_OP(land, vv_uint8, uint8_t);
  COMMUTABLE_BINARY_OP(land, vv_uint16, uint16_t);
  LIBDEVICE_ATTRIBUTE void operator()(vv_bool &dst, vv_bool src1,
                                      vv_bool src2) {
    __vv_and(dst, src1, src2);
  }
};

struct __vec_lor {
  COMMUTABLE_BINARY_OP(lor, vv_int32, int);
  COMMUTABLE_BINARY_OP(lor, vv_int8, int8_t);
  COMMUTABLE_BINARY_OP(lor, vv_int16, int16_t);
  COMMUTABLE_BINARY_OP(lor, vv_uint32, uint32_t);
  COMMUTABLE_BINARY_OP(lor, vv_uint8, uint8_t);
  COMMUTABLE_BINARY_OP(lor, vv_uint16, uint16_t);
  LIBDEVICE_ATTRIBUTE void operator()(vv_bool &dst, vv_bool src1,
                                      vv_bool src2) {
    __vv_or(dst, src1, src2);
  }
};

struct __vec_lxor {
  COMMUTABLE_BINARY_OP(lor, vv_int32, int);
  COMMUTABLE_BINARY_OP(lor, vv_int8, int8_t);
  COMMUTABLE_BINARY_OP(lor, vv_int16, int16_t);
  COMMUTABLE_BINARY_OP(lor, vv_uint32, uint32_t);
  COMMUTABLE_BINARY_OP(lor, vv_uint8, uint8_t);
  COMMUTABLE_BINARY_OP(lor, vv_uint16, uint16_t);
  LIBDEVICE_ATTRIBUTE void operator()(vv_bool &dst, vv_bool src1,
                                      vv_bool src2) {
    __vv_xor(dst, src1, src2);
  }
};

struct __vec_eq {
  COMMUTABLE_BINARY_OP(eq, vv_float, float);
  COMMUTABLE_BINARY_OP(eq, vv_int32, int);
  COMMUTABLE_BINARY_OP(eq, vv_int8, int8_t);
  COMMUTABLE_BINARY_OP(eq, vv_int16, int16_t);
  COMMUTABLE_BINARY_OP(eq, vv_uint32, uint32_t);
  COMMUTABLE_BINARY_OP(eq, vv_uint8, uint8_t);
  COMMUTABLE_BINARY_OP(eq, vv_uint16, uint16_t);
  RELATION_OP_SETP(eq, vv_float);
  RELATION_OP_SETP(eq, vv_int32);
  RELATION_OP_SETP(eq, vv_int8);
  RELATION_OP_SETP(eq, vv_int16);
  RELATION_OP_SETP(eq, vv_uint32);
  RELATION_OP_SETP(eq, vv_uint8);
  RELATION_OP_SETP(eq, vv_uint16);
};

struct __vec_ne {
  COMMUTABLE_BINARY_OP(ne, vv_float, float);
  COMMUTABLE_BINARY_OP(ne, vv_int32, int);
  COMMUTABLE_BINARY_OP(ne, vv_int8, int8_t);
  COMMUTABLE_BINARY_OP(ne, vv_int16, int16_t);
  COMMUTABLE_BINARY_OP(ne, vv_uint32, uint32_t);
  COMMUTABLE_BINARY_OP(ne, vv_uint8, uint8_t);
  COMMUTABLE_BINARY_OP(ne, vv_uint16, uint16_t);
  RELATION_OP_SETP(ne, vv_float);
  RELATION_OP_SETP(ne, vv_int32);
  RELATION_OP_SETP(ne, vv_int8);
  RELATION_OP_SETP(ne, vv_int16);
  RELATION_OP_SETP(ne, vv_uint32);
  RELATION_OP_SETP(ne, vv_uint8);
  RELATION_OP_SETP(ne, vv_uint16);
};

struct __vec_gt {
  RELATION_OP_SETP(gt, vv_float);
  RELATION_OP_SETP(gt, vv_int32);
  RELATION_OP_SETP(gt, vv_int8);
  RELATION_OP_SETP(gt, vv_int16);
  RELATION_OP_SETP(gt, vv_uint32);
  RELATION_OP_SETP(gt, vv_uint8);
  RELATION_OP_SETP(gt, vv_uint16);
};

struct __vec_lt {
  RELATION_OP_SETP(lt, vv_float);
  RELATION_OP_SETP(lt, vv_int32);
  RELATION_OP_SETP(lt, vv_int8);
  RELATION_OP_SETP(lt, vv_int16);
  RELATION_OP_SETP(lt, vv_uint32);
  RELATION_OP_SETP(lt, vv_uint8);
  RELATION_OP_SETP(lt, vv_uint16);
};

struct __vec_ge {
  RELATION_OP_SETP(ge, vv_float);
  RELATION_OP_SETP(ge, vv_int32);
  RELATION_OP_SETP(ge, vv_int8);
  RELATION_OP_SETP(ge, vv_int16);
  RELATION_OP_SETP(ge, vv_uint32);
  RELATION_OP_SETP(ge, vv_uint8);
  RELATION_OP_SETP(ge, vv_uint16);
};

struct __vec_le {
  RELATION_OP_SETP(le, vv_float);
  RELATION_OP_SETP(le, vv_int32);
  RELATION_OP_SETP(le, vv_int8);
  RELATION_OP_SETP(le, vv_int16);
  RELATION_OP_SETP(le, vv_uint32);
  RELATION_OP_SETP(le, vv_uint8);
  RELATION_OP_SETP(le, vv_uint16);
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

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst, simd<bool> &mask) {
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

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst, simd<bool> &mask) {
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

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst, simd<bool> &mask) {
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

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst, simd<bool> &mask) {
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

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst, simd<bool> &mask) {
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
    simd<T> tmp_right;
    closure.left_expr.eval(dst);
    closure.right_expr.eval(tmp_right);
    Oper()(dst.get_reg(), dst.get_reg(), tmp_right.get_reg());
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst, simd<bool> &mask) {
    simd<T> tmp_right;
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

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst) {
    Oper()(dst.get_reg(), closure.left_operand.get_reg(),
           closure.right_operand);
  }

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst, simd<bool> &mask) {
    Oper()(dst.get_reg(), closure.left_operand.get_reg(), closure.right_operand,
           mask);
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

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst, simd<bool> &mask) {
    simd<T> tmp;
    closure.left_expr.eval(tmp);
    Oper()(dst.get_reg(), tmp.get_reg(), closure.right_operand, mask);
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

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst, simd<bool> &mask) {
    Oper()(dst.get_reg(), closure.left_operand, closure.right_operand.get_reg(),
           mask);
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

  LIBDEVICE_ATTRIBUTE void eval(simd<T> &dst, simd<bool> &mask) {
    simd<T> tmp;
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

/***********************************************************
 * Operations
 ***********************************************************/

/***********************************************************
 * Basic Binary Operations: +, -, *, /
 ***********************************************************/

/***********************************************************
 * Addition, operator+
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
BINARY_OPERATIRON_DEFINE(&&, __vec_land);
BINARY_OPERATIRON_DEFINE(||, __vec_lor);
BINARY_OPERATIRON_DEFINE(>>, __vec_sl);
BINARY_OPERATIRON_DEFINE(<<, __vec_sr);

/***********************************************************
 * Comparison Operations: ==, !=, <, >, <=, >=
 ***********************************************************/

/***********************************************************
 * Bitwise Shift Operations: <<, >>
 *************************************************************/
