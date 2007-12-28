AM_CFLAGS = -Wall -Werror
AUTOMAKE_OPTIONS = no-dependencies
sxsincdir = $(includedir)/sxs
lib_LTLIBRARIES = libsxs.la
libsxs_la_LDFLAGS = -no-undefined -version-info 0:0:0 @SXS_SYSTEM@
libsxs_la_SOURCES = sxs.c sxs_error.c
sxsinc_HEADERS = sxs.h sxs_error.h sxs_export.h sxs_types.h sxs_config.h
