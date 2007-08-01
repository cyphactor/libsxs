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
 * @file sxs.c
 * @brief This is an implementation file for lib_sxs API.
 *
 * The sxs.c file is an implementation file which contains all the
 * definitions for the functions which compose the general API of
 * lib_sxs.
 */

#include "sxs.h"
#include "sxs_config.h"

sxs_error_t sxs_init(void) {
#ifdef WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    sxs_errno_t errsv;

    wVersionRequested = MAKEWORD(2,0);
    errsv = WSAStartup(wVersionRequested, &wsaData);
    if (errsv != 0) {
        if (errsv == WSASYSNOTREADY) {
            return SXS_WSASYSNOTREADY;
        } else if (errsv == WSAVERNOTSUPPORTED) {
            return SXS_WSAVERNOTSUPPORTED;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAEPROCLIM) {
            return SXS_WSAEPROCLIM;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
    }
#endif

    return SXS_SUCCESS;
}

sxs_error_t sxs_uninit(void) {
#ifdef WIN32
    sxs_errno_t errsv;

    if (WSACleanup() == SXS_SOCKET_ERROR) {
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
    }
#endif

    return SXS_SUCCESS;
}

sxs_error_t sxs_socket(int domain, int type, int protocol,
    sxs_socket_t *p_sd) {

    sxs_socket_t sd;
    sxs_errno_t errsv;

    sd = socket(domain, type, protocol);
    if (sd == SXS_INVALID_SOCKET) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEAFNOSUPPORT) {
            return SXS_EAFNOSUPPORT;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAEMFILE) {
            return SXS_EMFILE;
        } else if (errsv == WSAENOBUFS) {
            return SXS_ENOBUFS;
        } else if (errsv == WSAEPROTONOSUPPORT) {
            return SXS_EPROTONOSUPPORT;
        } else if (errsv == WSAEPROTOTYPE) {
            return SXS_EPROTOTYPE;
        } else if (errsv == WSAESOCKTNOSUPPORT) {
            return SXS_ESOCKTNOSUPPORT;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EACCES) {
            return SXS_EACCES;
        } else if (errsv == EPROTONOSUPPORT) {
            return SXS_EPROTONOSUPPORT;
        } else if (errsv == EMFILE) {
            return SXS_EMFILE;
        } else if (errsv == ENFILE) {
            return SXS_ENFILE;
        } else if (errsv == ENOBUFS) {
            return SXS_ENOBUFS;
    #ifndef __APPLE__
        } else if (errsv == EAFNOSUPPORT) {
            return SXS_EAFNOSUPPORT;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    (*p_sd) = sd;
    return SXS_SUCCESS;
}

sxs_error_t sxs_bind(sxs_socket_t sd, const struct sockaddr *my_addr,
    sxs_socklen_t addrlen) {

    int r;
    sxs_errno_t errsv;

    r = bind(sd, my_addr, addrlen);
    if (r == SXS_SOCKET_ERROR) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEACCES) {
            return SXS_EACCES;
        } else if (errsv == WSAEADDRINUSE) {
            return SXS_EADDRINUSE;
        } else if (errsv == WSAEADDRNOTAVAIL) {
            return SXS_EADDRNOTAVAIL;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAEINVAL) {
            return SXS_EINVAL;
        } else if (errsv == WSAENOBUFS) {
            return SXS_ENOBUFS;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EACCES) {
            return SXS_EACCES;
        } else if (errsv == EADDRINUSE) {
            return SXS_EADDRINUSE;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == EADDRNOTAVAIL) {
            return SXS_EADDRNOTAVAIL;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == ELOOP) {
            return SXS_ELOOP;
        } else if (errsv == ENAMETOOLONG) {
            return SXS_ENAMETOOLONG;
        } else if (errsv == ENOENT) {
            return SXS_ENOENT;
        } else if (errsv == ENOTDIR) {
            return SXS_ENOTDIR;
        } else if (errsv == EROFS) {
            return SXS_EROFS;
    #ifdef __APPLE__
        } else if (errsv == EIO) {
            return SXS_EIO;
        } else if (errsv == EISDIR) {
            return SXS_EISDIR;
    #else
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_listen(sxs_socket_t sd, int backlog) {
    int r;
    sxs_errno_t errsv;

    r = listen(sd, backlog);
    if (r == SXS_SOCKET_ERROR) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEADDRINUSE) {
            return SXS_EADDRINUSE;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAEINVAL) {
            return SXS_EINVAL;
        } else if (errsv == WSAEISCONN) {
            return SXS_EISCONN;
        } else if (errsv == WSAEMFILE) {
            return SXS_EMFILE;
        } else if (errsv == WSAENOBUFS) {
            return SXS_ENOBUFS;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == WSAEOPNOTSUPP) {
            return SXS_EOPNOTSUPP;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == EOPNOTSUPP) {
            return SXS_EOPNOTSUPP;
    #ifndef __APPLE__
        } else if (errsv == EADDRINUSE) {
            return SXS_EADDRINUSE;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_accept(sxs_socket_t sd, struct sockaddr *addr,
    sxs_socklen_t *addrlen, sxs_socket_t *p_sd) {

    sxs_socket_t connsd;
    sxs_errno_t errsv;

    connsd = accept(sd, addr, addrlen);
    if (connsd == SXS_INVALID_SOCKET) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAECONNRESET) {
            return SXS_ECONNRESET;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else if (errsv == WSAEINTR) {
            return SXS_EINTR;
        } else if (errsv == WSAEINVAL) {
            return SXS_EINVAL;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAEMFILE) {
            return SXS_EMFILE;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAENOBUFS) {
            return SXS_ENOBUFS;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == WSAEOPNOTSUPP) {
            return SXS_EOPNOTSUPP;
        } else if (errsv == WSAEWOULDBLOCK) {
            return SXS_EWOULDBLOCK;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EWOULDBLOCK) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == EMFILE) {
            return SXS_EMFILE;
        } else if (errsv == ENFILE) {
            return SXS_ENFILE;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == EOPNOTSUPP) {
            return SXS_EOPNOTSUPP;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
    #ifndef __APPLE__
        } else if (errsv == EAGAIN) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == ECONNABORTED) {
            return SXS_ECONNABORTED;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
        } else if (errsv == ENOBUFS) {
            return SXS_ENOBUFS;
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
        } else if (errsv == EPROTO) {
            return SXS_EPROTO;
        } else if (errsv == EPERM) {
            return SXS_EPERM;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    (*p_sd) = connsd;

    return SXS_SUCCESS;
}

sxs_error_t sxs_connect(sxs_socket_t sd, const struct sockaddr *serv_addr,
    sxs_socklen_t addrlen) {

    int r;
    sxs_errno_t errsv;

    r = connect(sd, serv_addr, addrlen);
    if (r == SXS_SOCKET_ERROR) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEADDRINUSE) {
            return SXS_EADDRINUSE;
        } else if (errsv == WSAEINTR) {
            return SXS_EINTR;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAEALREADY) {
            return SXS_EALREADY;
        } else if (errsv == WSAEADDRNOTAVAIL) {
            return SXS_EADDRNOTAVAIL;
        } else if (errsv == WSAEAFNOSUPPORT) {
            return SXS_EAFNOSUPPORT;
        } else if (errsv == WSAECONNREFUSED) {
            return SXS_ECONNREFUSED;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else if (errsv == WSAEINVAL) {
            return SXS_EINVAL;
        } else if (errsv == WSAEISCONN) {
            return SXS_EISCONN;
        } else if (errsv == WSAENETUNREACH) {
            return SXS_ENETUNREACH;
        } else if (errsv == WSAEHOSTUNREACH) {
            return SXS_EHOSTUNREACH;
        } else if (errsv == WSAENOBUFS) {
            return SXS_ENOBUFS;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == WSAETIMEDOUT) {
            return SXS_ETIMEDOUT;
        } else if (errsv == WSAEWOULDBLOCK) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == WSAEACCES) {
            return SXS_EACCES;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EACCES) {
            return SXS_EACCES;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == EAFNOSUPPORT) {
            return SXS_EAFNOSUPPORT;
        } else if (errsv == EISCONN) {
            return SXS_EISCONN;
        } else if (errsv == ETIMEDOUT) {
            return SXS_ETIMEDOUT;
        } else if (errsv == ECONNREFUSED) {
            return SXS_ECONNREFUSED;
        } else if (errsv == ENETUNREACH) {
            return SXS_ENETUNREACH;
        } else if (errsv == EADDRINUSE) {
            return SXS_EADDRINUSE;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == EINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == EALREADY) {
            return EALREADY;
    #ifdef __APPLE__
        } else if (errsv == EADDRNOTAVAIL) {
            return SXS_EADDRNOTAVAIL;
        } else if (errsv == ENOTDIR) {
            return SXS_ENOTDIR;
        } else if (errsv == ENAMETOOLONG) {
            return SXS_ENAMETOOLONG;
        } else if (errsv == ENOENT) {
            return SXS_ENOENT;
        } else if (errsv == ELOOP) {
            return SXS_ELOOP;
    #else
        } else if (errsv == EPERM) {
            return SXS_EPERM;
        } else if (errsv == EAGAIN) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_connect_nb(sxs_socket_t sd, const struct sockaddr *serv_addr,
    sxs_socklen_t addrlen, const struct timeval *p_timeout) {

    sxs_error_t reterr;
    struct timeval timeout;
    fd_set sendfds;
    int num_ready;
    int connected_flag;
    sxs_socklen_t connected_flag_size;
    sxs_errno_t errsv;

    num_ready = 0;
    connected_flag_size = sizeof(connected_flag);

    /* Set the socket to non-blocknig I/O mode */
    reterr = sxs_set_nonblock(sd, 1);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_connect_nb: sxs_set_nonblock:", reterr);
        return SXS_ERRSETNONBLOCK;
    }

    /* Initiate the connect sequence with non-blocking socket */
    reterr = sxs_connect(sd, serv_addr, addrlen);
    if (reterr != SXS_SUCCESS) {
        if (reterr == SXS_EINPROGRESS) {    /* not connected yet */
            timeout.tv_sec = p_timeout->tv_sec;
            timeout.tv_usec = p_timeout->tv_usec;
            FD_ZERO(&sendfds);
            FD_SET(sd, &sendfds);

            /* Wait for connection process to succeed or fail */
            reterr = sxs_select((sd + 1), NULL, &sendfds, NULL, &timeout,
                &num_ready);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_connect_nb: sxs_select:", reterr);
                reterr = sxs_set_nonblock(sd, 0);
                if (reterr != SXS_SUCCESS) {
                    sxs_perror("sxs_connect_nb: sxs_set_nonblock:", reterr);
                    return SXS_ERRSETNONBLOCK;
                }

                reterr = sxs_close(sd);
                if (reterr != SXS_SUCCESS) {
                    sxs_perror("sxs_connect_nb: sxs_close:", reterr);
                    return SXS_ERRCLOSEFAIL;
                }

                return SXS_ERRSELECTFAIL;
            }

            /* Check if the connection process timedout out or completed */
            if (num_ready == 0) { /* timeout reached before conn finished */
                reterr = sxs_set_nonblock(sd, 0);
                if (reterr != SXS_SUCCESS) {
                    sxs_perror("sxs_connect_nb: sxs_set_nonblock:", reterr);
                    return SXS_ERRSETNONBLOCK;
                }

                reterr = sxs_close(sd);
                if (reterr != SXS_SUCCESS) {
                    sxs_perror("sxs_connect_nb: sxs_close:", reterr);
                    return SXS_ERRCLOSEFAIL;
                }

                return SXS_ERRCONNTIMEDOUT;
            } else {    /* connection process completed */
                /* check if it completed in success or failure */
                reterr = sxs_getsockopt(sd, SOL_SOCKET, SO_ERROR,
                    (sxs_buf_t)&connected_flag, &connected_flag_size);
                if (reterr != SXS_SUCCESS) {
                    sxs_perror("sxs_connect_nb: sxs_getsockopt:", reterr);
                    return SXS_ERRGETSOCKOPTFAIL;
                }

                if (connected_flag != 0) { /* failed to connect */
                    reterr = sxs_set_nonblock(sd, 0);
                    if (reterr != SXS_SUCCESS) {
                        sxs_perror("sxs_connect_nb: sxs_set_nonblock:",
                            reterr);
                        return SXS_ERRSETNONBLOCK;
                    }

                    reterr = sxs_close(sd);
                    if (reterr != SXS_SUCCESS) {
                        sxs_perror("sxs_connect_nb: sxs_close:", reterr);
                        return SXS_ERRCLOSEFAIL;
                    }

                    /* handle the error value */
                    errsv = connected_flag;
#ifdef WIN32
                    if (errsv == WSANOTINITIALISED) {
                        return SXS_WSANOTINITIALISED;
                    } else if (errsv == WSAENETDOWN) {
                        return SXS_ENETDOWN;
                    } else if (errsv == WSAEADDRINUSE) {
                        return SXS_EADDRINUSE;
                    } else if (errsv == WSAEINTR) {
                        return SXS_EINTR;
                    } else if (errsv == WSAEINPROGRESS) {
                        return SXS_EINPROGRESS;
                    } else if (errsv == WSAEALREADY) {
                        return SXS_EALREADY;
                    } else if (errsv == WSAEADDRNOTAVAIL) {
                        return SXS_EADDRNOTAVAIL;
                    } else if (errsv == WSAEAFNOSUPPORT) {
                        return SXS_EAFNOSUPPORT;
                    } else if (errsv == WSAECONNREFUSED) {
                        return SXS_ECONNREFUSED;
                    } else if (errsv == WSAEFAULT) {
                        return SXS_EFAULT;
                    } else if (errsv == WSAEINVAL) {
                        return SXS_EINVAL;
                    } else if (errsv == WSAEISCONN) {
                        return SXS_EISCONN;
                    } else if (errsv == WSAENETUNREACH) {
                        return SXS_ENETUNREACH;
                    } else if (errsv == WSAEHOSTUNREACH) {
                        return SXS_EHOSTUNREACH;
                    } else if (errsv == WSAENOBUFS) {
                        return SXS_ENOBUFS;
                    } else if (errsv == WSAENOTSOCK) {
                        return SXS_ENOTSOCK;
                    } else if (errsv == WSAETIMEDOUT) {
                        return SXS_ETIMEDOUT;
                    } else if (errsv == WSAEWOULDBLOCK) {
                        return SXS_EWOULDBLOCK;
                    } else if (errsv == WSAEACCES) {
                        return SXS_EACCES;
                    } else {
                        return SXS_UNKNOWN_ERROR;
                    }
#else
                    if (errsv == EACCES) {
                        return SXS_EACCES;
                    } else if (errsv == EBADF) {
                        return SXS_EBADF;
                    } else if (errsv == ENOTSOCK) {
                        return SXS_ENOTSOCK;
                    } else if (errsv == EAFNOSUPPORT) {
                        return SXS_EAFNOSUPPORT;
                    } else if (errsv == EISCONN) {
                        return SXS_EISCONN;
                    } else if (errsv == ETIMEDOUT) {
                        return SXS_ETIMEDOUT;
                    } else if (errsv == ECONNREFUSED) {
                        return SXS_ECONNREFUSED;
                    } else if (errsv == ENETUNREACH) {
                        return SXS_ENETUNREACH;
                    } else if (errsv == EADDRINUSE) {
                        return SXS_EADDRINUSE;
                    } else if (errsv == EFAULT) {
                        return SXS_EFAULT;
                    } else if (errsv == EINPROGRESS) {
                        return SXS_EINPROGRESS;
                    } else if (errsv == EALREADY) {
                        return EALREADY;
        #ifdef __APPLE__
                    } else if (errsv == EADDRNOTAVAIL) {
                        return SXS_EADDRNOTAVAIL;
                    } else if (errsv == ENOTDIR) {
                        return SXS_ENOTDIR;
                    } else if (errsv == ENAMETOOLONG) {
                        return SXS_ENAMETOOLONG;
                    } else if (errsv == ENOENT) {
                        return SXS_ENOENT;
                    } else if (errsv == ELOOP) {
                        return SXS_ELOOP;
        #else
                    } else if (errsv == EPERM) {
                        return SXS_EPERM;
                    } else if (errsv == EAGAIN) {
                        return SXS_EWOULDBLOCK;
                    } else if (errsv == EINTR) {
                        return SXS_EINTR;
        #endif
                    } else {
                        return SXS_UNKNOWN_ERROR;
                    }
#endif
                } else { /* successfully connected */
                    reterr = sxs_set_nonblock(sd, 0);
                    if (reterr != SXS_SUCCESS) {
                        sxs_perror("sxs_connect_nb: sxs_set_nonblock:",
                            reterr);
                        return SXS_ERRSETNONBLOCK;
                    }

                    return SXS_SUCCESS;
                }
            }
        } else {
            reterr = sxs_set_nonblock(sd, 0);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_connect_nb: sxs_set_nonblock:", reterr);
                return SXS_ERRSETNONBLOCK;
            }
            
            return reterr;
        }
    }

    reterr = sxs_set_nonblock(sd, 0);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_connect_nb: sxs_set_nonblock:", reterr);
        return SXS_ERRSETNONBLOCK;
    }

    return SXS_ERRUNEXPECTED;
}

sxs_error_t sxs_send(sxs_socket_t sd, const sxs_buf_t buf, sxs_size_t len,
    int flags, sxs_ssize_t *p_sent) {
    
    sxs_ssize_t r;
    sxs_errno_t errsv;
    
    r = send(sd, buf, len, flags);
    if (r == SXS_SOCKET_ERROR) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else if (errsv == WSAENOTCONN) {
            return SXS_ENOTCONN;
        } else if (errsv == WSAEINTR) {
            return SXS_EINTR;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAENETRESET) {
            return SXS_ENETRESET;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == WSAEOPNOTSUPP) {
            return SXS_EOPNOTSUPP;
        } else if (errsv == WSAESHUTDOWN) {
            return SXS_ESHUTDOWN;
        } else if (errsv == WSAEWOULDBLOCK) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == WSAEMSGSIZE) {
            return SXS_EMSGSIZE;
        } else if (errsv == WSAEINVAL) {
            return SXS_EINVAL;
        } else if (errsv == WSAECONNABORTED) {
            return SXS_ECONNABORTED;
        } else if (errsv == WSAETIMEDOUT) {
            return SXS_ETIMEDOUT;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EACCES) {
            return SXS_EACCES;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == EAGAIN) {
            return SXS_EWOULDBLOCK;
    #ifdef __APPLE__
        } else if (errsv == EMSGSIZE) {
            return SXS_EMSGSIZE;
        } else if (errsv == ENOBUFS) {
            return SXS_ENOBUFS;
        } else if (errsv == EHOSTUNREACH) {
            return SXS_EHOSTUNREACH;
    #else
        } else if (errsv == EWOULDBLOCK) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == ECONNREFUSED) {
            return SXS_ECONNREFUSED;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
        } else if (errsv == ENOTCONN) {
            return SXS_ENOTCONN;
        } else if (errsv == EOPNOTSUPP) {
            return SXS_EOPNOTSUPP;
        } else if (errsv == EPIPE) {
            return SXS_EPIPE;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    (*p_sent) = r;

    return SXS_SUCCESS;
}

sxs_error_t sxs_send_nb(sxs_socket_t sd, const sxs_buf_t buf,
    sxs_size_t len, int flags, const struct timeval *p_timeout,
    sxs_ssize_t *p_sent) {

    sxs_error_t reterr;
    fd_set sendfds;
    struct timeval timeout;
    int num_ready;

    reterr = sxs_set_nonblock(sd, 1);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_send_nb: sxs_set_nonblock:", reterr);
        return SXS_ERRSETNONBLOCK;
    }

    FD_ZERO(&sendfds);
    FD_SET(sd, &sendfds);
    timeout.tv_sec = p_timeout->tv_sec;
    timeout.tv_usec = p_timeout->tv_usec;
    reterr = sxs_select((sd + 1), NULL, &sendfds, NULL, &timeout, &num_ready);
    if (reterr != SXS_SUCCESS) {
            sxs_perror("sxs_send_nb: sxs_select:", reterr);
            reterr = sxs_set_nonblock(sd, 0);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_send_nb: sxs_set_nonblock:", reterr);
                return SXS_ERRSETNONBLOCK;
            }
            return SXS_ERRSELECTFAIL;
    }

    if (num_ready == 0) {   /* reached the timeout */
        reterr = sxs_set_nonblock(sd, 0);
        if (reterr != SXS_SUCCESS) {
            sxs_perror("sxs_send_nb: sxs_set_nonblock:", reterr);
            return SXS_ERRSETNONBLOCK;
        }
        return SXS_ERRSENDTIMEDOUT;
    } else {    /* data is available and ready on the socket */
        reterr = sxs_send(sd, buf, len, 0, p_sent);
        if (reterr != SXS_SUCCESS) {
            sxs_perror("sxs_send_nb: sxs_recv:", reterr);
            reterr = sxs_set_nonblock(sd, 0);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_send_nb: sxs_set_nonblock:", reterr);
                return SXS_ERRSETNONBLOCK;
            }
            return SXS_ERRSENDFAIL;
        }
    }
    
    reterr = sxs_set_nonblock(sd, 0);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_send_nb: sxs_set_nonblock:", reterr);
        return SXS_ERRSETNONBLOCK;
    }


    return SXS_SUCCESS;
}

sxs_error_t sxs_send_nbytes(sxs_socket_t sd, const sxs_buf_t buf,
    sxs_size_t len) {

    sxs_ssize_t tot_bytes_sent;
    sxs_ssize_t bytes_sent;
    sxs_error_t reterr;

    tot_bytes_sent = 0;

    while (tot_bytes_sent < len) {
        reterr = sxs_send(sd, (buf + tot_bytes_sent), (len - tot_bytes_sent),
            0, &bytes_sent);
        if (reterr != SXS_SUCCESS) {
            return reterr;
        } else {
            tot_bytes_sent = tot_bytes_sent + bytes_sent;
        }
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_send_nbytes_nb(sxs_socket_t sd, const sxs_buf_t buf,
    sxs_size_t len, const struct timeval *p_timeout) {

    sxs_ssize_t tot_bytes_sent;
    sxs_ssize_t bytes_sent;
    sxs_error_t reterr;
    fd_set sendfds;
    struct timeval timeout;
    int num_ready;

    tot_bytes_sent = 0;

    reterr = sxs_set_nonblock(sd, 1);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_send_nbytes_nb: sxs_set_nonblock:", reterr);
        return SXS_ERRSETNONBLOCK;
    }

    while (tot_bytes_sent < len) {
        FD_ZERO(&sendfds);
        FD_SET(sd, &sendfds);
        timeout.tv_sec = p_timeout->tv_sec;
        timeout.tv_usec = p_timeout->tv_usec;
        reterr = sxs_select((sd + 1), NULL, &sendfds, NULL, &timeout,
            &num_ready);
        if (reterr != SXS_SUCCESS) {
            sxs_perror("sxs_send_nbytes_nb: sxs_select:", reterr);
            reterr = sxs_set_nonblock(sd, 0);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_send_nbytes_nb: sxs_set_nonblock:", reterr);
                return SXS_ERRSETNONBLOCK;
            }
            return SXS_ERRSELECTFAIL;
        }

        if (num_ready == 0) {   /* reach the specified timeout */
            reterr = sxs_set_nonblock(sd, 0);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_send_nbytes_nb: sxs_set_nonblock:", reterr);
                return SXS_ERRSETNONBLOCK;
            }
            return SXS_ERRSENDTIMEDOUT;
        } else {    /* socket has data and is ready for recving */
            reterr = sxs_send(sd, (buf + tot_bytes_sent),
                (len - tot_bytes_sent), 0, &bytes_sent);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_send_nbytes_nb: sxs_recv:", reterr);
                reterr = sxs_set_nonblock(sd, 0);
                if (reterr != SXS_SUCCESS) {
                    sxs_perror("sxs_send_nbytes_nb: sxs_set_nonblock:",
                        reterr);
                    return SXS_ERRSETNONBLOCK;
                }
                return SXS_ERRSENDFAIL;
            } else {
                tot_bytes_sent = tot_bytes_sent + bytes_sent;
            }
        }
    }

    reterr = sxs_set_nonblock(sd, 0);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_send_nbytes_nb: sxs_set_nonblock:", reterr);
        return SXS_ERRSETNONBLOCK;
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_recv(sxs_socket_t sd, sxs_buf_t buf, sxs_size_t len,
    int flags, sxs_ssize_t *p_recvd) {
    
    sxs_ssize_t r;
    sxs_errno_t errsv;

    r = recv(sd, buf, len, flags);
    if (r == SXS_SOCKET_ERROR) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else if (errsv == WSAENOTCONN) {
            return SXS_ENOTCONN;
        } else if (errsv == WSAEINTR) {
            return SXS_EINTR;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAENETRESET) {
            return SXS_ENETRESET;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == WSAEOPNOTSUPP) {
            return SXS_EOPNOTSUPP;
        } else if (errsv == WSAESHUTDOWN) {
            return SXS_ESHUTDOWN;
        } else if (errsv == WSAEWOULDBLOCK) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == WSAEMSGSIZE) {
            return SXS_EMSGSIZE;
        } else if (errsv == WSAEINVAL) {
            return SXS_EINVAL;
        } else if (errsv == WSAECONNABORTED) {
            return SXS_ECONNABORTED;
        } else if (errsv == WSAETIMEDOUT) {
            return SXS_ETIMEDOUT;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EAGAIN) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == ENOTCONN) {
            return SXS_ENOTCONN;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
    #ifndef __APPLE__
        } else if (errsv == ECONNREFUSED) {
            return SXS_ECONNREFUSED;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    (*p_recvd) = r;

    return SXS_SUCCESS;
}

sxs_error_t sxs_recv_nb(sxs_socket_t sd, sxs_buf_t buf, sxs_size_t len,
    int flags, const struct timeval *p_timeout, sxs_ssize_t *p_recvd) {

    sxs_ssize_t bytes_recvd;
    sxs_error_t reterr;
    fd_set recvfds;
    struct timeval timeout;
    int num_ready;

    reterr = sxs_set_nonblock(sd, 1);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_recv_nb: sxs_set_nonblock:", reterr);
        return SXS_ERRSETNONBLOCK;
    }

    FD_ZERO(&recvfds);
    FD_SET(sd, &recvfds);
    timeout.tv_sec = p_timeout->tv_sec;
    timeout.tv_usec = p_timeout->tv_usec;
    reterr = sxs_select((sd + 1), &recvfds, NULL, NULL, &timeout, &num_ready);
    if (reterr != SXS_SUCCESS) {
            sxs_perror("sxs_recv_nb: sxs_select:", reterr);
            reterr = sxs_set_nonblock(sd, 0);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_recv_nb: sxs_set_nonblock:", reterr);
                return SXS_ERRSETNONBLOCK;
            }
            return SXS_ERRSELECTFAIL;
    }

    if (num_ready == 0) {   /* reached the timeout */
        reterr = sxs_set_nonblock(sd, 0);
        if (reterr != SXS_SUCCESS) {
            sxs_perror("sxs_recv_nb: sxs_set_nonblock:", reterr);
            return SXS_ERRSETNONBLOCK;
        }
        return SXS_ERRRECVTIMEDOUT;
    } else {    /* data is available and ready on the socket */
        reterr = sxs_recv(sd, buf, len, 0, &bytes_recvd);
        if (reterr != SXS_SUCCESS) {
            sxs_perror("sxs_recv_nb: sxs_recv:", reterr);
            reterr = sxs_set_nonblock(sd, 0);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_recv_nb: sxs_set_nonblock:", reterr);
                return SXS_ERRSETNONBLOCK;
            }
            return SXS_ERRRECVFAIL;
        } else {
            *p_recvd = bytes_recvd;
            if (bytes_recvd == 0) { /* peer cleanly disconnected */
                /* The peer cleanly closed the connection before the
                 * tot number of bytes were read nito the buffer. */
                reterr = sxs_set_nonblock(sd, 0);
                if (reterr != SXS_SUCCESS) {
                    sxs_perror("sxs_recv_nb: sxs_set_nonblock:", reterr);
                    return SXS_ERRSETNONBLOCK;
                }
                return SXS_ERRCONNCLOSED;
            }
        }
    }
    
    reterr = sxs_set_nonblock(sd, 0);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_recv_nb: sxs_set_nonblock:", reterr);
        return SXS_ERRSETNONBLOCK;
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_recv_nbytes(sxs_socket_t sd, sxs_buf_t buf,
    sxs_size_t len) {

    sxs_ssize_t tot_bytes_recvd;
    sxs_ssize_t bytes_recvd;
    sxs_error_t reterr;

    tot_bytes_recvd = 0;

    while (tot_bytes_recvd < len) {
        reterr = sxs_recv(sd, (buf + tot_bytes_recvd),
            (len - tot_bytes_recvd), 0, &bytes_recvd);
        if (reterr != SXS_SUCCESS) { /* failed in error */
            return reterr;
        } else {
            if (bytes_recvd == 0) { /* peer cleanly disconnected */
                /* The peer cleanly closed the connection before the
                 * total number of bytes were read into the buffer. */
                return SXS_ERRCONNCLOSED;
            } else { /* recv'd some data */
                tot_bytes_recvd = tot_bytes_recvd + bytes_recvd;
            }
        }
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_recv_nbytes_nb(sxs_socket_t sd, sxs_buf_t buf,
    sxs_size_t len, const struct timeval *p_timeout) {

    sxs_ssize_t tot_bytes_recvd;
    sxs_ssize_t bytes_recvd;
    sxs_error_t reterr;
    fd_set recvfds;
    struct timeval timeout;
    int num_ready;

    tot_bytes_recvd = 0;

    reterr = sxs_set_nonblock(sd, 1);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_recv_nbytes_nb: sxs_set_nonblock:", reterr);
        return SXS_ERRSETNONBLOCK;
    }

    while (tot_bytes_recvd < len) {
        FD_ZERO(&recvfds);
        FD_SET(sd, &recvfds);
        timeout.tv_sec = p_timeout->tv_sec;
        timeout.tv_usec = p_timeout->tv_usec;
        reterr = sxs_select((sd + 1), &recvfds, NULL, NULL, &timeout,
            &num_ready);
        if (reterr != SXS_SUCCESS) {
            sxs_perror("sxs_recv_nbytes_nb: sxs_select:", reterr);
            reterr = sxs_set_nonblock(sd, 0);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_recv_nbytes_nb: sxs_set_nonblock:", reterr);
                return SXS_ERRSETNONBLOCK;
            }
            return SXS_ERRSELECTFAIL;
        }

        if (num_ready == 0) {   /* reach the specified timeout */
            reterr = sxs_set_nonblock(sd, 0);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_recv_nbytes_nb: sxs_set_nonblock:", reterr);
                return SXS_ERRSETNONBLOCK;
            }
            return SXS_ERRRECVTIMEDOUT;
        } else {    /* socket has data and is ready for recving */
            reterr = sxs_recv(sd, (buf + tot_bytes_recvd),
                (len - tot_bytes_recvd), 0, &bytes_recvd);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_recv_nbytes_nb: sxs_recv:", reterr);
                reterr = sxs_set_nonblock(sd, 0);
                if (reterr != SXS_SUCCESS) {
                    sxs_perror("sxs_recv_nbytes_nb: sxs_set_nonblock:",
                        reterr);
                    return SXS_ERRSETNONBLOCK;
                }
                return SXS_ERRRECVFAIL;
            } else {
                if (bytes_recvd == 0) { /* peer cleanly disconnected */
                    /* The peer cleanly closed the connection before the
                     * tot number of bytes were read nito the buffer. */
                    reterr = sxs_set_nonblock(sd, 0);
                    if (reterr != SXS_SUCCESS) {
                        sxs_perror("sxs_recv_nbytes_nb: sxs_set_nonblock:",
                            reterr);
                        return SXS_ERRSETNONBLOCK;
                    }
                    return SXS_ERRCONNCLOSED;
                } else {
                    tot_bytes_recvd = tot_bytes_recvd + bytes_recvd;
                }
            }
        }
    }

    reterr = sxs_set_nonblock(sd, 0);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_recv_nbytes_nb: sxs_set_nonblock:", reterr);
        return SXS_ERRSETNONBLOCK;
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_close(sxs_socket_t sd) {
    int r;
    sxs_errno_t errsv;

#ifdef WIN32
    r = closesocket(sd);
#else
    r = close(sd);
#endif
    if (r == SXS_SOCKET_ERROR) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAEINTR) {
            return SXS_EINTR;
        } else if (errsv == WSAEWOULDBLOCK) {
            return SXS_EWOULDBLOCK;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
    #ifndef __APPLE__
        } else if (errsv == EIO) {
            return SXS_EIO;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_active_close(sxs_socket_t sd) {

    sxs_error_t reterr;
    struct linger linger_data;

    linger_data.l_onoff = 1;
    linger_data.l_linger = 0;

    reterr = sxs_setsockopt(sd, SOL_SOCKET, SO_LINGER,
        (sxs_buf_t)&linger_data, sizeof(linger_data));
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_active_close: sxs_setsockopt:", reterr);
        return SXS_ERRSETSOCKOPTFAIL;
    }

    reterr = sxs_close(sd);
    if (reterr != SXS_SUCCESS) {
        return reterr;
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
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEINVAL) {
            return SXS_EINVAL;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAENOTCONN) {
            return SXS_ENOTCONN;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == ENOTCONN) {
            return SXS_ENOTCONN;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    return SXS_SUCCESS;
}

sxs_in_addr_t sxs_inet_addr(const char *cp) {
    return inet_addr(cp);
}

sxs_buf_t sxs_inet_ntoa(struct in_addr in) {
    return inet_ntoa(in);
}

sxs_error_t sxs_gethostbyname(const char *name, struct hostent **ret) {
    sxs_errno_t errsv;
    struct hostent *r;

    r = gethostbyname(name);
    if (r == NULL) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAHOST_NOT_FOUND) {
            return SXS_WSAHOST_NOT_FOUND;
        } else if (errsv == WSATRY_AGAIN) {
            return SXS_WSATRY_AGAIN;
        } else if (errsv == WSANO_RECOVERY) {
            return SXS_WSANO_RECOVERY;
        } else if (errsv == WSANO_DATA) {
            return SXS_WSANO_DATA;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else if (errsv == WSAEINTR) {
            return SXS_EINTR;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        /* Note: The following line is abnormal in that errsv is
         * obtaining it's value from h_errno rather than the normal
         * errno. This is due to the fact that the gethostbyname()
         * functions in the Unix varients set the errors in h_errno. */
        errsv = h_errno;
        if (errsv == HOST_NOT_FOUND) {
            return SXS_HOST_NOT_FOUND;
        } else if (errsv == NO_DATA) {
            return SXS_NO_DATA;
        } else if (errsv == NO_RECOVERY) {
            return SXS_NO_RECOVERY;
        } else if (errsv == TRY_AGAIN) {
            return SXS_TRY_AGAIN;
    #ifndef __APPLE__
        } else if (errsv == NO_ADDRESS) {
            return SXS_NO_DATA;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    (*ret) = r;

    return SXS_SUCCESS;
}

sxs_uint32_t sxs_htonl(sxs_uint32_t hostlong) {
    return htonl(hostlong);
}

sxs_uint16_t sxs_htons(sxs_uint16_t hostshort) {
    return htons(hostshort);
}

sxs_uint32_t sxs_ntohl(sxs_uint32_t netlong) {
    return ntohl(netlong);
}

sxs_uint16_t sxs_ntohs(sxs_uint16_t netshort) {
    return ntohs(netshort);
}

sxs_error_t sxs_select(int nfds, fd_set *readfds, fd_set *writefds,
    fd_set *exceptfds, struct timeval *timeout, int *num_ready) {

    int retval;
    sxs_errno_t errsv;

    retval = select(nfds, readfds, writefds, exceptfds, timeout);
    if (retval == SXS_SOCKET_ERROR) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEINVAL) {
            return SXS_EINVAL;
        } else if (errsv == WSAEINTR) {
            return SXS_EINTR;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
    #ifndef __APPLE__
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }
    
    *num_ready = retval;

    return SXS_SUCCESS;
}

sxs_error_t sxs_getsockopt(sxs_socket_t sd, int level, int optname,
    sxs_buf_t optval, sxs_socklen_t *optlen) {

    int retval;
    sxs_errno_t errsv;

    retval = getsockopt(sd, level, optname, optval, optlen);
    if (retval == SXS_SOCKET_ERROR) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAEINVAL) {
            return SXS_EINVAL;
        } else if (errsv == WSAENOPROTOOPT) {
            return SXS_ENOPROTOOPT;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == ENOPROTOOPT) {
            return SXS_ENOPROTOOPT;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
    #ifdef __APPLE__
        } else if (errsv == EDOM) {
            return SXS_EDOM;
    #else
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_setsockopt(sxs_socket_t sd, int level, int optname,
    const sxs_buf_t optval, sxs_socklen_t optlen) {

    int retval;
    sxs_errno_t errsv;

    retval = setsockopt(sd, level, optname, optval, optlen);
    if (retval == SXS_SOCKET_ERROR) {
#ifdef WIN32
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAEINVAL) {
            return SXS_EINVAL;
        } else if (errsv == WSAENETRESET) {
            return SXS_ENETRESET;
        } else if (errsv == WSAENOPROTOOPT) {
            return SXS_ENOPROTOOPT;
        } else if (errsv == WSAENOTCONN) {
            return SXS_ENOTCONN;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#else
        errsv = errno;
        if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == ENOPROTOOPT) {
            return SXS_ENOPROTOOPT;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
    #ifdef __APPLE__
        } else if (errsv == EDOM) {
            return SXS_EDOM;
    #else
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    return SXS_SUCCESS;
}

sxs_error_t sxs_set_nonblock(sxs_socket_t sd, int flag) {
    sxs_errno_t errsv;
    int retval;
#ifdef WIN32
    u_long mode;

    if (flag != 0)
        mode = 1;
    else
        mode = 0;

    retval = ioctlsocket(sd, FIONBIO, &mode);
    if (retval == SXS_SOCKET_ERROR) {
        errsv = WSAGetLastError();
        if (errsv == WSANOTINITIALISED) {
            return SXS_WSANOTINITIALISED;
        } else if (errsv == WSAENETDOWN) {
            return SXS_ENETDOWN;
        } else if (errsv == WSAEINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == WSAENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == WSAEFAULT) {
            return SXS_EFAULT;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
    }
#else
    int sockflags;
    sockflags = fcntl(sd, F_GETFL, 0);
    if (sockflags == SXS_SOCKET_ERROR) { /* error occurred */
        errsv = errno;
        if (errsv == EACCES) {
            return SXS_EACCES;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == EDEADLK) {
            return SXS_EDEADLK;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
        } else if (errsv == EMFILE) {
            return SXS_EMFILE;
        } else if (errsv == ENOLCK) {
            return SXS_ENOLCK;
    #ifdef __APPLE__
        } else if (errsv == ESRCH) {
            return SXS_ESRCH;
    #else
        } else if (errsv == EAGAIN) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == EPERM) {
            return SXS_EPERM;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
    }

    if ((sockflags & O_NONBLOCK) == O_NONBLOCK) { /* currently enabled */
        if (flag != 0) { /* return in error, already non-blocking */
            return SXS_ERRALREADYNONBLOCK;
        } else {
            retval = fcntl(sd, F_SETFL, sockflags & (~O_NONBLOCK));
        }
    } else { /* currently disabled */
        if (flag != 0) {
            retval = fcntl(sd, F_SETFL, sockflags | O_NONBLOCK);
        } else { /* return in error, already blocking */
            return SXS_ERRALREADYBLOCK;
        }
    }

    if (retval == SXS_SOCKET_ERROR) {
        errsv = errno;
        if (errsv == EACCES) {
            return SXS_EACCES;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == EDEADLK) {
            return SXS_EDEADLK;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
        } else if (errsv == EMFILE) {
            return SXS_EMFILE;
        } else if (errsv == ENOLCK) {
            return SXS_ENOLCK;
    #ifdef __APPLE__
        } else if (errsv == ESRCH) {
            return SXS_ESRCH;
    #else
        } else if (errsv == EAGAIN) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == EPERM) {
            return SXS_EPERM;
    #endif
        } else {
            return SXS_UNKNOWN_ERROR;
        }
    }
#endif

    return SXS_SUCCESS;
}

void sxs_perror(const char *s, sxs_error_t errnum) {
    char buf[256];
    sxs_errno_t errval;
    sxs_uint32_t err_index;

#ifdef WIN32
    int i;
    struct { sxs_errno_t code; const char *msg; } windows_sock_errs[] = {
        {WSA_INVALID_HANDLE, "Specified event object handle is invalid."},
        {WSA_NOT_ENOUGH_MEMORY, "Insufficient memory available."},
        {WSA_INVALID_PARAMETER, "One or more parameters ar invalid."},
        {WSA_OPERATION_ABORTED, "Overlapped operation aborted."},
        {WSA_IO_INCOMPLETE, "Overlapped I/O event object not in signaled state."},
        {WSA_IO_PENDING, "Overlapped operation will complete later."},
        {WSAEINTR, "Interrupted function call."},
        {WSAEBADF, "File handle is not valid."},
        {WSAEACCES, "Permission denied."},
        {WSAEFAULT, "Bad address."},
        {WSAEINVAL, "Invalid argument."},
        {WSAEMFILE, "Too many open files."},
        {WSAEWOULDBLOCK, "Resource temporarily unavailable."},
        {WSAEINPROGRESS, "Operation now in progress."},
        {WSAEALREADY, "Operation already in progress."},
        {WSAENOTSOCK, "Sock operation on nonsocket."},
        {WSAEDESTADDRREQ, "Destination address required."},
        {WSAEMSGSIZE, "Message too long."},
        {WSAEPROTOTYPE, "Protocol wrong type for socket."},
        {WSAENOPROTOOPT, "Bad protocol option."},
        {WSAEPROTONOSUPPORT, "Protocol not supported."},
        {WSAESOCKTNOSUPPORT, "Socket type not supported."},
        {WSAEOPNOTSUPP, "Operation not supported."},
        {WSAEPFNOSUPPORT, "Protocol family not supported."},
        {WSAEAFNOSUPPORT, "Address family not supported by protocol family."},
        {WSAEADDRINUSE, "Address already in use."},
        {WSAEADDRNOTAVAIL, "Cannot assign requested address."},
        {WSAENETDOWN, "Network is down."},
        {WSAENETUNREACH, "Network is unreachable."},
        {WSAENETRESET, "Network dropped connection on reset."},
        {WSAECONNABORTED, "Software caused connection abort."},
        {WSAECONNRESET, "Connection reset by peer."},
        {WSAENOBUFS, "No buffer space available."},
        {WSAEISCONN, "Socket is already connected."},
        {WSAENOTCONN, "Socket is not connected."},
        {WSAESHUTDOWN, "Cannot send after socket shutdown."},
        {WSAETOOMANYREFS, "Too many references."},
        {WSAETIMEDOUT, "Connection timed out."},
        {WSAECONNREFUSED, "Connection refused."},
        {WSAELOOP, "Cannot translate name."},
        {WSAENAMETOOLONG, "Name too long."},
        {WSAEHOSTDOWN, "Host is down."},
        {WSAEHOSTUNREACH, "No route to host."},
        {WSAENOTEMPTY, "Directory not empty."},
        {WSAEPROCLIM, "Too many processes."},
        {WSAEUSERS, "User quota exceeded."},
        {WSAEDQUOT, "Disk quota exceeded."},
        {WSAESTALE, "Stale file handle reference."},
        {WSAEREMOTE, "Item is remote."},
        {WSASYSNOTREADY, "Network subsystem unavailable."},
        {WSAVERNOTSUPPORTED, "Winsock.dll version out of range."},
        {WSANOTINITIALISED, "Successful WSAStartup not yet performed."},
        {WSAEDISCON, "Graceful shutdown in progress."},
        {WSAENOMORE, "No more results."},
        {WSAECANCELLED, "Call has been canceled."},
        {WSAEINVALIDPROCTABLE, "Procedure call table is invalid."},
        {WSAEINVALIDPROVIDER, "Service provider is invalide."},
        {WSAEPROVIDERFAILEDINIT, "Service provider failed to initialize."},
        {WSASYSCALLFAILURE, "System call failure."},
        {WSASERVICE_NOT_FOUND, "Service not found."},
        {WSATYPE_NOT_FOUND, "Class type not found."},
        {WSA_E_NO_MORE, "No more results."},
        {WSA_E_CANCELLED, "Call was cancelled."},
        {WSAEREFUSED, "Database query was refused."},
        {WSAHOST_NOT_FOUND, "Host not found."},
        {WSATRY_AGAIN, "Nonauthoritative host not found."},
        {WSANO_RECOVERY, "This is a nonrecoverable error."},
        {WSANO_DATA, "Valid name, no data record of requested type."},
        {WSA_QOS_RECEIVERS, "QOS receivers."},
        {WSA_QOS_SENDERS, "QOS senders."},
        {WSA_QOS_NO_SENDERS, "No QOS senders."},
        {WSA_QOS_NO_RECEIVERS, "QOS no receivers."},
        {WSA_QOS_REQUEST_CONFIRMED, "QOS request confirmed."},
        {WSA_QOS_ADMISSION_FAILURE, "QOS admission error."},
        {WSA_QOS_POLICY_FAILURE, "QOS policy failure."},
        {WSA_QOS_BAD_STYLE, "QOS bad style."},
        {WSA_QOS_BAD_OBJECT, "QOS bad object."},
        {WSA_QOS_TRAFFIC_CTRL_ERROR, "QOS traffic control error."},
        {WSA_QOS_GENERIC_ERROR, "QOS generic error."},
        {WSA_QOS_ESERVICETYPE, "QOS service type error."},
        {WSA_QOS_EFLOWSPEC, "QOS flowspec error."},
        {WSA_QOS_EPROVSPECBUF, "Invalid QOS provider buffer."},
        {WSA_QOS_EFILTERSTYLE, "Invalid QOS filter style."},
        {WSA_QOS_EFILTERTYPE, "Invalid QOS filter type."},
        {WSA_QOS_EFILTERCOUNT, "Incorrect QOS filter count."},
        {WSA_QOS_EOBJLENGTH, "Invalid QOS object length."},
        {WSA_QOS_EFLOWCOUNT, "Incorrect QOS flow count."},
        {WSA_QOS_EUNKNOWNPSOBJ, "Unrecognized QOS object."},
        {WSA_QOS_EPOLICYOBJ, "Invalid QOS policy object."},
        {WSA_QOS_EFLOWDESC, "Invalid QOS flow description."},
        {WSA_QOS_EPSFLOWSPEC, "Invalid QOS provider-specific flowspec."},
        {WSA_QOS_EPSFILTERSPEC, "Invalid QOS provider-pecific filterspec."},
        {WSA_QOS_ESDMODEOBJ, "Invalid QOS shape discard mode object."},
        {WSA_QOS_ESHAPERATEOBJ, "Invalid QOS shaping rate object."},
        {WSA_QOS_RESERVED_PETYPE, "Reserved policy QOS element type."},
        { -1, NULL }
    };
#endif

    buf[0] = '\0';
    
    fprintf(stderr, "%s: sxs error num %d\n", s, (int)errnum); 

    /* Use the error code maps to get the proper operating system
     * specific error code so that I can use the OS specific functions
     * like strerror_r() on unix. */
    if ((errnum >= SXS_UNIXWIN_ERR_START) &&
        (errnum <= SXS_UNIXWIN_ERR_END)) {
        
        err_index = errnum - SXS_UNIXWIN_ERR_START;
#ifdef WIN32
        errval = sxs_winboth_errmap[err_index];
#else
        errval = sxs_unixboth_errmap[err_index];
#endif
    } else if (errnum == SXS_UNKNOWN_ERROR) {
        fprintf(stderr, "%s: unkown error\n", s);
        return;
    } else if (errnum == SXS_SUCCESS) {
        fprintf(stderr, "%s: success\n", s);
        return;
    } else if ((errnum >= SXS_ERR_START) && (errnum <= SXS_UNIX_HERR_END)) {
        return;
    } else {
#ifdef WIN32
        err_index = errnum - SXS_WIN_ERR_START;
        errval = sxs_win_errmap[err_index];
#elif __APPLE__
        if ((errnum >= SXS_MAC_ERR_START) && (errnum <= SXS_MAC_ERR_END)) {
            err_index = errnum - SXS_MAC_ERR_START;
            errval = sxs_mac_errmap[err_index];
        } else if ((errnum >= SXS_UNIX_HERR_START) &&
            (errnum <= SXS_UNIX_HERR_END)) {

            err_index = errnum - SXS_UNIX_HERR_START;
            errval = sxs_unix_herrmap[err_index];
        } else if ((errnum >= SXS_UNIXMAC_ERR_START) &&
            (errnum <= SXS_UNIXMAC_ERR_END)) {

            err_index = errnum - SXS_UNIXMAC_ERR_START;
            errval = sxs_unixmac_errmap[err_index];
        } else {
            fprintf(stderr, "%s: sxs error code out of valid ranges.\n", s);
            return;
        }
#else
        if ((errnum >= SXS_UNIX_ERR_START) && (errnum <= SXS_UNIX_ERR_END)) {
            err_index = errnum - SXS_UNIX_ERR_START;
            errval = sxs_unix_errmap[err_index];
        } else if ((errnum >= SXS_UNIX_HERR_START) &&
            (errnum <= SXS_UNIX_HERR_END)) {

            err_index = errnum - SXS_UNIX_HERR_START;
            errval = sxs_unix_herrmap[err_index];
        } else if ((errnum >= SXS_UNIXMAC_ERR_START) &&
            (errnum <= SXS_UNIXMAC_ERR_END)) {

            err_index = errnum - SXS_UNIXMAC_ERR_START;
            errval = sxs_unixmac_errmap[err_index];
        } else {
            fprintf(stderr, "%s: sxs error code out of valid ranges.\n", s);
            return;
        }
#endif
    }

    fprintf(stderr, "%s: os specific error value %d\n", s, errval);

#ifndef WIN32
    strerror_r(errval, buf, 255);
    buf[255] = '\0';
    fprintf(stderr, "%s: %s\n", s, buf);
#else
    for (i = 0; windows_sock_errs[i].code >= 0; i++) {
        if (errval == windows_sock_errs[i].code) {
            fprintf(stderr, "%s: %s\n", s, windows_sock_errs[i].msg);
            return;
        }
    }
#endif

    return;
}
