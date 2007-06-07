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
 * @file sxs_error.h
 * @brief This is a specifications file for error hanlding in lib_sxs.
 *
 * The sxs_error.h file is a specifications file that defines the types
 * which represent errors and all their possible values, as well as
 * providing prototypes for error handling functions.
 */

#ifndef SXS_ERROR_H
#define SXS_ERROR_H

#include "sxs_types.h"

#define SXS_SUCCESS 0 /**< Operation completed successfully */
#define SXS_UNKNOWN_ERROR 0xffffffff /**< An undefined error occured */

/* The following are errors which are shared between both Unix varients
 * such as linux and mac as well as Windows. */
#define SXS_UNIXWIN_ERR_START 1
#define SXS_UNIXWIN_ERR_END 333
#define SXS_EINTR 1 /**< Interrupted system call */
#define SXS_EBADF 2 /**< Bad file number */
#define SXS_EACCES 3 /**< Permission denied */
#define SXS_EFAULT 4 /**< Bad address */
#define SXS_EINVAL 5 /**< Invalid argument */
#define SXS_EMFILE 6 /**< Too many open files */
#define SXS_EWOULDBLOCK 7 /**< Operation would block */
#define SXS_EINPROGRESS 8 /**< Operation now in progress */
#define SXS_EALREADY 9 /**< Operation already in progress */
#define SXS_ENOTSOCK 10 /**< Socket operation on non-socket */
#define SXS_EDESTADDRREQ 11 /**< Destination address required */
#define SXS_EMSGSIZE 12 /**< Message too long */
#define SXS_EPROTOTYPE 13 /**< Protocol wrong type for socket */
#define SXS_ENOPROTOOPT 14 /**< Protocol not available */
#define SXS_EPROTONOSUPPORT 15 /**< Protocol not supported */
#define SXS_ESOCKTNOSUPPORT 16 /**< Socket type not supported */
#define SXS_EOPNOTSUPP 17 /**< Operation not supported on transport endpoint */
#define SXS_EPFNOSUPPORT 18 /**< Protocol family not supported */
#define SXS_EAFNOSUPPORT 19 /**< Address family not supported by protocol */
#define SXS_EADDRINUSE 20 /**< Address already in use */
#define SXS_EADDRNOTAVAIL 21 /**< Cannot assign requested address */
#define SXS_ENETDOWN 22 /**< Network is down */
#define SXS_ENETUNREACH 23 /**< Network is unreachable */
#define SXS_ENETRESET 24 /**< Network dropped connection because of reset */
#define SXS_ECONNABORTED 25 /**< Software caused connection abort */
#define SXS_ECONNRESET 26 /**< Connection reset by peer */
#define SXS_ENOBUFS 27 /**< No buffer space available */
#define SXS_EISCONN 28 /**< Transport endpoint is already connected */
#define SXS_ENOTCONN 29 /**< Transport endpoint is not connected */
#define SXS_ESHUTDOWN 30 /**< Cannot send after transport endpoint shutdown */
#define SXS_ETOOMANYREFS 31 /**< Too mayn references: cannot splice */
#define SXS_ETIMEDOUT 32 /**< Connection timed out */
#define SXS_ECONNREFUSED 33 /**< Connection refused */
#define SXS_ELOOP 34 /**< Too many symbolic links encountered */
#define SXS_ENAMETOOLONG 35 /**< File name too long */
#define SXS_EHOSTDOWN 36 /**< Host is down */
#define SXS_EHOSTUNREACH 37 /**< No route to host */
#define SXS_ENOTEMPTY 38 /**< Directory not empty */
#define SXS_EUSERS 39 /**< Too many users */
#define SXS_EDQUOT 40 /**< Quota exceeded */
#define SXS_ESTALE 41 /**< Stale NFS file handle */
#define SXS_EREMOTE 42 /**< Remote I/O error */
#define SXS_ECANCELED 43 /**< Operation Canceled */
#ifdef WIN32
extern sxs_int32_t sxs_winboth_errmap[43];
#else
extern sxs_int32_t sxs_unixboth_errmap[43];
#endif


#define SXS_WIN_ERR_START 334
#define SXS_WIN_ERR_END 667
#define SXS_WSA_INVALID_HANDLE 334 /**< Event object handle is invalid */
#define SXS_WSA_NOT_ENOUGH_MEMORY 335 /**< Insufficient memory available */
#define SXS_WSA_INVALID_PARAMETER 336 /**< One or more params are invalid */
#define SXS_WSA_OPERATION_ABORTED 337 /**< Overlapped operation aborted */
#define SXS_WSA_IO_INCOMPLETE 338 /**< Overlapped I/O event object not in signaled state */
#define SXS_WSA_IO_PENDING 339 /**< Overlapped operations will complete later */
#define SXS_WSAEPROCLIM 340 /**< Too many processes */
#define SXS_WSASYSNOTREADY 341 /**< Network subsystem unavailable */
#define SXS_WSAVERNOTSUPPORTED 342 /**< Winsock.dll version out of range */
#define SXS_WSANOTINITIALISED 343 /**< Successful WSAStartup not yet performed */
#define SXS_WSAEDISCON 344 /**< Graceful shutdown in progress */
#define SXS_WSAENOMORE 345 /**< No more results */
#define SXS_WSAEINVALIDPROCTABLE 346 /**< Procedure call table is invalid */
#define SXS_WSAEINVALIDPROVIDER 347 /**< Service provider is invalid */
#define SXS_WSAEPROVIDERFAILEDINIT 348 /**< Service provider failed init */
#define SXS_WSASYSCALLFAILURE 349 /**< System call failure */
#define SXS_WSASERVICE_NOT_FOUND 350 /**< Service not found */
#define SXS_WSATYPE_NOT_FOUND 351 /**< Class type not found */
#define SXS_WSA_E_NO_MORE 352 /**< No more results */
#define SXS_WSA_E_CANCELLED 353 /**< Call was canceled */
#define SXS_WSAREFUSED 354 /**< Database query was refused */
#define SXS_WSAHOST_NOT_FOUND 355 /**< Host not found */
#define SXS_WSATRY_AGAIN 356 /**< Nonauthoritative host not found */
#define SXS_WSANO_RECOVERY 357 /**< This is a nonrecoverable error */
#define SXS_WSANO_DATA 358 /**< Valid name, no data record */
#define SXS_WSA_QOS_RECEIVERS 359 /**< QOS receivers */
#define SXS_WSA_QOS_SENDERS 360 /**< QOS senders */
#define SXS_WSA_QOS_NO_SENDERS 361 /**< No QOS senders */
#define SXS_WSA_QOS_NO_RECEIVERS 362 /**< No QOS receivers */
#define SXS_WSA_QOS_REQUEST_CONFIRMED 363 /**< QOS request confirmed */
#define SXS_WSA_QOS_ADMISSION_FAILURE 364 /**< QOS admission error */
#define SXS_WSA_QOS_POLICY_FAILURE 365 /**< QOS policy failure */
#define SXS_WSA_QOS_BAD_STYLE 366 /**< QOS bad style */
#define SXS_WSA_QOS_BAD_OBJECT 367 /**< QOS bad object */
#define SXS_WSA_QOS_TRAFFIC_CTRL_ERROR 368 /**< QOS traffic control error */
#define SXS_WSA_QOS_GENERIC_ERROR 369 /**< QOS generic error */
#ifdef WIN32
extern sxs_int32_t sxs_win_errmap[36];
#endif

#define SXS_UNIX_ERR_START 668
#define SXS_UNIX_ERR_END 1000
#define SXS_EPERM 668 /**< Operation not permitted */
#define SXS_ENOENT 669 /**< No such file or directory */
#define SXS_ESRCH 670 /**< No such process */
#define SXS_EIO 671 /**< I/O error */
#define SXS_ENXIO 672 /**< No such device or address */
#define SXS_E2BIG 673 /**< Argument list too long */
#define SXS_ENOEXEC 674 /**< Exec format error */
#define SXS_ECHILD 675 /**< No child processes */
#define SXS_ENOMEM 676 /**< Out of memory */
#define SXS_ENOTBLK 677 /**< Block device required */
#define SXS_EBUSY 678 /**< Device or resource busy */
#define SXS_EEXIST 679 /**< File exists */
#define SXS_EXDEV 680 /**< Cross-device link */
#define SXS_ENODEV 681 /**< No such device */
#define SXS_ENOTDIR 682 /**< Not a directory */
#define SXS_EISDIR 683 /**< Is a directory */
#define SXS_ENFILE 684 /**< File table overflow */
#define SXS_ENOTTY 685 /**< Not a typewriter */
#define SXS_ETXTBSY 686 /**< Text file busy */
#define SXS_EFBIG 687 /**< File too large */
#define SXS_ENOSPC 688 /**< No space left on device */
#define SXS_ESPIPE 689 /**< Illegal seek */
#define SXS_EROFS 690 /**< Read-only file system */
#define SXS_EMLINK 691 /**< Too many links */
#define SXS_EPIPE 692 /**< Broken pipe */
#define SXS_EDOM 693 /**< Math argument out of domain of func */
#define SXS_ERANGE 694 /**< Math result not representable */
#define SXS_EDEADLK 695 /**< Resource deadlock would occur */
#define SXS_ENOLCK 696 /**< No record locks available */
#define SXS_ENOSYS 697 /**< Function not implemented */
#define SXS_ENOMSG 698 /**< No message of desired type */
#define SXS_EIDRM 699 /**< Identifier removed */
#define SXS_ECHRNG 700 /**< Channel number out of range */
#define SXS_EL2NSYNC 701 /**< Level 2 not synchronized */
#define SXS_EL3HLT 702 /**< Level 3 halted */
#define SXS_EL3RST 703 /**< Level 3 reset */
#define SXS_ELNRNG 704 /**< Link number out of range */
#define SXS_EUNATCH 705 /**< Protocol driver not attached */
#define SXS_ENOCSI 706 /**< No CSI structure available */
#define SXS_EL2HLT 707 /**< Level 2 halted */
#define SXS_EBADE 708 /**< Invalid exchange */
#define SXS_EBADR 709 /**< Invalid request descriptor */
#define SXS_EXFULL 710 /**< Exchange full */
#define SXS_ENOANO 711 /**< No anode */
#define SXS_EBADRQC 712 /**< Invalid request code */
#define SXS_EBADSLT 713 /**< Invalid slot */
#define SXS_EBFONT 714 /**< Bad font file format */
#define SXS_ENOSTR 715 /**< Device not a stream */
#define SXS_ENODATA 716 /**< No data available */
#define SXS_ETIME 717 /**< Timer expired */
#define SXS_ENOSR 718 /**< Out of streams resources */
#define SXS_ENONET 719 /**< Machine is not on the network */
#define SXS_ENOPKG 720 /**< Package not installed */
#define SXS_ENOLINK 721 /**< Link has been severed */
#define SXS_EADV 722 /**< Advertise error */
#define SXS_ESRMNT 723 /**< Srmount error */
#define SXS_ECOMM 724 /**< Communication error on send */
#define SXS_EPROTO 725 /**< Protocol error */
#define SXS_EMULTIHOP 726 /**< Multiphop attempted */
#define SXS_EDOTDOT 727 /**< RFS specific error */
#define SXS_EBADMSG 728 /**< Not a data message */
#define SXS_EOVERFLOW 729 /**< Value too large for defined data type */
#define SXS_ENOTUNIQ 730 /**< Name not unique on network */
#define SXS_EBADFD 731 /**< File descriptor in bad state */
#define SXS_EREMCHG 732 /**< Remote address changed */
#define SXS_ELIBACC 733 /**< Can not access a needed shared library */
#define SXS_ELIBBAD 734 /**< Accessing a corrupted shared library */
#define SXS_ELIBSCN 735 /**< .lib section in a.out corrupted */
#define SXS_ELIBMAX 736 /**< Attempting to link to too many shared libraries */
#define SXS_ELIBEXEC 737 /**< Cannot exec a shared library directly */
#define SXS_EILSEQ 738 /**< Illegal byte sequence */
#define SXS_ERESTART 739 /**< Interrupted system call should be restarted */
#define SXS_ESTRPIPE 740 /**< Streams pipe error */
#define SXS_EUCLEAN 741 /**< Structure needs cleaning */
#define SXS_ENOTNAM 742 /**< Not a XENIX named type file */
#define SXS_ENAVAIL 743 /**< No XENIX semaphores available */
#define SXS_EISNAM 744 /**< Is a named type file */
#define SXS_EREMOTEIO 745 /**< Remote I/O error */
#define SXS_ENOMEDIUM 746 /**< No medium found */
#define SXS_EMEDIUMTYPE 747 /**< Wrong medium type */
#define SXS_ENOKEY 748 /**< Required key not available */
#define SXS_EKEYEXPIRED 749 /**< Key has expired */
#define SXS_EKEYREVOKED 750 /**< Key has been revoked */
#define SXS_EKEYREJECTED 751 /**< Key was rejected by service */
#define SXS_EOWNERDEAD 752 /**< Owner died */
#define SXS_ENOTRECOVERABLE 753 /**< State not recoverable */
#ifndef WIN32
extern sxs_int32_t sxs_unix_errmap[86];
#endif


#endif
