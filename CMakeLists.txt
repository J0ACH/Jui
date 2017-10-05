cmake_minimum_required( VERSION 3.7.2 )
cmake_policy(SET CMP0048 NEW)
project (Jui VERSION 0.0.5)

message(STATUS "")
message(STATUS "Jui [${PROJECT_VERSION}] config init...")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(CMAKE_AUTOMOC ON)

set(cacheDir ${CMAKE_SOURCE_DIR}/cache)
set(buildDir ${CMAKE_SOURCE_DIR}/build)
set(installDir ${CMAKE_SOURCE_DIR}/install)

message(STATUS "\t cacheDir: ${cacheDir}")
message(STATUS "\t buildDir: ${buildDir}")
message(STATUS "\t installDir: ${installDir}")

add_subdirectory(source)

message(STATUS "Jui config done...\n")

# CPACK SETUP ###################################################
# otevri package.vcxproj - pMouse - Open dev cmd propmpt - "cpack"

if(WIN32)
	set(CPACK_GENERATOR WIX)
	set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
	set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
	set(CPACK_PACKAGE_DIRECTORY ${buildDir})
	set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CMAKE_PROJECT_NAME})
	
	set(CPACK_WIX_UPGRADE_GUID "EE4C89CB-D529-4698-8EF7-659EEAB9CA4E")
	set(CPACK_WIX_CMAKE_PACKAGE_REGISTRY "Jui")
	
	include(CPack)
endif()