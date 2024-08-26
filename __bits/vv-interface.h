#pragma once
struct vv_general {
  int regNum;
  vv_general();
};
struct vv_float : public vv_general {};
struct vv_int32 : public vv_general {};
struct vv_bool : public vv_general {};

void __vv_add(vv_float &a, vv_float b, vv_float c);
void __vv_add(vv_float &a, vv_float b, float c);
void __vv_add(vv_int32 &a, vv_int32 b, vv_int32 c);
void __vv_add(vv_int32 &a, vv_int32 b, int c);

void __vv_mul(vv_float &a, vv_float b, vv_float c);
void __vv_mul(vv_float &a, vv_float b, float c);
void __vv_mul(vv_int32 &a, vv_int32 b, vv_int32 c);
void __vv_mul(vv_int32 &a, vv_int32 b, int c);

void __vv_sub(vv_float &a, vv_float b, vv_float c);
void __vv_sub(vv_float &a, vv_float b, float c);
void __vv_sub(vv_int32 &a, vv_int32 b, vv_int32 c);
void __vv_sub(vv_int32 &a, vv_int32 b, int c);

void __vv_div(vv_float &a, vv_float b, vv_float c);
void __vv_div(vv_float &a, vv_float b, float c);
void __vv_div(vv_int32 &a, vv_int32 b, vv_int32 c);
void __vv_div(vv_int32 &a, vv_int32 b, int c);

void __vv_neg(vv_float &a, vv_float b);
void __vv_neg(vv_int32 &a, vv_int32 b);

void __vv_move(vv_float &a, vv_float b);
void __vv_move(vv_float &a, float b);
void __vv_move(vv_int32 &a, vv_int32 b);
void __vv_move(vv_int32 &a, int b);
void __vv_move(vv_bool &a, vv_bool b);

void __vv_not(vv_int32 &a, vv_int32 b);
void __vv_lnot(vv_int32 &a, vv_int32 b);
void __vv_and(vv_int32 &a, vv_int32 b, vv_int32 c);
void __vv_and(vv_int32 &a, vv_int32 b, int c);
void __vv_or(vv_int32 &a, vv_int32 b, vv_int32 c);
void __vv_or(vv_int32 &a, vv_int32 b, int c);
void __vv_xor(vv_int32 &a, vv_int32 b, vv_int32 c);
void __vv_xor(vv_int32 &a, vv_int32 b, int c);

void __vv_load(vv_float &a, float *b);
void __vv_load(vv_int32 &a, int *b);
void __vv_store(float *a, vv_float b);
void __vv_store(int *a, vv_int32 b);

void __vv_load(vv_float &a, float *b, int len);
void __vv_load(vv_int32 &a, int *b, int len);
void __vv_store(float *a, vv_float b, int len);
void __vv_store(int *a, vv_int32 b, int len);

//---

void __vv_add_m(vv_float &a, vv_float b, vv_float c, vv_bool p);
void __vv_add_m(vv_float &a, vv_float b, float c, vv_bool p);
void __vv_add_m(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_add_m(vv_int32 &a, vv_int32 b, int c, vv_bool p);

void __vv_mul_m(vv_float &a, vv_float b, vv_float c, vv_bool p);
void __vv_mul_m(vv_float &a, vv_float b, float c, vv_bool p);
void __vv_mul_m(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_mul_m(vv_int32 &a, vv_int32 b, int c, vv_bool p);

void __vv_sub_m(vv_float &a, vv_float b, vv_float c, vv_bool p);
void __vv_sub_m(vv_float &a, vv_float b, float c, vv_bool p);
void __vv_sub_m(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_sub_m(vv_int32 &a, vv_int32 b, int c, vv_bool p);

void __vv_div_m(vv_float &a, vv_float b, vv_float c, vv_bool p);
void __vv_div_m(vv_float &a, vv_float b, float c, vv_bool p);
void __vv_div_m(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_div_m(vv_int32 &a, vv_int32 b, int c, vv_bool p);

void __vv_neg_m(vv_float &a, vv_float b, vv_bool p);
void __vv_neg_m(vv_int32 &a, vv_int32 b, vv_bool p);

void __vv_move_m(vv_float &a, vv_float b, vv_bool p);
void __vv_move_m(vv_float &a, float b, vv_bool p);
void __vv_move_m(vv_int32 &a, vv_int32 b, vv_bool p);
void __vv_move_m(vv_int32 &a, int b, vv_bool p);

void __vv_not_m(vv_int32 &a, vv_int32 b, vv_bool p);
void __vv_lnot_m(vv_int32 &a, vv_int32 b, vv_bool p);
void __vv_and_m(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_and_m(vv_int32 &a, vv_int32 b, int c, vv_bool p);
void __vv_or_m(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_or_m(vv_int32 &a, vv_int32 b, int c, vv_bool p);
void __vv_xor_m(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_xor_m(vv_int32 &a, vv_int32 b, int c, vv_bool p);
// ---

void __vv_add_z(vv_float &a, vv_float b, vv_float c, vv_bool p);
void __vv_add_z(vv_float &a, vv_float b, float c, vv_bool p);
void __vv_add_z(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_add_z(vv_int32 &a, vv_int32 b, int c, vv_bool p);

void __vv_mul_z(vv_float &a, vv_float b, vv_float c, vv_bool p);
void __vv_mul_z(vv_float &a, vv_float b, float c, vv_bool p);
void __vv_mul_z(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_mul_z(vv_int32 &a, vv_int32 b, int c, vv_bool p);

void __vv_sub_z(vv_float &a, vv_float b, vv_float c, vv_bool p);
void __vv_sub_z(vv_float &a, vv_float b, float c, vv_bool p);
void __vv_sub_z(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_sub_z(vv_int32 &a, vv_int32 b, int c, vv_bool p);

void __vv_div_z(vv_float &a, vv_float b, vv_float c, vv_bool p);
void __vv_div_z(vv_float &a, vv_float b, float c, vv_bool p);
void __vv_div_z(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_div_z(vv_int32 &a, vv_int32 b, int c, vv_bool p);

void __vv_neg_z(vv_float &a, vv_float b, vv_bool p);
void __vv_neg_z(vv_int32 &a, vv_int32 b, vv_bool p);

void __vv_move_z(vv_float &a, vv_float b, vv_bool p);
void __vv_move_z(vv_float &a, float b, vv_bool p);
void __vv_move_z(vv_int32 &a, vv_int32 b, vv_bool p);
void __vv_move_z(vv_int32 &a, int b, vv_bool p);

void __vv_not_z(vv_int32 &a, vv_int32 b, vv_bool p);
void __vv_lnot_z(vv_int32 &a, vv_int32 b, vv_bool p);
void __vv_and_z(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_and_z(vv_int32 &a, vv_int32 b, int c, vv_bool p);
void __vv_or_z(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_or_z(vv_int32 &a, vv_int32 b, int c, vv_bool p);
void __vv_xor_z(vv_int32 &a, vv_int32 b, vv_int32 c, vv_bool p);
void __vv_xor_z(vv_int32 &a, vv_int32 b, int c, vv_bool p);

//------------------------------------------------
void __vv_setp_eq(vv_bool &p, vv_int32 a, vv_int32 b);
void __vv_setp_ne(vv_bool &p, vv_int32 a, vv_int32 b);
void __vv_setp_lt(vv_bool &p, vv_int32 a, vv_int32 b);
void __vv_setp_gt(vv_bool &p, vv_int32 a, vv_int32 b);
void __vv_setp_le(vv_bool &p, vv_int32 a, vv_int32 b);
void __vv_setp_ge(vv_bool &p, vv_int32 a, vv_int32 b);

void __vv_setp_eq(vv_bool &p, vv_int32 a, int b);
void __vv_setp_ne(vv_bool &p, vv_int32 a, int b);
void __vv_setp_lt(vv_bool &p, vv_int32 a, int b);
void __vv_setp_gt(vv_bool &p, vv_int32 a, int b);
void __vv_setp_le(vv_bool &p, vv_int32 a, int b);
void __vv_setp_ge(vv_bool &p, vv_int32 a, int b);

void __vv_setp_eq(vv_bool &p, vv_float a, vv_float b);
void __vv_setp_ne(vv_bool &p, vv_float a, vv_float b);
void __vv_setp_lt(vv_bool &p, vv_float a, vv_float b);
void __vv_setp_gt(vv_bool &p, vv_float a, vv_float b);
void __vv_setp_le(vv_bool &p, vv_float a, vv_float b);
void __vv_setp_ge(vv_bool &p, vv_float a, vv_float b);

void __vv_setp_eq(vv_bool &p, vv_float a, float b);
void __vv_setp_ne(vv_bool &p, vv_float a, float b);
void __vv_setp_lt(vv_bool &p, vv_float a, float b);
void __vv_setp_gt(vv_bool &p, vv_float a, float b);
void __vv_setp_le(vv_bool &p, vv_float a, float b);
void __vv_setp_ge(vv_bool &p, vv_float a, float b);

void __vv_not(vv_bool &p, vv_bool a);
