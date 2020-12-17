cmake_minimum_required(VERSION 3.13)
project(guesser C CXX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0")

include(FindGettext)
include(GNUInstallDirs)

add_executable(guesser guesser.cpp)

install(TARGETS guesser RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
GETTEXT_PROCESS_PO_FILES(ru ALL INSTALL_DESTINATION ${CMAKE_INSTALL_FULL_LOCALEDIR} PO_FILES guesser.po)

add_custom_target(allclean COMMAND rm -rf CMakeCache.txt  CMakeFiles  cmake_install.cmake Makefile ru guesser guesser.gmo)
