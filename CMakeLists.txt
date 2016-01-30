cmake_minimum_required(VERSION 2.8.8)
project(m)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PkgConfig)

find_package(Qt5Widgets REQUIRED)
pkg_check_modules(LIBSSH2 libssh2)
include_directories(AFTER LIBSSH2_INCLUDE_DIR)
include_directories(AFTER ${CMAKE_SOURCE_DIR}/3rd/qtermwidget/lib)

add_executable(m main.cpp mshell.cpp mterminal.cpp mprocesstextbinder.cpp
    mabstractexecutor.cpp mptyexecutor.cpp mshellcontext.cpp
    3rd/qtermwidget/lib/kprocess.cpp 3rd/qtermwidget/lib/kpty.cpp
		3rd/qtermwidget/lib/kptydevice.cpp 3rd/qtermwidget/lib/kptyprocess.cpp
		3rd/qtermwidget/lib/Pty.cpp)
qt5_use_modules(m Widgets)
add_definitions(-DHAVE_POSIX_OPENPT -DHAVE_SYS_TIME_H)
TARGET_LINK_LIBRARIES(m ${LIBSSH2_LIBS})
