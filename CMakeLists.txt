cmake_minimum_required(VERSION 3.10)

project(PAL)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic -Wall -Wextra")

add_subdirectory(src/AAL)
add_subdirectory(src/CGL)
add_subdirectory(src/VLL)
add_subdirectory(testsuite)

add_executable(${PROJECT_NAME} main.cpp)

#target_include_directories(${PROJECT_NAME} PUBLIC )

target_link_libraries(${PROJECT_NAME} lib_AA lib_CG lib_VL lib_test)
