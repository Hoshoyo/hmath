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
    assert(rsmul.x == v1.x * s1);

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

void test_vec4d()
{
    
}

void test_mat4()
{

}

int main(int argc, char** argv)
{
    test_vec4();
    return 0;
}