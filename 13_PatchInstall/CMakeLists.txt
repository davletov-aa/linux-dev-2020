cmake_minimum_required(VERSION 3.13)
project(guesser C CXX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0")

include(FindGettext)
include(GNUInstallDirs)

add_executable(guesser guesser.cpp)
add_dependencies(guesser locale_gen)
target_compile_definitions(guesser PRIVATE LOCALE_PATH="/usr/share/locale")

install(TARGETS guesser RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
GETTEXT_PROCESS_PO_FILES(ru ALL INSTALL_DESTINATION ${CMAKE_INSTALL_FULL_LOCALEDIR} PO_FILES guesser.po)
add_compile_definitions(CMAKE_INSTALL_FULL_LOCALEDIR=${CMAKE_INSTALL_FULL_LOCALEDIR})

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
