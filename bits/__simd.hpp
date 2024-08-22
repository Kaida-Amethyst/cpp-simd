#pragma once
// Optional header
#include "vv-interface.h"
#include <cstdint>
#include <iostream>
static int regCnt = 0;
static int regCnt_p = 0; // only for vv_bool
//-----------------

#include "__utils.hpp"

template <typename S>
using __allowed_scalar_type =
    MatchIf<S, int, unsigned int, long, unsigned long, long long,
            unsigned long long, float, double>;

template <typename D>
using __allowed_data_type =
    MatchIf<D, int8_t, int16_t, int32_t, uint8_t, uint16_t, uint32_t, float>;
// using __allowed_data = MatchIf<D, int8_t, int16_t, int32_t, uint8_t,
// uint16_t, uint32_t, float, half, bfloat16_t>;

template <typename Addr>
using __allowed_addr_type = MatchIf<Addr, char, short, int, unsigned char,
                                    unsigned short, unsigned int, float>;
// using __allowed_addr_type = MatchIf<Addr, char, short, int, unsigned char,
// unsigned short, unsigned int, float, half, bfloat16_t>;

//------------------------------------------------------------

template <> struct _Vreg<float> {
  vv_float reg;
  using regtype = vv_float;
};

template <> struct _Vreg<int32_t> {
  vv_int32 reg;
  using regtype = vv_int32;
};

template <> struct _Vreg<bool> {
  vv_bool reg;
  using regtype = vv_bool;
};

// template <> struct _Vreg<int8_t> {
//   vv_int8 reg;
//   using regtype = vv_int8;
// };
//
// template <> struct _Vreg<int16_t> {
//   vv_int16 reg;
//   using regtype = vv_int16;
// };
//
// template <> struct _Vreg<uint8_t> {
//   vv_uint8 reg;
//   using regtype = vv_uint8;
// };
//
// template <> struct _Vreg<uint16_t> {
//   vv_uint16 reg;
//   using regtype = vv_uint16;
// };
//
// template <> struct _Vreg<uint32_t> {
//   vv_uint32 reg;
//   using regtype = vv_uint32;
// };
//
// template <> struct _Vreg<float> {
//   vv_float reg;
//   using regtype = vv_float;
// };
//
// template <> struct _Vreg<half> {
//   vv_half reg;
//   using regtype = vv_half;
// };
//
// // Note: It is different with others
// template <> struct _Vreg<bfloat16_t> {
//   vv_int32 reg;
//   using regtype = vv_int32;
// };

// template <> struct TypeTrait<half> {
// static constexpr TypeTag tag = Half;
// };
// template <> struct TypeTrait<bfloat16_t> {
// static constexpr TypeTag tag = Bfloat16;
// };

template <typename T, TypeTag> struct simd_base {};
template <typename T> using simd = simd_base<T, TypeTrait<T>::tag>;

template <typename T, template <typename, TypeTag> class SimdBase>
struct CommonOperation {
  using _Simd = SimdBase<T, TypeTrait<T>::tag>;

  // __mlu_func__ CommonOperation() {
  //   static_cast<_Simd &>(*this).reg.reg.regNum = regCnt++;
  // };

  __mlu_func__ _Simd &operator=(_Simd &other) {
    __vv_move(static_cast<_Simd &>(*this).get_reg(), other.get_reg());
    return static_cast<_Simd &>(*this);
  }

  template <typename Scalar> __mlu_func__ _Simd &operator=(Scalar &&s) {
    __vv_move(static_cast<_Simd &>(*this).get_reg(), s);
    return static_cast<_Simd &>(*this);
  }

  template <template <class, typename, class, class> class Closure, class Oper,
            class L, class R>
  __mlu_func__ _Simd &operator=(Closure<Oper, T, L, R> &&clos) {
    clos.eval(static_cast<_Simd &>(*this));
    return static_cast<_Simd &>(*this);
  }

  __mlu_func__ _Simd &operator+=(_Simd &other) {
    __vv_add(static_cast<_Simd &>(*this).get_reg(),
             static_cast<_Simd &>(*this).get_reg(), other.get_reg());
    return static_cast<_Simd &>(*this);
  }

  template <typename Scalar> __mlu_func__ _Simd &operator+=(Scalar &&s) {
    __vv_add(static_cast<_Simd &>(*this).get_reg(),
             static_cast<_Simd &>(*this).get_reg(), s);
    return static_cast<_Simd &>(*this);
  }

  template <template <class, typename, class, class> class Closure, class Op,
            class L, class R>
  __mlu_func__ _Simd &operator+=(Closure<Op, T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_add(static_cast<_Simd &>(*this).get_reg(),
             static_cast<_Simd &>(*this).get_reg(), clos.res.get_reg());
    return static_cast<_Simd &>(*this);
  }

  __mlu_func__ _Simd &operator-=(const _Simd &other) {
    __vv_sub(static_cast<_Simd &>(*this).get_reg(),
             static_cast<_Simd &>(*this).get_reg(), other.get_reg());
    return static_cast<_Simd &>(*this);
  }

  template <typename Scalar> __mlu_func__ _Simd &operator-=(Scalar &&s) {
    __vv_sub(static_cast<_Simd &>(*this).get_reg(),
             static_cast<_Simd &>(*this).get_reg(), s);
    return static_cast<_Simd &>(*this);
  }

  template <template <class, typename, class, class> class Closure, class Op,
            class L, class R>
  __mlu_func__ _Simd &operator-=(Closure<Op, T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_sub(static_cast<_Simd &>(*this).get_reg(),
             static_cast<_Simd &>(*this).get_reg(), clos.res.get_reg());
    return static_cast<_Simd &>(*this);
  }

  __mlu_func__ _Simd &operator*=(_Simd &other) {
    __vv_mul(static_cast<_Simd &>(*this).get_reg(),
             static_cast<_Simd &>(*this).get_reg(), other.get_reg());
    return static_cast<_Simd &>(*this);
  }

  template <typename Scalar> __mlu_func__ _Simd &operator*=(Scalar &&s) {
    __vv_mul(static_cast<_Simd &>(*this).get_reg(),
             static_cast<_Simd &>(*this).get_reg(), s);
    return static_cast<_Simd &>(*this);
  }

  template <template <class, typename, class, class> class Closure, class Op,
            class L, class R>
  __mlu_func__ _Simd &operator*=(Closure<Op, T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_mul(static_cast<_Simd &>(*this).get_reg(),
             static_cast<_Simd &>(*this).get_reg(), clos.res.get_reg());
  }
  // ------
  // div
  // ------

  // TODO: fix this, add (vv_uint32) transform
  template <typename Addr> __mlu_func__ void load(Addr *s) {
    __vv_load(static_cast<_Simd &>(*this).get_reg(), s);
  }
  template <typename Addr> __mlu_func__ void load(Addr *s, int len) {
    __vv_load(static_cast<_Simd &>(*this).get_reg(), s, len);
  }
  template <typename Addr> __mlu_func__ void store(Addr *d) {
    __vv_store(d, static_cast<_Simd &>(*this).get_reg());
  }
  template <typename Addr> __mlu_func__ void store(Addr *d, int len) {
    __vv_store(d, static_cast<_Simd &>(*this).get_reg(), len);
  }
};

template <typename T>
struct simd_base<T, TypeTag::Integer> : public CommonOperation<T, simd_base> {

  _Vreg<T> reg;

  __mlu_func__ typename _Vreg<T>::regtype &get_reg() { return reg.reg; }
  __mlu_func__ const typename _Vreg<T>::regtype &get_reg() const {
    return reg.reg;
  }

  // Real constructor
  // __mlu_func__ simd_base() = default;
  __mlu_func__ simd_base() { reg.reg.regNum = regCnt++; }

  __mlu_func__ simd_base(simd<T> &other) {
    __vv_move(this->get_reg(), other.get_reg());
  }

  template <typename Scalar> __mlu_func__ simd_base(Scalar &&s) {
    __vv_move(this->get_reg(), static_cast<T>(s));
  }

  template <template <class, typename, class, class> class Closure, class Oper,
            class L, class R>
  __mlu_func__ simd_base(Closure<Oper, T, L, R> &&clos) {
    clos.eval(*this);
  }

  __mlu_func__ UnClosure<__vec_neg, T, _Simd, _Simd> operator-() const {
    return UnClosure<__vec_neg, T, _Simd, _Simd>(*this);
  }
  __mlu_func__ simd<T> &operator+() const { return *this; }

  __mlu_func__ UnClosure<__vec_lnot, T, _Simd, _Simd> operator!() const {
    return UnClosure<__vec_lnot, T, _Simd, _Simd>(*this);
  }

  __mlu_func__ UnClosure<__vec_not, T, _Simd, _Simd> operator~() const {
    return UnClosure<__vec_not, T, _Simd, _Simd>(*this);
  }
};

template <typename T>
struct simd_base<T, TypeTag::Float> : public CommonOperation<T, simd_base> {

  _Vreg<T> reg;

  __mlu_func__ typename _Vreg<T>::regtype &get_reg() { return reg.reg; }
  __mlu_func__ const typename _Vreg<T>::regtype &get_reg() const {
    return reg.reg;
  }

  // Real constructor
  // __mlu_func__ simd_base() = default;
  __mlu_func__ simd_base() { reg.reg.regNum = regCnt++; }

  __mlu_func__ simd_base(simd<T> &other) {
    __vv_move(this->get_reg(), other.get_reg());
  }

  template <typename Scalar> __mlu_func__ simd_base(Scalar &&s) {
    __vv_move(this->get_reg(), static_cast<T>(s));
  }

  template <template <class, typename, class, class> class Closure, class Oper,
            class L, class R>
  __mlu_func__ simd_base(Closure<Oper, T, L, R> &&clos) {
    clos.eval(*this);
  }

  __mlu_func__ UnClosure<__vec_neg, T, _Simd, _Simd> operator-() const {
    return UnClosure<__vec_neg, T, _Simd, _Simd>(*this);
  }
  __mlu_func__ simd_base &operator+() const { return *this; }

  __mlu_func__ UnClosure<__vec_lnot, T, _Simd, _Simd> operator!() const {
    return UnClosure<__vec_lnot, T, _Simd, _Simd>(*this);
  }
};

template <> struct simd_base<bool, TypeTag::Pred> {

  _Vreg<bool> reg;

  __mlu_func__ typename _Vreg<bool>::regtype &get_reg() { return reg.reg; }
  __mlu_func__ const typename _Vreg<bool>::regtype &get_reg() const {
    return reg.reg;
  }

  __mlu_func__ simd_base() = default;
  __mlu_func__ simd_base(simd_base &other) {
    __vv_move(this->get_reg(), other.get_reg());
  }

  template <template <class, typename, class, class> class Closure, class Oper,
            class L, class R>
  __mlu_func__ simd_base(Closure<Oper, bool, L, R> &&clos) {
    clos.eval(*this);
  }

  template <template <class, typename, class, class> class Closure, class Oper,
            class T, class L, class R>
  __mlu_func__ simd_base(Closure<Oper, T, L, R> &&clos) {
    clos.set_eval(*this);
  }

  // TODO: change B to bool
  template <typename B, typename = MatchIf<B, bool>>
  __mlu_func__ UnClosure<__vec_not, B, _Simd, _Simd> operator~() const {
    return UnClosure<__vec_not, B, _Simd, _Simd>(*this);
  }

  template <typename B, typename = MatchIf<B, bool>>
  __mlu_func__ UnClosure<__vec_not, B, _Simd, _Simd> operator!() const {
    return UnClosure<__vec_not, B, _Simd, _Simd>(*this);
  }
};
