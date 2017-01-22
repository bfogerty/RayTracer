cmake_minimum_required(VERSION 3.5)

project( RayTracer )

SET(GCC_COVERAGE_COMPILE_FLAGS "-v")

set(SRC src)
set(COLOR_SRC src/color)
set(MATH_SRC src/math)
set(TIME_SRC src/time)
set(RENDERER_SRC src/renderer)
set(EXPORT_SRC src/export)
set(PYTHON_SRC src/external/python)
set(PYTHON_FILTER_SRC src/filter/python)

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

file(GLOB renderer_src
    "${RENDERER_SRC}/*.h"
    "${RENDERER_SRC}/*.cpp"
    "${RENDERER_SRC}/*.c"
)

file(GLOB export_src
    "${EXPORT_SRC}/*.h"
    "${EXPORT_SRC}/*.cpp"
    "${EXPORT_SRC}/*.c"
)

file(GLOB python_src
    "${PYTHON_SRC}/*.h"
    "${PYTHON_SRC}/*.cpp"
    "${PYTHON_SRC}/*.c"
)

file(GLOB python_filter_src
    "${PYTHON_FILTER_SRC}/*.h"
    "${PYTHON_FILTER_SRC}/*.cpp"
    "${PYTHON_FILTER_SRC}/*.c"
)

source_group("src" FILES ${main_src})
source_group("color" FILES ${color_src})
source_group("math" FILES ${math_src})
source_group("time" FILES ${time_src})
source_group("renderer" FILES ${renderer_src})
source_group("export" FILES ${export_src})
source_group("python" FILES ${python_src})
source_group("python filter" FILES ${python_filter_src})

list(SORT main_src)
list(SORT color_src)
list(SORT math_src)
list(SORT time_src)
list(SORT renderer_src)
list(SORT export_src)
list(SORT python_src)
list(SORT python_filter_src)

link_directories(src/external/python/lib/)

# add the executable
add_executable(RayTracer ${main_src} ${color_src} ${math_src} ${time_src} ${renderer_src} ${export_src} ${python_src} ${python_filter_src})
