file(GLOB SOURCES
    "*.cpp"
    "*.c")
file(GLOB HEADERS
    "*.h")

add_executable(TEST ${SOURCES} ${HEADERS})
target_include_directories(TEST PUBLIC ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
