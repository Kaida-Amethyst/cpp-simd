#pragma once
#include <cstdint>

struct vv_general {
  int regNum;
  vv_general();
};
struct vv_int32 : public vv_general {};
struct vv_int8 : public vv_general {};
struct vv_int16 : public vv_general {};
struct vv_uint8 : public vv_general {};
struct vv_uint16 : public vv_general {};
struct vv_uint32 : public vv_general {};
struct vv_float : public vv_general {};
struct vv_half : public vv_general {};

struct vv_bool {
  int regNum;
};

// +, -, *, /
void __vv_add(vv_float &dst, vv_float src1, vv_float src2);
void __vv_add(vv_float &dst, vv_float src1, float src2);
void __vv_add(vv_float &dst, float src1, vv_float src2);
void __vv_add_m(vv_float &dst, vv_float src1, vv_float src2, vv_bool mask);
void __vv_add_m(vv_float &dst, vv_float src1, float src2, vv_bool mask);
void __vv_add_m(vv_float &dst, float src1, vv_float src2, vv_bool mask);

void __vv_add(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_add(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_add(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_add_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_add_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_add_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_add(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_add(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_add(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_add_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_add_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_add_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_add(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_add(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_add(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_add_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_add_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_add_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_add(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_add(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_add(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_add_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_add_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_add_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_add(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_add(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_add(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_add_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_add_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_add_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_add(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_add(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_add(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_add_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_add_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_add_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);

void __vv_sub(vv_float &dst, vv_float src1, vv_float src2);
void __vv_sub(vv_float &dst, vv_float src1, float src2);
void __vv_sub(vv_float &dst, float src1, vv_float src2);
void __vv_sub_m(vv_float &dst, vv_float src1, vv_float src2, vv_bool mask);
void __vv_sub_m(vv_float &dst, vv_float src1, float src2, vv_bool mask);
void __vv_sub_m(vv_float &dst, float src1, vv_float src2, vv_bool mask);

void __vv_sub(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_sub(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_sub(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_sub_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_sub_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_sub_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_sub(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_sub(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_sub(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_sub_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_sub_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_sub_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_sub(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_sub(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_sub(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_sub_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_sub_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_sub_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_sub(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_sub(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_sub(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_sub_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_sub_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_sub_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_sub(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_sub(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_sub(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_sub_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_sub_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_sub_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_sub(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_sub(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_sub(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_sub_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_sub_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_sub_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);

void __vv_mul(vv_float &dst, vv_float src1, vv_float src2);
void __vv_mul(vv_float &dst, vv_float src1, float src2);
void __vv_mul(vv_float &dst, float src1, vv_float src2);
void __vv_mul_m(vv_float &dst, vv_float src1, vv_float src2, vv_bool mask);
void __vv_mul_m(vv_float &dst, vv_float src1, float src2, vv_bool mask);
void __vv_mul_m(vv_float &dst, float src1, vv_float src2, vv_bool mask);

void __vv_mul(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_mul(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_mul(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_mul_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_mul_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_mul_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_mul(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_mul(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_mul(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_mul_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_mul_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_mul_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_mul(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_mul(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_mul(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_mul_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_mul_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_mul_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_mul(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_mul(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_mul(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_mul_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_mul_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_mul_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_mul(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_mul(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_mul(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_mul_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_mul_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_mul_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_mul(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_mul(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_mul(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_mul_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_mul_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_mul_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);

void __vv_div(vv_float &dst, vv_float src1, vv_float src2);
void __vv_div(vv_float &dst, vv_float src1, float src2);
void __vv_div(vv_float &dst, float src1, vv_float src2);
void __vv_div_m(vv_float &dst, vv_float src1, vv_float src2, vv_bool mask);
void __vv_div_m(vv_float &dst, vv_float src1, float src2, vv_bool mask);
void __vv_div_m(vv_float &dst, float src1, vv_float src2, vv_bool mask);

void __vv_div(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_div(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_div(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_div_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_div_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_div_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_div(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_div(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_div(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_div_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_div_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_div_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_div(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_div(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_div(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_div_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_div_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_div_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_div(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_div(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_div(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_div_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_div_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_div_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_div(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_div(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_div(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_div_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_div_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_div_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_div(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_div(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_div(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_div_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_div_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_div_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);

// land, lor, lxor
void __vv_land(vv_float &dst, vv_float src1, vv_float src2);
void __vv_land(vv_float &dst, vv_float src1, float src2);
void __vv_land(vv_float &dst, float src1, vv_float src2);
void __vv_land_m(vv_float &dst, vv_float src1, vv_float src2, vv_bool mask);
void __vv_land_m(vv_float &dst, vv_float src1, float src2, vv_bool mask);
void __vv_land_m(vv_float &dst, float src1, vv_float src2, vv_bool mask);

void __vv_land(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_land(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_land(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_land_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_land_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_land_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_land(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_land(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_land(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_land_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_land_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_land_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_land(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_land(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_land(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_land_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_land_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_land_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_land(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_land(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_land(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_land_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_land_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_land_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_land(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_land(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_land(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_land_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_land_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_land_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_land(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_land(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_land(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_land_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_land_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_land_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);

// lor
void __vv_lor(vv_float &dst, vv_float src1, vv_float src2);
void __vv_lor(vv_float &dst, vv_float src1, float src2);
void __vv_lor(vv_float &dst, float src1, vv_float src2);
void __vv_lor_m(vv_float &dst, vv_float src1, vv_float src2, vv_bool mask);
void __vv_lor_m(vv_float &dst, vv_float src1, float src2, vv_bool mask);
void __vv_lor_m(vv_float &dst, float src1, vv_float src2, vv_bool mask);

void __vv_lor(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_lor(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_lor(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_lor_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_lor_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_lor_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_lor(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_lor(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_lor(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_lor_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_lor_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_lor_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_lor(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_lor(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_lor(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_lor_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_lor_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_lor_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_lor(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_lor(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_lor(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_lor_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_lor_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_lor_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_lor(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_lor(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_lor(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_lor_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_lor_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_lor_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_lor(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_lor(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_lor(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_lor_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_lor_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_lor_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);

// xor
void __vv_lxor(vv_float &dst, vv_float src1, vv_float src2);
void __vv_lxor(vv_float &dst, vv_float src1, float src2);
void __vv_lxor(vv_float &dst, float src1, vv_float src2);
void __vv_lxor_m(vv_float &dst, vv_float src1, vv_float src2, vv_bool mask);
void __vv_lxor_m(vv_float &dst, vv_float src1, float src2, vv_bool mask);
void __vv_lxor_m(vv_float &dst, float src1, vv_float src2, vv_bool mask);

void __vv_lxor(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_lxor(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_lxor(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_lxor_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_lxor_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_lxor_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_lxor(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_lxor(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_lxor(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_lxor_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_lxor_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_lxor_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_lxor(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_lxor(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_lxor(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_lxor_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_lxor_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_lxor_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_lxor(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_lxor(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_lxor(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_lxor_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_lxor_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_lxor_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_lxor(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_lxor(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_lxor(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_lxor_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_lxor_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_lxor_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_lxor(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_lxor(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_lxor(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_lxor_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_lxor_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_lxor_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);

// %, and, or, xor
void __vv_rem(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_rem(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_rem(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_rem_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_rem_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_rem_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_rem(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_rem(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_rem(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_rem_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_rem_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_rem_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_rem(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_rem(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_rem(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_rem_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_rem_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_rem_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_rem(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_rem(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_rem(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_rem_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_rem_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_rem_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_rem(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_rem(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_rem(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_rem_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_rem_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_rem_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_rem(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_rem(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_rem(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_rem_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_rem_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_rem_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);

// and
void __vv_and(vv_bool &dst, vv_bool src1, vv_bool src2);
void __vv_and(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_and(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_and(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_and_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_and_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_and_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_and(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_and(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_and(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_and_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_and_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_and_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_and(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_and(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_and(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_and_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_and_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_and_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_and(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_and(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_and(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_and_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_and_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_and_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_and(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_and(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_and(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_and_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_and_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_and_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_and(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_and(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_and(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_and_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_and_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_and_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);
// or
void __vv_or(vv_bool &dst, vv_bool src1, vv_bool src2);
void __vv_or(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_or(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_or(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_or_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_or_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_or_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_or(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_or(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_or(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_or_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_or_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_or_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_or(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_or(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_or(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_or_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_or_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_or_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_or(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_or(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_or(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_or_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_or_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_or_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_or(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_or(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_or(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_or_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_or_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_or_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_or(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_or(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_or(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_or_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_or_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_or_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);
// xor
void __vv_xor(vv_bool &dst, vv_bool src1, vv_bool src2);
void __vv_xor(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_xor(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_xor(vv_int32 &dst, int src1, vv_int32 src2);
void __vv_xor_m(vv_int32 &dst, vv_int32 src1, vv_int32 src2, vv_bool mask);
void __vv_xor_m(vv_int32 &dst, vv_int32 src1, int src2, vv_bool mask);
void __vv_xor_m(vv_int32 &dst, int src1, vv_int32 src2, vv_bool mask);

void __vv_xor(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_xor(vv_int8 &dst, vv_int8 src1, int src2);
void __vv_xor(vv_int8 &dst, int src1, vv_int8 src2);
void __vv_xor_m(vv_int8 &dst, vv_int8 src1, vv_int8 src2, vv_bool mask);
void __vv_xor_m(vv_int8 &dst, vv_int8 src1, int src2, vv_bool mask);
void __vv_xor_m(vv_int8 &dst, int src1, vv_int8 src2, vv_bool mask);

void __vv_xor(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_xor(vv_int16 &dst, vv_int16 src1, int src2);
void __vv_xor(vv_int16 &dst, int src1, vv_int16 src2);
void __vv_xor_m(vv_int16 &dst, vv_int16 src1, vv_int16 src2, vv_bool mask);
void __vv_xor_m(vv_int16 &dst, vv_int16 src1, int src2, vv_bool mask);
void __vv_xor_m(vv_int16 &dst, int src1, vv_int16 src2, vv_bool mask);

void __vv_xor(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_xor(vv_uint32 &dst, vv_uint32 src1, int src2);
void __vv_xor(vv_uint32 &dst, int src1, vv_uint32 src2);
void __vv_xor_m(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2, vv_bool mask);
void __vv_xor_m(vv_uint32 &dst, vv_uint32 src1, int src2, vv_bool mask);
void __vv_xor_m(vv_uint32 &dst, int src1, vv_uint32 src2, vv_bool mask);

void __vv_xor(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_xor(vv_uint8 &dst, vv_uint8 src1, int src2);
void __vv_xor(vv_uint8 &dst, int src1, vv_uint8 src2);
void __vv_xor_m(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2, vv_bool mask);
void __vv_xor_m(vv_uint8 &dst, vv_uint8 src1, int src2, vv_bool mask);
void __vv_xor_m(vv_uint8 &dst, int src1, vv_uint8 src2, vv_bool mask);

void __vv_xor(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_xor(vv_uint16 &dst, vv_uint16 src1, int src2);
void __vv_xor(vv_uint16 &dst, int src1, vv_uint16 src2);
void __vv_xor_m(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2, vv_bool mask);
void __vv_xor_m(vv_uint16 &dst, vv_uint16 src1, int src2, vv_bool mask);
void __vv_xor_m(vv_uint16 &dst, int src1, vv_uint16 src2, vv_bool mask);

// ==, != , <, <=, >, >=
void __vv_eq(vv_float &dst, vv_float src1, vv_float src2);
void __vv_eq(vv_float &dst, vv_float src1, float src2);
void __vv_eq(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_eq(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_eq(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_eq(vv_int8 &dst, vv_int8 src1, int8_t src2);
void __vv_eq(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_eq(vv_int16 &dst, vv_int16 src1, int16_t src2);
void __vv_eq(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_eq(vv_uint32 &dst, vv_uint32 src1, uint32_t src2);
void __vv_eq(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_eq(vv_uint8 &dst, vv_uint8 src1, uint8_t src2);
void __vv_eq(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_eq(vv_uint16 &dst, vv_uint16 src1, uint16_t src2);

void __vv_ne(vv_float &dst, vv_float src1, vv_float src2);
void __vv_ne(vv_float &dst, vv_float src1, float src2);
void __vv_ne(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_ne(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_ne(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_ne(vv_int8 &dst, vv_int8 src1, int8_t src2);
void __vv_ne(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_ne(vv_int16 &dst, vv_int16 src1, int16_t src2);
void __vv_ne(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_ne(vv_uint32 &dst, vv_uint32 src1, uint32_t src2);
void __vv_ne(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_ne(vv_uint8 &dst, vv_uint8 src1, uint8_t src2);
void __vv_ne(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_ne(vv_uint16 &dst, vv_uint16 src1, uint16_t src2);

void __vv_lt(vv_float &dst, vv_float src1, vv_float src2);
void __vv_lt(vv_float &dst, vv_float src1, float src2);
void __vv_lt(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_lt(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_lt(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_lt(vv_int8 &dst, vv_int8 src1, int8_t src2);
void __vv_lt(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_lt(vv_int16 &dst, vv_int16 src1, int16_t src2);
void __vv_lt(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_lt(vv_uint32 &dst, vv_uint32 src1, uint32_t src2);
void __vv_lt(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_lt(vv_uint8 &dst, vv_uint8 src1, uint8_t src2);
void __vv_lt(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_lt(vv_uint16 &dst, vv_uint16 src1, uint16_t src2);

void __vv_ge(vv_float &dst, vv_float src1, vv_float src2);
void __vv_ge(vv_float &dst, vv_float src1, float src2);
void __vv_ge(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_ge(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_ge(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_ge(vv_int8 &dst, vv_int8 src1, int8_t src2);
void __vv_ge(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_ge(vv_int16 &dst, vv_int16 src1, int16_t src2);
void __vv_ge(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_ge(vv_uint32 &dst, vv_uint32 src1, uint32_t src2);
void __vv_ge(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_ge(vv_uint8 &dst, vv_uint8 src1, uint8_t src2);
void __vv_ge(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_ge(vv_uint16 &dst, vv_uint16 src1, uint16_t src2);

// ==, != , <, <=, >, >=
void __vv_setp_eq(vv_bool &dst, vv_float src1, vv_float src2);
void __vv_setp_eq(vv_bool &dst, vv_float src1, float src2);
void __vv_setp_eq(vv_bool &dst, vv_int32 src1, vv_int32 src2);
void __vv_setp_eq(vv_bool &dst, vv_int32 src1, int src2);
void __vv_setp_eq(vv_bool &dst, vv_int8 src1, vv_int8 src2);
void __vv_setp_eq(vv_bool &dst, vv_int8 src1, int src2);
void __vv_setp_eq(vv_bool &dst, vv_int16 src1, vv_int16 src2);
void __vv_setp_eq(vv_bool &dst, vv_int16 src1, int src2);
void __vv_setp_eq(vv_bool &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_setp_eq(vv_bool &dst, vv_uint32 src1, int src2);
void __vv_setp_eq(vv_bool &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_setp_eq(vv_bool &dst, vv_uint8 src1, int src2);
void __vv_setp_eq(vv_bool &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_setp_eq(vv_bool &dst, vv_uint16 src1, int src2);

void __vv_setp_ne(vv_bool &dst, vv_float src1, vv_float src2);
void __vv_setp_ne(vv_bool &dst, vv_float src1, float src2);
void __vv_setp_ne(vv_bool &dst, vv_int32 src1, vv_int32 src2);
void __vv_setp_ne(vv_bool &dst, vv_int32 src1, int src2);
void __vv_setp_ne(vv_bool &dst, vv_int8 src1, vv_int8 src2);
void __vv_setp_ne(vv_bool &dst, vv_int8 src1, int src2);
void __vv_setp_ne(vv_bool &dst, vv_int16 src1, vv_int16 src2);
void __vv_setp_ne(vv_bool &dst, vv_int16 src1, int src2);
void __vv_setp_ne(vv_bool &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_setp_ne(vv_bool &dst, vv_uint32 src1, int src2);
void __vv_setp_ne(vv_bool &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_setp_ne(vv_bool &dst, vv_uint8 src1, int src2);
void __vv_setp_ne(vv_bool &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_setp_ne(vv_bool &dst, vv_uint16 src1, int src2);

void __vv_setp_gt(vv_bool &dst, vv_float src1, vv_float src2);
void __vv_setp_gt(vv_bool &dst, vv_float src1, float src2);
void __vv_setp_gt(vv_bool &dst, vv_int32 src1, vv_int32 src2);
void __vv_setp_gt(vv_bool &dst, vv_int32 src1, int src2);
void __vv_setp_gt(vv_bool &dst, vv_int8 src1, vv_int8 src2);
void __vv_setp_gt(vv_bool &dst, vv_int8 src1, int src2);
void __vv_setp_gt(vv_bool &dst, vv_int16 src1, vv_int16 src2);
void __vv_setp_gt(vv_bool &dst, vv_int16 src1, int src2);
void __vv_setp_gt(vv_bool &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_setp_gt(vv_bool &dst, vv_uint32 src1, int src2);
void __vv_setp_gt(vv_bool &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_setp_gt(vv_bool &dst, vv_uint8 src1, int src2);
void __vv_setp_gt(vv_bool &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_setp_gt(vv_bool &dst, vv_uint16 src1, int src2);

void __vv_setp_lt(vv_bool &dst, vv_float src1, vv_float src2);
void __vv_setp_lt(vv_bool &dst, vv_float src1, float src2);
void __vv_setp_lt(vv_bool &dst, vv_int32 src1, vv_int32 src2);
void __vv_setp_lt(vv_bool &dst, vv_int32 src1, int src2);
void __vv_setp_lt(vv_bool &dst, vv_int8 src1, vv_int8 src2);
void __vv_setp_lt(vv_bool &dst, vv_int8 src1, int src2);
void __vv_setp_lt(vv_bool &dst, vv_int16 src1, vv_int16 src2);
void __vv_setp_lt(vv_bool &dst, vv_int16 src1, int src2);
void __vv_setp_lt(vv_bool &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_setp_lt(vv_bool &dst, vv_uint32 src1, int src2);
void __vv_setp_lt(vv_bool &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_setp_lt(vv_bool &dst, vv_uint8 src1, int src2);
void __vv_setp_lt(vv_bool &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_setp_lt(vv_bool &dst, vv_uint16 src1, int src2);

void __vv_setp_ge(vv_bool &dst, vv_float src1, vv_float src2);
void __vv_setp_ge(vv_bool &dst, vv_float src1, float src2);
void __vv_setp_ge(vv_bool &dst, vv_int32 src1, vv_int32 src2);
void __vv_setp_ge(vv_bool &dst, vv_int32 src1, int src2);
void __vv_setp_ge(vv_bool &dst, vv_int8 src1, vv_int8 src2);
void __vv_setp_ge(vv_bool &dst, vv_int8 src1, int src2);
void __vv_setp_ge(vv_bool &dst, vv_int16 src1, vv_int16 src2);
void __vv_setp_ge(vv_bool &dst, vv_int16 src1, int src2);
void __vv_setp_ge(vv_bool &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_setp_ge(vv_bool &dst, vv_uint32 src1, int src2);
void __vv_setp_ge(vv_bool &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_setp_ge(vv_bool &dst, vv_uint8 src1, int src2);
void __vv_setp_ge(vv_bool &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_setp_ge(vv_bool &dst, vv_uint16 src1, int src2);

void __vv_setp_le(vv_bool &dst, vv_float src1, vv_float src2);
void __vv_setp_le(vv_bool &dst, vv_float src1, float src2);
void __vv_setp_le(vv_bool &dst, vv_int32 src1, vv_int32 src2);
void __vv_setp_le(vv_bool &dst, vv_int32 src1, int src2);
void __vv_setp_le(vv_bool &dst, vv_int8 src1, vv_int8 src2);
void __vv_setp_le(vv_bool &dst, vv_int8 src1, int src2);
void __vv_setp_le(vv_bool &dst, vv_int16 src1, vv_int16 src2);
void __vv_setp_le(vv_bool &dst, vv_int16 src1, int src2);
void __vv_setp_le(vv_bool &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_setp_le(vv_bool &dst, vv_uint32 src1, int src2);
void __vv_setp_le(vv_bool &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_setp_le(vv_bool &dst, vv_uint8 src1, int src2);
void __vv_setp_le(vv_bool &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_setp_le(vv_bool &dst, vv_uint16 src1, int src2);

// unary, neg
void __vv_neg(vv_float &dst, vv_float src);
void __vv_neg(vv_int32 &dst, vv_int32 src);
void __vv_neg(vv_int8 &dst, vv_int8 src);
void __vv_neg(vv_int16 &dst, vv_int16 src);
void __vv_neg(vv_uint32 &dst, vv_uint32 src);
void __vv_neg(vv_uint8 &dst, vv_uint8 src);
void __vv_neg(vv_uint16 &dst, vv_uint16 src);

void __vv_neg_m(vv_float &dst, vv_float src, vv_bool mask);
void __vv_neg_m(vv_int32 &dst, vv_int32 src, vv_bool mask);
void __vv_neg_m(vv_int8 &dst, vv_int8 src, vv_bool mask);
void __vv_neg_m(vv_int16 &dst, vv_int16 src, vv_bool mask);
void __vv_neg_m(vv_uint32 &dst, vv_uint32 src, vv_bool mask);
void __vv_neg_m(vv_uint8 &dst, vv_uint8 src, vv_bool mask);
void __vv_neg_m(vv_uint16 &dst, vv_uint16 src, vv_bool mask);

// unary, not
void __vv_not(vv_int32 &dst, vv_int32 src);
void __vv_not(vv_int8 &dst, vv_int8 src);
void __vv_not(vv_int16 &dst, vv_int16 src);
void __vv_not(vv_uint32 &dst, vv_uint32 src);
void __vv_not(vv_uint8 &dst, vv_uint8 src);
void __vv_not(vv_uint16 &dst, vv_uint16 src);

void __vv_not_m(vv_int32 &dst, vv_int32 src, vv_bool mask);
void __vv_not_m(vv_int8 &dst, vv_int8 src, vv_bool mask);
void __vv_not_m(vv_int16 &dst, vv_int16 src, vv_bool mask);
void __vv_not_m(vv_uint32 &dst, vv_uint32 src, vv_bool mask);
void __vv_not_m(vv_uint8 &dst, vv_uint8 src, vv_bool mask);
void __vv_not_m(vv_uint16 &dst, vv_uint16 src, vv_bool mask);
// lnot
void __vv_lnot(vv_float &dst, vv_float src);
void __vv_lnot(vv_int32 &dst, vv_int32 src);
void __vv_lnot(vv_int8 &dst, vv_int8 src);
void __vv_lnot(vv_int16 &dst, vv_int16 src);
void __vv_lnot(vv_uint32 &dst, vv_uint32 src);
void __vv_lnot(vv_uint8 &dst, vv_uint8 src);
void __vv_lnot(vv_uint16 &dst, vv_uint16 src);

void __vv_lnot_m(vv_float &dst, vv_float src, vv_bool mask);
void __vv_lnot_m(vv_int32 &dst, vv_int32 src, vv_bool mask);
void __vv_lnot_m(vv_int8 &dst, vv_int8 src, vv_bool mask);
void __vv_lnot_m(vv_int16 &dst, vv_int16 src, vv_bool mask);
void __vv_lnot_m(vv_uint32 &dst, vv_uint32 src, vv_bool mask);
void __vv_lnot_m(vv_uint8 &dst, vv_uint8 src, vv_bool mask);
void __vv_lnot_m(vv_uint16 &dst, vv_uint16 src, vv_bool mask);

// load
void __vv_load(vv_float &dst, float *src);
void __vv_load(vv_int32 &dst, int *src);
void __vv_load(vv_int8 &dst, int8_t *src);
void __vv_load(vv_int16 &dst, int16_t *src);
void __vv_load(vv_uint32 &dst, uint32_t *src);
void __vv_load(vv_uint8 &dst, uint8_t *src);
void __vv_load(vv_uint16 &dst, uint16_t *src);

void __vv_load_m(vv_float &dst, float *src, vv_bool mask);
void __vv_load_m(vv_int32 &dst, int *src, vv_bool mask);
void __vv_load_m(vv_int8 &dst, int8_t *src, vv_bool mask);
void __vv_load_m(vv_int16 &dst, int16_t *src, vv_bool mask);
void __vv_load_m(vv_uint32 &dst, uint32_t *src, vv_bool mask);
void __vv_load_m(vv_uint8 &dst, uint8_t *src, vv_bool mask);
void __vv_load_m(vv_uint16 &dst, uint16_t *src, vv_bool mask);

void __vv_store(float *dst, vv_float src);
void __vv_store(int *dst, vv_int32 src);
void __vv_store(int8_t *dst, vv_int8 src);
void __vv_store(int16_t *dst, vv_int16 src);
void __vv_store(uint32_t *dst, vv_uint32 src);
void __vv_store(uint8_t *dst, vv_uint8 src);
void __vv_store(uint16_t *dst, vv_uint16 src);

void __vv_store_m(float *dst, vv_float src, vv_bool mask);
void __vv_store_m(int *dst, vv_int32 src, vv_bool mask);
void __vv_store_m(int8_t *dst, vv_int8 src, vv_bool mask);
void __vv_store_m(int16_t *dst, vv_int16 src, vv_bool mask);
void __vv_store_m(uint32_t *dst, vv_uint32 src, vv_bool mask);
void __vv_store_m(uint8_t *dst, vv_uint8 src, vv_bool mask);
void __vv_store_m(uint16_t *dst, vv_uint16 src, vv_bool mask);

// move
void __vv_move(vv_float &dst, vv_float src);
void __vv_move(vv_int32 &dst, vv_int32 src);
void __vv_move(vv_int8 &dst, vv_int8 src);
void __vv_move(vv_int16 &dst, vv_int16 src);
void __vv_move(vv_uint32 &dst, vv_uint32 src);
void __vv_move(vv_uint8 &dst, vv_uint8 src);
void __vv_move(vv_uint16 &dst, vv_uint16 src);

void __vv_move_m(vv_float &dst, vv_float src, vv_bool mask);
void __vv_move_m(vv_int32 &dst, vv_int32 src, vv_bool mask);
void __vv_move_m(vv_int8 &dst, vv_int8 src, vv_bool mask);
void __vv_move_m(vv_int16 &dst, vv_int16 src, vv_bool mask);
void __vv_move_m(vv_uint32 &dst, vv_uint32 src, vv_bool mask);
void __vv_move_m(vv_uint8 &dst, vv_uint8 src, vv_bool mask);
void __vv_move_m(vv_uint16 &dst, vv_uint16 src, vv_bool mask);

void __vv_move(vv_float &dst, float src);
void __vv_move(vv_int32 &dst, int src);
void __vv_move(vv_int8 &dst, int8_t src);
void __vv_move(vv_int16 &dst, int16_t src);
void __vv_move(vv_uint32 &dst, uint32_t src);
void __vv_move(vv_uint8 &dst, uint8_t src);
void __vv_move(vv_uint16 &dst, uint16_t src);

void __vv_move_m(vv_float &dst, vv_float src, vv_bool mask);
void __vv_move_m(vv_int32 &dst, vv_int32 src, vv_bool mask);
void __vv_move_m(vv_int8 &dst, vv_int8 src, vv_bool mask);
void __vv_move_m(vv_int16 &dst, vv_int16 src, vv_bool mask);
void __vv_move_m(vv_uint32 &dst, vv_uint32 src, vv_bool mask);
void __vv_move_m(vv_uint8 &dst, vv_uint8 src, vv_bool mask);
void __vv_move_m(vv_uint16 &dst, vv_uint16 src, vv_bool mask);

void __vv_sll(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_sll(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_sll(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_sll(vv_int8 &dst, vv_int8 src1, int8_t src2);
void __vv_sll(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_sll(vv_int16 &dst, vv_int16 src1, int16_t src2);
void __vv_sll(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_sll(vv_uint32 &dst, vv_uint32 src1, uint32_t src2);
void __vv_sll(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_sll(vv_uint8 &dst, vv_uint8 src1, uint8_t src2);
void __vv_sll(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_sll(vv_uint16 &dst, vv_uint16 src1, uint16_t src2);

void __vv_sll(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_sll(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_sll(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_sll(vv_int8 &dst, vv_int8 src1, int8_t src2);
void __vv_sll(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_sll(vv_int16 &dst, vv_int16 src1, int16_t src2);
void __vv_sll(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_sll(vv_uint32 &dst, vv_uint32 src1, uint32_t src2);
void __vv_sll(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_sll(vv_uint8 &dst, vv_uint8 src1, uint8_t src2);
void __vv_sll(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_sll(vv_uint16 &dst, vv_uint16 src1, uint16_t src2);

void __vv_srl(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_srl(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_srl(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_srl(vv_int8 &dst, vv_int8 src1, int8_t src2);
void __vv_srl(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_srl(vv_int16 &dst, vv_int16 src1, int16_t src2);
void __vv_srl(vv_uint32 &dst, vv_uint32 src1, vv_uint32 src2);
void __vv_srl(vv_uint32 &dst, vv_uint32 src1, uint32_t src2);
void __vv_srl(vv_uint8 &dst, vv_uint8 src1, vv_uint8 src2);
void __vv_srl(vv_uint8 &dst, vv_uint8 src1, uint8_t src2);
void __vv_srl(vv_uint16 &dst, vv_uint16 src1, vv_uint16 src2);
void __vv_srl(vv_uint16 &dst, vv_uint16 src1, uint16_t src2);

void __vv_sra(vv_int32 &dst, vv_int32 src1, vv_int32 src2);
void __vv_sra(vv_int32 &dst, vv_int32 src1, int src2);
void __vv_sra(vv_int8 &dst, vv_int8 src1, vv_int8 src2);
void __vv_sra(vv_int8 &dst, vv_int8 src1, int8_t src2);
void __vv_sra(vv_int16 &dst, vv_int16 src1, vv_int16 src2);
void __vv_sra(vv_int16 &dst, vv_int16 src1, int16_t src2);
