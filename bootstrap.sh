#!/bin/sh
#
# NOTE: This script SHOULD be run if you just checked out a copy of the
#       code from subversion, to generate the configure script. 
#
# Author: Andrew De Ponte <cyphactor@gmail.com>
# Description:  This is a script which I wrote to assist in generating
#               all of the build environment for this project. This
#               includes generating the configure script so that the
#               standard ./configure && make && make install build
#               sequence can be used.

#aclocal
#autoheader
#autoconf
#automake --add-missing

# The above has now been replaced by autoreconf

autoreconf -i
