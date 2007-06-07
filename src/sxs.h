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

SXS_EXPORT sxs_error_t sxs_init(void);

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
 * @retval SXS_SUCCESS Successfully shutdown the socket.
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
 * @retval SXS_SUCCESS Successfully shutdown the socket.
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
 * @retval SXS_SUCCESS Successfully shutdown the socket.
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
 * @retval SXS_SUCCESS Successfully shutdown the socket.
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
 * @retval SXS_SUCCESS Successfully shutdown the socket.
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
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_connect(sxs_socket_t sd,
    const struct sockaddr *serv_addr, sxs_socklen_t addrlen);

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
 * @retval SXS_SUCCESS Successfully shutdown the socket.
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
 * @retval SXS_UNKNOWN_ERROR An unkwon error has occured.
 */
SXS_EXPORT sxs_error_t sxs_send(sxs_socket_t sd, const sxs_buf_t buf,
    sxs_size_t len, int flags, sxs_ssize_t *p_sent);

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
 * @retval SXS_SUCCESS Successfully shutdown the socket.
 */
SXS_EXPORT sxs_error_t sxs_send_nbytes(sxs_socket_t sd, const sxs_buf_t buf,
    sxs_size_t len);

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
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully shutdown the socket.
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
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully shutdown the socket.
 */
SXS_EXPORT sxs_error_t sxs_recv_nbytes(sxs_socket_t sd, sxs_buf_t buf,
    sxs_size_t len);

/**
 * Close the socket associated with the given socket descriptor.
 *
 * The sxs_close() function closes the socket associated with the given
 * socket descriptor so that the socket descriptor may be reused.
 * @param sd Socket descriptor representing a socket.
 * @return A a value representing an error or success.
 * @retval SXS_SUCCESS Successfully shutdown the socket.
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
 * @retval SXS_SUCCESS Successfully shutdown the socket.
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
