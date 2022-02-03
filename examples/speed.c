#include <stdio.h>
#include "../hmath.h"
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

int random()
{
    int result = 0;
    _rdrand32_step(&result);
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
void
test_vec4()
{
    const int count = 1024 * 1024;
    vec4* vecs1 = calloc(1, count * sizeof(vec4));
    vec4* vecs2 = calloc(1, count * sizeof(vec4));
    vec4* results = calloc(1, count * sizeof(vec4));
    float* fresults = calloc(1, count * sizeof(float));
    for(int i = 0; i < count; ++i)
    {
        vecs1[i] = (vec4){ random() / 1000.0f, random() / 1000.0f, random() / 1000.0f, random() / 1000.0f };
        vecs2[i] = (vec4){ random() / 1000.0f, random() / 1000.0f, random() / 1000.0f, random() / 1000.0f };
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
void
test_dvec4()
{
    const int count = 1024 * 1024;
    dvec4* vecs1 = calloc(1, count * sizeof(dvec4));
    dvec4* vecs2 = calloc(1, count * sizeof(dvec4));
    dvec4* results = calloc(1, count * sizeof(dvec4));
    double* fresults = calloc(1, count * sizeof(double));
    for(int i = 0; i < count; ++i)
    {
        vecs1[i] = (dvec4){ random() / 1000.0f, random() / 1000.0f, random() / 1000.0f, random() / 1000.0f };
        vecs2[i] = (dvec4){ random() / 1000.0f, random() / 1000.0f, random() / 1000.0f, random() / 1000.0f };
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
void
test_dvec3()
{
    const int count = 1024 * 1024;
    dvec3* vecs1 = calloc(1, count * sizeof(dvec3));
    dvec3* vecs2 = calloc(1, count * sizeof(dvec3));
    dvec3* results = calloc(1, count * sizeof(dvec3));
    double* fresults = calloc(1, count * sizeof(double));
    for(int i = 0; i < count; ++i)
    {
        vecs1[i] = (dvec3){ random() / 1000.0f, random() / 1000.0f, random() / 1000.0f };
        vecs2[i] = (dvec3){ random() / 1000.0f, random() / 1000.0f, random() / 1000.0f };
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
void
test_vec3()
{
    const int count = 1024 * 1024;
    vec3* vecs1 = calloc(1, count * sizeof(vec3));
    vec3* vecs2 = calloc(1, count * sizeof(vec3));
    vec3* results = calloc(1, count * sizeof(vec3));
    float* fresults = calloc(1, count * sizeof(float));
    for(int i = 0; i < count; ++i)
    {
        vecs1[i] = (vec3){ random() / 1000.0f, random() / 1000.0f, random() / 1000.0f };
        vecs2[i] = (vec3){ random() / 1000.0f, random() / 1000.0f, random() / 1000.0f };
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
}

int main()
{
    os_time_init();
    printf("1 billion operations\n");

    //test_vec4();
    test_dvec4();
    //test_vec3();
    //test_dvec3();
    
    return 0;
}