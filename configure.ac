# Must contain a call to AC_INIT before the checks, and call to
# AC_OUTPUT at the end.
#
# The layout of standard autoconf.ac
#
# AC_INIT(package, version, bug-report-address)
# information on the package
# checks for programs
# checks for libraries
# checks for header files
# checks for types
# checks for structures
# checks for compiler characteristics
# checks for library functions
# checks for system services
# AC_CONFIG_FILES([file...])
# AC_OUTPUT
#

AC_PREREQ(2.59)
AC_INIT(Spartan Cross-Platform Sockets Library, 0.3.0, cyphactor@gmail.com, lib_sxs)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/sxs.c])
AM_CONFIG_HEADER([src/sxs_config.h])


# checks for programs
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL
AC_PROG_CC

# checks for libraries

case $host in
    # Handle the mingw32 (Windows 32-bit Cross-Compiler options,
    # necessary to be able to build the Windows DLL and link to the
    # proper mingw32 libraries. The '-Wl,--output-def,.libspmf.def'
    # option tells it linker (mingw32 version) to output the
    # .libspmf.def, a file that is used on a Windows machine to build
    # the import .LIB library for the DLL. The '-s' linker option
    # stripts all symbol information from the output file. This reduces
    # the size of the DLL since the mingw32 linker includes all symbols
    # by default.
    *mingw32*) SXS_SYSTEM='-Wl,--output-def,.libs/libsxs.def,-s -lws2_32' ;;

    # Handle the Mac OS X specific build options such as the
    # '-Wl,-prebind,-seg1addr,0xC0000000' followed by the normal
    # libraries to link to. The '-Wl,-prebind' passing the -prebind
    # option to the linker (ld) to tell it to map the functions to
    # addresses at build time so that applications that use the library
    # don't have to. This increases the loading speed of applications
    # for Mac OS X 10.3 and below. The '-seg1addr,0xC0000000' option
    # specifies to the linker (ld) that the starting address at which it
    # should start binding is 0xC0000000. This is done to avoid overlap
    # of address space mapping.
    #*-apple-darwin*) SXS_SYSTEM='-Wl,-prebind,-seg1addr,0xC0000000' ;;
	*darwin8*) CFLAGS="$CFALGS -isysroot /Developer/SDKs/MacOSX10.4u.sdk -arch i386 -arch ppc"
	LDFLAGS="$LDFLAGS -Wl,-syslibroot,/Developer/SDKs/MacOSX10.4u.sdk -arch i386 -arch ppc" ;;
	*darwin9*) CFLAGS="$CFLAGS -arch i386 -arch ppc" ;;

    #
    # FIX-ME:
    #
    # Currently in order for applications that link to libpmf have to
    # have it in the same directory as the exectubale or in the system
    # directories. This goes against Mac's standard for application
    # packagesing which requires that all the libraries are put inside
    # the application package. However, when in the application package
    # the applications cannot find libpmf because the library is built
    # for a system path such as /usr/lib/ rather than the appropriate
    # path relative to the executable
    # (@executable_path/../Frameworks/libbz2.1.0.2.dylib). The following
    # is an example of a possible fix.
    #*-apple-darwin*) PMF_SYSTEM='-install_name @executable_path/../Frameworks/libbz2.1.02.2.dylib-Wl,-prebind,-seg1addr,0xC0000000 -lssl -lpthread' ;;

    # Handle linking to the proper libraries for all other machines.
    *)          SXS_SYSTEM='' ;;
esac

#case $host in
    # Handle setting the propper CFLAGS for the mingw32 build,
    # specifically setting the include path to the project provided
    # include path and defining the PTW32_STATIC_LIB macro so that we
    # can properly build and link to the provided PTW32 static library.
#    *mingw32*)  PMF_CFLAGS='-I../include -DPTW32_STATIC_LIB' ;;

    # Handle setting the propper CFLAGS for all other machines.
#    *)          PMF_CFLAGS='' ;;
#esac

# This is set to replace the default CFLAGS value provided by the
# AC_PROG_CC macro which is '-g -02'. Hence, there will be no more '-g'
# (the debug symbols option), meaning that the default build version of
# the library is the release version.
#CFLAGS='-O2'

AC_SUBST([CFLAGS])
AC_SUBST([SXS_SYSTEM])
#AC_SUBST([PMF_CFLAGS])

# checks for header files
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h netinet/in.h string.h sys/socket.h stdint.h])

# checks for types

# checks for structures

# checks for compiler characteristics
AC_C_BIGENDIAN

# checks for library functions
AC_CHECK_FUNCS([memset socket])

# checks for system services

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
