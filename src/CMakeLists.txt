cmake_minimum_required(VERSION 3.0)

file(GLOB_RECURSE HEADERS graph/*.hpp)

add_library(graph INTERFACE)

install(
	FILES
		${HEADERS}
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


