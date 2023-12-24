cmake_minimum_required(VERSION 3.8)

project("dummy")

set(CMAKE_CXX_STANDARD 17)

set(LINKER_FLAGS "-ffixed-x18 -Wl,--hash-style=both")
set(C_FLAGS "-Werror=format -fdata-sections -ffunction-sections -std=c2x -Wno-error=format-security -w -fno-rtti -fpermissive")
set(CXX_FLAGS "${CXX_FLAGS} -Wno-error=format-security -ffunction-sections -fdata-sections -w -Werror -s -std=c++20 -Wno-error=c++20-narrowing -fms-extensions -fno-rtti -fpermissive")

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(C_FLAGS "${C_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
    set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,-exclude-libs,ALL -Wl,--gc-sections -Wl,--strip-all")
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${C_FLAGS} ${CXX_FLAGS} -O0")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LINKER_FLAGS}")

add_library(
        dummy SHARED
        dummy.cpp
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_android.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        libs/xdl/xdl.c
        libs/xdl/xdl_iterate.c
        libs/xdl/xdl_linker.c
        libs/xdl/xdl_lzma.c
        libs/xdl/xdl_util.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/dobby/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/assets)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/xdl)

set(DOBBY_LIB ${CMAKE_CURRENT_SOURCE_DIR}/libs/dobby/${CMAKE_ANDROID_ARCH_ABI}/libdobby.a)

target_link_libraries(dummy android EGL GLESv3 log ${DOBBY_LIB})