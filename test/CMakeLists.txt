include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	)

add_executable(testrunner
	utils/Test_priority_queue.cpp
	graph/Test_adjmatrix.cpp
	graph/Test_dfs.cpp
	graph/Test_bfs.cpp
	graph/Test_toposort.cpp
	graph/Test_mst.cpp
	graph/Test_dot.cpp
	graph/Test_path.cpp
	)

target_link_libraries(testrunner
	graph
	gmock
	pthread
	)

add_test(
	NAME unittest-testrunner
	COMMAND testrunner
	WORKING_DIRECTOR "${CMAKE_CURRENT_BINARY_DIR}"
	)
run_unittest(testrunner)

