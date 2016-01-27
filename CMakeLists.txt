project (Jui)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(LINUX 1)
endif()

cmake_minimum_required (VERSION 2.8.11)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH test1)

# CMAKE_SOURCE_DIR || CMAKE_CURRENT_SOURCE_DIR-> zdrojovy adresar
# CMAKE_BINARY_DIR || CMAKE_CURRENT_BINARY_DIR-> cilovy adresar sestaveni

#cesta pro instal
SET(CMAKE_INSTALL_PATH "${CMAKE_CURRENT_BINARY_DIR}/Jui_Install" CACHE STRING "Build dir")

add_executable(Jui testQt.cpp)

if (WIN32)
	message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
	message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
	message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
	message(STATUS  "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
	message(STATUS "CMAKE_INSTALL_PATH: ${CMAKE_INSTALL_PATH}")
	#message(SEND_ERROR "CMAKE_INSTALL_PATH: ${CMAKE_INSTALL_PATH}")
endif()

#target_include_directories (libsclang ${FFTW3F_INCLUDE_DIR})
	#target_link_libraries(libsclang ${FFTW3F_LIBRARY})

#set(SC_SOURCE_DIR "SC_SOURCE_PATH" CACHE STRING "A path to SuperCollider source directory")
#set(SC_BUILD_DIR "SC_BUILD_PATH" CACHE STRING "A path to SuperCollider build directory")
SET(QT_DIR "QT_DIR" CACHE STRING "Qt source dir")
#SET(QT_LIB "QT_Lib" CACHE STRING "Qt source dir")

include_directories ("${QT_DIR}")