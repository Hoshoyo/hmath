## HMath

Simple single header math library that uses basic SIMD with SSE, AVX and AVX2.

```c
	// 32-bit vector4
    int hm_vec4_equal(vec4 v1, vec4 v2);
    vec4 hm_vec4_add(vec4* restrict v1, vec4* restrict v2);
    vec4 hm_vec4_sub(vec4* restrict v1, vec4* restrict v2);
    float hm_vec4_dot(vec4* restrict v1, vec4* restrict v2);
    vec4 hm_vec4_cross(vec4* restrict v1, vec4* restrict v2);
    vec4 hm_vec4_scalar_mul(vec4* restrict v, float s);
    vec4 hm_vec4_abs(vec4* restrict v);
    vec4 hm_vec4_normalize_fast(vec4* restrict v);
    vec4 hm_vec4_normalize(vec4* restrict v);
    float hm_vec4_length(vec4* restrict v);

	// 32-bit vector3
    int hm_vec3_equal(vec3 v1, vec3 v2);
    vec3 hm_vec3_add(vec3* restrict v1, vec3* restrict v2);
    vec3 hm_vec3_sub(vec3* restrict v1, vec3* restrict v2);
    float hm_vec3_dot(vec3* restrict v1, vec3* restrict v2);
    vec3 hm_vec3_cross(vec3* restrict v1, vec3* restrict v2);
    vec3 hm_vec3_scalar_mul(vec3* restrict v, float s);
    vec3 hm_vec3_abs(vec3* restrict v);
    vec3 hm_vec3_normalize_fast(vec3* restrict v);
    vec3 hm_vec3_normalize(vec3* restrict v);
    float hm_vec3_length(vec3* restrict v);

	// 32-bit vector2
    int hm_vec2_equal(vec2 v1, vec2 v2);
    vec2 hm_vec2_add(vec2* restrict v1, vec2* restrict v2);
    vec2 hm_vec2_sub(vec2* restrict v1, vec2* restrict v2);
    float hm_vec2_dot(vec2* restrict v1, vec2* restrict v2);
    vec2 hm_vec2_cross(vec2* restrict v1, vec2* restrict v2);
    vec2 hm_vec2_scalar_mul(vec2* restrict v, float s);
    vec2 hm_vec2_abs(vec2* restrict v);
    vec2 hm_vec2_normalize_fast(vec2* restrict v);
    vec2 hm_vec2_normalize(vec2* restrict v);
    float hm_vec2_length(vec2* restrict v);

	// 64-bit vector4
    int hm_dvec4_equal(dvec4 v1, dvec4 v2);
    dvec4 hm_dvec4_add(dvec4* restrict v1, dvec4* restrict v2);
    dvec4 hm_dvec4_sub(dvec4* restrict v1, dvec4* restrict v2);
    double hm_dvec4_dot(dvec4* restrict v1, dvec4* restrict v2);
    dvec4 hm_dvec4_cross(dvec4* restrict v1, dvec4* restrict v2);
    dvec4 hm_dvec4_scalar_mul(dvec4* restrict v, double s);
    dvec4 hm_dvec4_abs(dvec4* restrict v);
    dvec4 hm_dvec4_normalize(dvec4* restrict v);
    double hm_dvec4_length(dvec4* restrict v);

	// 64-bit vector3
    int hm_dvec3_equal(dvec3 v1, dvec3 v2);
    dvec3 hm_dvec3_add(dvec3* restrict v1, dvec3* restrict v2);
    dvec3 hm_dvec3_sub(dvec3* restrict v1, dvec3* restrict v2);
    double hm_dvec3_dot(dvec3* restrict v1, dvec3* restrict v2);
    dvec3 hm_dvec3_cross(dvec3* restrict v1, dvec3* restrict v2);
    dvec3 hm_dvec3_scalar_mul(dvec3* restrict v, double s);
    dvec3 hm_dvec3_abs(dvec3* restrict v);
    dvec3 hm_dvec3_normalize(dvec3* restrict v);
    double hm_dvec3_length(dvec3* restrict v);

	// 64-bit vector2
    int hm_dvec2_equal(dvec2 v1, dvec2 v2);
    dvec2 hm_dvec2_add(dvec2* restrict v1, dvec2* restrict v2);
    dvec2 hm_dvec2_sub(dvec2* restrict v1, dvec2* restrict v2);
    double hm_dvec2_dot(dvec2* restrict v1, dvec2* restrict v2);
    dvec2 hm_dvec2_scalar_mul(dvec2* restrict v, double s);
    dvec2 hm_dvec2_abs(dvec2* restrict v);
    dvec2 hm_dvec2_normalize(dvec2* restrict v);
    double hm_dvec2_length(dvec2* restrict v);

	// 32-bit matrix4
    vec4 hm_mat4_multiply_vec4(mat4* restrict m, vec4* restrict v);
    vec3 hm_mat4_multiply_vec3(mat4* restrict m, vec3* restrict v);
    mat4 hm_mat4_scalar_product(mat4* restrict m, float scalar);
    mat4 hm_mat4_transpose(mat4* restrict m);
    mat4 hm_mat4_multiply(mat4* restrict m1, mat4* restrict m2);
    mat4 hm_mat4_identity();

	// 32-bit matrix3
    vec3 hm_mat3_multiply_vec3(mat3* restrict m, vec3* restrict v);
    mat3 hm_mat3_scalar_product(mat3* restrict m, float scalar);
    mat3 hm_mat3_transpose(mat3* restrict m);
    mat3 hm_mat3_multiply(mat3* restrict m1, mat3* restrict m2);
    mat3 hm_mat3_identity();

	// 32-bit matrix2
    mat2 hm_mat2_multiply(mat2* restrict m1, mat2* restrict m2);
    mat2 hm_mat2_transpose(mat2* restrict m);
    mat2 hm_mat2_scalar_product(mat2* restrict m, float scalar);
    mat2 hm_mat2_identity();

	// 64-bit matrix4
    dvec4 hm_dmat4_multiply_dvec4(dmat4* restrict m, dvec4* restrict v);
    dvec3 hm_dmat4_multiply_dvec3(dmat4* restrict m, dvec3* restrict v);
    dmat4 hm_dmat4_scalar_product(dmat4* restrict m, double scalar);
    dmat4 hm_dmat4_transpose(dmat4* restrict m);
    dmat4 hm_dmat4_multiply(dmat4* restrict m1, dmat4* restrict m2);
    dmat4 hm_dmat4_identity();

	// 64-bit matrix3
    dvec3 hm_dmat3_multiply_dvec3(dmat3* restrict m, dvec3* restrict v);
    dmat3 hm_dmat3_scalar_product(dmat3* restrict m, double scalar);
    dmat3 hm_dmat3_transpose(dmat3* restrict m);
    dmat3 hm_dmat3_multiply(dmat3* restrict m1, dmat3* restrict m2);
    dmat3 hm_dmat3_identity();

	// 64-bit matrix2
    dmat2 hm_dmat2_multiply(dmat2* restrict m1, dmat2* restrict m2);
    dmat2 hm_dmat2_transpose(dmat2* restrict m);
    dmat2 hm_dmat2_scalar_product(dmat2* restrict m, double scalar);
    dmat2 hm_dmat2_identity();
```