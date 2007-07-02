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
        } else if (errsv == EAFNOSUPPORT) {
            return SXS_EAFNOSUPPORT;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
        } else if (errsv == EMFILE) {
            return SXS_EMFILE;
        } else if (errsv == ENFILE) {
            return SXS_ENFILE;
        } else if (errsv == ENOBUFS) {
            return SXS_ENOBUFS;
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
        } else if (errsv == EPROTONOSUPPORT) {
            return SXS_EPROTONOSUPPORT;
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
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
        } else if (errsv == ENOTDIR) {
            return SXS_ENOTDIR;
        } else if (errsv == EROFS) {
            return SXS_EROFS;
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
        if (errsv == EADDRINUSE) {
            return SXS_EADDRINUSE;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == EOPNOTSUPP) {
            return SXS_EOPNOTSUPP;
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
        if ((errsv == EAGAIN) || (errsv == EWOULDBLOCK)) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == ECONNABORTED) {
            return SXS_ECONNABORTED;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
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
        } else if (errsv == ENOBUFS) {
            return SXS_ENOBUFS;
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
        } else if (errsv == EPROTO) {
            return SXS_EPROTO;
        } else if (errsv == EPERM) {
            return SXS_EPERM;
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
        } else if (errsv == EPERM) {
            return SXS_EPERM;
        } else if (errsv == EADDRINUSE) {
            return SXS_EADDRINUSE;
        } else if (errsv == EAFNOSUPPORT) {
            return SXS_EAFNOSUPPORT;
        } else if (errsv == EAGAIN) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == EALREADY) {
            return EALREADY;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == ECONNREFUSED) {
            return SXS_ECONNREFUSED;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == EINPROGRESS) {
            return SXS_EINPROGRESS;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
        } else if (errsv == EISCONN) {
            return SXS_EISCONN;
        } else if (errsv == ENETUNREACH) {
            return SXS_ENETUNREACH;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == ETIMEDOUT) {
            return SXS_ETIMEDOUT;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
    }

    return SXS_SUCCESS;
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
        } else if (errsv == EAGAIN) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == EWOULDBLOCK) {
            return SXS_EWOULDBLOCK;
        } else if (errsv == EBADF) {
            return SXS_EBADF;
        } else if (errsv == ECONNREFUSED) {
            return SXS_ECONNREFUSED;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
        } else if (errsv == ENOTCONN) {
            return SXS_ENOTCONN;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
        } else if (errsv == EOPNOTSUPP) {
            return SXS_EOPNOTSUPP;
        } else if (errsv == EPIPE) {
            return SXS_EPIPE;
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
                sxs_perror("sxs_recv_nb: sxs_set_nonblock:", reterr);
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
            sxs_perror("sxs_recv_nb: sxs_recv:", reterr);
            reterr = sxs_set_nonblock(sd, 0);
            if (reterr != SXS_SUCCESS) {
                sxs_perror("sxs_recv_nb: sxs_set_nonblock:", reterr);
                return SXS_ERRSETNONBLOCK;
            }
            return SXS_ERRSENDFAIL;
        }
    }
    
    reterr = sxs_set_nonblock(sd, 0);
    if (reterr != SXS_SUCCESS) {
        sxs_perror("sxs_recv_nb: sxs_set_nonblock:", reterr);
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
        sxs_perror("sxs_recv_nbytes_nb: sxs_set_nonblock:", reterr);
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
                sxs_perror("sxs_sent_nbytes_nb: sxs_set_nonblock:", reterr);
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
        sxs_perror("sxs_recv_nbytes_nb: sxs_set_nonblock:", reterr);
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
        } else if (errsv == ECONNREFUSED) {
            return SXS_ECONNREFUSED;
        } else if (errsv == EFAULT) {
            return SXS_EFAULT;
        } else if (errsv == EINTR) {
            return SXS_EINTR;
        } else if (errsv == EINVAL) {
            return SXS_EINVAL;
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
        } else if (errsv == ENOTCONN) {
            return SXS_ENOTCONN;
        } else if (errsv == ENOTSOCK) {
            return SXS_ENOTSOCK;
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
        } else if (errsv == EIO) {
            return SXS_EIO;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif
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
        } else if ((errsv == NO_DATA) || (errsv == NO_ADDRESS)) {
            return SXS_NO_DATA;
        } else if (errsv == NO_RECOVERY) {
            return SXS_NO_RECOVERY;
        } else if (errsv == TRY_AGAIN) {
            return SXS_TRY_AGAIN;
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
        } else if (errsv == ENOMEM) {
            return SXS_ENOMEM;
        } else {
            return SXS_UNKNOWN_ERROR;
        }
#endif

    }
    
    *num_ready = retval;

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
#endif

    return;
}
