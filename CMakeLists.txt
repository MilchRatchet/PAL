cmake_minimum_required(VERSION 3.10)

project(PAL)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic -Wall -Wextra")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)

set(CMAKE_SKIP_INSTALL_RULES True)

add_subdirectory(src/AAL)
add_subdirectory(src/CGL)
add_subdirectory(src/VLL)
add_subdirectory(testsuite)

#target_include_directories(${PROJECT_NAME} PUBLIC )

#target_link_libraries(${PROJECT_NAME} lib_AA lib_CG lib_VL lib_test)
