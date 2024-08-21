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

template <typename T> struct simd_base {
  _Vreg<T> reg;

  __mlu_func__ typename _Vreg<T>::regtype &get_reg() { return reg.reg; }
  __mlu_func__ const typename _Vreg<T>::regtype &get_reg() const {
    return reg.reg;
  }

  // Real constructor
  // __mlu_func__ simd_base() = default;
  __mlu_func__ simd_base() { reg.reg.regNum = regCnt++; }

  __mlu_func__ simd_base &operator=(const simd_base &other) {
    __vv_move(this->get_reg(), other.get_reg());
    return *this;
  }
};

template <typename T> struct simd : public simd_base<T> {

  __mlu_func__ simd() = default;

  __mlu_func__ simd(const simd<T> &other) {
    __vv_move(this->get_reg(), other.get_reg());
  }

  template <typename S> __mlu_func__ simd(const S &scalar) {
    __vv_move(this->get_reg(), static_cast<T>(scalar));
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ simd(Closure<T, L, R> &&clos) {
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

  __mlu_func__ UnClosure<T, _Simd, _Simd> operator~() const {
    return UnClosure<T, _Simd, _Simd>(*this, __vv_not, __vv_not_m, __vv_not_z);
  }
  __mlu_func__ UnClosure<T, _Simd, _Simd> operator!() const {
    return UnClosure<T, _Simd, _Simd>(*this, __vv_lnot, __vv_lnot_m,
                                      __vv_lnot_z);
  }

  __mlu_func__ void load(T *s) { __vv_load(this->get_reg(), s); }
  __mlu_func__ void load(T *s, int len) { __vv_load(this->get_reg(), s, len); }
  __mlu_func__ void store(T *d) { __vv_store(d, this->get_reg()); }
  __mlu_func__ void store(T *d, int len) {
    __vv_store(d, this->get_reg(), len);
  }
};

template <> struct simd<bool> : public simd_base<bool> {
  __mlu_func__ simd() = default;
  __mlu_func__ simd(const simd<bool> &other) {
    __vv_move(this->get_reg(), other.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ simd(Closure<bool, L, R> &&clos) {
    clos.eval(*this);
  }

  template <template <typename, class, class> class Closure, class T, class L,
            class R>
  __mlu_func__ simd(Closure<T, L, R> &&clos) {
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
