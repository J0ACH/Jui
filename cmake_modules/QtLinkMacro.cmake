
#use like: QtLink(target_library Core Widgets)

FUNCTION (QtLink Target)

	SET(QtComponents ${ARGN})
	STRING(TOUPPER ${CMAKE_CONFIGURATION_TYPES} ConfigType)
	MESSAGE(STATUS "QtLink macro for ${Target} init [ConfigType: ${ConfigType}]")
		
	FOREACH(oneComponent ${QtComponents})
		MESSAGE(STATUS "\t - adding link to " ${oneComponent})
		GET_TARGET_PROPERTY(COMPONENT_INCLUDE_DIRS Qt5::${oneComponent} INTERFACE_INCLUDE_DIRECTORIES)
		GET_TARGET_PROPERTY(COMPONENT_LIBRARIES Qt5::${oneComponent} IMPORTED_IMPLIB_${ConfigType})
		GET_TARGET_PROPERTY(COMPONENT_LOCATION Qt5::${oneComponent} IMPORTED_LOCATION_${ConfigType})
		
		TARGET_INCLUDE_DIRECTORIES(${Target} PUBLIC ${COMPONENT_INCLUDE_DIRS})
		TARGET_LINK_LIBRARIES(${Target} PUBLIC ${COMPONENT_LIBRARIES})
		
		MESSAGE(STATUS "\t\t - ${oneComponent} LIBRARIES: ${COMPONENT_LIBRARIES}")
		MESSAGE(STATUS "\t\t - ${oneComponent} INCLUDE_DIRS:")
		FOREACH(onePath ${COMPONENT_INCLUDE_DIRS})
	 		MESSAGE(STATUS "\t\t\t - " ${onePath})
		ENDFOREACH(onePath)
		MESSAGE(STATUS "\t\t - ${oneComponent} LOCATION: ${COMPONENT_LOCATION}")

		#ADD_CUSTOM_COMMAND(TARGET ${Target}
		#	POST_BUILD
		#	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		#	${COMPONENT_LOCATION} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ConfigType}
		#)
		
		INSTALL(FILES ${COMPONENT_LOCATION} DESTINATION install)	

	ENDFOREACH(oneComponent)

	IF(WIN32)
		GET_FILENAME_COMPONENT(QT_BIN_DIR ${COMPONENT_LOCATION} PATH)
		#MESSAGE(STATUS "QT_BIN_DIR: " ${QT_BIN_DIR} )
		INSTALL(
			FILES  ${QT_BIN_DIR}/../plugins/platforms/qwindows.dll
			DESTINATION install/platforms
		)
	ENDIF(WIN32)

	MESSAGE(STATUS "QtLink macro done...\n")

ENDFUNCTION(QtLink)

FUNCTION (TestPozdrav)
	MESSAGE(STATUS "QtLink macro pozdrav...\n")
ENDFUNCTION (TestPozdrav)