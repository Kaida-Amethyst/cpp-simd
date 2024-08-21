// Optional header
#include "vv-interface.h"
#include <cstdint>
#define __mlu_func__
static int regCnt = 0;
static int regCnt_p = 0; // only for vv_bool
//-----------------

template <typename T, class Loperand, class Roperand> struct BinClosure;
template <typename T, class Dummy1, class Dummy2> struct UnClosure;
class _Simd;
class _Literal;

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
  template <class L, class R>
  __mlu_func__ simd<T> &operator=(const BinClosure<T, L, R> &bin) {
    bin.eval(*this);
    return *this;
  }

  __mlu_func__ UnClosure<T, _Simd, _Simd> operator-() const {
    return UnClosure<T, _Simd, _Simd>(*this, __vv_neg);
  }

  __mlu_func__ void load(T *s) { __vv_load(this->get_reg(), s); }
  __mlu_func__ void store(T *d) { __vv_store(d, this->get_reg()); }
};
