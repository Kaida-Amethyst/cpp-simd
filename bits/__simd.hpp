// Optional header
#include "vv-interface.h"
#include <cstdint>
#define __mlu_func__
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

template <typename T, class Loperand, class Roperand> struct BinClosure;
template <typename T, class Dummy1, class Dummy2> struct UnClosure;
class _Simd;
class _Scalar;

template <typename T> struct _Vreg;

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

enum TypeTag {
  Integer, // int, unsigned,
  Float,   // float
  // Half,  // half
  // Bfloat16, // bfloat16_t
  Pred,
};

template <typename T> struct TypeTrait;
template <> struct TypeTrait<bool> {
  static constexpr TypeTag tag = Pred;
};
template <> struct TypeTrait<char> {
  static constexpr TypeTag tag = Integer;
};
template <> struct TypeTrait<int> {
  static constexpr TypeTag tag = Integer;
};
template <> struct TypeTrait<unsigned> {
  static constexpr TypeTag tag = Integer;
};
template <> struct TypeTrait<int8_t> {
  static constexpr TypeTag tag = Integer;
};
template <> struct TypeTrait<int16_t> {
  static constexpr TypeTag tag = Integer;
};
template <> struct TypeTrait<uint8_t> {
  static constexpr TypeTag tag = Integer;
};
template <> struct TypeTrait<uint16_t> {
  static constexpr TypeTag tag = Integer;
};
template <> struct TypeTrait<float> {
  static constexpr TypeTag tag = Float;
};
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

  __mlu_func__ _Simd &operator=(const _Simd &other) {
    __vv_move(this->get_reg(), other.get_reg());
  }

  template <typename Scalar> __mlu_func__ _Simd &operator=(const Scalar &s) {
    __vv_move(this->get_reg(), s);
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ _Simd &operator=(Closure<T, L, R> &&clos) {
    clos.eval(*this);
  }

  __mlu_func__ _Simd &operator+=(const _Simd &other) {
    __vv_add(this->get_reg(), this->get_reg(), other.get_reg());
  }

  template <typename Scalar> __mlu_func__ _Simd &operator+=(const Scalar &s) {
    __vv_add(this->get_reg(), this->get_reg(), s);
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ _Simd &operator+=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_add(this->get_reg(), this->get_reg(), clos.res.get_reg());
  }

  __mlu_func__ _Simd &operator-=(const _Simd &other) {
    __vv_sub(this->get_reg(), this->get_reg(), other.get_reg());
  }

  template <typename Scalar> __mlu_func__ _Simd &operator-=(const Scalar &s) {
    __vv_sub(this->get_reg(), this->get_reg(), s);
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ _Simd &operator-=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_sub(this->get_reg(), this->get_reg(), clos.res.get_reg());
  }

  __mlu_func__ _Simd &operator*=(const _Simd &other) {
    __vv_mul(this->get_reg(), this->get_reg(), other.get_reg());
  }

  template <typename Scalar> __mlu_func__ _Simd &operator*=(const Scalar &s) {
    __vv_mul(this->get_reg(), this->get_reg(), s);
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ _Simd &operator*=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_mul(this->get_reg(), this->get_reg(), clos.res.get_reg());
  }
  // ------
  // div
  // ------

  // TODO: fix this, add (vv_uint32) transform
  template <typename Addr> __mlu_func__ void load(Addr *s) {
    __vv_load(this->get_reg(), s);
  }
  template <typename Addr> __mlu_func__ void load(Addr *s, int len) {
    __vv_load(this->get_reg(), s, len);
  }
  template <typename Addr> __mlu_func__ void store(Addr *d) {
    __vv_store(d, this->get_reg());
  }
  template <typename Addr> __mlu_func__ void store(Addr *d, int len) {
    __vv_store(d, this->get_reg(), len);
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

  // __mlu_func__ simd_base &operator=(const simd_base &other) {
  //   __vv_move(this->get_reg(), other.get_reg());
  //   return *this;
  // }

  __mlu_func__ simd_base(const simd<T> &other) {
    __vv_move(this->get_reg(), other.get_reg());
  }

  template <typename S> __mlu_func__ simd_base(const S &scalar) {
    __vv_move(this->get_reg(), static_cast<T>(scalar));
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ simd_base(Closure<T, L, R> &&clos) {
    clos.eval(*this);
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ simd<T> &operator=(Closure<T, L, R> &&clos) {
    clos.eval(*this);
    return *this;
  }

  __mlu_func__ UnClosure<T, _Simd, _Simd> operator-() const {
    return UnClosure<T, _Simd, _Simd>(*this, __vv_neg, __vv_neg_m, __vv_neg_z);
  }
  __mlu_func__ simd<T> &operator+() const { return *this; }

  __mlu_func__ UnClosure<T, _Simd, _Simd> operator!() const {
    return UnClosure<T, _Simd, _Simd>(*this, __vv_lnot, __vv_lnot_m,
                                      __vv_lnot_z);
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

  // __mlu_func__ simd_base &operator=(const simd_base &other) {
  //   __vv_move(this->get_reg(), other.get_reg());
  //   return *this;
  // }

  __mlu_func__ simd_base(const simd<T> &other) {
    __vv_move(this->get_reg(), other.get_reg());
  }

  template <typename S> __mlu_func__ simd_base(const S &scalar) {
    __vv_move(this->get_reg(), static_cast<T>(scalar));
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ simd_base(Closure<T, L, R> &&clos) {
    clos.eval(*this);
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ simd<T> &operator=(Closure<T, L, R> &&clos) {
    clos.eval(*this);
    return *this;
  }

  __mlu_func__ UnClosure<T, _Simd, _Simd> operator-() const {
    return UnClosure<T, _Simd, _Simd>(*this, __vv_neg, __vv_neg_m, __vv_neg_z);
  }
  __mlu_func__ simd<T> &operator+() const { return *this; }

  __mlu_func__ UnClosure<T, _Simd, _Simd> operator!() const {
    return UnClosure<T, _Simd, _Simd>(*this, __vv_lnot, __vv_lnot_m,
                                      __vv_lnot_z);
  }
};

template <> struct simd_base<bool, TypeTag::Pred> {

  _Vreg<bool> reg;

  __mlu_func__ typename _Vreg<bool>::regtype &get_reg() { return reg.reg; }
  __mlu_func__ const typename _Vreg<bool>::regtype &get_reg() const {
    return reg.reg;
  }

  __mlu_func__ simd_base() = default;
  __mlu_func__ simd_base(const simd<bool> &other) {
    __vv_move(this->get_reg(), other.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ simd_base(Closure<bool, L, R> &&clos) {
    clos.eval(*this);
  }

  template <template <typename, class, class> class Closure, class T, class L,
            class R>
  __mlu_func__ simd_base(Closure<T, L, R> &&clos) {
    clos.set_eval(*this);
  }

  // TODO: change B to bool
  template <typename B, typename = MatchIf<B, bool>>
  __mlu_func__ UnClosure<B, _Simd, _Simd> operator~() const {
    return UnClosure<B, _Simd, _Simd>(*this, __vv_not, nullptr, nullptr);
  }

  template <typename B, typename = MatchIf<B, bool>>
  __mlu_func__ UnClosure<B, _Simd, _Simd> operator!() const {
    return UnClosure<B, _Simd, _Simd>(*this, __vv_not, nullptr, nullptr);
  }
};
