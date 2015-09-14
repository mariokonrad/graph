cmake_minimum_required(VERSION 3.0)

add_library(libgraph
	graph/adjmatrix.hpp
	graph/graph_bfs.hpp
	graph/graph_dfs.hpp
	graph/graph_mst.hpp
	graph/graph_path.hpp
	graph/graph_toposort.hpp
	graph/property_map.hpp
	utils/priority_queue.hpp
	dummy.cpp
	)

install(
	DIRECTORY
		graph
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


