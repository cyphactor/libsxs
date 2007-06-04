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
         * functions in the Unix varients set the errors in h_errno.
         * Currently in this function this just returns an
         * SXS_UNKNOWN_ERROR value in the case of all errors because a
         * mapping has not yet been implemented in the library to handle
         * all the possible values of h_errno. This has already been
         * listed as a ticket in the project's Trac environment. */
        errsv = h_errno;
        return SXS_UNKNOWN_ERROR;
#endif
    }

    (*ret) = r;

    return SXS_SUCCESS;
}
