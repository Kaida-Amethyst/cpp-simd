#include "vec_interface.h"
#include <format>
#include <iostream>
#include <string_view>
#include <utility>
static int regCnt = 0;

vv_general::vv_general() : regNum(regCnt++) {}

void __vv_add(vv_float &dst, vv_float src1, vv_float src2) {
  std::cout << std::format("vec.add.f32 %{}, %{}, %{}\n", dst.regNum,
                           src1.regNum, src2.regNum);
}

void __vv_add(vv_float &dst, vv_float src1, float src2) {
  std::cout << std::format("vec.add.f32 %{}, %{}, ${}\n", dst.regNum,
                           src1.regNum, src2);
}

void __vv_load(vv_float &dst, float *src) {
  std::cout << std::format("vec.load.f32 %{}\n", dst.regNum);
}

void __vv_store(float *dst, vv_float src) {
  std::cout << std::format("vec.store.f32 %{}\n", src.regNum);
}

void __vv_move(vv_float &dst, vv_float src) {
  std::cout << std::format("vec.move.f32 %{}, %{}\n", dst.regNum, src.regNum);
}
