CMAKE_MINIMUM_REQUIRED(VERSION 3.1 FATAL_ERROR)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(RUST_AND_FOLDER debug)
else()
    message(FATAL_ERROR "Unexpected build type ${CMAKE_BUILD_TYPE} specified.")
endif()

if(${ANDROID_ABI} MATCHES "arm64-v8a")
    set(RUST_AND_FOLDER "aarch64-linux-android/${RUST_AND_FOLDER}")
elseif(ANDROID_ABI MATCHES "armeabi-v7a")
    set(RUST_AND_FOLDER "armv7-linux-androideabi/${RUST_AND_FOLDER}")
else()
    message(FATAL_ERROR "Unexpected arch ${ANDROID_ABI} specified.")
endif()

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
add_library(main SHARED main.c)
target_link_libraries(
        main
        log
        ${CMAKE_SOURCE_DIR}/../../../../../rust-graphics-hello-triangle/target/${RUST_AND_FOLDER}/librust_graphics_lib.a)