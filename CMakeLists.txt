cmake_minimum_required(VERSION 3.3)

project( RayTracer )

SET(GCC_COVERAGE_COMPILE_FLAGS "-v")

set(SRC src)

include_directories(
    "${SRC}"
)

file(GLOB main_src
    "${SRC}/*.h"
    "${SRC}/*.cpp"
    "${SRC}/*.c"
)

source_group("src" FILES ${main_src})

list(SORT main_src)

# add the executable
add_executable(RayTracer ${main_src})
