#pragma once

#include "__simd.hpp"
#include "vv-interface.h"

struct __vec_neg {

  template <typename T>
  __mlu_func__ inline void operator()(simd<T> &a, simd<T> &b) {
    __vv_neg(a.get_reg(), b.get_reg());
  }

  template <typename T>
  __mlu_func__ inline void operator()(simd<T> &a, simd<T> &b, simd<bool> &p) {
    __vv_neg_m(a.get_reg(), b.get_reg(), p.get_reg());
  }

  template <typename T>
  __mlu_func__ inline void operator()(__zero_mask_tag, simd<T> &a, simd<T> &b,
                                      simd<bool> &p) {
    __vv_neg_z(a.get_reg(), b.get_reg(), p.get_reg());
  }
};

struct __vec_not {

  template <typename T>
  __mlu_func__ inline void operator()(simd<T> &a, simd<T> b) {
    __vv_not(a, b);
  }

  template <typename T>
  __mlu_func__ inline void operator()(simd<T> &a, simd<T> &b, simd<bool> &p) {
    __vv_not_m(a, b, p);
  }

  template <typename T>
  __mlu_func__ inline void operator()(__zero_mask_tag m, simd<T> &a, simd<T> &b,
                                      simd<bool> &p) {
    __vv_not_z(a.get_reg(), b.get_reg(), p.get_reg());
  }
};

struct __vec_add {

  template <typename T>
  __mlu_func__ inline void operator()(simd<T> &a, simd<T> &b, simd<T> &c) {
    __vv_add(a.get_reg(), b.get_reg(), c.get_reg());
  }

  template <typename T>
  __mlu_func__ inline void operator()(simd<T> &a, simd<T> &b, T c) {
    __vv_add(a.get_reg(), b.get_reg(), c);
  }

  template <typename T>
  __mlu_func__ inline void operator()(simd<T> &a, T b, simd<T> &&c) {
    __vv_add(a.get_reg(), b, c.get_reg());
  }

  template <typename T>
  __mlu_func__ inline void operator()(simd<T> &a, simd<T> &b, simd<T> &c,
                                      simd<bool> &p) {
    __vv_add_m(a.get_reg(), b.get_reg(), c.get_reg(), p.get_reg());
  }

  template <typename T>
  __mlu_func__ inline void operator()(simd<T> &a, simd<T> &b, T c,
                                      simd<bool> &p) {
    __vv_add_m(a.get_reg(), b.get_reg(), c, p.get_reg());
  }

  template <typename T>
  __mlu_func__ inline void operator()(simd<T> &a, T b, simd<T> &c,
                                      simd<bool> &p) {
    __vv_add_z(a.get_reg(), b, c.get_reg(), p.get_reg());
  }

  template <typename T>
  __mlu_func__ inline void operator()(__zero_mask_tag, simd<T> &a, simd<T> &b,
                                      simd<T> &c, simd<bool> &p) {
    __vv_add_z(a.get_reg(), b.get_reg(), c.get_reg(), p.get_reg());
  }

  template <typename T>
  __mlu_func__ inline void operator()(__zero_mask_tag, simd<T> &a, simd<T> &b,
                                      T c, simd<bool> &p) {
    __vv_add_z(a.get_reg(), b.get_reg(), c, p.get_reg());
  }

  template <typename T>
  __mlu_func__ inline void operator()(__zero_mask_tag, simd<T> &a, T b,
                                      simd<T> &c, simd<bool> &p) {
    __vv_add_z(a.get_reg(), b, c.get_reg(), p.get_reg());
  }
};
