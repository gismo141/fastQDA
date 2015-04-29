cmake_minimum_required(VERSION 2.8.11)

project(fastQDA)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_definitions(-std=c++11)

if( APPLE )
	set(PROGNAME fastQDA )
	# set(MACOSX_BUNDLE_ICON_FILE fastQDA.icns )
	set(MACOSX_BUNDLE_SHORT_VERSION_STRING 0.1-alpha )
    set(MACOSX_BUNDLE_VERSION 0.1-alpha )
    set(MACOSX_BUNDLE_LONG_VERSION_STRING Version 0.1-alpha )
else( APPLE )
	set(PROGNAME fastQDA )
endif( APPLE )

find_package(Qt5Core REQUIRED)
find_package(Poppler COMPONENTS Qt5 REQUIRED)

# Can be multiple include directories for poppler
separate_arguments(POPPLER_INCLUDE_DIRS)
foreach(_include_dir ${POPPLER_INCLUDE_DIRS})
    include_directories(${_include_dir})
endforeach(_include_dir ${POPPLER_INCLUDE_DIRS})

include_directories("inc")

add_subdirectory(documentation) # doxygen documentation
add_subdirectory(src)			# create library

set(_MOC_HDRS					# moc all headers
	inc/model/code.h
	inc/control/codeManager.h
	inc/view/codeList.h
	inc/view/codeSettings.h
	inc/view/documentList.h
	inc/view/mainWidget.h
	inc/view/documentwidget.h
	inc/view/fastqda.h)

qt5_wrap_cpp(_MOC_SRCS ${_MOC_HDRS})

if(APPLE)
	add_executable(
		${PROGNAME} MACOSX_BUNDLE main.cpp ${_SRCS} ${_MOC_SRCS}
	)
    add_custom_command(TARGET fastQDA POST_BUILD
    	command mkdir ARGS -p
    	${CMAKE_CURRENT_BINARY_DIR}/${PROGNAME}.app/Contents/Resources
    	command cp ARGS
    	../${MACOSX_BUNDLE_ICON_FILE}
    	${CMAKE_CURRENT_BINARY_DIR}/${PROGNAME}.app/Contents/Resources
    	command cp ARGS
    	../*.md
    	${CMAKE_CURRENT_BINARY_DIR}/${PROGNAME}.app/Contents/Resources
    )
elseif(WIN32)
	add_executable(
		${PROGNAME} WIN32 main.cpp ${_SRCS} ${_MOC_SRCS}
	)
else(APPLE)
	add_executable(
		${PROGNAME} main.cpp ${_SRCS} ${_MOC_SRCS}
	)
endif(APPLE)

target_link_libraries(${PROGNAME} ${QT_LIBRARIES} ${POPPLER_LIBRARIES} fastqdaLib)
qt5_use_modules(${PROGNAME} Widgets)