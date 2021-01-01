/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

struct vec3d {
    float x;
    float y;
    float z;
};
void __program_sredtest_internal(vec3d * __restrict__ A)
{

    {
        
        
        {
            vec3d a;

            ///////////////////
            // Tasklet code (sredtest_10)
            a = vec3d { .x = float(1.0), .y = float(2.0), .z = float(3.0) };
            ///////////////////

            dace::wcr_custom<vec3d>:: template reduce([] (const vec3d& a, const vec3d& b) { return vec3d { .x = (a.x + b.x), .y = (a.y + b.y), .z = (a.z + b.z) }; }, A, a);
        }
    }
}

DACE_EXPORTED void __program_sredtest(vec3d * __restrict__ A)
{
    __program_sredtest_internal(A);
}

DACE_EXPORTED int __dace_init_sredtest(vec3d * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_sredtest(vec3d * __restrict__ A)
{
}

