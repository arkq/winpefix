# CMakeLists.txt
# Copyright (c) 2015-2018 Arkadiusz Bokowy
#
# This file is a part of WinPEFix.
#
# This project is licensed under the terms of the MIT license.

cmake_minimum_required(VERSION 3.1)
project(winpefix)

set(SRCS
	src/PELinkFix.cpp
	src/main.cpp
)

set(SRCS_QT
	src/MainWindowQt.cpp
	src/MainWindow.ui
)

set(SRCS_WINAPI
	src/MainWindowWin.cpp
	src/MainWindow.rc
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_BINARY_DIR}/bin
)

if(WIN32)

	ADD_DEFINITIONS(-DUNICODE)
	ADD_DEFINITIONS(-D_UNICODE)

	add_executable(WinPEFix WIN32 ${SRCS} ${SRCS_WINAPI})

	target_compile_features(WinPEFix PRIVATE cxx_std_11)
	target_include_directories(WinPEFix PRIVATE src)
	target_link_libraries(WinPEFix comdlg32 shlwapi)

else()

	set(CMAKE_AUTOMOC ON)
	set(CMAKE_AUTOUIC ON)

	find_package(Qt5Widgets CONFIG REQUIRED)

	add_executable(winpefix ${SRCS} ${SRCS_QT})

	target_compile_features(winpefix PRIVATE cxx_std_11)
	target_include_directories(winpefix PRIVATE src)
	target_link_libraries(winpefix Qt5::Widgets)

endif()
