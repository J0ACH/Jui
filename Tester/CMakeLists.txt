message(STATUS "Jui Tester")
message(STATUS ${PROJECT_SOURCE_DIR})
message(STATUS ${PROJECT_BINARY_DIR})

FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)



# tohle funguje az kdyz probiha druhy install, jinak v cily nic neni

#INCLUDE_DIRECTORIES(your/header/dir)
#LINK_DIRECTORIES(your/library/dir)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/JuiLibrary/include)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/JuiLibrary/lib)
# 


SET(QT_TESTER_LIBRARIES 
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets
)

ADD_EXECUTABLE(JuiTester WIN32 JuiTester.cpp)

TARGET_LINK_LIBRARIES(JuiTester ${QT_TESTER_LIBRARIES})

#LINKER(EXE TARGET)
TARGET_LINK_LIBRARIES(JuiTester Jui)

INSTALL(TARGETS JuiTester DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

if(WIN32)	
	SET(QT_DLL_DIR ${Qt5Core_DIR}/../../../bin)
	
	SET(QT_LIBRARIES_RELEASE
		${QT_DLL_DIR}/Qt5Core.dll
		${QT_DLL_DIR}/Qt5Gui.dll
		${QT_DLL_DIR}/Qt5Widgets.dll
		${QT_DLL_DIR}/icuin53.dll
		${QT_DLL_DIR}/icuuc53.dll
		${QT_DLL_DIR}/icudt53.dll
	)

	IF(CMAKE_C_FLAGS_RELEASE)
		FILE(COPY ${QT_LIBRARIES_RELEASE} DESTINATION ${PROJECT_BINARY_DIR}/JuiLibrary/bin)
	ENDIF()
ENDIF()