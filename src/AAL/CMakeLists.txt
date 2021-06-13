file(GLOB SOURCES
    "*.cpp"
    "*.c")
file(GLOB HEADERS
    "*.h")

add_library(lib_AA STATIC ${SOURCES} ${HEADERS})
target_include_directories(lib_AA PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
