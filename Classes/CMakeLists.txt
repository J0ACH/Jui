message(STATUS "Jui Classes")

FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)

SET(QT_JUI_LIBRARIES 
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

SET(Jui_src
	Canvan.cpp
	Button.cpp
	Console.cpp
)

SET(Jui_hdr
	Canvan.h
	Button.h
	Console.h
)

SET(Jui_res
	
)



message(STATUS ${Jui_hdr})

ADD_LIBRARY(Jui STATIC 
	${Jui_src}
	${Jui_hdr}
	${Jui_res}
)

TARGET_LINK_LIBRARIES(Jui ${QT_JUI_LIBRARIES})

INSTALL(TARGETS Jui DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
INSTALL(FILES ${Jui_hdr} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)





