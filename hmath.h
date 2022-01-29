#include <smmintrin.h>
#include <immintrin.h>

/* Constant definitions */
#define PI_F 3.14159265358979f
#define PI_D 3.14159265358979

/* Declaration of types */
typedef union {
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };
} vec4;

typedef union {
    struct { float x, y, z; };
    struct { float r, g, b; };
} vec3;

typedef union {
    struct { float x, y; };
    struct { float r, g; };
} vec2;

typedef union {
    struct { double x, y, z, w; };
    struct { double r, g, b, a; };
} dvec4;

typedef union {
    struct { double x, y, z; };
    struct { double r, g, b; };
} dvec3;

typedef union {
    struct { double x, y; };
    struct { double r, g; };
} dvec2;

typedef union {
    float data[4][4];
    struct { vec4 rows[4]; };
} mat4;

typedef union {
    float data[3][3];
    struct { vec3 rows[3]; };
} mat3;

typedef union {
    float data[2][2];
    struct { vec2 rows[2]; };
} mat2;

typedef union {
    double data[4][4];
    struct { dvec4 rows[4]; };
} dmat4;

typedef union {
    double data[3][3];
    struct { dvec3 rows[3]; };
} dmat3;

typedef union {
    double data[2][2];
    struct { dvec2 rows[2]; };
} dmat2;

/* vec4 functions */
inline int hm_vec4_equal(vec4 v1, vec4 v2)
{
	return (*(unsigned long long*)&v1.x == *(unsigned long long*)&v2.x) && 
		   (*(unsigned long long*)&v1.z == *(unsigned long long*)&v2.z);
}

inline vec4 hm_vec4_add(vec4* restrict v1, vec4* restrict v2)
{
	__m128 a = _mm_load_ps((const float*)v1);
	__m128 b = _mm_load_ps((const float*)v2);
	return *(vec4*)_mm_add_ps(a, b).m128_f32;
}

inline vec4 hm_vec4_sub(vec4* restrict v1, vec4* restrict v2)
{
	__m128 a = _mm_load_ps((const float*)v1);
	__m128 b = _mm_load_ps((const float*)v2);
	return *(vec4*)_mm_sub_ps(a, b).m128_f32;
}

inline float hm_vec4_dot(vec4* restrict v1, vec4* restrict v2)
{
	__m128 a = _mm_load_ps((const float*)v1);
	__m128 b = _mm_load_ps((const float*)v2);

	return _mm_dp_ps(a, b, 0xff).m128_f32[0];
}

inline vec4 hm_vec4_cross(vec4* restrict v1, vec4* restrict v2)
{
	__m128 a1 = _mm_load_ps((const float*)v1);
	__m128 a2 = _mm_load_ps((const float*)v2);
	__m128 a = _mm_permute_ps(a1, _MM_PERM_DACB);
	__m128 b = _mm_permute_ps(a2, _MM_PERM_DBAC);
	__m128 c = _mm_permute_ps(a1, _MM_PERM_DBAC);
	__m128 d = _mm_permute_ps(a2, _MM_PERM_DACB);

	__m128 e = _mm_mul_ps(a, b);
	__m128 f = _mm_mul_ps(c, d);

	return *(vec4*)_mm_sub_ps(e, f).m128_f32;
}

inline vec4 hm_vec4_scalar_mul(vec4* restrict v, float s)
{
	__m128 scalar = _mm_set_ps(s, s, s, s);
	__m128 a = _mm_load_ps((const float*)v);

	return *(vec4*)_mm_mul_ps(a, scalar).m128_f32;
}

inline vec4 hm_vec4_abs(vec4* restrict v)
{
	__m128 minus_two = _mm_set1_ps(-2.0f);
	__m128 constant = _mm_set1_ps(0);
	__m128 a = _mm_load_ps((const float*)v);
	__m128 b = _mm_cmplt_ps(a, constant);
	__m128 mask = _mm_add_ps(_mm_and_ps(minus_two, b), _mm_set_ps(1.0f, 1.0f, 1.0f, 1.0f));
	return *(vec4*)_mm_mul_ps(a, mask).m128_f32;
}

inline vec4 hm_vec4_normalize(vec4* restrict v)
{
	__m128 a = _mm_load_ps((const float*)v);
	__m128 b = _mm_dp_ps(a, a, 0xff);
	__m128 c = _mm_rsqrt_ps(b);

	return *(vec4*)_mm_mul_ps(c, a).m128_f32;
}

inline float hm_vec4_length(vec4* restrict v)
{
	__m128 a = _mm_load_ps((const float*)v);
	__m128 b = _mm_dp_ps(a, a, 0xff);
	return _mm_sqrt_ps(b).m128_f32[0];
}

/* vec3 functions */

/* vec2 functions */

/* dvec4 functions */

/* dvec3 functions */

/* dvec2 functions */

/* mat4 functions */
inline vec4 hm_mat4_multiply_vec4(mat4* restrict m, vec4* restrict v)
{
	__m128 vec = _mm_load_ps((const float*)v);
	__m128 r1 = _mm_load_ps((const float*)&m->data[0][0]);
	__m128 r2 = _mm_load_ps((const float*)&m->data[1][0]);
	__m128 r3 = _mm_load_ps((const float*)&m->data[2][0]);
	__m128 r4 = _mm_load_ps((const float*)&m->data[3][0]);

	__m128 prod1 = _mm_dp_ps(r1, vec, 0xFF);
	__m128 prod2 = _mm_dp_ps(r2, vec, 0xFF);
	__m128 prod3 = _mm_dp_ps(r3, vec, 0xFF);
	__m128 prod4 = _mm_dp_ps(r4, vec, 0xFF);

	__m128 result = _mm_shuffle_ps(_mm_movelh_ps(prod1, prod2), _mm_movelh_ps(prod3, prod4), _MM_SHUFFLE(2, 0, 2, 0));

	return *(vec4*)result.m128_f32;
}

inline mat4 hm_mat4_multiply(mat4* restrict m1, mat4* restrict m2)
{
	__m128 row1 = _mm_load_ps((const float*)&m1->data[0][0]);
	__m128 row2 = _mm_load_ps((const float*)&m1->data[1][0]);
	__m128 row3 = _mm_load_ps((const float*)&m1->data[2][0]);
	__m128 row4 = _mm_load_ps((const float*)&m1->data[3][0]);

	mat4 result;

	for (int i = 0; i < 4; i++)
	{
		__m128 brod1 = _mm_set1_ps(m2->data[i][0]);
		__m128 brod2 = _mm_set1_ps(m2->data[i][1]);
		__m128 brod3 = _mm_set1_ps(m2->data[i][2]);
		__m128 brod4 = _mm_set1_ps(m2->data[i][3]);

		__m128 row = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(brod1, row1),
				_mm_mul_ps(brod2, row2)),
			_mm_add_ps(
				_mm_mul_ps(brod3, row3),
				_mm_mul_ps(brod4, row4)));
		_mm_store_ps((float*)&result.data[i][0], row);
	}

	return result;
}

inline mat4 hm_mat4_scalar_product(mat4* restrict m, float scalar)
{
	__m128 t1 = _mm_load_ps((const float*)&m->data[0][0]);
	__m128 t2 = _mm_load_ps((const float*)&m->data[1][0]);
	__m128 t3 = _mm_load_ps((const float*)&m->data[2][0]);
	__m128 t4 = _mm_load_ps((const float*)&m->data[3][0]);
	__m128 s = _mm_set1_ps(scalar);

	t1 = _mm_mul_ps(t1, s);
	t2 = _mm_mul_ps(t2, s);
	t3 = _mm_mul_ps(t3, s);
	t4 = _mm_mul_ps(t4, s);

	mat4 result;
	_mm_store_ps((float*)&result.data[0][0], t1);
	_mm_store_ps((float*)&result.data[1][0], t2);
	_mm_store_ps((float*)&result.data[2][0], t3);
	_mm_store_ps((float*)&result.data[3][0], t4);

	return result;
}

/* mat3 functions */

/* mat2 functions */

/* dmat4 functions */

/* dmat3 functions */

/* dmat2 functions */