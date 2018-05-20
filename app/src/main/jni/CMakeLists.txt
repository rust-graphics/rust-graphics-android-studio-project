cmake_minimum_required(VERSION 3.4.1)
set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
add_library(
    native_app_glue
    STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
add_library(vulkust SHARED main.cpp)
target_include_directories(
    vulkust
    PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue)
target_link_libraries(
    vulkust
    android
    native_app_glue
    log
    vulkan
    /Users/hossein/Documents/Projects/vulkust/target/aarch64-linux-android/libvulkust-static.a)