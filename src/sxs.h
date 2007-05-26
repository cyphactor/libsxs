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
 * \file sxs.h
 * \brief This is a specifications file for lib_sxs API.
 *
 * The sxs.h file is a specifications file that defines the functions
 * which compose the general API for lib_sxs.
 */

#ifndef SXS_H
#define SXS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sxs_export.h"
#include "sxs_types.h"
#include "sxs_error.h"

SXS_EXPORT sxs_error_t sxs_init(void);

SXS_EXPORT sxs_error_t sxs_uninit(void);

SXS_EXPORT sxs_error_t sxs_socket(int domain, int type, int protocol,
    sxs_socket_t *p_socket);

SXS_EXPORT sxs_error_t sxs_bind(sxs_socket_t sd,
    const struct sockaddr *my_addr, sxs_socklen_t addrlen);

/**
 * Place the specified socket into a listening state.
 *
 * The sxs_listen() function attempts to place the specified socket
 * descritor, 'sd', into a listening state using a backlog of size
 * 'backlog'.
 * \param sd Socket descriptor representing a socket.
 * \param backlog Maximum length of the queue of pending connections.
 * \return A a value representing an error or success.
 * \retval SXS_SUCCESS Successfully shutdown the socket.
 * \retval SXS_EADDRINUSE Another socket is listening on the same port.
 * \retval SXS_EBADF The argument 'sd' is not a valid socket descriptor.
 * \retval SXS_ENOTSOCK The argument 'sd' is not a socket.
 * \retval SXS_EOPNOTSUPP Socket type does not support listening.
 * \retval SXS_WSANOTINITIALIZED The library was not initialized.
 * \retval SXS_ENETDOWN The network subsystem has failed.
 * \retval SXS_EINPROGRESS A blocking call is in progress.
 * \retval SXS_EINVAL Parameter 'sd' has not been bound with 'sxs_bind'.
 * \retval SXS_EISCONN Socket is already connected.
 * \retval SXS_EMFILE No more socket descriptors available.
 * \retval SXS_ENOBUFS No buffer space is available.
 * \retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_listen(sxs_socket_t sd, int backlog);

SXS_EXPORT sxs_error_t sxs_accept(sxs_socket_t sd, struct sockaddr *addr,
    sxs_socklen_t *addrlen, sxs_socket_t *p_sd);

/**
 * Connect the specified socket to the specified address.
 *
 * The sxs_connect() function attepmts to connect the specified socket
 * to the specified address. The format of the specified address depends
 * on the type of socket 'sd' is.
 * \param sd Socket descriptor representing a socket.
 * \param serv_addr Address struct representing remote server to conn to.
 * \param addrlen The len in bytes of the address structure.
 * \return A a value representing an error or success.
 * \retval SXS_SUCCESS Successfully shutdown the socket.
 * \retval SXS_EACCES Write permission denied on the Unix domain socket.
 * \retval SXS_EPERM User tried to conn to bcast addr without having the
 * socket bcast flag enabled or the connection request failed because of
 * a local firewall rule.
 * \retval SXS_EADDRINUSE Local address is already in use.
 * \retval SXS_EAFNOSUPPORT The passed address didn't have a correct
 * address family.
 * \retval SXS_EALREADY Socket is non-blocking and a previous connect
 * accempt has not completed.
 * \retval SXS_EBADF Socket descriptor is invalid.
 * \retval SXS_ECONNREFUSED No one listening on the remote address.
 * \retval SXS_EFAULT The socket structure address is outside the user's
 * address space.
 * \retval SXS_EINPROGRESS The socket is non-blocking and the connection
 * cannot be completed immediately.
 * \retval SXS_EINTR Call was interrupted by a signal that was caught.
 * \retval SXS_EISCONN The socket is already connected.
 * \retval SXS_ENETUNREACH The network is unreachable.
 * \retval SXS_ENOTSOCK The socket descriptor is not a socket.
 * \retval SXS_ETIMEDOUT Timedout while attempting to connect.
 * \retval SXS_WSANOTINITIALIZED The library was not initialized.
 * \retval SXS_ENETDOWN The network subsystem has failed.
 * \retval SXS_EADDRNOTAVAIL Remote address is not a valid address.
 * \retval SXS_EINVAL Parameter 'sd' is in listening state.
 * \retval SXS_EHOSTUNREACH Remote host is unreachable.
 * \retval SXS_ENOBUFS No buffer space available, sock cannot connect.
 * \retval SXS_EWOULDBLOCK Socket is non-blocking and cannot be
 * completed immediately.
 * \retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_connect(sxs_socket_t sd,
    const struct sockaddr *serv_addr, sxs_socklen_t addrlen);

/**
 * Close the socket associated with the given socket descriptor.
 *
 * The sxs_close() function closes the socket associated with the given
 * socket descriptor so that the socket descriptor may be reused.
 * \param sd Socket descriptor representing a socket.
 * \return A a value representing an error or success.
 * \retval SXS_SUCCESS Successfully shutdown the socket.
 * \retval SXS_EBADF The socket 'sd' is not a valid open descriptor.
 * \retval SXS_EINTR The sxs_close() call was interrupted by a signal.
 * \retval SXS_EIO An I/O error occurred.
 * \retval SXS_WSANOTINITIALIZED The library was not initialized.
 * \retval SXS_ENETDOWN The network subsystem has failed.
 * \retval SXS_ENOTSOCK The socket 'sd' is a file, not a socket.
 * \retval SXS_EINPROGRESS A blocking call is in progress.
 * \retval SXS_EWOULDBLOCK Normally would block but it is non-blocking.
 * \retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_close(sxs_socket_t sd);

/**
 * Shutdown all or part of a full-duplex socket based connection.
 *
 * The sxs_shutdown() function either shuts down all or part of a
 * full-duplex socket based connection dependeing on the value of the
 * 'how' parameter. If 'how' is SXS_SHUT_RD, receptions on the socket
 * will no longer be allowed. If 'how' is SXS_SHUT_WR, transmissions on
 * the socket will no longer be allowed. If 'how' is SXS_SHUT_RDWR, both
 * receptions and transissions on the socket will no longer be allowed.
 * \param sd Socket representing the full-duplex connection to shutdown.
 * \param how Flag used to specify how to shutdown the socket.
 * \return A a value representing an error or success.
 * \retval SXS_SUCCESS Successfully shutdown the socket.
 * \retval SXS_EBADF The socket 'sd' is not a valid socket descriptor.
 * \retval SXS_ENOTCONN The specified socket is not connected.
 * \retval SXS_ENOTSOCK The socket 'sd' is a file, not a socket.
 * \retval SXS_ENETDOWN The network subsystem has failed.
 * \retval SXS_EINVAL The 'how' parameter is invalid for socket type.
 * \retval SXS_EINPROGRESS A blocking call is in progress.
 * \retval SXS_WSANOTINITIALIZED The library was not initialized.
 * \retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_shutdown(sxs_socket_t sd, int how);

#ifdef __cplusplus
}
#endif

#endif
