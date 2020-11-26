cmake_minimum_required(VERSION 3.13)
project(guesser CXX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0")

option(BUILD_DOC "Build documentation" ON)

add_executable(guesser guesser.cpp)
add_dependencies(guesser locale_gen)
target_compile_definitions(guesser PRIVATE LOCALE_PATH="/usr/share/locale")

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/title.dox
        DEPENDS guesser
        COMMAND ./guesser --help-doxy > ${CMAKE_CURRENT_SOURCE_DIR}/title.dox
    )

    add_custom_command(
        OUTPUT html
        DEPENDS title.dox
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        COMMAND rm ${CMAKE_CURRENT_SOURCE_DIR}/title.dox
    )

    add_custom_target(docs DEPENDS html)

endif (DOXYGEN_FOUND)

find_program(HELP2MAN_FOUND help2man)
if (NOT HELP2MAN_FOUND)
    message(FATAL_ERROR "Can't find help2man tool")
endif()

add_custom_command(
    OUTPUT guesser.1
    COMMAND help2man -o guesser.1 --name="guesser" ./guesser
    DEPENDS guesser
)

add_custom_command(
    OUTPUT guesser.1.gz
    DEPENDS guesser.1
    COMMAND gzip guesser.1
)
add_custom_target(man DEPENDS guesser.1.gz)


add_custom_command(
	OUTPUT guesser.po
	DEPENDS update_pot
	COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/guesser.po" guesser.po
	COMMAND msgmerge -U guesser.po new_guesser.pot
)
add_custom_target(update_po DEPENDS guesser.po)

add_custom_command(
	OUTPUT new_guesser.pot
	DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/guesser.pot" "${CMAKE_CURRENT_SOURCE_DIR}/guesser.cpp"
	COMMAND xgettext -k_ -c "${CMAKE_CURRENT_SOURCE_DIR}/guesser.cpp" -o update_guesser.pot
	COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/guesser.po" new_guesser.pot
	COMMAND msgmerge -U new_guesser.pot update_guesser.pot
)
add_custom_target(update_pot DEPENDS new_guesser.pot)

add_custom_command(
	OUTPUT "ru/LC_MESSAGES/guesser.mo"
	DEPENDS update_po
	COMMAND mkdir -p "ru/LC_MESSAGES/"
	COMMAND msgfmt guesser.po -o "ru/LC_MESSAGES/guesser.mo"
)
add_custom_target(locale_gen DEPENDS "ru/LC_MESSAGES/guesser.mo")

add_custom_target(allclean COMMAND rm -rf CMakeCache.txt  CMakeFiles  cmake_install.cmake new_guesser.pot new_guesser.pot~ update_guesser.pot Makefile ru guesser)