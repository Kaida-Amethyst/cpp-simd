
struct vv_general {
  int regNum;
  vv_general();
};
struct vv_float : public vv_general {};
struct vv_int32 : public vv_general {};

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

void __vv_not(vv_int32 &a, vv_int32 b);
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
