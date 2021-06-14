file(GLOB SOURCES
    "*.cpp"
    "*.c")
file(GLOB HEADERS
    "*.h")

add_library(VLL STATIC ${SOURCES} ${HEADERS})
target_include_directories(VLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET VLL POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               "${HEADERS}"
                ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
