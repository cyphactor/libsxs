/*
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
 * @file sxs_types.h
 * @brief This is a specifications file for types to be used with lib_sxs.
 *
 * The sxs_types.h file is a specifications file that defines the
 * necessary types to handle the complexities of being cross-platform
 * relative to differences in data types.
 */

#ifndef SXS_TYPES_H
#define SXS_TYPES_H

/* Here we handle the different includes for the different operating
 * systems. */
#ifdef WIN32
/* get rid of unused Windows ass. This also seems to have
 * some effect on windows sockets 2 compatibility. At the very
 * least its keeping Windows ass out of our projects, so lets
 * keep it in for now. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#else
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @typedef sxs_socket_t
 * @brief A socket.
 *
 * The sxs_socket_t is a cross-platform type which represents a socket.
 * Some might refer to it as a socket descriptor or a socket handle.
 */

/**
 * @typedef sxs_uint8_t
 * @brief An unsigned 8 bit integer.
 *
 * The sxs_uint8_t is a cross-platform type which represents an unsigned
 * 8 bit integer.
 */

/**
 * @typedef sxs_uint16_t
 * @brief An unsigned 16 bit integer.
 *
 * The sxs_uint16_t is a cross-platform type which represents an
 * unsigned 16 bit integer.
 */

/**
 * @typedef sxs_uint32_t
 * @brief An unsigned 32 bit integer.
 *
 * The sxs_uint32_t is a cross-platform type which represents an
 * unsigned 32 bit integer.
 */

/**
 * @typedef sxs_int8_t
 * @brief An signed 8 bit integer.
 *
 * The sxs_int8_t is a cross-platform type which represents an signed
 * 8 bit integer.
 */

/**
 * @typedef sxs_int16_t
 * @brief An signed 16 bit integer.
 *
 * The sxs_int16_t is a cross-platform type which represents an
 * signed 16 bit integer.
 */

/**
 * @typedef sxs_int32_t
 * @brief An signed 32 bit integer.
 *
 * The sxs_int32_t is a cross-platform type which represents an
 * signed 32 bit integer.
 */

/**
 * @typedef sxs_socklen_t
 * @brief A length of a socket address.
 *
 * The sxs_socklen_t is a cross-platform type which represents a length
 * of an socket address.
 */

/* Here we hanlde defining a common set of types that can be used
 * depending on the different operating systems */
#ifndef WIN32
    #define SXS_SOCKET_ERROR -1
    #define SXS_INVALID_SOCKET -1
    #define SXS_SHUT_RD SHUT_RD
    #define SXS_SHUT_WR SHUT_WR
    #define SXS_SHUT_RDWR SHUT_RDWR
    typedef int sxs_socket_t;
    typedef void *sxs_buf_t;
    typedef size_t sxs_size_t;
    typedef ssize_t sxs_ssize_t;
    typedef uint8_t sxs_uint8_t;
    typedef uint16_t sxs_uint16_t;
    typedef uint32_t sxs_uint32_t;
    typedef int8_t sxs_int8_t;
    typedef int16_t sxs_int16_t;
    typedef int32_t sxs_int32_t;
    typedef socklen_t sxs_socklen_t;
    typedef in_addr_t sxs_in_addr_t;
#else
    #define SXS_SOCKET_ERROR SOCKET_ERROR
    #define SXS_INVALID_SOCKET INVALID_SOCKET
    #define SXS_SHUT_RD SD_RECEIVE
    #define SXS_SHUT_WR SD_SEND
    #define SXS_SHUT_RDWR SD_BOTH
    typedef SOCKET sxs_socket_t;
    typedef char FAR *sxs_buf_t;
    typedef int sxs_size_t;
    typedef int sxs_ssize_t;
    typedef unsigned __int8 sxs_uint8_t;
    typedef unsigned __int16 sxs_uint16_t;
    typedef unsigned __int32 sxs_uint32_t;
    typedef __int8 sxs_int8_t;
    typedef __int16 sxs_int16_t;
    typedef __int32 sxs_int32_t;
    typedef int sxs_socklen_t;
    typedef sxs_uint32_t sxs_in_addr_t;
#endif

/**
 * @typedef sxs_errno_t
 * @brief An error code.
 * 
 * The sxs_errno_t is a cross-platform type which represents an error
 * code.
 */

/**
 * @typedef sxs_error_t
 * @brief An error code.
 *
 * The sxs_error_t is a cross-platform type which represents an error
 * code.
 */

typedef sxs_int32_t sxs_error_t;
typedef int sxs_errno_t;
#define SXS_INADDR_NONE INADDR_NONE

#endif /* SXS_TYPES_H */
