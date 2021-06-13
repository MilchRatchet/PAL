file(GLOB SOURCES
    "*.cpp"
    "*.c")
file(GLOB HEADERS
    "*.h")

add_library(lib_VL STATIC ${SOURCES} ${HEADERS})
target_include_directories(lib_VL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
