#pragma once

#include "__simd.hpp"
#include "__utils.hpp"
#include "vv-interface.h"

struct __vec_neg {
  template <typename Arg1, typename Arg2>
  __mlu_func__ inline void operator()(Arg1 &a, Arg2 &&b) {
    __vv_neg(a, b);
  }

  template <typename Arg1, typename Arg2>
  __mlu_func__ inline void operator()(Arg1 &a, Arg2 &&b, vv_bool p) {
    __vv_neg_m(a, b, p);
  }

  template <typename Arg1, typename Arg2>
  __mlu_func__ inline void operator()(__zero_mask_tag, Arg1 &a, Arg2 &&b,
                                      vv_bool p) {
    __vv_neg_z(a, b, p);
  }
};

struct __vec_not {
  template <typename Arg1, typename Arg2>
  __mlu_func__ inline void operator()(Arg1 &a, Arg2 &&b) {
    __vv_not(a, b);
  }

  template <typename Arg1, typename Arg2>
  __mlu_func__ inline void operator()(Arg1 &a, Arg2 &&b, vv_bool p) {
    __vv_not_m(a, b, p);
  }

  template <typename Arg1, typename Arg2>
  __mlu_func__ inline void operator()(__zero_mask_tag, Arg1 &a, Arg2 &&b,
                                      vv_bool p) {
    __vv_not_z(a, b, p);
  }
};

struct __vec_add {
  template <typename Arg1, typename Arg2, typename Arg3>
  __mlu_func__ inline void operator()(Arg1 &a, Arg2 &&b, Arg3 &&c) {
    __vv_add(a, b, c);
  }

  template <typename Arg1, typename Arg2, typename Arg3>
  __mlu_func__ inline void operator()(Arg1 &a, Arg2 &&b, Arg3 &&c, vv_bool p) {
    __vv_add_m(a, b, c, p);
  }

  template <typename Arg1, typename Arg2, typename Arg3>
  __mlu_func__ inline void operator()(__zero_mask_tag, Arg1 &a, Arg2 &&b,
                                      Arg3 &&c, vv_bool p) {
    __vv_add_z(a, b, c, p);
  }
};
