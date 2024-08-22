#include "vv-interface.h"

struct __mask_tag {};
struct __zero_mask_tag {};

struct __vec_add {

  template <typename A1, typename A2, typename A3>
  inline void operator()(A1 &a, A2 b, A3 c) {
    __vv_add(a, b, c);
  }

  template <typename A1, typename A2, typename A3>
  inline void operator()(__mask_tag m, A1 &a, A2 b, A3 c, vv_bool p) {
    __vv_add_m(a, b, c, p);
  }

  template <typename A1, typename A2, typename A3>
  inline void operator()(__zero_mask_tag m, A1 &a, A2 b, A3 c, vv_bool p) {
    __vv_add_z(a, b, c, p);
  }
};
