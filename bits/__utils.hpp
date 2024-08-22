#pragma once
#include <cstdint>

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

// -----------------------------------------------------
template <typename Oper, typename T, class Loperand, class Roperand>
struct BinClosure;
template <typename Oper, typename T, class Dummy1, class Dummy2>
struct UnClosure;
class _Simd;
class _Scalar;

template <typename T> struct _Vreg;

enum class TypeTag;
template <typename T> struct TypeTrait;
template <typename T, TypeTag> struct simd_base;

enum class TypeTag {
  Integer, // int, unsigned,
  Float,   // float
  // Half,  // half
  // Bfloat16, // bfloat16_t
  Pred,
};

template <> struct TypeTrait<bool> {
  static constexpr TypeTag tag = TypeTag::Pred;
};
template <> struct TypeTrait<char> {
  static constexpr TypeTag tag = TypeTag::Integer;
};
template <> struct TypeTrait<int> {
  static constexpr TypeTag tag = TypeTag::Integer;
};
template <> struct TypeTrait<unsigned> {
  static constexpr TypeTag tag = TypeTag::Integer;
};
template <> struct TypeTrait<int8_t> {
  static constexpr TypeTag tag = TypeTag::Integer;
};
template <> struct TypeTrait<int16_t> {
  static constexpr TypeTag tag = TypeTag::Integer;
};
template <> struct TypeTrait<uint8_t> {
  static constexpr TypeTag tag = TypeTag::Integer;
};
template <> struct TypeTrait<uint16_t> {
  static constexpr TypeTag tag = TypeTag::Integer;
};
template <> struct TypeTrait<float> {
  static constexpr TypeTag tag = TypeTag::Float;
};

template <typename T> using simd = simd_base<T, TypeTrait<T>::tag>;
//-----------------------
struct __vec_neg;
struct __vec_not;
struct __vec_lnot;
struct __vec_add;
struct __vec_sub;
struct __vec_mul;
struct __vec_div;
struct __vec_sll;
struct __vec_srl;
struct __vec_sra;
struct __vec_and;
struct __vec_or;
struct __vec_xor;
