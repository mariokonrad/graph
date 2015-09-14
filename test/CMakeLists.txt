include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	)

add_executable(testrunner
	utils/Test_priority_queue.cpp
	)

target_link_libraries(testrunner
	libgraph
	gmock
	pthread
	)

add_test(
	NAME unittest-testrunner
	COMMAND testrunner
	WORKING_DIRECTOR "${CMAKE_CURRENT_BINARY_DIR}"
	)
run_unittest(testrunner)

