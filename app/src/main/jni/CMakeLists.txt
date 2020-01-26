CMAKE_MINIMUM_REQUIRED(VERSION 3.1 FATAL_ERROR)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(RUST_AND_FOLDER debug)
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    set(RUST_AND_FOLDER release)
else()
    message(FATAL_ERROR "Unexpected build type ${CMAKE_BUILD_TYPE} specified.")
endif()

if(${ANDROID_ABI} MATCHES "arm64-v8a")
    set(RUST_AND_FOLDER "aarch64-linux-android/${RUST_AND_FOLDER}")
elseif(${ANDROID_ABI} MATCHES "x86_64")
    set(RUST_AND_FOLDER "x86_64-linux-android/${RUST_AND_FOLDER}")
elseif(${ANDROID_ABI} MATCHES "x86")
    set(RUST_AND_FOLDER "i686-linux-android/${RUST_AND_FOLDER}")
elseif(ANDROID_ABI MATCHES "armeabi-v7a")
    set(RUST_AND_FOLDER "armv7-linux-androideabi/${RUST_AND_FOLDER}")
else()
    message(FATAL_ERROR "Unexpected arch ${ANDROID_ABI} specified.")
endif()

set(RUST_AND_FOLDER "target/${RUST_AND_FOLDER}")

set(APP_GLUE_PATH "${ANDROID_NDK}/sources/android/native_app_glue")
add_library(native-app-glue STATIC ${APP_GLUE_PATH}/android_native_app_glue.c)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(main SHARED main.c)
target_link_libraries(
        main
        log
        android
        EGL
        m
        native-app-glue
        ${CMAKE_SOURCE_DIR}/../../../../../rust-graphics-hello-triangle/${RUST_AND_FOLDER}/librust_graphics_lib.a)