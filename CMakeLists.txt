cmake_minimum_required(VERSION 2.8.8)
project(m)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PkgConfig)

find_package(Qt5Widgets REQUIRED)
pkg_check_modules(LIBSSH2 libssh2)
include_directories(AFTER LIBSSH2_INCLUDE_DIR)


add_executable(m main.cpp mshell.cpp mdumbterminal.cpp mprocesstextbinder.cpp)
qt5_use_modules(m Widgets)
TARGET_LINK_LIBRARIES(m ${LIBSSH2_LIBS})
