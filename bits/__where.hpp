#pragma once

#include "__closure.hpp"

template <typename T, typename = __allowed_data_type<T>> struct __mwhere_simd {
  simd<T> &r;
  simd<bool> &m;

  __mlu_func__ __mwhere_simd(simd<T> &r, simd<bool> &m) : r{r}, m{m} {};

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator=(const S &rhs) {
    __vv_move_m(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator=(const simd<T> &rhs) {
    __vv_move_m(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator=(Closure<T, L, R> &&clos) {
    clos.meval(r, m);
  }

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator+=(const S &rhs) {
    __vv_add_m(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator+=(const simd<T> &rhs) {
    __vv_add_m(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator+=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_add_m(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator-=(const S &rhs) {
    __vv_sub_m(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator-=(const simd<T> &rhs) {
    __vv_sub_m(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator-=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_sub_m(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }

  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator*=(const S &rhs) {
    __vv_mul_m(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator*=(const simd<T> &rhs) {
    __vv_mul_m(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator*=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_mul_m(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }

  // #if __BANG_ARCH__ > 500
  template <typename S, typename = __allowed_scalar_type<S>>
  __mlu_func__ void operator/=(const S &rhs) {
    __vv_div_m(r.get_reg(), static_cast<S>(rhs), m.get_reg());
  }

  __mlu_func__ void operator/=(const simd<T> &rhs) {
    __vv_div_m(r.get_reg(), rhs.get_reg(), m.get_reg());
  }

  template <template <typename, class, class> class Closure, class L, class R>
  __mlu_func__ void operator/=(Closure<T, L, R> &&clos) {
    clos.eval(clos.res);
    __vv_div_m(r.get_reg(), clos.res.get_reg(), m.get_reg());
  }
  // #endif

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
