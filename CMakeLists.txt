cmake_minimum_required(VERSION 3.5)

project( RayTracer )

SET(GCC_COVERAGE_COMPILE_FLAGS "-v")

set(SRC src)
set(COLOR_SRC src/color)
set(MATH_SRC src/math)
set(TIME_SRC src/time)
set(EXPORT_SRC src/export)

include_directories(
    "${SRC}"
)

file(GLOB main_src
    "${SRC}/*.h"
    "${SRC}/*.cpp"
    "${SRC}/*.c"
)

file(GLOB color_src
    "${COLOR_SRC}/*.h"
    "${COLOR_SRC}/*.cpp"
    "${COLOR_SRC}/*.c"
)

file(GLOB math_src
    "${MATH_SRC}/*.h"
    "${MATH_SRC}/*.cpp"
    "${MATH_SRC}/*.c"
)

file(GLOB time_src
    "${TIME_SRC}/*.h"
    "${TIME_SRC}/*.cpp"
    "${TIME_SRC}/*.c"
)

file(GLOB export_src
    "${EXPORT_SRC}/*.h"
    "${EXPORT_SRC}/*.cpp"
    "${EXPORT_SRC}/*.c"
)

source_group("src" FILES ${main_src})
source_group("color" FILES ${color_src})
source_group("math" FILES ${math_src})
source_group("time" FILES ${time_src})
source_group("export" FILES ${export_src})

list(SORT main_src)
list(SORT color_src)
list(SORT math_src)
list(SORT time_src)
list(SORT export_src)

# add the executable
add_executable(RayTracer ${main_src} ${color_src} ${math_src} ${time_src} ${export_src})
