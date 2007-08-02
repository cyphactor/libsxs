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
 * @file sxs.h
 * @brief This is a specifications file for lib_sxs API.
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

/**
 * Initialize the library.
 *
 * The sxs_init() function must be called before any of the other
 * functions can be called and is used to initialize data and state kept
 * within the library.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully initialized the library.
 * @retval SXS_WSASYSNOTREADY Network subsystem is not ready for comm.
 * @retval SXS_WSAVERNOTSUPPORTED Version of Winsock is not supported.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_WSAEPROCLIM Max number of processes has been hit.
 * @retval SXS_EFAULT One of the internal parameters was not a valid
 * pointer.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_init(void);

/**
 * Uninitialize the library.
 *
 * The sxs_uninit() function must be called once the library is no
 * longer needed to cleanup the data and state kept within the library.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully initialized the library.
 * @retval SXS_WSANOTINITIALISED The library was not initialised.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_uninit(void);

/**
 * Create an new socket descriptor to represent a communication  endpoint.
 *
 * The sxs_socket() function creates a new endpoint for communication
 * and passes back a socket descriptor representing this endopint via
 * the 'p_socket' parameter. The 'domain' parameter specifies a
 * communication domain which selects the protocol family (a.k.a.
 * address family). Acceptable values for the 'domain' are the
 * following, AF_INET,  and AF_INET6. The 'type' parameter specifies the
 * communication semantics to use given one of the following types,
 * SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET, SOCK_RAW, and SOCK_RDM. The
 * 'protocol' parameter specifies a particular protocol to be used with
 * the socket. Normally only a single protocol exists to support a
 * particular socket type within a given protocol family, in which case
 * 'protocol' can be specified as 0. Generally, 0 should almost always
 * be used for the value of the 'protocol' parameter. The only situation
 * in which it shouldn't is if you understand the inner workings of this
 * library.
 * @param domian Specifies domain containing protocol (address) family.
 * @param type Specifies the communication semantics to use.
 * @param protocol Specifies protocol to use in protocol family.
 * @param p_sd Pointer to socket descriptor to store new socket in.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully created the socket.
 * @retval SXS_EACCES Perm to create sock of specified type denied.
 * @retval SXS_EAFNOSUPPORT No support for specified address family.
 * @retval SXS_EINVAL Unknown protocol, or protocol family not available.
 * @retval SXS_EMFILE Process file table overflow.
 * @retval SXS_ENFILE The system limit on num of open files been reached.
 * @retval SXS_ENOBUFS Insufficient memory is available.
 * @retval SXS_ENOMEM Insufficient memory is available.
 * @retval SXS_EPROTONOSUPPORT Protocol type not supported.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is currently in progress.
 * @retval SXS_EPROTOTYPE Specified protocol is wrong type for socket.
 * @retval SXS_ESOCKTNOSUPPORT Socket type not supported in address family.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_socket(int domain, int type, int protocol,
    sxs_socket_t *p_sd);

/**
 * Bind the specified address to the specified socket.
 *
 * The sxs_bind() function attempts to associate the local address
 * 'my_addr' with the socket specified by 'sd'.
 * @param sd Socket descriptor representing a socket.
 * @param my_addr The address to associate with the socket 'sd'.
 * @param addrlen The length of the address structure in bytes.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully bound the address to the socket.
 * @retval SXS_EACCES Address is protected, and user is not superuser.
 * @retval SXS_EADDRINUSE The given address is already in use.
 * @retval SXS_EBADF 'sd' is not a valid socket descriptor.
 * @retval SXS_EINVAL The socket is already bound to an address.
 * @retval SXS_ENOTSOCK 'sd' is a descriptor for a file, not a socket.
 * @retval SXS_EADDRNOTAVAIL The requested address was not local.
 * @retval SXS_EFAULT 'my_addr' points outside user addressable space.
 * @retval SXS_ELOOP To many symbolic links found resolving 'my_addr'.
 * @retval SXS_ENAMETOOLONG 'my_addr' is too long.
 * @retval SXS_ENOENT The file does not exist.
 * @retval SXS_ENOMEM Insufficient kernel memory available.
 * @retval SXS_ENOTDIR A component of path prefix is not a directory.
 * @retval SXS_EROFS The socket inode is on read-only file system.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_ENOBUFS Not enough buffers available, too many connections.
 * @retval SXS_EIO An I/O error occurred while making the directory
 * entry or allocating the inode.
 * @retval SXS_EISDIR An empty path name was specified.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_bind(sxs_socket_t sd,
    const struct sockaddr *my_addr, sxs_socklen_t addrlen);

/**
 * Place the specified socket into a listening state.
 *
 * The sxs_listen() function attempts to place the specified socket
 * descritor, 'sd', into a listening state using a backlog of size
 * 'backlog'.
 * @param sd Socket descriptor representing a socket.
 * @param backlog Maximum length of the queue of pending connections.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully put the socket into listening state.
 * @retval SXS_EADDRINUSE Another socket is listening on the same port.
 * @retval SXS_EBADF The argument 'sd' is not a valid socket descriptor.
 * @retval SXS_ENOTSOCK The argument 'sd' is not a socket.
 * @retval SXS_EOPNOTSUPP Socket type does not support listening.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_EINVAL Parameter 'sd' has not been bound with 'sxs_bind'.
 * @retval SXS_EISCONN Socket is already connected.
 * @retval SXS_EMFILE No more socket descriptors available.
 * @retval SXS_ENOBUFS No buffer space is available.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_listen(sxs_socket_t sd, int backlog);

/**
 * Accept the first connection request on the conneciton queue.
 *
 * The sxs_accept() function attempts to accept the first connection
 * request on the queue of pending connections, create a new connected
 * socket, and pass the new socket descriptor via the 'p_sd' parameter.
 * Note: The original socket 'sd' is unaffected by this call.
 * @param sd Listening socket to accept the first queued connection from.
 * @param addr Pointer to sockaddr structure to store peer socket addr.
 * @param addrlen Initially contain size of sockaddr struct in bytes, on
 * return it will contain the actual length of the address returned in
 * bytes. When 'addr' is NULL nothing is filled in.
 * @param p_sd Pointer to socket descriptor to store new socket in.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully accepted a connection.
 * @retval SXS_EWOULDBLOCK The socket is non-blocking and no conns are
 * present to be accepted.
 * @retval SXS_EBADF The socket descriptor is invalid.
 * @retval SXS_ECONNABORTED A connection has been aborted.
 * @retval SXS_EINTR The system call was interrupted by a signal.
 * @retval SXS_EINVAL Socket is not listening, or 'addrlen' is invalid.
 * @retval SXS_EMFILE The per-process open file descriptor limit was hit.
 * @retval SXS_ENFILE The system limit of open file descriptors was hit.
 * @retval SXS_ENOTSOCK The descriptor references a file, not a socket.
 * @retval SXS_EOPNOTSUPP The socket is not a connection based socket.
 * @retval SXS_EFAULT The 'addr' is not in writable part of user address
 * space.
 * @retval SXS_ENOBUFS Not enough free memory.
 * @retval SXS_ENOMEM Not enough free memory.
 * @retval SXS_EPROTO Protocol error.
 * @retval SXS_EPORM Firewal rules forbid connection.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ECONNRESET The peer reset the connection.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_accept(sxs_socket_t sd, struct sockaddr *addr,
    sxs_socklen_t *addrlen, sxs_socket_t *p_sd);

/**
 * Connect the specified socket to the specified address.
 *
 * The sxs_connect() function attepmts to connect the specified socket
 * to the specified address. The format of the specified address depends
 * on the type of socket 'sd' is.
 * @param sd Socket descriptor representing a socket.
 * @param serv_addr Address struct representing remote server to conn to.
 * @param addrlen The len in bytes of the address structure.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully connected the socket.
 * @retval SXS_EACCES Write permission denied on the Unix domain socket.
 * @retval SXS_EPERM User tried to conn to bcast addr without having the
 * socket bcast flag enabled or the connection request failed because of
 * a local firewall rule.
 * @retval SXS_EADDRINUSE Local address is already in use.
 * @retval SXS_EAFNOSUPPORT The passed address didn't have a correct
 * address family.
 * @retval SXS_EALREADY Socket is non-blocking and a previous connect
 * accempt has not completed.
 * @retval SXS_EBADF Socket descriptor is invalid.
 * @retval SXS_ECONNREFUSED No one listening on the remote address.
 * @retval SXS_EFAULT The socket structure address is outside the user's
 * address space.
 * @retval SXS_EINPROGRESS The socket is non-blocking and the connection
 * cannot be completed immediately.
 * @retval SXS_EINTR Call was interrupted by a signal that was caught.
 * @retval SXS_EISCONN The socket is already connected.
 * @retval SXS_ENETUNREACH The network is unreachable.
 * @retval SXS_ENOTSOCK The socket descriptor is not a socket.
 * @retval SXS_ETIMEDOUT Timedout while attempting to connect.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EADDRNOTAVAIL Remote address is not a valid address.
 * @retval SXS_EINVAL Parameter 'sd' is in listening state.
 * @retval SXS_EHOSTUNREACH Remote host is unreachable.
 * @retval SXS_ENOBUFS No buffer space available, sock cannot connect.
 * @retval SXS_EWOULDBLOCK Socket is non-blocking and cannot be
 * completed immediately.
 * @retval SXS_EADDRNOTAVAIL The specified address is not available on
 * this machine.
 * @retval SXS_ENOTDIR A component of the path prefix is not a
 * directory.
 * @retval SXS_ENAMETOOLONG A component of the pathname exceeded
 * NAME_MAX characters, or an entire path exceeded PATH_MAX characters.
 * @retval SXS_ENOENT The named socket does not exist.
 * @retval SXS_ELOOP Too many symbolic links were encountered in
 * translating the pathname.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_connect(sxs_socket_t sd,
    const struct sockaddr *serv_addr, sxs_socklen_t addrlen);

/**
 * Connect the socket to the specified address in a non-blocking fashion.
 *
 * The sxs_connect_nb() function attepmts to connect the specified
 * socket to the specified address within the given timeout. The format
 * of the specified address depends on the type of socket 'sd' is.
 * @param sd Socket descriptor representing a socket.
 * @param serv_addr Address struct representing remote server to conn to.
 * @param addrlen The len in bytes of the address structure.
 * @param p_timeout Pointer to timeval struct containing timeout values.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully connected the socket.
 * @retval SXS_ERRSETNONBLOCK Failed to set socket to non-blocking mode.
 * @retval SXS_ERRCLOSEFAIL Failed to close the socket in cleanup.
 * @retval SXS_ERRSELECTFAIL Failed to monitor socket for write ability.
 * @retval SXS_ERRCONNTIMEDOUT Connect attempt timed out.
 * @retval SXS_ERRGETSOCKOPTFAIL Failed to get socket optionn.
 * @retval SXS_ERRUNEXPECTED Took an unexpected path.
 * @retval SXS_EACCES Write permission denied on the Unix domain socket.
 * @retval SXS_EPERM User tried to conn to bcast addr without having the
 * socket bcast flag enabled or the connection request failed because of
 * a local firewall rule.
 * @retval SXS_EADDRINUSE Local address is already in use.
 * @retval SXS_EAFNOSUPPORT The passed address didn't have a correct
 * address family.
 * @retval SXS_EALREADY Socket is non-blocking and a previous connect
 * accempt has not completed.
 * @retval SXS_EBADF Socket descriptor is invalid.
 * @retval SXS_ECONNREFUSED No one listening on the remote address.
 * @retval SXS_EFAULT The socket structure address is outside the user's
 * address space.
 * @retval SXS_EINPROGRESS The socket is non-blocking and the connection
 * cannot be completed immediately.
 * @retval SXS_EINTR Call was interrupted by a signal that was caught.
 * @retval SXS_EISCONN The socket is already connected.
 * @retval SXS_ENETUNREACH The network is unreachable.
 * @retval SXS_ENOTSOCK The socket descriptor is not a socket.
 * @retval SXS_ETIMEDOUT Timedout while attempting to connect.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EADDRNOTAVAIL Remote address is not a valid address.
 * @retval SXS_EINVAL Parameter 'sd' is in listening state.
 * @retval SXS_EHOSTUNREACH Remote host is unreachable.
 * @retval SXS_ENOBUFS No buffer space available, sock cannot connect.
 * @retval SXS_EWOULDBLOCK Socket is non-blocking and cannot be
 * completed immediately.
 * @retval SXS_EADDRNOTAVAIL The specified address is not available on
 * this machine.
 * @retval SXS_ENOTDIR A component of the path prefix is not a
 * directory.
 * @retval SXS_ENAMETOOLONG A component of the pathname exceeded
 * NAME_MAX characters, or an entire path exceeded PATH_MAX characters.
 * @retval SXS_ENOENT The named socket does not exist.
 * @retval SXS_ELOOP Too many symbolic links were encountered in
 * translating the pathname.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_connect_nb(sxs_socket_t sd,
    const struct sockaddr *serv_addr, sxs_socklen_t addrlen,
    const struct timeval *p_timeout);

/**
 * Send up to the specified number of bytes.
 *
 * The sxs_send() function sends bytes from 'buf' over the specified
 * socket descritpor 'sd'. When the 'flags' parameter is 0 sxs_send()
 * behaves equivalent to a normal write() call. Note: sxs_send()
 * attempts to send the specified number of bytes but there is no
 * guarantee that the specified number of bytes will actually be sent.
 * @param sd The socket descriptor of the socket to receive bytes on.
 * @param buf The pointer to the buffer containing data to send.
 * @param len The number of bytes to attempt to send over the socket..
 * @param flags One or more OR'd message flags controlling behavior,
 * generally 0.
 * @param p_sent Pointer to var to store resulting num of bytes sent.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully sent the data on the socket.
 * @retval SXS_EACCES Write permission denied on dest socket file.
 * @retval SXS_EWOULDBLOCK Socket is non-blocking but would block.
 * @retval SXS_EBADF 'sd' is an invalid socket descriptor.
 * @retval SXS_ECONNRESET Connection reset by remote peer.
 * @retval SXS_EDESTADDRREQ Socket is not connection-mode and no peer
 * address is set.
 * @retval SXS_EFAULT Invalid user space address specified as parameter.
 * @retval SXS_EINTR The receive was interrupted by a signal.
 * @retval SXS_EINVAL Invalid argument passed.
 * @retval SXS_EISCONN Connection-mode socket was already connected.
 * @retval SXS_EMSGSIZE Socket type requires message to be sent
 * atomically, and message size is too large.
 * @retval SXS_ENOBUFS Interface output queue was full.
 * @retval SXS_ENOMEM No memory available.
 * @retval SXS_ENOTCONN Socket is associated with connection-oriented
 * protocol and has not been connected.
 * @retval SXS_ENOTSOCK 'sd' does not refere to a socket.
 * @retval SXS_EOPNOTSUPP A bit in 'flags' is inappropriate for 'sd' type.
 * @retval SXS_EPIPE The local end has been shut down on connection
 * oriented socket.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_ENETRESET Connection broken due to keep-alive activity
 * detecting a failure while operation was in progress.
 * @retval SXS_ESHUTDOWN The socket has been shutdown on recv end.
 * @retval SXS_EHOSTUNREACH Remote host cannot be reached.
 * @retval SXS_ECONNABORTED Terminated due to timout or failure.
 * @retval SXS_ETIMEDOUT Connection dropped because of network failure.
 * @retval SXS_EMSGSIZE The socket requires that message be sent
 * atomically, and the size of the message to be sent made this
 * impossible.
 * @retval SXS_ENOBUFS The output queue for the network interface was
 * full. This generally indicates that the interface has stopped
 * sending, but may be caused by transient congestion.
 * @retval SXS_EHOSTUNREACH The destination address specified an
 * unreachable host.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_send(sxs_socket_t sd, const sxs_buf_t buf,
    sxs_size_t len, int flags, sxs_ssize_t *p_sent);

/**
 * Send up to the specified num of bytes from non-blocking socket.
 *
 * The sxs_send_nb() function first attempts to set the sockets I/O mode
 * to non-blocking and then sends bytes from 'buf' over the specified
 * socket descriptor 'sd'. When the 'flags' parameter is 0 sxs_send_nb()
 * behaves equivalent to a normal write() call. Note: sxs_send_nb()
 * attempts to send the specified number of bytes but there is no
 * gaurantee that the specified number of bytes will actually be sent.
 * sxs_send_nb() also takes a pointer to a timeval struct which
 * specifies how long to wait for the socket to be ready to write to it
 * before returning in error. If 'p_timeout' is NULL it will block
 * indefinitley waiting for the socket to be ready for writing. If
 * 'p_timeval' points to a timeval structure containing all 0's then
 * sxs_send_nb() have no timeout, hence, it will basically act as
 * polling mechanism.
 * @param sd The socket descriptor of the socket to receive bytes on.
 * @param buf The pointer to the buffer containing data to send.
 * @param len The number of bytes to attempt to send over the socket..
 * @param flags One or more OR'd message flags controlling behavior,
 * generally 0.
 * @param p_timeout Pointer to timeval struct containing the upper bound
 * to use for waiting for the socket to be ready to send data on.
 * @param p_sent Pointer to var to store resulting num of bytes sent.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully sent the data on the socket.
 * @retval SXS_ERRSETNONBLOCK Failed to set the sockets
 * non-blocking/blocking state.
 * @retval SXS_ERRSELECTFAIL Failed to monitor socket descriptor for
 * available data.
 * @retval SXS_ERRSENDTIMEDOUT Timedout out waiting for data to become
 * available on the socket descriptor.
 * @retval SXS_ERRSENDFAIL Failed to receive data from the socket.
 */
SXS_EXPORT sxs_error_t sxs_send_nb(sxs_socket_t sd, const sxs_buf_t buf,
    sxs_size_t len, int flags, const struct timeval *p_timeout,
    sxs_ssize_t *p_sent);

/**
 * Send a specified number of bytes.
 *
 * The sxs_send_nbytes() function atemmpts to send exactly the specified
 * number of bytes, no less, from 'buf' over the specified socket
 * descritpor 'sd'. If this function fails it will return an error
 * value associated with the sxs_send() function. Hence, refer to the
 * documentation for the sxs_send() function to find the possible error
 * values and their meanings.
 * @param sd The socket descriptor of the socket to receive bytes on.
 * @param buf The pointer to the buffer containing data to send.
 * @param len The number of bytes to attempt to send over the socket..
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully sent all the data on the socket.
 */
SXS_EXPORT sxs_error_t sxs_send_nbytes(sxs_socket_t sd, const sxs_buf_t buf,
    sxs_size_t len);

/**
 * Send a specified number of bytes from non-blocking socket.
 *
 * The sxs_send_nbytes_nb() function first attempts to set the sockets
 * I/O mode to non-blocking and then sends exactly 'len' bytes from
 * 'buf' over the specified socket descriptor 'sd'. The 'timeout'
 * parameter is used to specify an upper bound on how long
 * sxs_send_nbytes_nb() should wait for the socket to be ready for
 * sending data. If the 'timeout' is set to zero, sxs_send_nbytes_nb()
 * will read as much data as it can until the socket is no longer ready
 * for sending at which point sxs_send_nbytes_nb() will return with the
 * SXS_ERRSENDTIMEDOUT error. If 'timeout' is set to NULL there will be
 * no upper bound on how long to wait before sending. Hence, it will
 * block until the socket is ready for sending. Before returning the
 * function returns it attempts to set the sockets I/O mode back to the
 * default state of blocking.
 * @param sd The socket descriptor of the socket to send bytes on.
 * @param buf The pointer to the buffer containing the data to send.
 * @param len The number of bytes to receive over the socket.
 * @param p_timeout Pointer to timeval struct containing the upper bound
 * to use for waiting for socket to be ready for sending.
 * @return A value representing an error or success.
 * @retval SXS_SUCCESS Successfully received all the data on the socket.
 * @retval SXS_ERRSETNONBLOCK Failed to set the sockets
 * non-blocking/blocking state.
 * @retval SXS_ERRSELECTFAIL Failed to monitor socket descriptor for
 * available data.
 * @retval SXS_ERRSENDIMEDOUT Timedout out waiting for data to become
 * available on the socket descriptor.
 * @retval SXS_ERRSENDVFAIL Failed to receive data from the socket.
 */
SXS_EXPORT sxs_error_t sxs_send_nbytes_nb(sxs_socket_t sd,
    const sxs_buf_t buf, sxs_size_t len, const struct timeval *p_timeout);

/**
 * Transmit a message to another socket.
 *
 * The sxs_sendto() function is used to transmit a message to another
 * socket. Unlike the sxs_send() family of functions the sxs_sendto()
 * function can be used on connection based sockets or non-connection
 * based sockets. The address of the target is given by 'to' with
 * 'tolen' specifying its size. The length of the message is given by
 * 'len'.
 * @param sd The socke tdescriptor of the socket to send message on.
 * @param msg The pointer to the message to send.
 * @param len The size of the message to send in bytes.
 * @param flags A parameter which may include one or more of the
 * following: MSG_OOB (used to send 'out of band' data on sockets which
 * support such) and MSG_DONTROUTE (used to bypass routing).
 * @param to The address to send message to using the socket 'sd'.
 * @param tolen The size of address structure to send message to.
 * @param p_sent Pointer to var to store resulting num of bytes sent.
 * @return A value represting an error or success.
 * @retval SXS_SUCCESS Successfully sent message to destination.
 * @retval SXS_EACCESS The SO_BROADCAST option is not set on the socket,
 * and a broadcast address was given as the destination.
 * @retval SXS_EBADF An invalid descriptor was specified.
 * @retval SXS_ENOTSOCK The argument 'sd' is not a socket.
 * @retval SXS_EFAULT An invalid user space address was specified for a
 * parameter.
 * @retval SXS_EMSGSIZE The socket requires that message be sent
 * atomically, and the size of the message to be sent made this
 * impossible.
 * @retval SXS_EWOULDBLOCK The socket is marked non-blocking and the
 * requested operation would block.
 * @retval SXS_ENOBUFS The output queue for a network interface was
 * full. This generally indicates that the interface has stopped
 * sending, but may be caused by transient congestion.
 * @retval SXS_EHOSTUNREACH The destination address specified an
 * unreachable host.
 * @retval SXS_ECONNRESET Connection reset by peer.
 * @retval SXS_EDESTADDRREQ The socket is not in connection-mode, and no
 * peer address is set.
 * @retval SXS_EINTR A signal occured before any data was transmitted.
 * @retval SXS_EINVAL Invalid argument passed.
 * @retval SXS_EISCONN The connection-mode socket was connected already.
 * @retval SXS_ENOMEM No memory available.
 * @retval SXS_ENOTCONN The socket is not connocted and no target has
 * been given.
 * @retval SXS_EOPNOTSUPP Some bit in the 'flags' argument is
 * inappropriate for the socket type.
 * @retval SXS_EPIPE The local end has been shut down on a connection
 * oriented socket. In this case the process will also receive a SIGPIPE
 * unless MSG_NOSIGNAL is set.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_ENETRESET The connection has been broken due to
 * keep-alive activity detecting a failure while the operation was in
 * progress.
 * @retval SXS_ESHUTDOWN The socket has been shutdown.
 * @retval SXS_ECONNABORTED The virtual circuit was terminated due to a
 * timeout or failure.
 * @retval SXS_EADDRNOTAVAIL The remote address is not a valid address.
 * @retval SXS_EAFNOSUPPORT Addresses in the specified family cannot be
 * used with this socket.
 * @retval SXS_ENETUNREACH The network cannot be reached from this host
 * at this time.
 * @retval SXS_ETIMEDOUT The connection has been dropped, because of
 * network failure or because the system on the other end went down
 * without notice.
 * @retval SXS_UNKNOWN_ERROR An unknown error has occured.
 */
SXS_EXPORT sxs_error_t sxs_sendto(sxs_socket_t sd, const sxs_buf_t msg,
    sxs_size_t len, int flags, const struct sockaddr *to,
    sxs_socklen_t tolen, sxs_ssize_t *p_sent);

/**
 * Receive up to the specified number of bytes from the socket.
 *
 * The sxs_recv() function receives up to the specified number of bytes
 * from the specified socket descritpor 'sd' and stores the received
 * bytes in the buffer 'buf'. Note: There is no guarantee that the
 * specified number of bytes will be received.
 * @param sd The socket descriptor of the socket to receive bytes on.
 * @param buf The pointer to the buffer to store received data in.
 * @param len The maximum number of bytes to receive over the socket.
 * @param flags One or more OR'd message flags controlling behavior,
 * generally 0.
 * @param p_recvd Pointer to var to store resulting num of bytes recv'd.
 * @return A value representing an error or success.
 * @retval SXS_SUCCESS Successfully received data on the socket.
 * @retval SXS_EWOULDBLOCK Socket is non-blocking but would block.
 * @retval SXS_EBADF 'sd' is an invalid socket descriptor.
 * @retval SXS_ECONNREFUSED Remote host refused network connection.
 * @retval SXS_EFAULT The receive buffer points outside process's
 * address space.
 * @retval SXS_EINTR The receive was interrupted by a signal.
 * @retval SXS_EINVAL Invalid argument passed.
 * @retval SXS_ENOMEM Could not allocate memory.
 * @retval SXS_ENOTCONN Socket is associated with connection-oriented
 * protocol and has not been connected.
 * @retval SXS_ENOTSOCK 'sd' does not refere to a socket.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_ENETRESET Connection broken due to keep-alive activity
 * detecting a failure while operation was in progress.
 * @retval SXS_EOPNOTSUPP flag does not match the socket type.
 * @retval SXS_ESHUTDOWN The socket has been shutdown on recv end.
 * @retval SXS_EMSGSIZE The message was too large to fit in 'buf'.
 * @retval SXS_ECONNABORTED Terminated due to timout or failure.
 * @retval SXS_ETIMEDOUT Connection dropped because of network failure.
 * @retval SXS_ECONNRESET Connection reset by remote peer.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_recv(sxs_socket_t sd, sxs_buf_t buf,
    sxs_size_t len, int flags, sxs_ssize_t *p_recvd);

/**
 * Receive up to the specified num of bytes from non-blocking socket.
 *
 * The sxs_recv_nb() function attempts to set a socket to non-blocking
 * I/O mode and receive up to 'len' bytes from the socket 'sd' within
 * the given timeout 'p_timeout'. Before the function returns it
 * attempts to set the sockets I/O mode back to a default state of
 * blocking.
 * @param sd The socket descriptor of the socket to receive bytes on.
 * @param buf The pointer to the buffer to store received data in.
 * @param len The maximum number of bytes to receive over the socket.
 * @param flags One or more OR'd message flags controlling behavior,
 * generally 0.
 * @param p_timeout Pointer to timeval struct containing the upper bound
 * to use for waiting for data to be available on the socket.
 * @param p_recvd Pointer to var to store resulting num of bytes recv'd.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully received data on the socket.
 * @retval SXS_ERRSETNONBLOCK Failed to set the sockets
 * non-blocking/blocking state.
 * @retval SXS_ERRSELECTFAIL Failed to monitor socket descriptor for
 * available data.
 * @retval SXS_ERRRECVTIMEDOUT Timedout out waiting for data to become
 * available on the socket descriptor.
 * @retval SXS_ERRRECVFAIL Failed to receive data from the socket.
 * @retval SXS_ERRCONNCLOSED Peer closed socket before finished
 * receiving all the data.
 */
SXS_EXPORT sxs_error_t sxs_recv_nb(sxs_socket_t sd, sxs_buf_t buf,
    sxs_size_t len, int flags, const struct timeval *p_timeout,
    sxs_ssize_t *p_recvd);

/**
 * Receive a specified number of bytes from the socket.
 *
 * The sxs_recv_nbytes() function attempts to receive exactly the
 * specified number of bytes from the specified socket descritpor 'sd'
 * and stores the received bytes in the buffer 'buf'.  If this function
 * fails it will return an error value associated with the sxs_recv()
 * function. Hence, refer to the documentation for the sxs_recv()
 * function to find the possible error values and their meanings.
 * @param sd The socket descriptor of the socket to receive bytes on.
 * @param buf The pointer to the buffer to store received data in.
 * @param len The maximum number of bytes to receive over the socket.
 * @return A value representing an error or success.
 * @retval SXS_SUCCESS Successfully received all the data on the socket.
 * @retval SXS_ERRCONNCLOSED Peer closed connection before finished.
 */
SXS_EXPORT sxs_error_t sxs_recv_nbytes(sxs_socket_t sd, sxs_buf_t buf,
    sxs_size_t len);

/**
 * Receive a specified number of bytes from the socket in non-blocking.
 *
 * The sxs_recv_nbytes_nb() function attempts to set a socket to
 * non-blocking I/O mode and receive exactly the specified number of
 * bytes 'len' from the specified socket descriptor 'sd'. The the
 * 'timeout' parameter is used to specify an upper bound on how long
 * sxs_recv_nbytes_nb() should wait for data to become available between
 * each chunk of data to receive. If 'p_timeout' is set to zero,
 * sxs_recv_nbytes_nb() will read as much data as it can until it hits
 * the upper bound, 'p_timeout', at which point it will return an error
 * of SXS_ERRRECVTIMEDOUT. If 'p_timeout' is set to NULL there will be
 * no upper bound set and sxs_recv_nbytes_nb() will block indefinitely
 * until all the data is obtained from the socket descriptor or an error
 * occurs. Before returning the function returns it attempts to set the
 * sockets I/O mode back to a default state of blocking.
 * @param sd The socket descripto of the socket to recevie bytes on.
 * @param buf The pointer to the buffer to store received data in.
 * @param len The number of bytes to receive over the socket.
 * @param p_timeout Pointer to timeval struct containing the upper bound
 * to use for waiting for data to be available on the socket.
 * @return A value representing an error or success.
 * @retval SXS_SUCCESS Successfully received all the data on the socket.
 * @retval SXS_ERRSETNONBLOCK Failed to set the sockets
 * non-blocking/blocking state.
 * @retval SXS_ERRSELECTFAIL Failed to monitor socket descriptor for
 * available data.
 * @retval SXS_ERRRECVTIMEDOUT Timedout out waiting for data to become
 * available on the socket descriptor.
 * @retval SXS_ERRRECVFAIL Failed to receive data from the socket.
 * @retval SXS_ERRCONNCLOSED Peer closed socket before finished
 * receiving all the data.
 */
SXS_EXPORT sxs_error_t sxs_recv_nbytes_nb(sxs_socket_t sd, sxs_buf_t buf,
    sxs_size_t len, const struct timeval *p_timeout);

/**
 * Receive a message from a socket.
 *
 * The sxs_recvfrom() function attempts to receive a message from a
 * socket and store the senders address. It may be used on
 * connection-oriented or non-connection-oriented sockets. The MSG_PEEK
 * flag causes the receive operation to return data from the beginning
 * of the receive queue without removing that data from the queue.
 * @param sd The socket descriptor of the socket to receive message on.
 * @param buf The pointer to buffer to store received message in.
 * @param len The size of the buffer to store the message in, in bytes.
 * @param flags A parameter to specify one or more of the low level
 * options, MSG_OOB (allows processing of 'out of band' data), MSG_PEEK
 * (peeks at incoming data).
 * @param from Pointer to address struct to store senders address in.
 * @param fromlen A value-result parameter, initialized to the size of
 * the buffer associated with 'from', and modified on return to indicate
 * the actual size of the address stored there.
 * @param p_recvd Pointer to var to store resulting num of bytes
 * received.
 * @return A value represting an error or success.
 * @retval SXS_SUCCESS Successfully sent message to destination.
 * @retval SXS_EBADF The argument 'sd' is an invalid descriptor.
 * @retval SXS_ENOTSOCK The argument 'sd' does not refer to a socket.
 * @retval SXS_ENOTCONN The socket is associated with a
 * connection-oriented protocol and has not been connected (see
 * sxs_connect() and sxs_accept()).
 * @retval SXS_EWOULDBLOCK The socket is marked non-blocking, and the
 * receive operation would block, or a receive timeout had been set, and
 * the timeout expired before data were received.
 * @retval SXS_EINTR The receive was interrupted by delivery of a signal
 * before any data were available.
 * @retval SXS_EFAULT The receive buffer pointer(s) point outside the
 * process's address space.
 * @retval SXS_ECONNREFUSED A remote host refused to allow the network
 * connection.
 * @retval SXS_EINVAL Invalid argument passed.
 * @retval SXS_ENOMEM Could not allocate memory.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_ENETRESET The connection has been broken due to
 * keep-alive activity detecting a failure while the operation was in
 * progress.
 * @retval SXS_EOPNOTSUPP An inappropriate bit was set in 'flag' for the
 * given protocol or socket type.
 * @retval SXS_ESHUTDOWN The socket has been shutdown.
 * @retval SXS_EMSGSIZE The message was too large to fit in the buffer.
 * @retval SXS_ETIMEDOUT The connection has been dropped, because of
 * network failure or because the system on the other end went down
 * without notice.
 * @retval SXS_ECONNRESET The virtual circuit was reset by the remote
 * side executing a hard or abortive close.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_recvfrom(sxs_socket_t sd, sxs_buf_t buf,
    sxs_size_t len, int flags, struct sockaddr *from,
    sxs_socklen_t *fromlen, sxs_ssize_t *p_recvd);

/**
 * Close the socket associated with the given socket descriptor.
 *
 * The sxs_close() function closes the socket associated with the given
 * socket descriptor so that the socket descriptor may be reused. This
 * is often thought of as a passive close due to that fact that it is
 * necessary to call this on a socket after a peer has initiated a close
 * to get the socket out of CLOSE_WAIT state. Despite the previously
 * stated this function is also used to initate the closure of a socket.
 * Note: If bypassing the standard TIME_WAIT state is necessary please
 * use the sxs_active_close() to initiate the closure of the socket.
 * @param sd Socket descriptor representing a socket.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully closed the socket.
 * @retval SXS_EBADF The socket 'sd' is not a valid open descriptor.
 * @retval SXS_EINTR The sxs_close() call was interrupted by a signal.
 * @retval SXS_EIO An I/O error occurred.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_ENOTSOCK The socket 'sd' is a file, not a socket.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_EWOULDBLOCK Normally would block but it is non-blocking.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_close(sxs_socket_t sd);

/**
 * Close the socket associated with the given socket descriptor.
 *
 * The sxs_active_close() function closes the socket associated with the
 * given socket descriptor so that the socket descriptor may be reused
 * similar to the sxs_close() function. The difference is that the
 * sxs_active_close() function is designed to eliminate the standard
 * TIME_WAIT state after closing a socket. Note: This must only be used
 * on connection based sockets.
 * @param sd Socket descriptor representing a socket.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully closed the socket.
 * @retval SXS_ERRSETSOCKOPTFAIL Failed to set the SO_LINGER socket option.
 * @retval SXS_EBADF The socket 'sd' is not a valid open descriptor.
 * @retval SXS_EINTR The sxs_close() call was interrupted by a signal.
 * @retval SXS_EIO An I/O error occurred.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_ENOTSOCK The socket 'sd' is a file, not a socket.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_EWOULDBLOCK Normally would block but it is non-blocking.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_active_close(sxs_socket_t sd);

/**
 * Shutdown all or part of a full-duplex socket based connection.
 *
 * The sxs_shutdown() function either shuts down all or part of a
 * full-duplex socket based connection dependeing on the value of the
 * 'how' parameter. If 'how' is SXS_SHUT_RD, receptions on the socket
 * will no longer be allowed. If 'how' is SXS_SHUT_WR, transmissions on
 * the socket will no longer be allowed. If 'how' is SXS_SHUT_RDWR, both
 * receptions and transissions on the socket will no longer be allowed.
 * @param sd Socket representing the full-duplex connection to shutdown.
 * @param how Flag used to specify how to shutdown the socket.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully shutdown the socket.
 * @retval SXS_EBADF The socket 'sd' is not a valid socket descriptor.
 * @retval SXS_ENOTCONN The specified socket is not connected.
 * @retval SXS_ENOTSOCK The socket 'sd' is a file, not a socket.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINVAL The 'how' parameter is invalid for socket type.
 * @retval SXS_EINPROGRESS A blocking call is in progress.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_shutdown(sxs_socket_t sd, int how);

/**
 * Convert a c-string dotted-quad IP address into binary data.
 *
 * The sxs_inet_addr() function converts the Internet host address 'cp'
 * from dotted-quad into binary data in network byte order.
 * @param cp c-string containing dotted-quad IP to convert to binary.
 * @return The binary data in network byte order, or SXS_INADDR_NONE.
 * @retval SXS_INADDR_NONE The address specified in 'cp' is invalid.
 */
SXS_EXPORT sxs_in_addr_t sxs_inet_addr(const char *cp);

/**
 * Convert a Internet address to a string in dotted-quad format.
 *
 * The sxs_inet_ntoa() function converts an Internet host address in
 * network byte ordere, 'in', int a string in stardard dotted-quad
 * notation. The string is returned in a statically allocated buffer,
 * which subsequent calls will overwrite.
 * @return Pointer to buffer containing dotted-quad of address.
 * @retval NULL Failed to convert IP to string.
 */
SXS_EXPORT sxs_buf_t sxs_inet_ntoa(struct in_addr in);

/**
 * Get a host IP address given the hosts name.
 *
 * The sxs_gethostbyname() function takes in an IP address or hostname
 * of a machine and returns it's associated IP address. If 'name' is an
 * IPv4 or IPv6 address, no lookup is performed and 'name' is coppied
 * into the 'h_name' field and it's struct in_addr equivalent into the
 * 'h_addr_list[0]' field of the internally maintained 'hostent'
 * structure. If 'name' is a hostname then 'name' is coppied to 'h_name'
 * and the 'h_addr_list' field of the internally maintained 'hostent'
 * structure is filled with all the addresses resulting from the lookup.
 * @param name c-string containing hostname or IP to find IP for.
 * @param ret Pointer to a pointer to a hostent structure to store the
 * address of the internally maintained hostent structure.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully got IP of host.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_WSAHOST_NOT_FOUND Authoritative answer host not found.
 * @retval SXS_WSATRY_AGAIN Nonauthoritative host not found, or server
 * failure.
 * @retval SXS_WSANO_RECOVERY A nonrecoverable error occured.
 * @retval SXS_WSANO_DATA Valid name, no data record of requested type.
 * @retval SXS_EINPROGRESS A blocking call is already in progress.
 * @retval SXS_EFAULT The 'name' parameter is not a valid part of user
 * address space.
 * @retval SXS_EINTR A call was interrupted by a signal.
 * @retval SXS_HOST_NOT_FOUND The specified host is unknown.
 * @retval SXS_NO_DATA The name is valid but has no IP address.
 * @retval SXS_NO_RECOVERY A non-recoverable name server error occured.
 * @retval SXS_TRY_AGAIN A temporary error occured on a name server.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_gethostbyname(const char *name,
    struct hostent **ret);

/**
 * Convert an unsigned 32 bit int to network byte order.
 *
 * The sxs_htonl() function takes a 32 bit unsigned integer in host
 * byte order and converts it to network byte order.
 * @param hostlong unsigned 32 bit integer in host byte order.
 * @return The converted unsigned 32 bit integer in network byte order.
 */
SXS_EXPORT sxs_uint32_t sxs_htonl(sxs_uint32_t hostlong);

/**
 * Convert an unsigned 16 bit int to network byte order.
 *
 * The sxs_htons() function takes a 16 bit unsigned integer in host
 * byte order and converts it to network byte order.
 * @param hostshort unsigned 16 bit integer in host byte order.
 * @return The converted unsigned 16 bit integer in network byte order.
 */
SXS_EXPORT sxs_uint16_t sxs_htons(sxs_uint16_t hostshort);

/**
 * Convert an network byte order unsigned 32 bit int to host byte order.
 *
 * The sxs_ntohl() function takes a 32 bit unsigned integer in network
 * byte order and converts it to host byte order.
 * @param netlong unsigned 32 bit integer in network byte order.
 * @return The converted unsigned 32 bit integer in host byte order.
 */
SXS_EXPORT sxs_uint32_t sxs_ntohl(sxs_uint32_t netlong);

/**
 * Convert an network byte order unsigned 16 bit int to host byte order.
 *
 * The sxs_ntohs() function takes a 16 bit unsigned integer in network
 * byte order and converts it to host byte order.
 * @param netshort unsigned 16 bit integer in network byte order.
 * @return The converted unsigned 16 bit integer in host byte order.
 */
SXS_EXPORT sxs_uint16_t sxs_ntohs(sxs_uint16_t netshort);

/**
 * Monitor multiple socket descriptors.
 *
 * The sxs_select() function can be used to monitor mulitple socket
 * descriptors by waiting until one ore more of the socket descriptors
 * becomes 'ready' for an I/O operation. A socket is considered ready if
 * it is possible to perform the corresponding I/O operation without
 * blocking. To manage the fd_set structures one should use the void
 * FD_CLR(sxs_socket_t sd, fd_set *set), int FD_ISSET(sxs_socket_t sd,
 * fd_set *set), void FD_SET(sxs_socket_t sd, fd_set *set), void
 * FD_ZERO(fd_set *set) macros. FD_CLR() removes the specified
 * descriptor from the given set. FD_ISSET() returns a non-zero value if
 * the specified socket descriptor is part of the given set, otherwise
 * zero is returned. FD_SET() adds the specified descriptor to the given
 * set.  FD_ZERO() initializes a set to a NULL or empty set.
 * @param nfds The highest-numbered socket descriptor in any of the
 * three sets plus 1.
 * @param readfds Pointer to set of sockets to be checked for
 * readability.
 * @param writefds Pointer to set of sockets to be checked for
 * writability.
 * @param exceptfds Pointer to set of sockets to be checked for
 * errors.
 * @param timout An upper bound on the amount of time to wait for a
 * socket to become 'ready' before returning.
 * @param p_num_ready A return-value parameter used to pass back the
 * total number of sockets in the three sets that are 'ready'.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully monitored the socket descriptors.
 * @retval SXS_EBADF An invalid socket descriptor given in one of the
 * socket descriptor sets.
 * @retval SXS_EINTR A signal was caught.
 * @retval SXS_EINVAL The value in 'timeout' is invalid.
 * @retval SXS_ENOMEM Unable to allocate memory for internal tables.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EFAULT Unable to allocate needed resources for internal
 * operations.
 * @retval SXS_EINPROGRESS A blocking call is already in progress.
 * @retval SXS_ENOTSOCK One of the sets contains a descriptor which is
 * not a valid socket.
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_select(int nfds, fd_set *readfds,
    fd_set *writefds, fd_set *exceptfds, struct timeval *timeout,
    int *p_num_ready);

/**
 * Obtain the options associated with a given socket.
 *
 * The sxs_getsockopt() function obtains the options associated with a
 * given socket. Options may exist at multiple protocol levels but are
 * always present at the uppermost "socket" level. To obtain an option
 * both the 'level' at which the option resides and the name of the
 * option 'optname' must be specified. To obtain options at the "socket"
 * level, 'level' is specified as SOL_SOCKET. To obtain options at any
 * other level the protocol number of the appropriate protocol
 * controlling the option is supplied. The following options are
 * recognized at socket level (SOL_SOCKET).
 *
 * SO_DEBUG enables recording of debugging information\n
 * SO_REUSEADDR enables local address reuse\n
 * SO_KEEPALIVE enables keep connections alive\n
 * SO_DONTROUTE enables routing bypass for outgoing messages\n
 * SO_LINGER linger on close if data present\n
 * SO_BROADCAST enables permission to transmit broadcast messages\n
 * SO_OOBINLINE enables reception of out-of-band data in band\n
 * SO_SNDBUF set buffer size for output\n
 * SO_RCVBUF set buffer size for input\n
 * SO_SNDLOWAT set minimum count for output\n
 * SO_RCVLOWAT set minimum count for output\n
 * SO_SNDTIMEO set timeout value for output\n
 * SO_RCVTIMEO set timeout value for input\n
 * SO_TYPE get the type of socket (sxs_getsockopt() only)\n
 * SO_ERROR get and clear error on the socket (sxs_getsockopt() only)\n
 *
 * @param sd The socket to obtain an associated socket option from.
 * @param level The level at which the option resides.
 * @param optname The name of the option to obtain.
 * @param optval Pointer to buffer to store options value in.
 * @param optlen A value-result parameter, initially containing the size
 * of the buffer pointed to by 'optval', and modified on return to
 * indicate the actual size of the value returned.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully obtained the socket option.
 * @retval SXS_EBADF Argument 'sd' is not a valid descriptor.
 * @retval SXS_EFAULT The 'optlen' parameter points to an address which
 * is not in a valid part of the process address space.
 * @retval SXS_ENOPROTOOPT The option is unknown at the level indicated.
 * @retval SXS_ENOTSOCK The argument 'sd' is a file, not a socket.
 * @retval SXS_EINVAL The 'optlen' parameter is invalid.
 * @retval SXS_EDOM The argument value is out of bounds.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is already in progress.
 * @retval SXS_UKNOWN_ERROR An unknown error has occurred.
 */
SXS_EXPORT sxs_error_t sxs_getsockopt(sxs_socket_t sd, int level,
    int optname, sxs_buf_t optval, sxs_socklen_t *optlen);

/**
 * Set the options associated with a given socket.
 *
 * The sxs_setsockopt() function sets the options associated with a
 * given socket. Options may exist at multiple protocol levels but are
 * always present at the uppermost "socket" level. To set an option both
 * the 'level' at which the option resides and the name of the option
 * 'optname' must be specified. To set options at the "socket" level,
 * 'level' is specified as SOL_SOCKET. To obtain options at any other
 * level the protocol numebr of the appropriate protocol controlling the
 * option is supplied. For a listing of acceptable options at the socket
 * level (SOL_SOCKET) please refer to the documentation for the
 * sxs_getsockopt() function.
 *
 * @param sd The socket to set an associated socket option for.
 * @param level The level at which the option resides.
 * @param optname The name of the option to set.
 * @param optval Pointer to buffer containing value to set option to.
 * @param optlen The size of the value in the buffer pointed to by
 * 'optval'.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully obtained the socket option.
 * @retval SXS_EBADF Argument 'sd' is not a valid descriptor.
 * @retval SXS_EFAULT The 'optlen' parameter points to an address which
 * is not in a valid part of the process address space.
 * @retval SXS_ENOPROTOOPT The option is unknown at the level indicated.
 * @retval SXS_ENOTSOCK The argument 'sd' is a file, not a socket.
 * @retval SXS_EINVAL The 'optlen' parameter is invalid.
 * @retval SXS_EDOM The argument value is out of bounds.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is already in progress.
 * @retval SXS_ENETRESET The connection has timedout when SO_KEEPALIVE
 * is set.
 * @retval SXS_ENOTCONN The connection has been reset when SO_KEEPALIVE
 * is set.
 * @retval SXS_UKNOWN_ERROR An unknown error has occurred.
 */
SXS_EXPORT sxs_error_t sxs_setsockopt(sxs_socket_t sd, int level,
    int optname, const sxs_buf_t optval, sxs_socklen_t optlen);

/**
 * Set a sockets I/O mode (blocking/non-blocking) state.
 *
 * The sxs_set_nonblocking() function allows one to control the I/O mode
 * of a socket. Specifically, allowing one to enable or disable
 * non-blocking mode, given that blocking is the default state of the
 * sockets I/O mode.
 * @param sd The socket descriptor of the socket to change the I/O mode
 * for.
 * @param flag The flag used to specify enable non-blocking (non-zero)
 * or disable non-blocking (zero) .
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully monitored the socket descriptors.
 * @retval SXS_ERRALREADYNONBLOCK The socket is already in non-blocking
 * mode.
 * @retval SXS_ERRALREADYBLOCK The socket is already in blocking mode.
 * @retval SXS_EACCES Operation is prohibited by locks held by other
 * processes.
 * @retval SXS_EWOULDBLOCK The operation is prohibited because the file
 * has been memory-mapped by another process.
 * @retval SXS_EBADF 'sd' is not an open socket descriptor.
 * @retval SXS_EDEADLK It was tected that the specified command would
 * cause a deadlock.
 * @retval SXS_EFAULT 'lock' is outside your accessible address space.
 * @retval SXS_EINTR The command was interrupted by a signal.
 * @retval SXS_EINVAL 'arg' is not an allowable signal number.
 * @retval SXS_EMFILE Process already has maximum number of open file
 * descriptors.
 * @retval SXS_ENOLCK Too many segment locks open, lock table is full.
 * @retval SXS_EPERM Attempted to clear the O_APPEND flag on the file
 * that has append-only attribute set.
 * @retval SXS_ESRCH Process ID given as 'arg' is not in use.
 * @retval SXS_WSANOTINITIALIZED The library was not initialized.
 * @retval SXS_ENETDOWN The network subsystem has failed.
 * @retval SXS_EINPROGRESS A blocking call is already in progress.
 * @retval SXS_ENOTSOCK 'sd' is not a valid socket descriptor.
 * @retval SXS_UNKNOWN_ERROR An knknown error has occured.
 */
SXS_EXPORT sxs_error_t sxs_set_nonblock(sxs_socket_t sd, int flag);

/**
 * Produce a message on stderr describing the specified error.
 *
 * The sxs_perror() function produces a message on the standard error
 * output, describing the error specified by the 'errnum' parameter. If
 * the the error does not have a correlating message it will simply
 * print the sxs error code and the operating system specific error
 * code. Note: The operating system specific error code meanings can be
 * looked up in the operatying system specific socket API documentation.
 * @param s c-string containing error header, generally name of the
 * function that failed.
 * @param errnum The error number returned in failure by a previous call.
 * @return This function returns no value.
 */
SXS_EXPORT void sxs_perror(const char *s, sxs_error_t errnum);

#ifdef __cplusplus
}
#endif

#endif
