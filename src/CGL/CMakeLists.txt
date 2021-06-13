file(GLOB SOURCES
    "*.cpp"
    "*.c")
file(GLOB HEADERS
    "*.h")

add_library(lib_CG STATIC ${SOURCES} ${HEADERS})
target_include_directories(lib_CG PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
