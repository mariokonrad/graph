add_executable(graph graph.cpp)
target_link_libraries(graph libgraph)

add_executable(dotify dotify.cpp)
target_link_libraries(dotify libgraph)
