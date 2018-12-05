AC_INIT([orthohedra], [1.0])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_SRCDIR([src/orthohedra.cpp])
AC_CONFIG_MACRO_DIRS([m4])

AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET

AC_CHECK_HEADERS([stddef.h stdlib.h])
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

AM_PROG_AR
LT_INIT
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
