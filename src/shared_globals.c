#include "config.h"
#include "shared_globals.h"

int global_argc, multi_argc = 0;
CARGV global_argv, multi_argv = NULL;
const char *const Version = VERSION;
DWORD VLActivationInterval = 60 * 2;   // 2 hours
DWORD VLRenewalInterval = 60 * 24 * 7; // 7 days
int_fast8_t DisconnectImmediately = FALSE;
const char *const cIPv4 = "IPv4";
const char *const cIPv6 = "IPv6";

#ifdef IS_LIBRARY
char ErrorMessage[MESSAGE_BUFFER_SIZE];
#endif // IS_LIBRARY

#ifndef NO_STRICT_MODES
uint32_t WhitelistingLevel = 0;
int_fast8_t CheckClientTime = FALSE;
#ifndef NO_CLIENT_LIST
int_fast8_t MaintainClients = FALSE;
int_fast8_t StartEmpty = FALSE;
#endif // NO_CLIENT_LIST
#endif // !NO_STRICT_MODES

#ifndef USE_MSRPC
int_fast8_t UseMultiplexedRpc = TRUE;
#ifndef SIMPLE_RPC
int_fast8_t UseServerRpcNDR64 = TRUE;
int_fast8_t UseServerRpcBTFN = TRUE;
#endif // !SIMPLE_RPC
int_fast8_t UseClientRpcNDR64 = TRUE;
int_fast8_t UseClientRpcBTFN = TRUE;
#endif // USE_MSRPC

#ifndef NO_SOCKETS
char *defaultport = (char*)"1688";
#endif // NO_SOCKETS

#if !defined(NO_PRIVATE_IP_DETECT)
uint32_t PublicIPProtectionLevel = 0;
#endif

#if !defined(NO_RANDOM_EPID) || !defined(NO_CL_PIDS) || !defined(NO_INI_FILE)
KmsResponseParam_t* KmsResponseParameters;
#endif // !defined(NO_RANDOM_EPID) || !defined(NO_CL_PIDS) || !defined(NO_INI_FILE)

#if !defined(NO_SOCKETS) && !defined(NO_SIGHUP)
int_fast8_t IsRestarted = FALSE;
#endif // !defined(NO_SOCKETS) && !defined(NO_SIGHUP)

#if !defined(NO_TIMEOUT)
DWORD ServerTimeout = 30;
#endif // !defined(NO_TIMEOUT)

#if !defined (NO_SOCKETS)
#ifdef USE_MSRPC
uint32_t MaxTasks = RPC_C_LISTEN_MAX_CALLS_DEFAULT;
#else // !USE_MSRPC
uint32_t MaxTasks = SEM_VALUE_MAX;
#endif // !USE_MSRPC
#endif // !defined (NO_SOCKETS)

#ifndef NO_LOG
int_fast8_t LogDateAndTime = TRUE;
char *fn_log = NULL;
int_fast8_t logstdout = 0;
#ifndef NO_VERBOSE_LOG
int_fast8_t logverbose = 0;
#endif // NO_VERBOSE_LOG
#endif // NO_LOG

#ifndef NO_SOCKETS
int_fast8_t ExitLevel = 0;
int_fast8_t nodaemon = 0;
int_fast8_t InetdMode = 0;
#else
int_fast8_t nodaemon = 1;
int_fast8_t InetdMode = 1;
#endif // NO_SOCKETS

PVlmcsdHeader_t KmsData = NULL;
#ifndef NO_EXTERNAL_DATA
#ifndef DATA_FILE
char *fn_data = NULL;
#else // DATA_FILE
char *fn_data = DATA_FILE;
#endif // DATA_FILE
#ifndef NO_INTERNAL_DATA
int_fast8_t ExplicitDataLoad = FALSE;
#endif // NO_INTERNAL_DATA
#endif // NO_EXTERNAL_DATA
const char *fn_exe = NULL;

#ifndef NO_RANDOM_EPID
int_fast8_t RandomizationLevel = 1;
uint16_t Lcid = 0;
uint16_t HostBuild = 0;
#endif

#if !defined(USE_MSRPC) && !defined(SIMPLE_RPC)
uint8_t IsNDR64Defined = FALSE;
#endif // !defined(USE_MSRPC) && !defined(SIMPLE_RPC)


#if !defined(NO_SOCKETS) && !defined(USE_MSRPC)
#ifdef SIMPLE_SOCKETS
SOCKET s_server;
#else
SOCKET *SocketList;
int numsockets = 0;
#endif

sem_t *MaxTaskSemaphore; // Posix
#endif // !defined(NO_SOCKETS) && !defined(USE_MSRPC)

#ifdef _NTSERVICE
int_fast8_t IsNTService = TRUE;
int_fast8_t ServiceShutdown = FALSE;
#endif // _NTSERVICE

#ifndef NO_LOG
#ifdef USE_THREADS
pthread_mutex_t logmutex = PTHREAD_MUTEX_INITIALIZER;
#endif // USE_THREADS
#endif // NO_LOG

#if HAVE_FREEBIND
int_fast8_t freebind = FALSE;
#endif // HAVE_FREEBIND


