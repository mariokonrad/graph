add_executable(demo demo.cpp)
target_link_libraries(demo graph)

add_executable(dotify dotify.cpp)
target_link_libraries(dotify graph)
