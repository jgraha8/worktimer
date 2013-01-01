#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([worktimer], [1.0], [jgraha8@gmail.com])
AM_INIT_AUTOMAKE([foreign])

AC_CONFIG_SRCDIR([worktimer.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strstr])
AC_CHECK_FUNCS([cos])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
