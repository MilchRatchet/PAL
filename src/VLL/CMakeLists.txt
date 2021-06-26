set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wl,-Bstatic -lSDL2main -lSDL2 -Wl,-Bdynamic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wl,-Bstatic -lSDL2main -lSDL2 -Wl,-Bdynamic")

file(GLOB SOURCES
    "*.cpp"
    "*.c")
file(GLOB HEADERS
    "*.h")

add_library(VLL STATIC ${SOURCES} ${HEADERS})
target_link_libraries(VLL SDL2main SDL2)

target_include_directories(VLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#
# This does not work here right now for some reason
#
#add_custom_command(TARGET VLL POST_BUILD
#               COMMAND ${CMAKE_COMMAND} -E copy_if_different
#               "${HEADERS}"
#                ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
