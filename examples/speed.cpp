#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include "../hmath.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

static double perf_frequency;
void
os_time_init()
{
	LARGE_INTEGER li = { 0 };
	QueryPerformanceFrequency(&li);
	perf_frequency = (double)(li.QuadPart);
}

double
os_time_ms()
{
	LARGE_INTEGER li = { 0 };
	QueryPerformanceCounter(&li);
	return ((double)(li.QuadPart) / perf_frequency) * 1000.0;
}
#elif defined(__linux__)
void os_time_init() {}
double os_time_ms()
{
	struct timespec t_spec;
	clock_gettime(CLOCK_MONOTONIC_RAW, &t_spec);
	unsigned long long res = t_spec.tv_nsec + 1000000000 * t_spec.tv_sec;
	return (double)res / 1000000.0;
}
#endif

static int random_int()
{
    int result = 0;
    result = rand();
    return result;
}

/*
Elapsed vec4 add: 3400.602400 ms
Elapsed vec4 dot: 3009.767900 ms
Elapsed vec4 normalize: 2607.739500 ms
Elapsed vec4 normalize fast: 3055.218200 ms
Elapsed vec4 length: 1756.106700 ms
Elapsed vec4 cross: 4293.393800 ms
Elapsed vec4 scalar mul: 2991.661900 ms
Elapsed vec4 abs: 2727.893600 ms
*/
float
test_vec4()
{
    const int count = 1024 * 1024;
    vec4* vecs1 = (vec4*)calloc(1, count * sizeof(vec4));
    vec4* vecs2 = (vec4*)calloc(1, count * sizeof(vec4));
    vec4* results = (vec4*)calloc(1, count * sizeof(vec4));
    float* fresults = (float*)calloc(1, count * sizeof(float));
    for(int i = 0; i < count; ++i)
    {
        vecs1[i] = { random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f };
        vecs2[i] = { random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f };
    }

    double start_vec4_add = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec4_add(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed vec4 add: %f ms\n", os_time_ms() - start_vec4_add);

    double start_vec4_sub = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        fresults[index] = hm_vec4_dot(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed vec4 dot: %f ms\n", os_time_ms() - start_vec4_sub);

    double start_vec4_normalize = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec4_normalize(&vecs1[index]);
    }
    printf("Elapsed vec4 normalize: %f ms\n", os_time_ms() - start_vec4_normalize);

    double start_vec4_normalize_fast = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec4_normalize_fast(&vecs1[index]);
    }
    printf("Elapsed vec4 normalize fast: %f ms\n", os_time_ms() - start_vec4_normalize_fast);
    
    double start_vec4_length = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        fresults[index] = hm_vec4_length(&vecs1[index]);
    }
    printf("Elapsed vec4 length: %f ms\n", os_time_ms() - start_vec4_length);

    double start_vec4_cross = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec4_cross(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed vec4 cross: %f ms\n", os_time_ms() - start_vec4_cross);

    double start_vec4_scalar_mul = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec4_scalar_mul(&vecs1[index], fresults[index]);
    }
    printf("Elapsed vec4 scalar mul: %f ms\n", os_time_ms() - start_vec4_scalar_mul);

    double start_vec4_abs = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec4_abs(&vecs1[index]);
    }
    printf("Elapsed vec4 abs: %f ms\n", os_time_ms() - start_vec4_abs);

    printf("\n");

    float rr = 0.0f;
    for(int i = 0; i < count; ++i)
    {
        rr += fresults[i] + results[i].x;
    }
    return rr;
}

/*
Elapsed dvec4 add: 5445.384000 ms
Elapsed dvec4 dot: 3646.020000 ms
Elapsed dvec4 normalize: 6133.261300 ms
Elapsed dvec4 length: 3725.622400 ms
Elapsed dvec4 cross: 6169.849200 ms
Elapsed dvec4 scalar mul: 4412.779000 ms
Elapsed dvec4 abs: 3993.645000 ms
*/
double
test_dvec4()
{
    const int count = 1024 * 1024;
#if defined(_WIN32) || defined(_WIN64)
    dvec4* vecs1 = (dvec4*)_aligned_malloc(count * sizeof(dvec4), 1024);
    dvec4* vecs2 =  (dvec4*)_aligned_malloc(count * sizeof(dvec4), 1024);
#else
    dvec4* vecs1 = (dvec4*)aligned_alloc(1024, count * sizeof(dvec4));
    dvec4* vecs2 =  (dvec4*)aligned_alloc(1024, count * sizeof(dvec4));
#endif
    dvec4* results = (dvec4*)calloc(1, count * sizeof(dvec4));
    double* fresults = (double*)calloc(1, count * sizeof(double));
    for(int i = 0; i < count; ++i)
    {
        vecs1[i] = { random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f };
        vecs2[i] = { random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f };
    }

    double start_vec4_add = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_dvec4_add(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed dvec4 add: %f ms\n", os_time_ms() - start_vec4_add);

    double start_vec4_sub = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        fresults[index] = hm_dvec4_dot(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed dvec4 dot: %f ms\n", os_time_ms() - start_vec4_sub);

    double start_vec4_normalize = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_dvec4_normalize(&vecs1[index]);
    }
    printf("Elapsed dvec4 normalize: %f ms\n", os_time_ms() - start_vec4_normalize);
    
    double start_vec4_length = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        fresults[index] = hm_dvec4_length(&vecs1[index]);
    }
    printf("Elapsed dvec4 length: %f ms\n", os_time_ms() - start_vec4_length);

    double start_vec4_cross = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_dvec4_cross(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed dvec4 cross: %f ms\n", os_time_ms() - start_vec4_cross);

    double start_vec4_scalar_mul = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_dvec4_scalar_mul(&vecs1[index], fresults[index]);
    }
    printf("Elapsed dvec4 scalar mul: %f ms\n", os_time_ms() - start_vec4_scalar_mul);

    double start_vec4_abs = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_dvec4_abs(&vecs1[index]);
    }
    printf("Elapsed dvec4 abs: %f ms\n", os_time_ms() - start_vec4_abs);

    printf("\n");

    double rr = 0.0;
    for(int i = 0; i < count; ++i)
    {
        rr += fresults[i] + results[i].x;
    }
    return rr;
}

/*
Elapsed dvec3 add: 4192.194500 ms
Elapsed dvec3 dot: 3079.720500 ms
Elapsed dvec3 normalize: 5686.107300 ms
Elapsed dvec3 length: 3435.396100 ms
Elapsed dvec3 cross: 4241.054300 ms
Elapsed dvec3 scalar mul: 3367.066000 ms
Elapsed dvec3 abs: 3140.505700 ms
*/
double
test_dvec3()
{
    const int count = 1024 * 1024;
    dvec3* vecs1 = (dvec3*)calloc(1, count * sizeof(dvec3));
    dvec3* vecs2 = (dvec3*)calloc(1, count * sizeof(dvec3));
    dvec3* results = (dvec3*)calloc(1, count * sizeof(dvec3));
    double* fresults = (double*)calloc(1, count * sizeof(double));
    for(int i = 0; i < count; ++i)
    {
        vecs1[i] = { random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f };
        vecs2[i] = { random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f };
    }

    double start_vec4_add = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_dvec3_add(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed dvec3 add: %f ms\n", os_time_ms() - start_vec4_add);

    double start_vec4_sub = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        fresults[index] = hm_dvec3_dot(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed dvec3 dot: %f ms\n", os_time_ms() - start_vec4_sub);

    double start_vec4_normalize = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_dvec3_normalize(&vecs1[index]);
    }
    printf("Elapsed dvec3 normalize: %f ms\n", os_time_ms() - start_vec4_normalize);
    
    double start_vec4_length = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        fresults[index] = hm_dvec3_length(&vecs1[index]);
    }
    printf("Elapsed dvec3 length: %f ms\n", os_time_ms() - start_vec4_length);

    double start_vec4_cross = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_dvec3_cross(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed dvec3 cross: %f ms\n", os_time_ms() - start_vec4_cross);

    double start_vec4_scalar_mul = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_dvec3_scalar_mul(&vecs1[index], fresults[index]);
    }
    printf("Elapsed dvec3 scalar mul: %f ms\n", os_time_ms() - start_vec4_scalar_mul);

    double start_vec4_abs = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_dvec3_abs(&vecs1[index]);
    }
    printf("Elapsed dvec3 abs: %f ms\n", os_time_ms() - start_vec4_abs);

    printf("\n");

    double rr = 0.0;
    for(int i = 0; i < count; ++i)
    {
        rr += fresults[i] + results[i].x;
    }
    return rr;
}

/*
Elapsed vec3 add: 2570.474500 ms
Elapsed vec3 dot: 1884.828700 ms
Elapsed vec3 normalize: 2250.588500 ms
Elapsed vec3 normalize fast: 2025.905800 ms
Elapsed vec3 length: 1305.576200 ms
Elapsed vec3 cross: 2293.234400 ms
Elapsed vec3 scalar mul: 1781.339500 ms
Elapsed vec3 abs: 1586.712500 ms
*/
float
test_vec3()
{
    const int count = 1024 * 1024;
    vec3* vecs1 = (vec3*)calloc(1, count * sizeof(vec3));
    vec3* vecs2 = (vec3*)calloc(1, count * sizeof(vec3));
    vec3* results = (vec3*)calloc(1, count * sizeof(vec3));
    float* fresults = (float*)calloc(1, count * sizeof(float));
    for(int i = 0; i < count; ++i)
    {
        vecs1[i] = { random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f };
        vecs2[i] = { random_int() / 1000.0f, random_int() / 1000.0f, random_int() / 1000.0f };
    }

    double start_vec4_add = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec3_add(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed vec3 add: %f ms\n", os_time_ms() - start_vec4_add);

    double start_vec4_sub = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        fresults[index] = hm_vec3_dot(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed vec3 dot: %f ms\n", os_time_ms() - start_vec4_sub);

    double start_vec4_normalize = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec3_normalize(&vecs1[index]);
    }
    printf("Elapsed vec3 normalize: %f ms\n", os_time_ms() - start_vec4_normalize);

    double start_vec4_normalize_fast = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec3_normalize_fast(&vecs1[index]);
    }
    printf("Elapsed vec3 normalize fast: %f ms\n", os_time_ms() - start_vec4_normalize_fast);
    
    double start_vec4_length = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        fresults[index] = hm_vec3_length(&vecs1[index]);
    }
    printf("Elapsed vec3 length: %f ms\n", os_time_ms() - start_vec4_length);

    double start_vec4_cross = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec3_cross(&vecs1[index], &vecs2[index]);
    }
    printf("Elapsed vec3 cross: %f ms\n", os_time_ms() - start_vec4_cross);

    double start_vec4_scalar_mul = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec3_scalar_mul(&vecs1[index], fresults[index]);
    }
    printf("Elapsed vec3 scalar mul: %f ms\n", os_time_ms() - start_vec4_scalar_mul);

    double start_vec4_abs = os_time_ms();
    for(int i = 0; i < 1024 * 1024 * 1024; ++i)
    {
        int index = i % (1024 * 1024);
        results[index] = hm_vec3_abs(&vecs1[index]);
    }
    printf("Elapsed vec3 abs: %f ms\n", os_time_ms() - start_vec4_abs);

    printf("\n");
    
    float rr = 0.0f;
    for(int i = 0; i < count; ++i)
    {
        rr += fresults[i] + results[i].x;
    }
    return rr;
}

int main()
{
    os_time_init();
    printf("1 billion operations\n");

    test_vec4();
    test_dvec4();
    test_vec3();
    test_dvec3();
    
    return 0;
}

/*
    Linux

    examples $ ./speed 
    1 billion operations
    Elapsed vec4 add: 2345.949028 ms
    Elapsed vec4 dot: 2212.202023 ms
    Elapsed vec4 normalize: 2043.374568 ms
    Elapsed vec4 normalize fast: 1789.477201 ms
    Elapsed vec4 length: 1356.521813 ms
    Elapsed vec4 cross: 2474.695104 ms
    Elapsed vec4 scalar mul: 1864.751791 ms
    Elapsed vec4 abs: 1744.302662 ms

    Elapsed dvec4 add: 5178.094389 ms
    Elapsed dvec4 dot: 3275.663008 ms
    Elapsed dvec4 normalize: 6307.718846 ms
    Elapsed dvec4 length: 3795.735880 ms
    Elapsed dvec4 cross: 5077.216081 ms
    Elapsed dvec4 scalar mul: 4211.299050 ms
    Elapsed dvec4 abs: 3989.876452 ms

    Elapsed vec3 add: 2760.888243 ms
    Elapsed vec3 dot: 1611.408845 ms
    Elapsed vec3 normalize: 2669.961244 ms
    Elapsed vec3 normalize fast: 2468.732401 ms
    Elapsed vec3 length: 1328.039708 ms
    Elapsed vec3 cross: 2794.601105 ms
    Elapsed vec3 scalar mul: 2657.731960 ms
    Elapsed vec3 abs: 2563.941205 ms

    Elapsed dvec3 add: 4268.896420 ms
    Elapsed dvec3 dot: 2802.857317 ms
    Elapsed dvec3 normalize: 6185.614056 ms
    Elapsed dvec3 length: 3771.633514 ms
    Elapsed dvec3 cross: 4250.477878 ms
    Elapsed dvec3 scalar mul: 3591.949945 ms
    Elapsed dvec3 abs: 3318.034499 ms
*/