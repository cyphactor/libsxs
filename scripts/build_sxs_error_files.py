#!/usr/bin/env python

import string

unixwin_err_start = 1
unixwin_err_end = 333
win_err_start = 334
win_err_end = 667
unix_err_start = 668
unix_err_end = 1000
unix_herr_start = 1001
unix_herr_end = 1332
sxs_err_start = 6001
sxs_err_end = 6332
unixmac_err_start = 6333
unixmac_err_end = 6665
mac_err_start = 6666
mac_err_end = 6998

copyright_hdr = """/*
 * Copyright 2007 Andrew De Ponte
 *
 * This file is part of lib_sxs.
 *
 * lib_sxs is the intellectual property of Andrew De Ponte; any
 * distribution and/or modifications and/or reproductions of any portion
 * of lib_sxs MUST be approved by Andrew De Ponte.
 *
 * lib_sxs is dirstributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 */

/**
 * @file sxs_error.h
 * @brief This is a specifications file for error hanlding in lib_sxs.
 *
 * The sxs_error.h file is a specifications file that defines the types
 * which represent errors and all their possible values, as well as
 * providing prototypes for error handling functions.
 */

 /* NOTE: This file is automatically generated and should never be
  * altered by hand. To make changes to this file please alter the
  * scripts/build_sxs_error_files.py script or any of it's associated
  * input files. */

#ifndef SXS_ERROR_H
#define SXS_ERROR_H

#include "sxs_types.h"

#define SXS_SUCCESS 0 /**< Operation completed successfully */
#define SXS_UNKNOWN_ERROR 0xffffffff /**< An undefined error occured */

/* The following are errors which are shared between both Unix varients
 * such as linux and mac as well as Windows. */
"""

copyright_src = """/*
 * Copyright 2007 Andrew De Ponte
 *
 * This file is part of lib_sxs.
 *
 * lib_sxs is the intellectual property of Andrew De Ponte; any
 * distribution and/or modifications and/or reproductions of any portion
 * of lib_sxs MUST be approved by Andrew De Ponte.
 *
 * lib_sxs is dirstributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 */

/**
 * @file sxs_error.c
 * @brief This is an implementations file for lib_sxs error handling.
 *
 * The sxs_error.c file is an implementations file for lib_sxs error
 * handleing. It provides all the definitions for any of the error
 * handling functions.
 */
 
 /* NOTE: This file is automatically generated and should never be
  * altered by hand. To make changes to this file please alter the
  * scripts/build_sxs_error_files.py script or any of it's associated
  * input files. */

#include "sxs_error.h"

"""

out_hdr_file = open('sxs_error.h', 'w')
out_src_file = open('sxs_error.c', 'w')

out_hdr_file.write(copyright_hdr)
out_src_file.write(copyright_src)

# Open and read in the errors that are common to both Windows and
# Unix/Mac operatying systems with respect to the sockets libraries.
both_errs_file = open('both_errs.in', 'r')
both_errs = both_errs_file.readlines()
both_errs_file.close()

out_str = "#define SXS_UNIXWIN_ERR_START " + str(unixwin_err_start) + "\n"
out_hdr_file.write(out_str)
out_str = "#define SXS_UNIXWIN_ERR_END " + str(unixwin_err_end) + "\n"
out_hdr_file.write(out_str)

# Loop through all the errors that are common to both Windows and
# Unix/Mac and create the defines for the common errors.
count = unixwin_err_start
for line in both_errs:
    line_split = string.split(line)
    out_str = '#define SXS_' + line_split[0] + ' ' + str(count) + ' ' + \
        string.join(line_split[1:])
    out_hdr_file.write(out_str + '\n')
    count = count + 1;

unixwin_err_last = (count - 1)

out_hdr_file.write('#define SXS_UNIXBOTH_ERRMAP_SIZE ' + \
    str(unixwin_err_last) + '\n')

# Write the extern statement for the winboth_array to the header file so
# that anyone that includes the header file will have access to the
# array.
out_hdr_file.write('#ifdef WIN32\nextern sxs_int32_t sxs_winboth_errmap[' + \
    'SXS_UNIXBOTH_ERRMAP_SIZE];\n#else\n')

# Write the winboth_array declaration and assignment to the source file.
out_src_file.write('#ifdef WIN32\nsxs_int32_t sxs_winboth_errmap[' + \
    'SXS_UNIXBOTH_ERRMAP_SIZE] = { ')

count = 0
for line in both_errs:
    line_split = string.split(line)
    if (count == (unixwin_err_last - 1)):
        out_src_file.write('WSA' + str(line_split[0]) + ' };\n')
    else:
        out_src_file.write('WSA' + str(line_split[0]) + ', ')
    count = count + 1
out_src_file.write('#else\n')

# Write the extern statement for the unixboth_array to the header file
# so that anyone that includes the header file will have access to the
# array.
out_hdr_file.write('extern sxs_int32_t sxs_unixboth_errmap[' + \
    'SXS_UNIXBOTH_ERRMAP_SIZE];\n#endif\n')

# Write the unixboth_array declaration and assignment to the source
# file.
out_src_file.write('sxs_int32_t sxs_unixboth_errmap[' + \
    'SXS_UNIXBOTH_ERRMAP_SIZE] = { ')

count = 0
for line in both_errs:
    line_split = string.split(line)
    if (count == (unixwin_err_last - 1)):
        out_src_file.write(str(line_split[0]) + ' };\n')
    else:
        out_src_file.write(str(line_split[0]) + ', ')
    count = count + 1
out_src_file.write('#endif\n\n')

out_hdr_file.write('\n\n')

win_errs_file = open('win_errs.in', 'r')
win_errs = win_errs_file.readlines()
win_errs_file.close()

start_line_out = "#define SXS_WIN_ERR_START " + str(win_err_start) + "\n"
out_hdr_file.write(start_line_out)
start_line_out = "#define SXS_WIN_ERR_END " + str(win_err_end) + "\n"
out_hdr_file.write(start_line_out)

# Loop through and define all the Windows only errors in the header file
# so that they may be referenced from client applications for error
# handling.
count = win_err_start
for line in win_errs:
    line_split = string.split(line)
    out_line = '#define SXS_' + line_split[0] + ' ' + str(count) + ' ' + \
        string.join(line_split[1:])
    out_hdr_file.write(str(out_line) + '\n')
    count = count + 1;

win_err_last = (count - win_err_start)

out_hdr_file.write('#define SXS_WIN_ERRMAP_SIZE ' + \
    str(win_err_last) + '\n')

# Write the extern statement for the win_array to the header file so
# that anyone that includes the header file will have access to the
# array.
out_hdr_file.write('#ifdef WIN32\nextern sxs_int32_t sxs_win_errmap[' + \
    'SXS_WIN_ERRMAP_SIZE];\n#endif')

# Write the win_array declaration and assignment to the source file.
out_src_file.write('#ifdef WIN32\nsxs_int32_t sxs_win_errmap[' + \
    'SXS_WIN_ERRMAP_SIZE] = { ')

count = 0
for line in win_errs:
    line_split = string.split(line)
    if (count == (win_err_last - 1)):
        out_src_file.write(str(line_split[0]) + ' };\n')
    else:
        out_src_file.write(str(line_split[0]) + ', ')
    count = count + 1
out_src_file.write('#elif __APPLE__\n\n#else\n')

out_hdr_file.write('\n\n')

unix_errs_file = open('unix_errs.in', 'r')
unix_errs = unix_errs_file.readlines()
unix_errs_file.close()

start_line_out = "#define SXS_UNIX_ERR_START " + str(unix_err_start) + "\n"
out_hdr_file.write(start_line_out)
start_line_out = "#define SXS_UNIX_ERR_END " + str(unix_err_end) + "\n"
out_hdr_file.write(start_line_out)

# Loop through and define all the Unix only errors in the header file so
# that they may be referenced from client applications for error
# handling.
count = unix_err_start
for line in unix_errs:
    line_split = string.split(line)
    out_line = '#define SXS_' + line_split[0] + ' ' + str(count) + ' ' + \
        string.join(line_split[1:])
    out_hdr_file.write(str(out_line) + '\n')
    count = count + 1;

unix_err_last = (count - unix_err_start)

out_hdr_file.write('#define SXS_UNIX_ERRMAP_SIZE ' + \
    str(unix_err_last) + '\n')

# Write the extern statement for the unix_array to the header file so
# that anyone that includes the header file will have access to the
# array.
out_hdr_file.write('#ifndef WIN32\n#ifndef __APPLE__\nextern sxs_int32_t sxs_unix_errmap[' + \
    'SXS_UNIX_ERRMAP_SIZE];\n#endif\n#endif\n\n')

# Write the unix_array declaration and assignment to the source file.
out_src_file.write('sxs_int32_t sxs_unix_errmap[' + \
    'SXS_UNIX_ERRMAP_SIZE] = { ')

count = 0
for line in unix_errs:
    line_split = string.split(line)
    if (count == (unix_err_last - 1)):
        out_src_file.write(str(line_split[0]) + ' };\n')
    else:
        out_src_file.write(str(line_split[0]) + ', ')
    count = count + 1
out_src_file.write('#endif\n\n')

# Open and read in the errors that are found in netdb.h specifically for
# the h_errno variable in Unix systems.
unix_herrs_file = open('unix_herrs.in', 'r')
unix_herrs = unix_herrs_file.readlines()
unix_herrs_file.close()

out_str = "#define SXS_UNIX_HERR_START " + str(unix_herr_start) + "\n"
out_hdr_file.write(out_str)
out_str = "#define SXS_UNIX_HERR_END " + str(unix_herr_end) + "\n"
out_hdr_file.write(out_str)

# Loop through all the errors that are found in netdb.h specifically for
# the h_errno variable in Unix systems.
count = unix_herr_start
for line in unix_herrs:
    line_split = string.split(line)
    out_str = '#define SXS_' + line_split[0] + ' ' + str(count) + ' ' + \
        string.join(line_split[1:])
    out_hdr_file.write(out_str + '\n')
    count = count + 1;

unix_herr_last = (count - unix_herr_start)

out_hdr_file.write('#define SXS_UNIX_HERRMAP_SIZE ' + \
    str(unix_herr_last) + '\n')

out_hdr_file.write('#ifndef WIN32\nextern sxs_int32_t sxs_unix_herrmap[' + \
    'SXS_UNIX_HERRMAP_SIZE];\n#endif\n\n')

out_src_file.write('#ifndef WIN32\nsxs_int32_t sxs_unix_herrmap[' + \
    'SXS_UNIX_HERRMAP_SIZE] = { ')

count = 0
for line in unix_herrs:
    line_split = string.split(line)
    if (count == (unix_herr_last - 1)):
        out_src_file.write(str(line_split[0]) + ' };\n')
    else:
        out_src_file.write(str(line_split[0]) + ', ')
    count = count + 1
out_src_file.write('#endif\n\n')

sxs_errs_file = open('sxs_errs.in', 'r')
sxs_errs = sxs_errs_file.readlines()
sxs_errs_file.close()

out_str = "#define SXS_ERR_START " + str(sxs_err_start) + "\n"
out_hdr_file.write(out_str)
out_str = "#define SXS_ERR_END " + str(sxs_err_end) + "\n"
out_hdr_file.write(out_str)

count = sxs_err_start
for line in sxs_errs:
    line_split = string.split(line)
    out_str = '#define SXS_' + line_split[0] + ' ' + str(count) + ' ' + \
        string.join(line_split[1:])
    out_hdr_file.write(out_str + '\n')
    count = count + 1;

out_hdr_file.write("\n\n")

unixmac_errs_file = open('unixmac_errs.in', 'r')
unixmac_errs = unixmac_errs_file.readlines()
unixmac_errs_file.close()

out_str = "#define SXS_UNIXMAC_ERR_START " + str(unixmac_err_start) + "\n"
out_hdr_file.write(out_str)
out_str = "#define SXS_UNIXMAC_ERR_END " + str(unixmac_err_end) + "\n"
out_hdr_file.write(out_str)

count = unixmac_err_start
for line in unixmac_errs:
    line_split = string.split(line)
    out_str = '#define SXS_' + line_split[0] + ' ' + str(count) + ' ' + \
        string.join(line_split[1:])
    out_hdr_file.write(out_str + '\n')
    count = count + 1;

unixmac_err_last = (count - unixmac_err_start);

out_hdr_file.write('#define SXS_UNIXMAC_ERRMAP_SIZE ' + \
    str(unixmac_err_last) + '\n')

out_hdr_file.write('#ifndef WIN32\nextern sxs_int32_t sxs_unixmac_errmap[SXS_UNIXMAC_ERRMAP_SIZE];\n#endif\n\n')

# Write the unixmac_array declaration and assignment to the source file.
out_src_file.write('#ifndef WIN32\nsxs_int32_t sxs_unixmac_errmap[' + \
    'SXS_UNIXMAC_ERRMAP_SIZE] = { ')

count = 0
for line in unixmac_errs:
    line_split = string.split(line)
    if (count == (unixmac_err_last - 1)):
        out_src_file.write(str(line_split[0]) + ' };\n')
    else:
        out_src_file.write(str(line_split[0]) + ', ')
    count = count + 1
out_src_file.write('#endif\n\n')

out_hdr_file.write("\n\n")

mac_errs_file = open('mac_errs.in', 'r')
mac_errs = mac_errs_file.readlines()
mac_errs_file.close()

out_str = "#define SXS_MAC_ERR_START " + str(mac_err_start) + "\n"
out_hdr_file.write(out_str)
out_str = "#define SXS_MAC_ERR_END " + str(mac_err_end) + "\n"
out_hdr_file.write(out_str)

count = mac_err_start
for line in mac_errs:
    line_split = string.split(line)
    out_str = '#define SXS_' + line_split[0] + ' ' + str(count) + ' ' + \
        string.join(line_split[1:])
    out_hdr_file.write(out_str + '\n')
    count = count + 1;

mac_err_last = (count - mac_err_start);

out_hdr_file.write('#define SXS_MAC_ERRMAP_SIZE ' + \
    str(mac_err_last) + '\n')

out_hdr_file.write('#ifdef __APPLE__\nextern sxs_int32_t sxs_mac_errmap[SXS_MAC_ERRMAP_SIZE];\n#endif\n\n')

# Write the mac_array declaration and assignment to the source file.
out_src_file.write('#ifdef __APPLE__\nsxs_int32_t sxs_mac_errmap[' + \
    'SXS_MAC_ERRMAP_SIZE] = { ')

count = 0
for line in mac_errs:
    line_split = string.split(line)
    if (count == (mac_err_last - 1)):
        out_src_file.write(str(line_split[0]) + ' };\n')
    else:
        out_src_file.write(str(line_split[0]) + ', ')
    count = count + 1
out_src_file.write('#endif\n\n')

out_hdr_file.write("#endif\n")

out_hdr_file.close()
out_src_file.close()
