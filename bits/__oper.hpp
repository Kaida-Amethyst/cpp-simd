#include "vv-interface.h"
#define __mlu_func__

struct __mask_tag {};
struct __zero_mask_tag {};

struct __vec_neg {

  template <typename A1, typename A2>
  __mlu_func__ inline void operator()(A1 &a, A2 b) {
    __vv_neg(a, b);
  }

  template <typename A1, typename A2>
  __mlu_func__ inline void operator()(__mask_tag m, A1 &a, A2 b, vv_bool p) {
    __vv_neg_m(a, b, p);
  }

  template <typename A1, typename A2>
  __mlu_func__ inline void operator()(__zero_mask_tag m, A1 &a, A2 b,
                                      vv_bool p) {
    __vv_neg_z(a, b, p);
  }
};

struct __vec_not {

  template <typename A1, typename A2>
  __mlu_func__ inline void operator()(A1 &a, A2 b) {
    __vv_not(a, b);
  }

  template <typename A1, typename A2>
  __mlu_func__ inline void operator()(__mask_tag m, A1 &a, A2 b, vv_bool p) {
    __vv_not_m(a, b, p);
  }

  template <typename A1, typename A2>
  __mlu_func__ inline void operator()(__zero_mask_tag m, A1 &a, A2 b,
                                      vv_bool p) {
    __vv_not_z(a, b, p);
  }
};

struct __vec_add {

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(A1 &a, A2 b, A3 c) {
    __vv_add(a, b, c);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_add_m(a, b, c, p);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__zero_mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_add_z(a, b, c, p);
  }
};

struct __vec_sub {

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(A1 &a, A2 b, A3 c) {
    __vv_sub(a, b, c);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_sub_m(a, b, c, p);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__zero_mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_sub_z(a, b, c, p);
  }
};

struct __vec_mul {

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(A1 &a, A2 b, A3 c) {
    __vv_mul(a, b, c);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_mul_m(a, b, c, p);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__zero_mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_mul_z(a, b, c, p);
  }
};

struct __vec_div {

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(A1 &a, A2 b, A3 c) {
    __vv_div(a, b, c);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_div_m(a, b, c, p);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__zero_mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_div_z(a, b, c, p);
  }
};

struct __vec_and {

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(A1 &a, A2 b, A3 c) {
    __vv_and(a, b, c);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_and_m(a, b, c, p);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__zero_mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_and_z(a, b, c, p);
  }
};

struct __vec_or {

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(A1 &a, A2 b, A3 c) {
    __vv_or(a, b, c);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_or_m(a, b, c, p);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__zero_mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_or_z(a, b, c, p);
  }
};

struct __vec_xor {

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(A1 &a, A2 b, A3 c) {
    __vv_xor(a, b, c);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_xor_m(a, b, c, p);
  }

  template <typename A1, typename A2, typename A3>
  __mlu_func__ inline void operator()(__zero_mask_tag m, A1 &a, A2 b, A3 c,
                                      vv_bool p) {
    __vv_xor_z(a, b, c, p);
  }
};
