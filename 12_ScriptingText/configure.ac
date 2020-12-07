#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([hashtext], [0.0], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_HEADERS([config.h])
AM_PATH_GLIB_2_0()


# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

define(DATE, `date`)dnl
define(SEDCOM, [\/\* COMMENT:: AC_PACKAGE_NAME, AC_PACKAGE_VERSION: DATE \*\/])dnl
define(SEDSTR, [1 s/^\/\* COMMENT::.*\*\//SEDCOM/; t; 1 s/^/SEDCOM\n/;])dnl
define(SEDOPT, ["SEDSTR"])dnl

sed -i -s SEDOPT *.{c,h}

