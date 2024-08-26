#pragma once

#include "__closure.hpp"

template <typename T, TypeTag> struct __mwhere_simd;

template <typename T, template <typename, TypeTag> class where_m_expr>
struct CommonOperationForWhereM {

  template <typename Scalar> __mlu_func__ void operator=(const Scalar &s) {
    __vv_move_m(this->r.get_reg(), static_cast<T>(s), this->m.get_reg());
  }

  __mlu_func__ void operator=(const simd<T> &other) {
    __vv_move_m(this->r.get_reg(), other.get_reg(), this->m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator=(Closure<T, L, R> &&clos) {
    clos.meval(this->r, this->m);
  }

  template <typename Scalar> __mlu_func__ void operator+=(const Scalar &s) {
    __vv_add_m(this->r.get_reg(), this->r.get_reg(), static_cast<T>(s),
               this->m.get_reg());
  }

  __mlu_func__ void operator+=(const simd<T> &other) {
    __vv_add_m(this->r.get_reg(), this->r.get_reg(), other.get_reg(),
               this->m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator+=(Closure<T, L, R> &&clos) {
    clos.eval(this->r, this->m);
    __vv_add_m(this->r.get_reg(), this->r.get_reg(), clos.res.get_reg(),
               this->m.get_reg());
  }

  template <typename Scalar> __mlu_func__ void operator-=(const Scalar &s) {
    __vv_sub_m(this->r.get_reg(), this->r.get_reg(), static_cast<T>(s),
               this->m.get_reg());
  }

  __mlu_func__ void operator-=(const simd<T> &other) {
    __vv_sub_m(this->r.get_reg(), this->r.get_reg(), other.get_reg(),
               this->m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator-=(Closure<T, L, R> &&clos) {
    clos.eval(this->r, this->m);
    __vv_sub_m(this->r.get_reg(), this->r.get_reg(), clos.res.get_reg(),
               this->m.get_reg());
  }

  template <typename Scalar> __mlu_func__ void operator*=(const Scalar &s) {
    __vv_mul_m(this->r.get_reg(), this->r.get_reg(), static_cast<T>(s),
               this->m.get_reg());
  }

  __mlu_func__ void operator*=(const simd<T> &other) {
    __vv_mul_m(this->r.get_reg(), this->r.get_reg(), other.get_reg(),
               this->m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator*=(Closure<T, L, R> &&clos) {
    clos.eval(this->r, this->m);
    __vv_mul_m(this->r.get_reg(), this->r.get_reg(), clos.res.get_reg(),
               this->m.get_reg());
  }

  // template <typename Scalar> __mlu_func__ void operator/=(const Scalar &s) {
  //   __vv_div_m(this->r.get_reg(), this->r.get_reg(), static_cast<T>(s),
  //              this->m.get_reg());
  // }
  //
  // # if __BANG_ARCH__ > 500
  // __mlu_func__ void operator/=(const simd<T> &other) {
  //   __vv_div_m(this->r.get_reg(), this->r.get_reg(), other.get_reg(),
  //              this->m.get_reg());
  // }
  //
  // template <template <typename, class, class> class Closure, class L, class
  // R>
  // __mlu_func__ void operator/=(Closure<T, L, R> &&clos) {
  //   clos.eval(this->r, this->m);
  //   __vv_div_m(this->r.get_reg(), this->r.get_reg(), clos.res.get_reg(),
  //              this->m.get_reg());
  // }
  // #endif

  // // TODO: fix this, add (vv_uint32) transform
  // template <typename Addr> __mlu_func__ void load(Addr *s) {
  //   __vv_load_m(this->r.get_reg(), s, this->m.get_reg());
  // }
  // template <typename Addr> __mlu_func__ void load(Addr *s, int len) {
  //   __vv_load_m(this->r.get_reg(), s, len, this->m.get_reg());
  // }
  // template <typename Addr> __mlu_func__ void store(Addr *d) {
  //   __vv_store(d, this->r.get_reg(), this->m.get_reg());
  // }
  // template <typename Addr> __mlu_func__ void store(Addr *d, int len) {
  //   __vv_store(d, this->r.get_reg(), len, this->m.get_reg());
  // }
};

template <typename T> struct __mwhere_simd<T, TypeTag::Integer> {
  simd<T> &r;
  simd<bool> &m;

  __mlu_func__ __mwhere_simd(simd<T> &r, simd<bool> &m) : r{r}, m{m} {};

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator&=(const S &rhs) {
    __vv_and_m(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator&=(const simd<T> &rhs) {
    __vv_and_m(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator&=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_and_m(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator|=(const S &rhs) {
    __vv_or_m(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator|=(const simd<T> &rhs) {
    __vv_or_m(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator|=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_or_m(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator^=(const S &rhs) {
    __vv_xor_m(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator^=(const simd<T> &rhs) {
    __vv_xor_m(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator^=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_xor_m(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }
};

template <typename T, typename = __allowed_data_type<T>> struct __zwhere_simd {
  simd<T> &r;
  simd<bool> &m;

  __mlu_func__ __zwhere_simd(simd<T> &r, simd<bool> &m) : r{r}, m{m} {};

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator=(const S &rhs) {
    __vv_move_z(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator=(const simd<T> &rhs) {
    __vv_move_z(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator=(Closure<T, L, R> &&clos) {
    clos.zeval(r, m);
  }

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator+=(const S &rhs) {
    __vv_add_z(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator+=(const simd<T> &rhs) {
    __vv_add_z(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator+=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_add_z(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator-=(const S &rhs) {
    __vv_sub_z(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator-=(const simd<T> &rhs) {
    __vv_sub_z(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator-=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_sub_z(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator*=(const S &rhs) {
    __vv_mul_z(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator*=(const simd<T> &rhs) {
    __vv_mul_z(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator*=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_mul_z(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }

  // #if __BANG_ARCH__ > 500
  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator/=(const S &rhs) {
    __vv_div_z(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator/=(const simd<T> &rhs) {
    __vv_div_z(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator/=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_div_z(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }
  // #endif

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator&=(const S &rhs) {
    __vv_and_z(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator&=(const simd<T> &rhs) {
    __vv_and_z(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator&=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_and_z(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator|=(const S &rhs) {
    __vv_or_z(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator|=(const simd<T> &rhs) {
    __vv_or_z(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator|=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_or_z(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator^=(const S &rhs) {
    __vv_xor_z(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator^=(const simd<T> &rhs) {
    __vv_xor_z(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator^=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_xor_z(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }
};

template <typename T>
__mlu_func__ __mwhere_simd<T> where(const simd<bool> &m, simd<T> &r) {
  return __mwhere_simd<T>(r, m);
}

template <typename T>
__mlu_func__ __mwhere_simd<T> whereM(const simd<bool> &m, simd<T> &r) {
  return __mwhere_simd<T>(r, m);
}

template <typename T>
__mlu_func__ __mwhere_simd<T> whereZ(const simd<bool> &m, simd<T> &r) {
  return __zwhere_simd<T>(r, m);
}
