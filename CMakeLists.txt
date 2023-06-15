cmake_minimum_required(VERSION 3.19)
project(tensorflowlite-examples)

#set(CMAKE_CXX_STANDARD 11)

add_definitions(-D${ARCH})

# 引入Conan的CMake
set(CONAN_DISABLE_CHECK_COMPILER 1)
if (${ARCH} STREQUAL "x64")
    execute_process(COMMAND sh build_local.sh
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/conan)
else ()
    execute_process(COMMAND sh build_aarch64.sh
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/conan)
endif ()
include(conan/build/conanbuildinfo.cmake)
set(CMAKE_C_FLAGS "-Wl,-rpath=./:./lib")
set(CMAKE_CXX_FLAGS "-Wl,-rpath=./:./lib")
conan_basic_setup(KEEP_RPATHS)
file(GLOB allCopyFiles  "conan/build/bin/*")
file(COPY ${allCopyFiles} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib FOLLOW_SYMLINK_CHAIN)
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
include(utility)
include(CPM)

if (${ARCH} STREQUAL "x64")
    include_directories(lib/x64)
    file(GLOB allCopyFiles "lib/x64/*.so" "lib/x64/*.so.*" "lib/x64/*.a")
    file(COPY ${allCopyFiles} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib FOLLOW_SYMLINK_CHAIN)
else ()
    include_directories(lib/arm64)
    file(GLOB allCopyFiles "lib/arm64/*.so" "lib/arm64/*.so.*" "lib/arm64/*.a")
    file(COPY ${allCopyFiles} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib FOLLOW_SYMLINK_CHAIN)
endif ()
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)
set(CMAKE_CXX_FLAGS "-Wl,-rpath=lib")

set(LIBS m pthread ${CONAN_LIBS})

add_subdirectory(detect_demo)
add_subdirectory(object_detection)
add_subdirectory(image_detection)
add_subdirectory(webcam_detection)