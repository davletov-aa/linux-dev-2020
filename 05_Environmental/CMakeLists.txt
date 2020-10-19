cmake_minimum_required(VERSION 3.16)

INCLUDE(CheckIncludeFiles)

project(regexer)

find_library(PCRE_LIBRARY pcre2-8)
find_library(NCURSES_LIBRARY ncursesw)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

option(WITHOUT_UTF "Disable UTF" OFF)
if (WITHOUT_UTF)
    add_compile_definitions(WITHOUT_UTF=1)
endif ()

add_executable(regexer window.c)

target_link_libraries(regexer ${NCURSES_LIBRARY} ${PCRE_LIBRARY})