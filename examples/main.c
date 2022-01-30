#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "hmath.h"

#define WITHIN_MARGIN(F, G, M) (((F) >= ((G) - (M))) && ((F) <= ((G) + (M))))

void test_vec4()
{
    vec4 v1 = (vec4){1.0f, 2.0f, 3.0f, 4.0f};
    vec4 v2 = (vec4){5.0f, 6.0f, 7.0f, 8.0f};
    vec4 v3 = (vec4){-5.0f, -6.0f, 7.0f, 8.0f};
    float s1 = 3.0f;
    float v1_len = sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z + v1.w * v1.w);

    assert(hm_vec4_equal(v1, v2) == 0);
    assert(hm_vec4_equal(v1, v1) != 0);

    vec4 radd = hm_vec4_add(&v1, &v2);
    assert(radd.x == (v1.x + v2.x) && radd.y == (v1.y + v2.y) && radd.z == (v1.z + v2.z) && radd.w == (v1.w + v2.w));
    vec4 rsub = hm_vec4_sub(&v1, &v2);
    assert(rsub.x == (v1.x - v2.x) && rsub.y == (v1.y - v2.y) && rsub.z == (v1.z - v2.z) && rsub.w == (v1.w - v2.w));

    float rdot = hm_vec4_dot(&v1, &v2);
    assert(rdot == (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w));

    vec4 rcross = hm_vec4_cross(&v1, &v2);
    assert( (rcross.x == v1.y * v2.z - v1.z * v2.y) &&
            (rcross.y == v1.z * v2.x - v1.x * v2.z) &&
            (rcross.z == v1.x * v2.y - v1.y * v2.x) &&
            (rcross.w == 0.0f));
    
    vec4 rsmul = hm_vec4_scalar_mul(&v1, s1);
    assert(rsmul.x == v1.x * s1 && rsmul.y == v1.y * s1 && rsmul.z == v1.z * s1 && rsmul.w == v1.w * s1);

    vec4 rabs = hm_vec4_abs(&v3);
    assert(rabs.x == fabsf(rabs.x) && rabs.y == fabsf(rabs.y) && rabs.z == fabsf(rabs.z) && rabs.w == fabsf(rabs.w));

    vec4 rnorm = hm_vec4_normalize(&v1);
    assert(rnorm.x == v1.x / v1_len && rnorm.y == v1.y / v1_len && rnorm.z == v1.z / v1_len && rnorm.w == v1.w / v1_len);
    
    vec4 rnormfast = hm_vec4_normalize_fast(&v1);
    assert(WITHIN_MARGIN(rnormfast.x, v1.x / v1_len, 0.0001f) && 
        WITHIN_MARGIN(rnormfast.y, v1.y / v1_len, 0.0001f) && 
        WITHIN_MARGIN(rnormfast.z, v1.z / v1_len, 0.0001f) && 
        WITHIN_MARGIN(rnormfast.w, v1.w / v1_len, 0.0001f));

    float len = hm_vec4_length(&v1);
    assert(len == v1_len); 
}

void test_vec3()
{
    vec3 v1 = (vec3){3.0f, 5.0f, 7.0f};
    vec3 v2 = (vec3){2.0f, 4.0f, 6.0f};
    vec3 v3 = (vec3){-2.0f, 4.0f, -7.0f};
    float v1_len = sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
    float s1 = 2.5f;

    assert(hm_vec3_equal(v1, v2) == 0);
    assert(hm_vec3_equal(v1, v1) != 0);

    vec3 radd = hm_vec3_add(&v1, &v2);
    assert(radd.x == (v1.x + v2.x) && radd.y == (v1.y + v2.y) && radd.z == (v1.z + v2.z));
    vec3 rsub = hm_vec3_sub(&v1, &v2);
    assert(rsub.x == (v1.x - v2.x) && rsub.y == (v1.y - v2.y) && rsub.z == (v1.z - v2.z));

    float rdot = hm_vec3_dot(&v1, &v2);
    assert(rdot == (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z));

    vec3 rcross = hm_vec3_cross(&v1, &v2);
    assert( (rcross.x == v1.y * v2.z - v1.z * v2.y) &&
            (rcross.y == v1.z * v2.x - v1.x * v2.z) &&
            (rcross.z == v1.x * v2.y - v1.y * v2.x));
    
    vec3 rsmul = hm_vec3_scalar_mul(&v1, s1);
    assert(rsmul.x == v1.x * s1 && rsmul.y == v1.y * s1 && rsmul.z == v1.z * s1);

    vec3 rabs = hm_vec3_abs(&v3);
    assert(rabs.x == fabsf(rabs.x) && rabs.y == fabsf(rabs.y) && rabs.z == fabsf(rabs.z));

    vec3 rnorm = hm_vec3_normalize(&v1);
    assert(rnorm.x == v1.x / v1_len && rnorm.y == v1.y / v1_len && rnorm.z == v1.z / v1_len);

    float rlv1 = hm_vec3_length(&v1);
    assert(v1_len == rlv1);
}

void test_vec2()
{
    vec2 v1 = (vec2){3.0f, 5.0f};
    vec2 v2 = (vec2){2.0f, 4.0f};
    vec2 v3 = (vec2){-2.0f, 4.0f};
    float v1_len = sqrtf(v1.x * v1.x + v1.y * v1.y);
    float s1 = 2.5f;

    assert(hm_vec2_equal(v1, v2) == 0);
    assert(hm_vec2_equal(v1, v1) != 0);

    vec2 radd = hm_vec2_add(&v1, &v2);
    assert(radd.x == (v1.x + v2.x) && radd.y == (v1.y + v2.y));
    vec2 rsub = hm_vec2_sub(&v1, &v2);
    assert(rsub.x == (v1.x - v2.x) && rsub.y == (v1.y - v2.y));

    float rdot = hm_vec2_dot(&v1, &v2);
    assert(rdot == (v1.x * v2.x + v1.y * v2.y));
    
    vec2 rsmul = hm_vec2_scalar_mul(&v1, s1);
    assert(rsmul.x == v1.x * s1 && rsmul.y == v1.y * s1);

    vec2 rabs = hm_vec2_abs(&v3);
    assert(rabs.x == fabsf(rabs.x) && rabs.y == fabsf(rabs.y));

    vec2 rnorm = hm_vec2_normalize(&v1);
    assert(rnorm.x == v1.x / v1_len && rnorm.y == v1.y / v1_len);

    float rlv1 = hm_vec2_length(&v1);
    assert(v1_len == rlv1);
}

void test_dvec4()
{
    dvec4 v1 = (dvec4){1.0, 2.0, 3.0, 4.0};
    dvec4 v2 = (dvec4){5.0, 6.0, 7.0, 8.0};
    dvec4 v3 = (dvec4){-5.0, -6.0, 7.0, 8.0};
    double s1 = 3.0;
    double v1_len = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z + v1.w * v1.w);

    assert(hm_dvec4_equal(v1, v2) == 0);
    assert(hm_dvec4_equal(v1, v1) != 0);

    dvec4 radd = hm_dvec4_add(&v1, &v2);
    assert(radd.x == (v1.x + v2.x) && radd.y == (v1.y + v2.y) && radd.z == (v1.z + v2.z) && radd.w == (v1.w + v2.w));
    dvec4 rsub = hm_dvec4_sub(&v1, &v2);
    assert(rsub.x == (v1.x - v2.x) && rsub.y == (v1.y - v2.y) && rsub.z == (v1.z - v2.z) && rsub.w == (v1.w - v2.w));

    double rdot = hm_dvec4_dot(&v1, &v2);
    assert(rdot == (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w));

    dvec4 rcross = hm_dvec4_cross(&v1, &v2);
    assert( (rcross.x == v1.y * v2.z - v1.z * v2.y) &&
            (rcross.y == v1.z * v2.x - v1.x * v2.z) &&
            (rcross.z == v1.x * v2.y - v1.y * v2.x) &&
            (rcross.w == 0.0));
    
    dvec4 rsmul = hm_dvec4_scalar_mul(&v1, s1);
    assert(rsmul.x == v1.x * s1 && rsmul.y == v1.y * s1 && rsmul.z == v1.z * s1 && rsmul.w == v1.w * s1);

    dvec4 rabs = hm_dvec4_abs(&v3);
    assert(rabs.x == fabs(rabs.x) && rabs.y == fabs(rabs.y) && rabs.z == fabs(rabs.z) && rabs.w == fabs(rabs.w));

    dvec4 rnorm = hm_dvec4_normalize(&v1);
    assert(rnorm.x == v1.x / v1_len && rnorm.y == v1.y / v1_len && rnorm.z == v1.z / v1_len && rnorm.w == v1.w / v1_len);

    double len = hm_dvec4_length(&v1);
    assert(len == v1_len); 
}

void test_dvec3()
{
    dvec3 v1 = (dvec3){3.0, 5.0, 7.0};
    dvec3 v2 = (dvec3){2.0, 4.0, 6.0};
    dvec3 v3 = (dvec3){-2.0, 4.0, -7.0};
    double v1_len = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
    double s1 = 2.5;

    assert(hm_dvec3_equal(v1, v2) == 0);
    assert(hm_dvec3_equal(v1, v1) != 0);

    dvec3 radd = hm_dvec3_add(&v1, &v2);
    assert(radd.x == (v1.x + v2.x) && radd.y == (v1.y + v2.y) && radd.z == (v1.z + v2.z));
    dvec3 rsub = hm_dvec3_sub(&v1, &v2);
    assert(rsub.x == (v1.x - v2.x) && rsub.y == (v1.y - v2.y) && rsub.z == (v1.z - v2.z));

    double rdot = hm_dvec3_dot(&v1, &v2);
    assert(rdot == (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z));

    dvec3 rcross = hm_dvec3_cross(&v1, &v2);
    assert( (rcross.x == v1.y * v2.z - v1.z * v2.y) &&
            (rcross.y == v1.z * v2.x - v1.x * v2.z) &&
            (rcross.z == v1.x * v2.y - v1.y * v2.x));
    
    dvec3 rsmul = hm_dvec3_scalar_mul(&v1, s1);
    assert(rsmul.x == v1.x * s1 && rsmul.y == v1.y * s1 && rsmul.z == v1.z * s1);

    dvec3 rabs = hm_dvec3_abs(&v3);
    assert(rabs.x == fabs(rabs.x) && rabs.y == fabs(rabs.y) && rabs.z == fabs(rabs.z));

    dvec3 rnorm = hm_dvec3_normalize(&v1);
    assert(rnorm.x == v1.x / v1_len && rnorm.y == v1.y / v1_len && rnorm.z == v1.z / v1_len);

    double rlv1 = hm_dvec3_length(&v1);
    assert(v1_len == rlv1);
}

void test_dvec2()
{
    dvec2 v1 = (dvec2){3.0, 5.0};
    dvec2 v2 = (dvec2){2.0, 4.0};
    dvec2 v3 = (dvec2){-2.0, 4.0};
    double v1_len = sqrt(v1.x * v1.x + v1.y * v1.y);
    double s1 = 2.5;

    assert(hm_dvec2_equal(v1, v2) == 0);
    assert(hm_dvec2_equal(v1, v1) != 0);

    dvec2 radd = hm_dvec2_add(&v1, &v2);
    assert(radd.x == (v1.x + v2.x) && radd.y == (v1.y + v2.y));
    dvec2 rsub = hm_dvec2_sub(&v1, &v2);
    assert(rsub.x == (v1.x - v2.x) && rsub.y == (v1.y - v2.y));

    double rdot = hm_dvec2_dot(&v1, &v2);
    assert(rdot == (v1.x * v2.x + v1.y * v2.y));
    
    dvec2 rsmul = hm_dvec2_scalar_mul(&v1, s1);
    assert(rsmul.x == v1.x * s1 && rsmul.y == v1.y * s1);

    dvec2 rabs = hm_dvec2_abs(&v3);
    assert(rabs.x == fabs(rabs.x) && rabs.y == fabs(rabs.y));

    dvec2 rnorm = hm_dvec2_normalize(&v1);
    assert(rnorm.x == v1.x / v1_len && rnorm.y == v1.y / v1_len);

    double rlv1 = hm_dvec2_length(&v1);
    assert(v1_len == rlv1);
}

void test_mat4()
{
    mat4 m1 = {
        0,1,2,3,
        4,5,6,7,
        8,9,10,11,
        12,13,14,15,
    };
    mat4 m2 = {
        5,5,5,5,
        3,-3,-3,3,
        1,2,3,4,
        0,2,4,6,
    };
    vec4 v = (vec4){1,2,3,4};
    vec3 v3 = (vec3){1,2,3};
    float scalar = 5.0f;

    vec4 rmulv4 = hm_mat4_multiply_vec4(&m1, &v);
    assert( (rmulv4.x == v.x * m1.data[0][0] + v.y * m1.data[0][1] + v.z * m1.data[0][2] + v.w * m1.data[0][3]) &&
            (rmulv4.y == v.x * m1.data[1][0] + v.y * m1.data[1][1] + v.z * m1.data[1][2] + v.w * m1.data[1][3]) &&
            (rmulv4.z == v.x * m1.data[2][0] + v.y * m1.data[2][1] + v.z * m1.data[2][2] + v.w * m1.data[2][3]) &&
            (rmulv4.w == v.x * m1.data[3][0] + v.y * m1.data[3][1] + v.z * m1.data[3][2] + v.w * m1.data[3][3]));

    vec3 rmulv3 = hm_mat4_multiply_vec3(&m1, &v3);
    assert( (rmulv3.x == m1.data[0][0] * v.x + m1.data[0][1] * v.y + m1.data[0][2] * v.z + m1.data[0][3] * 1.0f) &&
	        (rmulv3.y == m1.data[1][0] * v.x + m1.data[1][1] * v.y + m1.data[1][2] * v.z + m1.data[1][3] * 1.0f) &&
	        (rmulv3.z == m1.data[2][0] * v.x + m1.data[2][1] * v.y + m1.data[2][2] * v.z + m1.data[2][3] * 1.0f));

    mat4 rmul = hm_mat4_multiply(&m1, &m2);
    assert( (rmul.data[0][0] == (m1.data[0][0] * m2.data[0][0] + m1.data[0][1] * m2.data[1][0] + m1.data[0][2] * m2.data[2][0] + m1.data[0][3] * m2.data[3][0])) &&
            (rmul.data[0][1] == (m1.data[0][0] * m2.data[0][1] + m1.data[0][1] * m2.data[1][1] + m1.data[0][2] * m2.data[2][1] + m1.data[0][3] * m2.data[3][1])) &&
            (rmul.data[0][2] == (m1.data[0][0] * m2.data[0][2] + m1.data[0][1] * m2.data[1][2] + m1.data[0][2] * m2.data[2][2] + m1.data[0][3] * m2.data[3][2])) &&
            (rmul.data[0][3] == (m1.data[0][0] * m2.data[0][3] + m1.data[0][1] * m2.data[1][3] + m1.data[0][2] * m2.data[2][3] + m1.data[0][3] * m2.data[3][3])) &&
            (rmul.data[1][0] == (m1.data[1][0] * m2.data[0][0] + m1.data[1][1] * m2.data[1][0] + m1.data[1][2] * m2.data[2][0] + m1.data[1][3] * m2.data[3][0])) &&
            (rmul.data[1][1] == (m1.data[1][0] * m2.data[0][1] + m1.data[1][1] * m2.data[1][1] + m1.data[1][2] * m2.data[2][1] + m1.data[1][3] * m2.data[3][1])) &&
            (rmul.data[1][2] == (m1.data[1][0] * m2.data[0][2] + m1.data[1][1] * m2.data[1][2] + m1.data[1][2] * m2.data[2][2] + m1.data[1][3] * m2.data[3][2])) &&
            (rmul.data[1][3] == (m1.data[1][0] * m2.data[0][3] + m1.data[1][1] * m2.data[1][3] + m1.data[1][2] * m2.data[2][3] + m1.data[1][3] * m2.data[3][3])) &&
            (rmul.data[2][0] == (m1.data[2][0] * m2.data[0][0] + m1.data[2][1] * m2.data[1][0] + m1.data[2][2] * m2.data[2][0] + m1.data[2][3] * m2.data[3][0])) &&
            (rmul.data[2][1] == (m1.data[2][0] * m2.data[0][1] + m1.data[2][1] * m2.data[1][1] + m1.data[2][2] * m2.data[2][1] + m1.data[2][3] * m2.data[3][1])) &&
            (rmul.data[2][2] == (m1.data[2][0] * m2.data[0][2] + m1.data[2][1] * m2.data[1][2] + m1.data[2][2] * m2.data[2][2] + m1.data[2][3] * m2.data[3][2])) &&
            (rmul.data[2][3] == (m1.data[2][0] * m2.data[0][3] + m1.data[2][1] * m2.data[1][3] + m1.data[2][2] * m2.data[2][3] + m1.data[2][3] * m2.data[3][3])) &&
            (rmul.data[3][0] == (m1.data[3][0] * m2.data[0][0] + m1.data[3][1] * m2.data[1][0] + m1.data[3][2] * m2.data[2][0] + m1.data[3][3] * m2.data[3][0])) &&
            (rmul.data[3][1] == (m1.data[3][0] * m2.data[0][1] + m1.data[3][1] * m2.data[1][1] + m1.data[3][2] * m2.data[2][1] + m1.data[3][3] * m2.data[3][1])) &&
            (rmul.data[3][2] == (m1.data[3][0] * m2.data[0][2] + m1.data[3][1] * m2.data[1][2] + m1.data[3][2] * m2.data[2][2] + m1.data[3][3] * m2.data[3][2])) &&
            (rmul.data[3][3] == (m1.data[3][0] * m2.data[0][3] + m1.data[3][1] * m2.data[1][3] + m1.data[3][2] * m2.data[2][3] + m1.data[3][3] * m2.data[3][3])));
    
    mat4 rsprod = hm_mat4_scalar_product(&m1, scalar);
    assert( (rsprod.data[0][0] == scalar * m1.data[0][0]) && (rsprod.data[0][1] == scalar * m1.data[0][1]) && (rsprod.data[0][2] == scalar * m1.data[0][2]) && (rsprod.data[0][3] == scalar * m1.data[0][3]) &&
            (rsprod.data[1][0] == scalar * m1.data[1][0]) && (rsprod.data[1][1] == scalar * m1.data[1][1]) && (rsprod.data[1][2] == scalar * m1.data[1][2]) && (rsprod.data[1][3] == scalar * m1.data[1][3]) &&
            (rsprod.data[2][0] == scalar * m1.data[2][0]) && (rsprod.data[2][1] == scalar * m1.data[2][1]) && (rsprod.data[2][2] == scalar * m1.data[2][2]) && (rsprod.data[2][3] == scalar * m1.data[2][3]) &&
            (rsprod.data[3][0] == scalar * m1.data[3][0]) && (rsprod.data[3][1] == scalar * m1.data[3][1]) && (rsprod.data[3][2] == scalar * m1.data[3][2]) && (rsprod.data[3][3] == scalar * m1.data[3][3]));
    
    mat4 rtransp = hm_mat4_transpose(&m1);
    assert( (rtransp.data[0][0] == m1.data[0][0]) && (rtransp.data[1][0] == m1.data[0][1]) && (rtransp.data[2][0] == m1.data[0][2]) && (rtransp.data[3][0] == m1.data[0][3]) &&
            (rtransp.data[0][1] == m1.data[1][0]) && (rtransp.data[1][1] == m1.data[1][1]) && (rtransp.data[2][1] == m1.data[1][2]) && (rtransp.data[3][1] == m1.data[1][3]) &&
            (rtransp.data[0][2] == m1.data[2][0]) && (rtransp.data[1][2] == m1.data[2][1]) && (rtransp.data[2][2] == m1.data[2][2]) && (rtransp.data[3][2] == m1.data[2][3]) &&
            (rtransp.data[0][3] == m1.data[3][0]) && (rtransp.data[1][3] == m1.data[3][1]) && (rtransp.data[2][3] == m1.data[3][2]) && (rtransp.data[3][3] == m1.data[3][3]));
    
    mat4 rident = hm_mat4_identity();
    assert( (rident.data[0][0] == 1.0) && (rident.data[1][0] == 0.0) && (rident.data[2][0] == 0.0) && (rident.data[3][0] == 0.0) &&
            (rident.data[0][1] == 0.0) && (rident.data[1][1] == 1.0) && (rident.data[2][1] == 0.0) && (rident.data[3][1] == 0.0) &&
            (rident.data[0][2] == 0.0) && (rident.data[1][2] == 0.0) && (rident.data[2][2] == 1.0) && (rident.data[3][2] == 0.0) &&
            (rident.data[0][3] == 0.0) && (rident.data[1][3] == 0.0) && (rident.data[2][3] == 0.0) && (rident.data[3][3] == 1.0));
}

void test_mat3()
{
    mat3 m1 = {
        0,1,2,
        4,5,6,
        8,9,10
    };
    mat3 m2 = {
        5,5,5,
        3,-3,-3,
        1,2,3,
    };
    vec3 v3 = (vec3){1,2,3};
    float scalar = 5.0f;

    vec3 rmulv3 = hm_mat3_multiply_vec3(&m1, &v3);
    assert( (rmulv3.x == m1.data[0][0] * v3.x + m1.data[0][1] * v3.y + m1.data[0][2] * v3.z) &&
	        (rmulv3.y == m1.data[1][0] * v3.x + m1.data[1][1] * v3.y + m1.data[1][2] * v3.z) &&
	        (rmulv3.z == m1.data[2][0] * v3.x + m1.data[2][1] * v3.y + m1.data[2][2] * v3.z));

    mat3 rmul = hm_mat3_multiply(&m1, &m2);
    assert(
        rmul.data[0][0] == (m1.data[0][0] * m2.data[0][0] + m1.data[0][1] * m2.data[1][0] + m1.data[0][2] * m2.data[2][0]) &&
        rmul.data[0][1] == (m1.data[0][0] * m2.data[0][1] + m1.data[0][1] * m2.data[1][1] + m1.data[0][2] * m2.data[2][1]) &&
        rmul.data[0][2] == (m1.data[0][0] * m2.data[0][2] + m1.data[0][1] * m2.data[1][2] + m1.data[0][2] * m2.data[2][2]) &&
        rmul.data[1][0] == (m1.data[1][0] * m2.data[0][0] + m1.data[1][1] * m2.data[1][0] + m1.data[1][2] * m2.data[2][0]) &&
        rmul.data[1][1] == (m1.data[1][0] * m2.data[0][1] + m1.data[1][1] * m2.data[1][1] + m1.data[1][2] * m2.data[2][1]) &&
        rmul.data[1][2] == (m1.data[1][0] * m2.data[0][2] + m1.data[1][1] * m2.data[1][2] + m1.data[1][2] * m2.data[2][2]) &&
        rmul.data[2][0] == (m1.data[2][0] * m2.data[0][0] + m1.data[2][1] * m2.data[1][0] + m1.data[2][2] * m2.data[2][0]) &&
        rmul.data[2][1] == (m1.data[2][0] * m2.data[0][1] + m1.data[2][1] * m2.data[1][1] + m1.data[2][2] * m2.data[2][1]) &&
        rmul.data[2][2] == (m1.data[2][0] * m2.data[0][2] + m1.data[2][1] * m2.data[1][2] + m1.data[2][2] * m2.data[2][2]));
    
    mat3 rsprod = hm_mat3_scalar_product(&m1, scalar);
    assert( (rsprod.data[0][0] == scalar * m1.data[0][0]) && (rsprod.data[0][1] == scalar * m1.data[0][1]) && (rsprod.data[0][2] == scalar * m1.data[0][2]) &&
            (rsprod.data[1][0] == scalar * m1.data[1][0]) && (rsprod.data[1][1] == scalar * m1.data[1][1]) && (rsprod.data[1][2] == scalar * m1.data[1][2]) &&
            (rsprod.data[2][0] == scalar * m1.data[2][0]) && (rsprod.data[2][1] == scalar * m1.data[2][1]) && (rsprod.data[2][2] == scalar * m1.data[2][2]));

    mat3 rtransp = hm_mat3_transpose(&m1);
    assert( (rtransp.data[0][0] == m1.data[0][0]) && (rtransp.data[1][0] == m1.data[0][1]) && (rtransp.data[2][0] == m1.data[0][2]) &&
            (rtransp.data[0][1] == m1.data[1][0]) && (rtransp.data[1][1] == m1.data[1][1]) && (rtransp.data[2][1] == m1.data[1][2]) &&
            (rtransp.data[0][2] == m1.data[2][0]) && (rtransp.data[1][2] == m1.data[2][1]) && (rtransp.data[2][2] == m1.data[2][2]));

    mat3 rident = hm_mat3_identity();
    assert( (rident.data[0][0] == 1.0) && (rident.data[1][0] == 0.0) && (rident.data[2][0] == 0.0) &&
            (rident.data[0][1] == 0.0) && (rident.data[1][1] == 1.0) && (rident.data[2][1] == 0.0) &&
            (rident.data[0][2] == 0.0) && (rident.data[1][2] == 0.0) && (rident.data[2][2] == 1.0));
}

void test_mat2()
{
    mat2 m1 = {
        1,2,
        3,4
    };
    mat2 m2 = {
        5,6,
        7,8
    };
    float scalar = 5.0f;

    mat2 rmul = hm_mat2_multiply(&m1, &m2);
    assert( rmul.data[0][0] == (m1.data[0][0] * m2.data[0][0] + m1.data[0][1] * m2.data[1][0]) &&
            rmul.data[0][1] == (m1.data[0][0] * m2.data[0][1] + m1.data[0][1] * m2.data[1][1]) &&
            rmul.data[1][0] == (m1.data[1][0] * m2.data[0][0] + m1.data[1][1] * m2.data[1][0]) &&
            rmul.data[1][1] == (m1.data[1][0] * m2.data[0][1] + m1.data[1][1] * m2.data[1][1]));
    
    mat2 rsprod = hm_mat2_scalar_product(&m1, scalar);
    assert( (rsprod.data[0][0] == scalar * m1.data[0][0]) && (rsprod.data[0][1] == scalar * m1.data[0][1]) &&
            (rsprod.data[1][0] == scalar * m1.data[1][0]) && (rsprod.data[1][1] == scalar * m1.data[1][1]));

    mat2 rtransp = hm_mat2_transpose(&m1);
    assert( (rtransp.data[0][0] == m1.data[0][0]) && (rtransp.data[1][0] == m1.data[0][1]) &&
            (rtransp.data[0][1] == m1.data[1][0]) && (rtransp.data[1][1] == m1.data[1][1]));

    mat2 rident = hm_mat2_identity();
    assert( (rident.data[0][0] == 1.0) && (rident.data[1][0] == 0.0) &&
            (rident.data[0][1] == 0.0) && (rident.data[1][1] == 1.0));
}

void test_dmat4()
{
    dmat4 m1 = {
        0,1,2,3,
        4,5,6,7,
        8,9,10,11,
        12,13,14,15,
    };
    dmat4 m2 = {
        5,5,5,5,
        3,-3,-3,3,
        1,2,3,4,
        0,2,4,6,
    };
    dvec4 v = (dvec4){1,2,3,4};
    dvec3 v3 = (dvec3){1,2,3};
    double scalar = 5.0f;

    dvec4 rmulv4 = hm_dmat4_multiply_dvec4(&m1, &v);
    assert( (rmulv4.x == v.x * m1.data[0][0] + v.y * m1.data[0][1] + v.z * m1.data[0][2] + v.w * m1.data[0][3]) &&
            (rmulv4.y == v.x * m1.data[1][0] + v.y * m1.data[1][1] + v.z * m1.data[1][2] + v.w * m1.data[1][3]) &&
            (rmulv4.z == v.x * m1.data[2][0] + v.y * m1.data[2][1] + v.z * m1.data[2][2] + v.w * m1.data[2][3]) &&
            (rmulv4.w == v.x * m1.data[3][0] + v.y * m1.data[3][1] + v.z * m1.data[3][2] + v.w * m1.data[3][3]));

    dvec3 rmulv3 = hm_dmat4_multiply_dvec3(&m1, &v3);
    assert( (rmulv3.x == m1.data[0][0] * v.x + m1.data[0][1] * v.y + m1.data[0][2] * v.z + m1.data[0][3] * 1.0f) &&
	        (rmulv3.y == m1.data[1][0] * v.x + m1.data[1][1] * v.y + m1.data[1][2] * v.z + m1.data[1][3] * 1.0f) &&
	        (rmulv3.z == m1.data[2][0] * v.x + m1.data[2][1] * v.y + m1.data[2][2] * v.z + m1.data[2][3] * 1.0f));

    dmat4 rmul = hm_dmat4_multiply(&m1, &m2);
    assert( (rmul.data[0][0] == (m1.data[0][0] * m2.data[0][0] + m1.data[0][1] * m2.data[1][0] + m1.data[0][2] * m2.data[2][0] + m1.data[0][3] * m2.data[3][0])) &&
            (rmul.data[0][1] == (m1.data[0][0] * m2.data[0][1] + m1.data[0][1] * m2.data[1][1] + m1.data[0][2] * m2.data[2][1] + m1.data[0][3] * m2.data[3][1])) &&
            (rmul.data[0][2] == (m1.data[0][0] * m2.data[0][2] + m1.data[0][1] * m2.data[1][2] + m1.data[0][2] * m2.data[2][2] + m1.data[0][3] * m2.data[3][2])) &&
            (rmul.data[0][3] == (m1.data[0][0] * m2.data[0][3] + m1.data[0][1] * m2.data[1][3] + m1.data[0][2] * m2.data[2][3] + m1.data[0][3] * m2.data[3][3])) &&
            (rmul.data[1][0] == (m1.data[1][0] * m2.data[0][0] + m1.data[1][1] * m2.data[1][0] + m1.data[1][2] * m2.data[2][0] + m1.data[1][3] * m2.data[3][0])) &&
            (rmul.data[1][1] == (m1.data[1][0] * m2.data[0][1] + m1.data[1][1] * m2.data[1][1] + m1.data[1][2] * m2.data[2][1] + m1.data[1][3] * m2.data[3][1])) &&
            (rmul.data[1][2] == (m1.data[1][0] * m2.data[0][2] + m1.data[1][1] * m2.data[1][2] + m1.data[1][2] * m2.data[2][2] + m1.data[1][3] * m2.data[3][2])) &&
            (rmul.data[1][3] == (m1.data[1][0] * m2.data[0][3] + m1.data[1][1] * m2.data[1][3] + m1.data[1][2] * m2.data[2][3] + m1.data[1][3] * m2.data[3][3])) &&
            (rmul.data[2][0] == (m1.data[2][0] * m2.data[0][0] + m1.data[2][1] * m2.data[1][0] + m1.data[2][2] * m2.data[2][0] + m1.data[2][3] * m2.data[3][0])) &&
            (rmul.data[2][1] == (m1.data[2][0] * m2.data[0][1] + m1.data[2][1] * m2.data[1][1] + m1.data[2][2] * m2.data[2][1] + m1.data[2][3] * m2.data[3][1])) &&
            (rmul.data[2][2] == (m1.data[2][0] * m2.data[0][2] + m1.data[2][1] * m2.data[1][2] + m1.data[2][2] * m2.data[2][2] + m1.data[2][3] * m2.data[3][2])) &&
            (rmul.data[2][3] == (m1.data[2][0] * m2.data[0][3] + m1.data[2][1] * m2.data[1][3] + m1.data[2][2] * m2.data[2][3] + m1.data[2][3] * m2.data[3][3])) &&
            (rmul.data[3][0] == (m1.data[3][0] * m2.data[0][0] + m1.data[3][1] * m2.data[1][0] + m1.data[3][2] * m2.data[2][0] + m1.data[3][3] * m2.data[3][0])) &&
            (rmul.data[3][1] == (m1.data[3][0] * m2.data[0][1] + m1.data[3][1] * m2.data[1][1] + m1.data[3][2] * m2.data[2][1] + m1.data[3][3] * m2.data[3][1])) &&
            (rmul.data[3][2] == (m1.data[3][0] * m2.data[0][2] + m1.data[3][1] * m2.data[1][2] + m1.data[3][2] * m2.data[2][2] + m1.data[3][3] * m2.data[3][2])) &&
            (rmul.data[3][3] == (m1.data[3][0] * m2.data[0][3] + m1.data[3][1] * m2.data[1][3] + m1.data[3][2] * m2.data[2][3] + m1.data[3][3] * m2.data[3][3])));
    
    dmat4 rsprod = hm_dmat4_scalar_product(&m1, scalar);
    assert( (rsprod.data[0][0] == scalar * m1.data[0][0]) && (rsprod.data[0][1] == scalar * m1.data[0][1]) && (rsprod.data[0][2] == scalar * m1.data[0][2]) && (rsprod.data[0][3] == scalar * m1.data[0][3]) &&
            (rsprod.data[1][0] == scalar * m1.data[1][0]) && (rsprod.data[1][1] == scalar * m1.data[1][1]) && (rsprod.data[1][2] == scalar * m1.data[1][2]) && (rsprod.data[1][3] == scalar * m1.data[1][3]) &&
            (rsprod.data[2][0] == scalar * m1.data[2][0]) && (rsprod.data[2][1] == scalar * m1.data[2][1]) && (rsprod.data[2][2] == scalar * m1.data[2][2]) && (rsprod.data[2][3] == scalar * m1.data[2][3]) &&
            (rsprod.data[3][0] == scalar * m1.data[3][0]) && (rsprod.data[3][1] == scalar * m1.data[3][1]) && (rsprod.data[3][2] == scalar * m1.data[3][2]) && (rsprod.data[3][3] == scalar * m1.data[3][3]));
    
    dmat4 rtransp = hm_dmat4_transpose(&m1);
    assert( (rtransp.data[0][0] == m1.data[0][0]) && (rtransp.data[1][0] == m1.data[0][1]) && (rtransp.data[2][0] == m1.data[0][2]) && (rtransp.data[3][0] == m1.data[0][3]) &&
            (rtransp.data[0][1] == m1.data[1][0]) && (rtransp.data[1][1] == m1.data[1][1]) && (rtransp.data[2][1] == m1.data[1][2]) && (rtransp.data[3][1] == m1.data[1][3]) &&
            (rtransp.data[0][2] == m1.data[2][0]) && (rtransp.data[1][2] == m1.data[2][1]) && (rtransp.data[2][2] == m1.data[2][2]) && (rtransp.data[3][2] == m1.data[2][3]) &&
            (rtransp.data[0][3] == m1.data[3][0]) && (rtransp.data[1][3] == m1.data[3][1]) && (rtransp.data[2][3] == m1.data[3][2]) && (rtransp.data[3][3] == m1.data[3][3]));
    
    dmat4 rident = hm_dmat4_identity();
    assert( (rident.data[0][0] == 1.0) && (rident.data[1][0] == 0.0) && (rident.data[2][0] == 0.0) && (rident.data[3][0] == 0.0) &&
            (rident.data[0][1] == 0.0) && (rident.data[1][1] == 1.0) && (rident.data[2][1] == 0.0) && (rident.data[3][1] == 0.0) &&
            (rident.data[0][2] == 0.0) && (rident.data[1][2] == 0.0) && (rident.data[2][2] == 1.0) && (rident.data[3][2] == 0.0) &&
            (rident.data[0][3] == 0.0) && (rident.data[1][3] == 0.0) && (rident.data[2][3] == 0.0) && (rident.data[3][3] == 1.0));
}

void test_dmat3()
{
    dmat3 m1 = {
        0,1,2,
        4,5,6,
        8,9,10
    };
    dmat3 m2 = {
        5,5,5,
        3,-3,-3,
        1,2,3,
    };
    dvec3 v3 = (dvec3){1,2,3};
    double scalar = 5.0f;

    dvec3 rmulv3 = hm_dmat3_multiply_dvec3(&m1, &v3);
    assert( (rmulv3.x == m1.data[0][0] * v3.x + m1.data[0][1] * v3.y + m1.data[0][2] * v3.z) &&
	        (rmulv3.y == m1.data[1][0] * v3.x + m1.data[1][1] * v3.y + m1.data[1][2] * v3.z) &&
	        (rmulv3.z == m1.data[2][0] * v3.x + m1.data[2][1] * v3.y + m1.data[2][2] * v3.z));

    dmat3 rmul = hm_dmat3_multiply(&m1, &m2);
    assert(
        rmul.data[0][0] == (m1.data[0][0] * m2.data[0][0] + m1.data[0][1] * m2.data[1][0] + m1.data[0][2] * m2.data[2][0]) &&
        rmul.data[0][1] == (m1.data[0][0] * m2.data[0][1] + m1.data[0][1] * m2.data[1][1] + m1.data[0][2] * m2.data[2][1]) &&
        rmul.data[0][2] == (m1.data[0][0] * m2.data[0][2] + m1.data[0][1] * m2.data[1][2] + m1.data[0][2] * m2.data[2][2]) &&
        rmul.data[1][0] == (m1.data[1][0] * m2.data[0][0] + m1.data[1][1] * m2.data[1][0] + m1.data[1][2] * m2.data[2][0]) &&
        rmul.data[1][1] == (m1.data[1][0] * m2.data[0][1] + m1.data[1][1] * m2.data[1][1] + m1.data[1][2] * m2.data[2][1]) &&
        rmul.data[1][2] == (m1.data[1][0] * m2.data[0][2] + m1.data[1][1] * m2.data[1][2] + m1.data[1][2] * m2.data[2][2]) &&
        rmul.data[2][0] == (m1.data[2][0] * m2.data[0][0] + m1.data[2][1] * m2.data[1][0] + m1.data[2][2] * m2.data[2][0]) &&
        rmul.data[2][1] == (m1.data[2][0] * m2.data[0][1] + m1.data[2][1] * m2.data[1][1] + m1.data[2][2] * m2.data[2][1]) &&
        rmul.data[2][2] == (m1.data[2][0] * m2.data[0][2] + m1.data[2][1] * m2.data[1][2] + m1.data[2][2] * m2.data[2][2]));
    
    dmat3 rsprod = hm_dmat3_scalar_product(&m1, scalar);
    assert( (rsprod.data[0][0] == scalar * m1.data[0][0]) && (rsprod.data[0][1] == scalar * m1.data[0][1]) && (rsprod.data[0][2] == scalar * m1.data[0][2]) &&
            (rsprod.data[1][0] == scalar * m1.data[1][0]) && (rsprod.data[1][1] == scalar * m1.data[1][1]) && (rsprod.data[1][2] == scalar * m1.data[1][2]) &&
            (rsprod.data[2][0] == scalar * m1.data[2][0]) && (rsprod.data[2][1] == scalar * m1.data[2][1]) && (rsprod.data[2][2] == scalar * m1.data[2][2]));

    dmat3 rtransp = hm_dmat3_transpose(&m1);
    assert( (rtransp.data[0][0] == m1.data[0][0]) && (rtransp.data[1][0] == m1.data[0][1]) && (rtransp.data[2][0] == m1.data[0][2]) &&
            (rtransp.data[0][1] == m1.data[1][0]) && (rtransp.data[1][1] == m1.data[1][1]) && (rtransp.data[2][1] == m1.data[1][2]) &&
            (rtransp.data[0][2] == m1.data[2][0]) && (rtransp.data[1][2] == m1.data[2][1]) && (rtransp.data[2][2] == m1.data[2][2]));

    dmat3 rident = hm_dmat3_identity();
    assert( (rident.data[0][0] == 1.0) && (rident.data[1][0] == 0.0) && (rident.data[2][0] == 0.0) &&
            (rident.data[0][1] == 0.0) && (rident.data[1][1] == 1.0) && (rident.data[2][1] == 0.0) &&
            (rident.data[0][2] == 0.0) && (rident.data[1][2] == 0.0) && (rident.data[2][2] == 1.0));
}

int main(int argc, char** argv)
{
    test_mat4();
    test_dmat4();
    test_mat3();
    test_dmat3();
    test_mat2();
    test_dvec2();
    test_dvec3();
    test_dvec4();
    test_vec4();
    test_vec3();
    test_vec2();
    return 0;
}