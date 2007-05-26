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
 * \file sxs_error.c
 * \brief This is an implementations file for lib_sxs error handling.
 *
 * The sxs_error.c file is an implementations file for lib_sxs error
 * handleing. It provides all the definitions for any of the error
 * handling functions.
 */

#include "sxs_error.h"

#ifdef WIN32
sxs_int32_t sxs_winboth_errmap[43] = { WSAEINTR, WSAEBADF, WSAEACCES, WSAEFAULT, WSAEINVAL, WSAEMFILE, WSAEWOULDBLOCK, WSAEINPROGRESS, WSAEALREADY, WSAENOTSOCK, WSAEDESTADDRREQ, WSAEMSGSIZE, WSAEPROTOTYPE, WSAENOPROTOOPT, WSAEPROTONOSUPPORT, WSAESOCKTNOSUPPORT, WSAEOPNOTSUPP, WSAEPFNOSUPPORT, WSAEAFNOSUPPORT, WSAEADDRINUSE, WSAEADDRNOTAVAIL, WSAENETDOWN, WSAENETUNREACH, WSAENETRESET, WSAECONNABORTED, WSAECONNRESET, WSAENOBUFS, WSAEISCONN, WSAENOTCONN, WSAESHUTDOWN, WSAETOOMANYREFS, WSAETIMEDOUT, WSAECONNREFUSED, WSAELOOP, WSAENAMETOOLONG, WSAEHOSTDOWN, WSAEHOSTUNREACH, WSAENOTEMPTY, WSAEUSERS, WSAEDQUOT, WSAESTALE, WSAEREMOTE, WSAECANCELED };
#else
sxs_int32_t sxs_unixboth_errmap[43] = { EINTR, EBADF, EACCES, EFAULT, EINVAL, EMFILE, EWOULDBLOCK, EINPROGRESS, EALREADY, ENOTSOCK, EDESTADDRREQ, EMSGSIZE, EPROTOTYPE, ENOPROTOOPT, EPROTONOSUPPORT, ESOCKTNOSUPPORT, EOPNOTSUPP, EPFNOSUPPORT, EAFNOSUPPORT, EADDRINUSE, EADDRNOTAVAIL, ENETDOWN, ENETUNREACH, ENETRESET, ECONNABORTED, ECONNRESET, ENOBUFS, EISCONN, ENOTCONN, ESHUTDOWN, ETOOMANYREFS, ETIMEDOUT, ECONNREFUSED, ELOOP, ENAMETOOLONG, EHOSTDOWN, EHOSTUNREACH, ENOTEMPTY, EUSERS, EDQUOT, ESTALE, EREMOTE, ECANCELED };
#endif

#ifdef WIN32
sxs_int32_t sxs_win_errmap[36] = { WSA_INVALID_HANDLE, WSA_NOT_ENOUGH_MEMORY, WSA_INVALID_PARAMETER, WSA_OPERATION_ABORTED, WSA_IO_INCOMPLETE, WSA_IO_PENDING, WSAEPROCLIM, WSASYSNOTREADY, WSAVERNOTSUPPORTED, WSANOTINITIALISED, WSAEDISCON, WSAENOMORE, WSAEINVALIDPROCTABLE, WSAEINVALIDPROVIDER, WSAEPROVIDERFAILEDINIT, WSASYSCALLFAILURE, WSASERVICE_NOT_FOUND, WSATYPE_NOT_FOUND, WSA_E_NO_MORE, WSA_E_CANCELLED, WSAREFUSED, WSAHOST_NOT_FOUND, WSATRY_AGAIN, WSANO_RECOVERY, WSANO_DATA, WSA_QOS_RECEIVERS, WSA_QOS_SENDERS, WSA_QOS_NO_SENDERS, WSA_QOS_NO_RECEIVERS, WSA_QOS_REQUEST_CONFIRMED, WSA_QOS_ADMISSION_FAILURE, WSA_QOS_POLICY_FAILURE, WSA_QOS_BAD_STYLE, WSA_QOS_BAD_OBJECT, WSA_QOS_TRAFFIC_CTRL_ERROR, WSA_QOS_GENERIC_ERROR };
#else
sxs_int32_t sxs_unix_errmap[86] = { EPERM, ENOENT, ESRCH, EIO, ENXIO, E2BIG, ENOEXEC, ECHILD, ENOMEM, ENOTBLK, EBUSY, EEXIST, EXDEV, ENODEV, ENOTDIR, EISDIR, ENFILE, ENOTTY, ETXTBSY, EFBIG, ENOSPC, ESPIPE, EROFS, EMLINK, EPIPE, EDOM, ERANGE, EDEADLK, ENOLCK, ENOSYS, ENOMSG, EIDRM, ECHRNG, EL2NSYNC, EL3HLT, EL3RST, ELNRNG, EUNATCH, ENOCSI, EL2HLT, EBADE, EBADR, EXFULL, ENOANO, EBADRQC, EBADSLT, EBFONT, ENOSTR, ENODATA, ETIME, ENOSR, ENONET, ENOPKG, ENOLINK, EADV, ESRMNT, ECOMM, EPROTO, EMULTIHOP, EDOTDOT, EBADMSG, EOVERFLOW, ENOTUNIQ, EBADFD, EREMCHG, ELIBACC, ELIBBAD, ELIBSCN, ELIBMAX, ELIBEXEC, EILSEQ, ERESTART, ESTRPIPE, EUCLEAN, ENOTNAM, ENAVAIL, EISNAM, EREMOTEIO, ENOMEDIUM, EMEDIUMTYPE, ENOKEY, EKEYEXPIRED, EKEYREVOKED, EKEYREJECTED, EOWNERDEAD, ENOTRECOVERABLE };
#endif
