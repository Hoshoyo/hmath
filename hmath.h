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
	__m128 a = _mm_load_ps((const float*)v1);
	__m128 b = _mm_load_ps((const float*)v2);

	__m128 aa = _mm_permute_ps(a, _MM_PERM_DACB);
	__m128 bb = _mm_permute_ps(b, _MM_PERM_DBAC);
	__m128 cc = _mm_permute_ps(a, _MM_PERM_DBAC);
	__m128 dd = _mm_permute_ps(b, _MM_PERM_DACB);

	__m128 e = _mm_mul_ps(aa, bb);
	__m128 f = _mm_mul_ps(cc, dd);

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
	__m128 zero = _mm_set1_ps(0);	
	__m128 a = _mm_load_ps((const float*)v);

	__m128 comp = _mm_cmplt_ps(a, zero);
	__m128 mask = _mm_add_ps(_mm_and_ps(minus_two, comp), _mm_set_ps(1.0f, 1.0f, 1.0f, 1.0f));
	
	return *(vec4*)_mm_mul_ps(a, mask).m128_f32;
}

inline vec4 hm_vec4_normalize_fast(vec4* restrict v)
{
	__m128 a = _mm_load_ps((const float*)v);
	__m128 dot = _mm_dp_ps(a, a, 0xff);
	__m128 rsqroot = _mm_rsqrt_ps(dot);

	return *(vec4*)_mm_mul_ps(a, rsqroot).m128_f32;
}

inline vec4 hm_vec4_normalize(vec4* restrict v)
{
	__m128 a = _mm_load_ps((const float*)v);
	__m128 dot = _mm_dp_ps(a, a, 0xff);
	__m128 sqroot = _mm_sqrt_ps(dot);

	return *(vec4*)_mm_div_ps(a, sqroot).m128_f32;
}

inline float hm_vec4_length(vec4* restrict v)
{
	__m128 a = _mm_load_ps((const float*)v);
	__m128 dot = _mm_dp_ps(a, a, 0xff);

	return _mm_sqrt_ps(dot).m128_f32[0];
}

/* vec3 functions */
inline int hm_vec3_equal(vec3 v1, vec3 v2)
{
	return (*(unsigned long long*)&v1.x == *(unsigned long long*)&v2.x) && (v1.z == v2.z);
}

inline vec3 hm_vec3_add(vec3* restrict v1, vec3* restrict v2)
{
	__m128i mask = _mm_set_epi32(0, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v1, mask);
	__m128 b = _mm_maskload_ps((const float*)v2, mask);

	return *(vec3*)_mm_add_ps(a, b).m128_f32;
}

inline vec3 hm_vec3_sub(vec3* restrict v1, vec3* restrict v2)
{
	__m128i mask = _mm_set_epi32(0, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v1, mask);
	__m128 b = _mm_maskload_ps((const float*)v2, mask);

	return *(vec3*)_mm_sub_ps(a, b).m128_f32;
}

inline float hm_vec3_dot(vec3* restrict v1, vec3* restrict v2)
{
	__m128i mask = _mm_set_epi32(0, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v1, mask);
	__m128 b = _mm_maskload_ps((const float*)v2, mask);

	return _mm_dp_ps(a, b, 0xff).m128_f32[0];
}

inline vec3 hm_vec3_cross(vec3* restrict v1, vec3* restrict v2)
{
	__m128i mask = _mm_set_epi32(0, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v1, mask);
	__m128 b = _mm_maskload_ps((const float*)v2, mask);

	__m128 aa = _mm_permute_ps(a, _MM_PERM_DACB);
	__m128 bb = _mm_permute_ps(b, _MM_PERM_DBAC);
	__m128 cc = _mm_permute_ps(a, _MM_PERM_DBAC);
	__m128 dd = _mm_permute_ps(b, _MM_PERM_DACB);

	__m128 e = _mm_mul_ps(aa, bb);
	__m128 f = _mm_mul_ps(cc, dd);

	return *(vec3*)_mm_sub_ps(e, f).m128_f32;
}

inline vec3 hm_vec3_scalar_mul(vec3* restrict v, float s)
{
	__m128 scalar = _mm_set_ps(s, s, s, s);
	__m128i mask = _mm_set_epi32(0, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v, mask);

	return *(vec3*)_mm_mul_ps(a, scalar).m128_f32;
}

inline vec3 hm_vec3_abs(vec3* restrict v)
{
	__m128 minus_two = _mm_set1_ps(-2.0f);
	__m128 zero = _mm_set1_ps(0);	
	__m128i loadmask = _mm_set_epi32(0, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v, loadmask);

	__m128 comp = _mm_cmplt_ps(a, zero);
	__m128 mask = _mm_add_ps(_mm_and_ps(minus_two, comp), _mm_set_ps(1.0f, 1.0f, 1.0f, 1.0f));
	
	return *(vec3*)_mm_mul_ps(a, mask).m128_f32;
}

inline vec3 hm_vec3_normalize_fast(vec3* restrict v)
{
	__m128i loadmask = _mm_set_epi32(0, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v, loadmask);
	__m128 dot = _mm_dp_ps(a, a, 0xff);
	__m128 rsqroot = _mm_rsqrt_ps(dot);

	return *(vec3*)_mm_mul_ps(a, rsqroot).m128_f32;
}

inline vec3 hm_vec3_normalize(vec3* restrict v)
{
	__m128i loadmask = _mm_set_epi32(0, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v, loadmask);
	__m128 dot = _mm_dp_ps(a, a, 0xff);
	__m128 sqroot = _mm_sqrt_ps(dot);

	return *(vec3*)_mm_div_ps(a, sqroot).m128_f32;
}

inline float hm_vec3_length(vec3* restrict v)
{
	__m128i loadmask = _mm_set_epi32(0, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v, loadmask);
	__m128 dot = _mm_dp_ps(a, a, 0xff);

	return _mm_sqrt_ps(dot).m128_f32[0];
}

/* vec2 functions */
inline int hm_vec2_equal(vec2 v1, vec2 v2)
{
	return (*(unsigned long long*)&v1.x == *(unsigned long long*)&v2.x);
}

inline vec2 hm_vec2_add(vec2* restrict v1, vec2* restrict v2)
{
	__m128i mask = _mm_set_epi32(0, 0, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v1, mask);
	__m128 b = _mm_maskload_ps((const float*)v2, mask);

	return *(vec2*)_mm_add_ps(a, b).m128_f32;
}

inline vec2 hm_vec2_sub(vec2* restrict v1, vec2* restrict v2)
{
	__m128i mask = _mm_set_epi32(0, 0, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v1, mask);
	__m128 b = _mm_maskload_ps((const float*)v2, mask);

	return *(vec2*)_mm_sub_ps(a, b).m128_f32;
}

inline float hm_vec2_dot(vec2* restrict v1, vec2* restrict v2)
{
	__m128i mask = _mm_set_epi32(0, 0, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v1, mask);
	__m128 b = _mm_maskload_ps((const float*)v2, mask);

	return _mm_dp_ps(a, b, 0xff).m128_f32[0];
}

inline vec2 hm_vec2_cross(vec2* restrict v1, vec2* restrict v2)
{
	__m128i mask = _mm_set_epi32(0, 0, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v1, mask);
	__m128 b = _mm_maskload_ps((const float*)v2, mask);

	__m128 aa = _mm_permute_ps(a, _MM_PERM_DACB);
	__m128 bb = _mm_permute_ps(b, _MM_PERM_DBAC);
	__m128 cc = _mm_permute_ps(a, _MM_PERM_DBAC);
	__m128 dd = _mm_permute_ps(b, _MM_PERM_DACB);

	__m128 e = _mm_mul_ps(aa, bb);
	__m128 f = _mm_mul_ps(cc, dd);

	return *(vec2*)_mm_sub_ps(e, f).m128_f32;
}

inline vec2 hm_vec2_scalar_mul(vec2* restrict v, float s)
{
	__m128 scalar = _mm_set_ps(s, s, s, s);
	__m128i mask = _mm_set_epi32(0, 0, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v, mask);

	return *(vec2*)_mm_mul_ps(a, scalar).m128_f32;
}

inline vec2 hm_vec2_abs(vec2* restrict v)
{
	__m128 minus_two = _mm_set1_ps(-2.0f);
	__m128 zero = _mm_set1_ps(0);	
	__m128i loadmask = _mm_set_epi32(0, 0, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v, loadmask);

	__m128 comp = _mm_cmplt_ps(a, zero);
	__m128 mask = _mm_add_ps(_mm_and_ps(minus_two, comp), _mm_set_ps(1.0f, 1.0f, 1.0f, 1.0f));
	
	return *(vec2*)_mm_mul_ps(a, mask).m128_f32;
}

inline vec2 hm_vec2_normalize_fast(vec2* restrict v)
{
	__m128i loadmask = _mm_set_epi32(0, 0, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v, loadmask);
	__m128 dot = _mm_dp_ps(a, a, 0xff);
	__m128 rsqroot = _mm_rsqrt_ps(dot);

	return *(vec2*)_mm_mul_ps(a, rsqroot).m128_f32;
}

inline vec2 hm_vec2_normalize(vec2* restrict v)
{
	__m128i loadmask = _mm_set_epi32(0, 0, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v, loadmask);
	__m128 dot = _mm_dp_ps(a, a, 0xff);
	__m128 sqroot = _mm_sqrt_ps(dot);

	return *(vec2*)_mm_div_ps(a, sqroot).m128_f32;
}

inline float hm_vec2_length(vec2* restrict v)
{
	__m128i loadmask = _mm_set_epi32(0, 0, 0xffffffff, 0xffffffff);
	__m128 a = _mm_maskload_ps((const float*)v, loadmask);
	__m128 dot = _mm_dp_ps(a, a, 0xff);

	return _mm_sqrt_ps(dot).m128_f32[0];
}

/* dvec4 functions */
inline int hm_dvec4_equal(dvec4 v1, dvec4 v2)
{
	return (*(unsigned long long*)&v1.x == *(unsigned long long*)&v2.x) && 
		   (*(unsigned long long*)&v1.y == *(unsigned long long*)&v2.y) &&
		   (*(unsigned long long*)&v1.z == *(unsigned long long*)&v2.z) &&
		   (*(unsigned long long*)&v1.w == *(unsigned long long*)&v2.w);
}

inline dvec4 hm_dvec4_add(dvec4* restrict v1, dvec4* restrict v2)
{
	__m256d a = _mm256_load_pd((const double*)v1);
	__m256d b = _mm256_load_pd((const double*)v2);
	return *(dvec4*)_mm256_add_pd(a, b).m256d_f64;
}

inline dvec4 hm_dvec4_sub(dvec4* restrict v1, dvec4* restrict v2)
{
	__m256d a = _mm256_load_pd((const double*)v1);
	__m256d b = _mm256_load_pd((const double*)v2);
	return *(dvec4*)_mm256_sub_pd(a, b).m256d_f64;
}

inline double hm_dvec4_dot(dvec4* restrict v1, dvec4* restrict v2)
{
	__m256d a = _mm256_load_pd((const double*)v1);
	__m256d b = _mm256_load_pd((const double*)v2);

	__m256d m = _mm256_mul_pd(a, b);
	__m256d h = _mm256_hadd_pd(m, m);

	return h.m256d_f64[0] + h.m256d_f64[2];
}

inline dvec4 hm_dvec4_cross(dvec4* restrict v1, dvec4* restrict v2)
{
	__m256d a = _mm256_load_pd((const double*)v1);
	__m256d b = _mm256_load_pd((const double*)v2);

	__m256d aa = _mm256_permute4x64_pd(a, _MM_PERM_DACB);
	__m256d bb = _mm256_permute4x64_pd(b, _MM_PERM_DBAC);
	__m256d cc = _mm256_permute4x64_pd(a, _MM_PERM_DBAC);
	__m256d dd = _mm256_permute4x64_pd(b, _MM_PERM_DACB);

	__m256d e = _mm256_mul_pd(aa, bb);
	__m256d f = _mm256_mul_pd(cc, dd);

	return *(dvec4*)_mm256_sub_pd(e, f).m256d_f64;
}

inline dvec4 hm_dvec4_scalar_mul(dvec4* restrict v, double s)
{
	__m256d scalar = _mm256_set_pd(s, s, s, s);
	__m256d a = _mm256_load_pd((const double*)v);

	return *(dvec4*)_mm256_mul_pd(a, scalar).m256d_f64;
}

inline dvec4 hm_dvec4_abs(dvec4* restrict v)
{
	__m256d minus_two = _mm256_set1_pd(-2.0);
	__m256d zero = _mm256_set1_pd(0);
	__m256d a = _mm256_load_pd((const double*)v);

	__m256d comp = _mm256_cmp_pd(a, zero, _CMP_LT_OS);
	__m256d mask = _mm256_add_pd(_mm256_and_pd(minus_two, comp), _mm256_set_pd(1.0, 1.0, 1.0, 1.0));

	return *(dvec4*)_mm256_mul_pd(a, mask).m256d_f64;
}

inline dvec4 hm_dvec4_normalize(dvec4* restrict v)
{
	__m256d a = _mm256_load_pd((const double*)v);

	__m256d aa = _mm256_mul_pd(a, a);
	__m256d hadd = _mm256_hadd_pd(aa, aa);
	__m256d dot = _mm256_set1_pd(hadd.m256d_f64[1] + hadd.m256d_f64[3]);
	__m256d len = _mm256_sqrt_pd(dot);

	return *(dvec4*)_mm256_div_pd(a, len).m256d_f64;
}

inline double hm_dvec4_length(dvec4* restrict v)
{
	__m256d a = _mm256_load_pd((const double*)v);

	__m256d aa = _mm256_mul_pd(a, a);
	__m256d hadd = _mm256_hadd_pd(aa, aa);
	__m256d dot = _mm256_set1_pd(hadd.m256d_f64[1] + hadd.m256d_f64[3]);
	
	return _mm256_sqrt_pd(dot).m256d_f64[0];
}

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

inline vec3 sm_mat4_multiply_vec3(mat4* restrict m, vec3* restrict v)
{
	__m128i mask = _mm_set_epi32(0, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128 vec = _mm_maskload_ps((const float*)v, mask);
	vec.m128_f32[3] = 1.0f;
	__m128 r1 = _mm_load_ps((const float*)&m->data[0][0]);
	__m128 r2 = _mm_load_ps((const float*)&m->data[1][0]);
	__m128 r3 = _mm_load_ps((const float*)&m->data[2][0]);
	__m128 r4 = _mm_load_ps((const float*)&m->data[3][0]);

	__m128 prod1 = _mm_dp_ps(r1, vec, 0xFF);
	__m128 prod2 = _mm_dp_ps(r2, vec, 0xFF);
	__m128 prod3 = _mm_dp_ps(r3, vec, 0xFF);
	__m128 prod4 = _mm_dp_ps(r4, vec, 0xFF);

	__m128 result = _mm_shuffle_ps(_mm_movelh_ps(prod1, prod2), _mm_movelh_ps(prod3, prod4), _MM_SHUFFLE(2, 0, 2, 0));

	return *(vec3*)result.m128_f32;
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