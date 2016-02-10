project (Jui)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(LINUX 1)
endif()

cmake_minimum_required( VERSION 2.8.11 )

INCLUDE("JuiVersion.txt" ${QT_USE_FILE})
SET(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}${PROJECT_VERSION_PATCH}")

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)

if(CMAKE_GENERATOR MATCHES "Visual Studio 12 2013")
    set(CMAKE_CONFIGURATION_TYPES Release)
    set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
        "Reset the configurations to what we need/support"
        FORCE
    )
    message(STATUS "Generating files with generator \"${CMAKE_GENERATOR}\"")
    message(STATUS "Please choose build configuration (\"Release\" or \"Debug\") in next step.")
ENDIF()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/JuiLibrary" CACHE STRING "Cmake install path" FORCE)
endif()

OPTION(JUI_CANVAN_SYSTEMFRAME "Canvan system frame" OFF)
CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/JuiConfig.h.in"
  "${PROJECT_BINARY_DIR}/JuiConfig.h"
)

MESSAGE(STATUS "JUI_VERSION : " ${PROJECT_VERSION} )

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

ADD_SUBDIRECTORY(Classes)
#ADD_SUBDIRECTORY(Resources)







