cmake_minimum_required(VERSION 3.13)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
project(qwqng-wrapper)

add_library ( qwqng-wrapper-x86-64 SHARED qwqng-wrapper.cpp )
#add_library ( qwqng-wrapper SHARED qwqng-wrapper.cpp )

target_compile_options ( qwqng-wrapper-x86-64 PUBLIC "-m64" )
target_link_options( qwqng-wrapper-x86-64 PUBLIC "-m64")

#target_compile_options ( qwqng-wrapper PUBLIC "-m32" )
#target_link_options( qwqng-wrapper PUBLIC "-m32")

#find_library(QWQNG_LIBRARY32 NAMES qwqng PATHS /usr/local/lib)
find_library(QWQNG_LIBRARY64 NAMES qwqng PATHS /usr/local/lib64 /usr/local/lib)
target_link_libraries(qwqng-wrapper-x86-64 ${QWQNG_LIBRARY64})
#target_link_libraries(qwqng-wrapper ${QWQNG_LIBRARY32})