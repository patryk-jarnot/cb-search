AC_PREREQ([2.69])
AC_INIT([nscsearch], [1.0.0], [patryk.jarnot@gmail.com])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([include/config-nscsearch.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.11 subdir-objects])
AC_CONFIG_FILES([Makefile])


# Find python executable
AM_PATH_PYTHON

# Get CPPFLAGS, etc., for Python module compilation
# http://www.gnu.org/software/autoconf-archive/ax_python_devel.html
AX_PYTHON_DEVEL

# Find swig executable
# http://www.gnu.org/software/autoconf-archive/ax_pkg_swig.html
AX_PKG_SWIG([], [], [ AC_MSG_ERROR([SWIG is required to build.]) ])

# Get SWIGFLAGS, CPPFLAGS, etc., for Python generation by swig
# http://www.gnu.org/software/autoconf-archive/ax_swig_python.html
AX_SWIG_PYTHON

# Use libtool to link libraries and modules
LT_INIT



# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
#AC_PROG_RANLIB

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT

