#ifndef INCLUDED_SHARED_GLOBALS_H
#define INCLUDED_SHARED_GLOBALS_H

#include "config.h"

#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pwd.h>
#include <grp.h>
#include <syslog.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#if !defined(NO_LIMIT)
#include <semaphore.h>
#endif // !defined(NO_LIMIT)


#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <ctype.h>
#include <stdarg.h>
//#include <semaphore.h>
#include "types.h"
#include "kms.h"

//#define MIN_CSVLK 6
typedef struct
{
	const char* Epid;
	const BYTE* HwId;
	#ifndef NO_LOG
	const char* EpidSource;
	uint8_t IsRandom;
	#endif // NO_LOG
} KmsResponseParam_t, *PKmsResponseParam_t;

typedef struct
{
	int8_t HasRpcDiag;
	int8_t HasBTFN;
	int8_t HasNDR64;
} RpcDiag_t, *PRpcDiag_t;

#if !defined(NO_LIMIT)
# ifndef SEM_VALUE_MAX // Android does not define this
#   define SEM_VALUE_MAX 0x7fff // Be cautious if unknown
# endif // !defined(SEM_VALUE_MAX)
#endif // !defined(NO_LIMIT)

extern const char *const Version;

//Fix for stupid eclipse parser
#ifndef UINT_MAX
#define UINT_MAX 4294967295
#endif

#define MESSAGE_BUFFER_SIZE 4096
#ifdef IS_LIBRARY
extern char ErrorMessage[MESSAGE_BUFFER_SIZE];
#endif // IS_LIBRARY


extern int global_argc, multi_argc;
extern CARGV global_argv, multi_argv;
extern int_fast8_t nodaemon;
extern DWORD VLActivationInterval;
extern DWORD VLRenewalInterval;
extern int_fast8_t DisconnectImmediately;

#if !defined(NO_RANDOM_EPID) || !defined(NO_CL_PIDS) || !defined(NO_INI_FILE)
extern KmsResponseParam_t* KmsResponseParameters;
#endif // !defined(NO_RANDOM_EPID) || !defined(NO_CL_PIDS) || !defined(NO_INI_FILE)

extern const char *const cIPv4;
extern const char *const cIPv6;
extern int_fast8_t InetdMode;
extern PVlmcsdHeader_t KmsData;
#ifndef NO_EXTERNAL_DATA
extern char* fn_data;
#ifndef NO_INTERNAL_DATA
extern int_fast8_t ExplicitDataLoad;
#endif // NO_INTERNAL_DATA
#endif // NO_EXTERNAL_DATA
extern const char* fn_exe;

#ifndef NO_STRICT_MODES
extern uint32_t WhitelistingLevel;
extern int_fast8_t CheckClientTime;
#ifndef NO_CLIENT_LIST
extern int_fast8_t MaintainClients;
extern int_fast8_t StartEmpty;
#endif // NO_CLIENT_LIST
#endif // !NO_STRICT_MODES


#ifndef USE_MSRPC
extern int_fast8_t UseMultiplexedRpc;
#ifndef SIMPLE_RPC
extern int_fast8_t UseServerRpcNDR64;
extern int_fast8_t UseServerRpcBTFN;
#endif // !SIMPLE_RPC
extern int_fast8_t UseClientRpcNDR64;
extern int_fast8_t UseClientRpcBTFN;
#endif // USE_MSRPC

#ifndef NO_SOCKETS
extern int_fast8_t ExitLevel;
extern char *defaultport;
#endif // NO_SOCKETS

#if !defined(NO_PRIVATE_IP_DETECT)
extern uint32_t PublicIPProtectionLevel;
#endif

#if !defined(NO_SOCKETS) && !defined(NO_SIGHUP)
extern int_fast8_t IsRestarted;
#endif // !defined(NO_SOCKETS) && !defined(NO_SIGHUP)

#if !defined(NO_TIMEOUT)
extern DWORD ServerTimeout;
#endif // !defined(NO_TIMEOUT)

#if !defined(NO_LIMIT) && !defined (NO_SOCKETS)
extern uint32_t MaxTasks;
#endif // !defined(NO_LIMIT) && !defined (NO_SOCKETS)

#ifndef NO_LOG
extern int_fast8_t LogDateAndTime;
extern char *fn_log;
extern int_fast8_t logstdout;
#ifndef NO_VERBOSE_LOG
extern int_fast8_t logverbose;
#endif
#endif

#if !defined(USE_MSRPC) && !defined(SIMPLE_RPC)
extern uint8_t IsNDR64Defined;
#endif 

#ifndef NO_RANDOM_EPID
extern int_fast8_t RandomizationLevel;
extern uint16_t Lcid;
extern uint16_t HostBuild;
#endif

#if !defined(NO_SOCKETS) && !defined(USE_MSRPC)
#if defined(SIMPLE_SOCKETS)
extern SOCKET s_server;
#else // !defined(SIMPLE_SOCKETS)
extern SOCKET *SocketList;
extern int numsockets;
#endif // !defined(SIMPLE_SOCKETS)

#if !defined(NO_LIMIT)
extern sem_t *MaxTaskSemaphore;
#endif // !defined(NO_LIMIT)

#endif // !defined(NO_SOCKETS) && !defined(USE_MSRPC)

#ifdef _NTSERVICE
extern int_fast8_t IsNTService;
extern int_fast8_t ServiceShutdown;
#endif

#ifndef NO_LOG
#ifdef USE_THREADS

extern pthread_mutex_t logmutex;

#endif // USE_THREADS
#endif // NO_LOG

#if HAVE_FREEBIND
extern int_fast8_t freebind;
#endif // HAVE_FREEBIND


#endif // INCLUDED_SHARED_GLOBALS_H
