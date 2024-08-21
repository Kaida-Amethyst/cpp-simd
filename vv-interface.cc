
#include "vv-interface.h"
#include <format>
#include <iostream>

vv_general::vv_general() : regNum(0) {}

void __vv_add(vv_float &a, vv_float b, vv_float c) {
  std::cout << std::format("add.vec.f32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_add(vv_float &a, vv_float b, float c) {
  std::cout << std::format("add.vec.f32 %{}, %{}, ${}\n", a.regNum, b.regNum,
                           c);
}

void __vv_add(vv_int32 &a, vv_int32 b, vv_int32 &c) {
  std::cout << std::format("add.vec.i32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_add(vv_int32 &a, vv_int32 b, int c) {
  std::cout << std::format("add.vec.i32 %{}, %{}, ${}\n", a.regNum, b.regNum,
                           c);
}

void __vv_mul(vv_float &a, vv_float b, vv_float c) {
  std::cout << std::format("mul.vec.f32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_mul(vv_float &a, vv_float b, float c) {
  std::cout << std::format("mul.vec.f32 %{}, %{}, ${}\n", a.regNum, b.regNum,
                           c);
}

void __vv_mul(vv_int32 &a, vv_int32 b, vv_int32 c) {
  std::cout << std::format("mul.vec.i32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_mul(vv_int32 &a, vv_int32 b, int c) {
  std::cout << std::format("mul.vec.i32 %{}, %{}, ${}\n", a.regNum, b.regNum,
                           c);
}
void __vv_sub(vv_float &a, vv_float b, vv_float c) {
  std::cout << std::format("sub.vec.f32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_sub(vv_float &a, vv_float b, float c) {
  std::cout << std::format("sub.vec.f32 %{}, %{}, {}\n", a.regNum, b.regNum, c);
}

void __vv_sub(vv_int32 &a, vv_int32 b, vv_int32 c) {
  std::cout << std::format("sub.vec.i32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_sub(vv_int32 &a, vv_int32 b, int c) {
  std::cout << std::format("sub.vec.i32 %{}, %{}, {}\n", a.regNum, b.regNum, c);
}

void __vv_div(vv_float &a, vv_float b, vv_float c) {
  std::cout << std::format("div.vec.f32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_div(vv_float &a, vv_float b, float c) {
  std::cout << std::format("div.vec.f32 %{}, %{}, {}\n", a.regNum, b.regNum, c);
}

void __vv_div(vv_int32 &a, vv_int32 b, vv_int32 &c) {
  std::cout << std::format("div.vec.i32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_div(vv_int32 &a, vv_int32 b, int c) {
  std::cout << std::format("div.vec.i32 %{}, %{}, ${}\n", a.regNum, b.regNum,
                           c);
}

void __vv_neg(vv_float &a, vv_float b) {
  std::cout << std::format("neg.vec.f32 %{}, %{}\n", a.regNum, b.regNum);
}
void __vv_neg(vv_int32 &a, vv_int32 b) {
  std::cout << std::format("neg.vec.i32 %{}, %{}\n", a.regNum, b.regNum);
}

void __vv_move(vv_float &a, vv_float b) {
  std::cout << std::format("mov.vec.f32 %{}, %{}\n", a.regNum, b.regNum);
}
void __vv_move(vv_float &a, float b) {
  std::cout << std::format("mov.vec.f32 %{}, ${}\n", a.regNum, b);
}

void __vv_move(vv_int32 &a, vv_int32 b) {
  std::cout << std::format("mov.vec.i32 %{}, %{}\n", a.regNum, b.regNum);
}
void __vv_move(vv_int32 &a, int b) {
  std::cout << std::format("mov.vec.i32 %{}, ${}\n", a.regNum, b);
}

void __vv_not(vv_int32 &a, vv_int32 b) {
  std::cout << std::format("not.vec.i32 %{}, %{}\n", a.regNum, b.regNum);
}

void __vv_and(vv_int32 &a, vv_int32 b, vv_int32 c) {
  std::cout << std::format("and.vec.i32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_and(vv_int32 &a, vv_int32 b, int c) {
  std::cout << std::format("and.vec.i32 %{}, %{}, ${}\n", a.regNum, b.regNum,
                           c);
}

void __vv_or(vv_int32 &a, vv_int32 b, vv_int32 c) {
  std::cout << std::format("or.vec.i32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_or(vv_int32 &a, vv_int32 b, int c) {
  std::cout << std::format("or.vec.i32 %{}, %{}, ${}\n", a.regNum, b.regNum, c);
}

void __vv_xor(vv_int32 &a, vv_int32 b, vv_int32 c) {
  std::cout << std::format("xor.vec.i32 %{}, %{}, %{}\n", a.regNum, b.regNum,
                           c.regNum);
}
void __vv_xor(vv_int32 &a, vv_int32 b, int c) {
  std::cout << std::format("xor.vec.i32 %{}, %{}, ${}\n", a.regNum, b.regNum,
                           c);
}

void __vv_load(vv_float &a, float *b) {
  std::cout << std::format("load.vec.f32 %{}\n", a.regNum);
}

void __vv_load(vv_int32 &a, int *b) {
  std::cout << std::format("load.vec.i32 %{}\n", a.regNum);
}

void __vv_store(float *a, vv_float b) {
  std::cout << std::format("store.vec.f32 %{}\n", b.regNum);
}

void __vv_store(int *a, vv_int32 b) {
  std::cout << std::format("store.vec.i32 %{}\n", b.regNum);
}
