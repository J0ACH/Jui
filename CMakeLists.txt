project (Jui)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(LINUX 1)
endif()

cmake_minimum_required (VERSION 2.8.11)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH test1)

SET(CMAKE_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/Jui_Install" CACHE STRING "Build dir")

set(SC_SOURCE_DIR "SC_SOURCE_PATH" CACHE STRING "A path to SuperCollider source directory")
set(SC_BUILD_DIR "SC_BUILD_PATH" CACHE STRING "A path to SuperCollider build directory")
SET(QT_DIR "QT_Dir" CACHE STRING "Qt source dir")
SET(QT_LIB "QT_Lib" CACHE STRING "Qt source dir")