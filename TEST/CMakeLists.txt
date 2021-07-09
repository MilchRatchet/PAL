file(GLOB SOURCES
    "*.cpp"
    "*.c")
file(GLOB HEADERS
    "*.h"
    "*.hpp")

add_executable(TEST ${SOURCES} ${HEADERS})
target_include_directories(TEST PUBLIC ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
target_link_libraries(TEST AAL CGL VLL)

add_dependencies(TEST AAL CGL VLL)
