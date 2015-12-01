cmake_minimum_required(VERSION 3.0)

add_library(graph
	graph/bfs.hpp
	graph/dfs.hpp
	utils/priority_queue.hpp
	graph/adjmatrix.cpp
	graph/dot.cpp
	graph/toposort.cpp
	graph/path.cpp
	graph/mst.cpp
	)

set_target_properties(graph
	PROPERTIES VERSION "${PROJECT_VERSION}"
	SOVERSION "${PROJECT_VERSION}"
	)

install(
	TARGETS graph
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

install(
	FILES
		graph/adjmatrix.hpp
		graph/dot.hpp
		graph/bfs.hpp
		graph/dfs.hpp
		graph/mst.hpp
		graph/path.hpp
		graph/toposort.hpp
	DESTINATION include/graph
	)

install(
	DIRECTORY
		utils
	DESTINATION include
	)

# stuff for the config and config-version files
set(INCLUDE_INSTALL_DIR include)
set(LIB_INSTALL_DIR lib)
include(CMakePackageConfigHelpers)
configure_package_config_file(
	config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
	INSTALL_DESTINATION "${LIB_INSTALL_DIR}/${PROJECT_NAME}/cmake"
	PATH_VARS INCLUDE_INSTALL_DIR
	)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	VERSION "${PROJECT_VERSION}"
	COMPATIBILITY SameMajorVersion)
install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	DESTINATION
		"${LIB_INSTALL_DIR}/${PROJECT_NAME}/cmake"
	)


