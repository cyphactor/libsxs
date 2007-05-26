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
 * \file sxs.c
 * \brief This is an implementation file for lib_sxs API.
 *
 * The sxs.c file is an implementation file which contains all the
 * definitions for the functions which compose the general API of
 * lib_sxs.
 */

#include "sxs.h"

sxs_error_t sxs_init(void) {
#ifdef WIN32
    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(2,0);
    if (WSAStartup(wVersionRequested, &wsData) != 0) {
        return 1;
    }
#endif

    return SXS_SUCCESS;
}

sxs_error_t sxs_uninit(void) {
#ifdef WIN32
    if (WSACleanup() == SXS_SOCKET_ERROR) {
        return 1;
    }
#endif

    return SXS_SUCCESS;
}

sxs_error_t sxs_socket(int domain, int type, int protocol,
    sxs_socket_t *p_socket) {

    sxs_socket_t sd;

    sd = socket(domain, type, protocol);
    if (sd == SXS_INVALID_SOCKET) {
        return 1;
    }

    (*p_socket) = sd;
    return SXS_SUCCESS;
}

sxs_error_t sxs_bind(sxs_socket_t sd, const struct sockaddr *my_addr,
    sxs_socklen_t addrlen) {

    int r;

    r = bind(sd, my_addr, addrlen);
    if (r == SXS_SOCKET_ERROR) {
        return 1;
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_listen(sxs_socket_t sd, int backlog) {
    int r;

    r = listen(sd, backlog);
    if (r == SXS_SOCKET_ERROR) {
        return 1;
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_accept(sxs_socket_t sd, struct sockaddr *addr,
    sxs_socklen_t *addrlen, sxs_socket_t *p_sd) {

    sxs_socket_t connsd;

    connsd = accept(sd, addr, addrlen);
    if (connsd == SXS_INVALID_SOCKET) {
        return 1;
    }

    (*p_sd) = connsd;

    return SXS_SUCCESS;
}

sxs_error_t sxs_connect(sxs_socket_t sd, const struct sockaddr *serv_addr,
    sxs_socklen_t addrlen) {

    int r;

    r = connect(sd, serv_addr, addrlen);
    if (r == SXS_SOCKET_ERROR) {
        return 1;
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_close(sxs_socket_t sd) {
    int r;

#ifdef WIN32
    r = closesocket(sd);
#else
    r = close(sd);
#endif
    if (r == SXS_SOCKET_ERROR) {
        return 1;
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_shutdown(sxs_socket_t sd, int how) {
    int r;
    sxs_errno_t errsv;

    r = shutdown(sd, how);
    if (r == SXS_SOCKET_ERROR) {
#ifdef WIN32
        errsv = WSAGetLastError();
#else
        errsv = errno;
        if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == ENOTCONN) {
            return SXS_ENOTCONN;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else {
            return 0xffffffff;
        }
#endif
    }

    return SXS_SUCCESS;
}
