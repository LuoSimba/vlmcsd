# call make from parent directory.
#
# compiler language: c
# target platform:   linux
################################################################################

.PHONY: clean

PROGRAM_NAME ?= ../bin/vlmcsd
CLIENT_NAME ?= ../bin/vlmcs
MULTI_NAME ?= ../bin/vlmcsdmulti
OBJ_NAME ?= ../build/libkms-static.o
A_NAME ?= ../lib/libkms.a

# Always from parent.
FROM_PARENT := 1

ifeq (1,$(FROM_PARENT))

  CLIENT_NAME_TEST=$(patsubst /%,/,$(CLIENT_NAME))
  MULTI_NAME_TEST=$(patsubst /%,/,$(MULTI_NAME))
  DLL_NAME_TEST=$(patsubst /%,/,$(DLL_NAME))
  A_NAME_TEST=$(patsubst /%,/,$(A_NAME))
  PROGRAM_NAME_TEST=$(patsubst /%,/,$(PROGRAM_NAME))

  ifneq (/,$(PROGRAM_NAME_TEST))
    PROGRAM_PREFIX=../
  endif

  ifneq (/,$(CLIENT_NAME_TEST))
    CLIENT_PREFIX=../
  endif

  ifneq (/,$(MULTI_NAME_TEST))
    MULTI_PREFIX=../
  endif

  ifneq (/,$(DLL_NAME_TEST))
    DLL_PREFIX=../
  endif

  ifneq (/,$(A_NAME_TEST))
    A_PREFIX=../
  endif

endif

REAL_PROGRAM_NAME=$(PROGRAM_PREFIX)$(PROGRAM_NAME)
REAL_CLIENT_NAME=$(CLIENT_PREFIX)$(CLIENT_NAME)
REAL_MULTI_NAME=$(MULTI_PREFIX)$(MULTI_NAME)
REAL_DLL_NAME=$(DLL_PREFIX)$(DLL_NAME)
REAL_A_NAME=$(A_PREFIX)$(A_NAME)


# crypto library to use for standard algos, could save ~1-2kb ;)
# can be either 'openssl', 'polarssl' or anything other for internal impl
CRYPTO ?= internal

# use DNS_PARSER=internal if your OS doesn't supply the DNS parser routines
DNS_PARSER ?= OS


FEATURES ?= full
VERBOSE ?= NO

################################################################################

CC ?= gcc

# show current platform:
#PLATFORM := $(shell LANG=en_US.UTF-8 $(CC) -v 2>&1 | grep '^Target: ' | cut -f 2 -d ' ')


DLL_NAME ?= ../lib/libkms.so


BASECFLAGS = -DVLMCSD_COMPILER=\"$(CC)\" -DVLMCSD_PLATFORM=\"i486-linux-gnu\" -DCONFIG=\"config.h\" -DBUILD_TIME=$(shell date '+%s') -g -Os -fno-strict-aliasing -fomit-frame-pointer -ffunction-sections -fdata-sections
BASELDFLAGS = 
STRIPFLAGS =
CLIENTLDFLAGS =
SERVERLDFLAGS =

ifndef SAFE_MODE
  BASECFLAGS += -fvisibility=hidden -pipe -fno-common -fno-exceptions -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fmerge-all-constants
  
  BASELDFLAGS += -Wl,-z,norelro

# ABOUT -flto
#
# -------------------------------------------------------
# GCC 10.2 Manual
# 3. GCC Command Options
# 3.11 Options That Control Optimization
#
#  -flto[=n]
#
#   This option runs the standard link-time optimizer.
# -------------------------------------------------------
#
# BUT -- My gcc version is 4.4.1, and not support this option.
# this option is introduced after version 4.4.7
  #BASECFLAGS += -flto

endif

PICFLAGS += -fPIC

ifeq ($(NOLIBS),1)
  NOLRESOLV=1
  NOLPTHREAD=1
endif

ifneq ($(NO_DNS),1)
  ifneq ($(NOLRESOLV),1)
      CLIENTLDFLAGS += -lresolv
  endif
else
  BASECFLAGS += -DNO_DNS
endif 

ifneq ($(CAT),2)
  BASECFLAGS += "-Wall"
endif  

BASELDFLAGS += -Wl,--gc-sections
STRIPFLAGS += -s

LIBRARY_CFLAGS = -DSIMPLE_SOCKETS -DNO_TIMEOUT -DNO_SIGHUP -DNO_CL_PIDS -DNO_LOG -DNO_RANDOM_EPID -DNO_INI_FILE -DNO_HELP -DNO_CUSTOM_INTERVALS -DNO_PID_FILE -DNO_USER_SWITCH -DNO_VERBOSE_LOG -DNO_LIMIT -DNO_VERSION_INFORMATION -DNO_PRIVATE_IP_DETECT -DNO_STRICT_MODES -DNO_CLIENT_LIST -DNO_TAP -UNO_SOCKETS -USIMPLE_RPC

ifeq ($(FEATURES), embedded)
  BASECFLAGS += -DNO_HELP -DNO_USER_SWITCH -DNO_CUSTOM_INTERVALS -DNO_PID_FILE -DNO_VERBOSE_LOG -DNO_VERSION_INFORMATION
else ifeq ($(FEATURES), autostart)
  BASECFLAGS += -DNO_HELP -DNO_VERSION_INFORMATION
else ifeq ($(FEATURES), minimum)
  BASECFLAGS += -DSIMPLE_RPC -DSIMPLE_SOCKETS -DNO_TIMEOUT -DNO_SIGHUP -DNO_CL_PIDS -DNO_LOG -DNO_RANDOM_EPID -DNO_INI_FILE -DNO_HELP -DNO_CUSTOM_INTERVALS -DNO_PID_FILE -DNO_USER_SWITCH -DNO_VERBOSE_LOG -DNO_LIMIT -DNO_VERSION_INFORMATION -DNO_PRIVATE_IP_DETECT -DSMALL_AES -DNO_STRICT_MODES -DNO_TAP -DNO_CLIENT_LIST -DUNSAFE_DATA_LOAD -DNO_EXTERNAL_DATA -UFULL_INTERNAL_DATA -U_PEDANTIC
else ifeq ($(FEATURES), most)
  BASECFLAGS += -DNO_SIGHUP -DNO_PID_FILE -DNO_LIMIT
else ifeq ($(FEATURES), inetd)
  BASECFLAGS += -DNO_SIGHUP -DNO_SOCKETS -DNO_PID_FILE -DNO_LIMIT -DNO_VERSION_INFORMATION
else ifeq ($(FEATURES), fixedepids)
  BASECFLAGS += -DNO_SIGHUP -DNO_CL_PIDS -DNO_RANDOM_EPID -DNO_INI_FILE
endif

ifdef INI
  BASECFLAGS += -DINI_FILE=\"$(INI)\"
endif

ifdef DATA
  BASECFLAGS += -DDATA_FILE=\"$(DATA)\"
endif

ifeq ($(NO_GETIFADDRS), 1)
  BASECFLAGS += -DNO_GETIFADDRS
endif

ifeq ($(THREADS), 1)
  BASECFLAGS += -DUSE_THREADS
endif

ifeq ($(CHILD_HANDLER), 1)
  BASECFLAGS += -DCHILD_HANDLER
endif

ifeq ($(NO_TIMEOUT), 1)
  BASECFLAGS += -DNO_TIMEOUT
endif

ifdef WINDOWS
  BASECFLAGS += -DEPID_WINDOWS=\"$(WINDOWS)\"
endif

ifdef OFFICE2010
  BASECFLAGS += -DEPID_OFFICE2010=\"$(OFFICE2010)\"
endif

ifdef OFFICE2013
  BASECFLAGS += -DEPID_OFFICE2013=\"$(OFFICE2013)\"
endif

ifdef OFFICE2016
  BASECFLAGS += -DEPID_OFFICE2016=\"$(OFFICE2016)\"
endif

ifdef HWID
  BASECFLAGS += -DHWID=$(HWID)
endif

ifdef TERMINAL_WIDTH
  BASECFLAGS += -DTERMINAL_FIXED_WIDTH=$(TERMINAL_WIDTH) -DDISPLAY_WIDTH=\"$(TERMINAL_WIDTH)\"
endif

ifeq ($(NOPROCFS), 1)
  BASECFLAGS += -DNO_PROCFS
endif

ifeq ($(AUXV), 1)
  BASECFLAGS += -DUSE_AUXV
endif

ifneq ($(NOLPTHREAD), 1)
  ifeq ($(THREADS), 1)
    SERVERLDFLAGS += -lpthread
  endif
  
  ifeq (,$(findstring NO_LIMIT,$(CFLAGS) $(BASECFLAGS)))  
    SERVERLDFLAGS += -lpthread
  endif
endif

$(REAL_MULTI_NAME): BASECFLAGS += -DMULTI_CALL_BINARY=1

all: $(REAL_CLIENT_NAME) $(REAL_PROGRAM_NAME)

allmulti: $(REAL_CLIENT_NAME) $(REAL_PROGRAM_NAME) $(REAL_MULTI_NAME)

vlmcsd: $(REAL_PROGRAM_NAME)
	+@true

vlmcs: $(REAL_CLIENT_NAME)
	+@true

vlmcsdmulti: $(REAL_MULTI_NAME)
	+@true

libkms: $(REAL_DLL_NAME)
	+@true

libkms-static: $(REAL_A_NAME)

# add vlmcsd version
BASECFLAGS += -DVERSION=\"my-private,\ built\ $(shell date -u '+%Y-%m-%d %H:%M:%S' | sed -e 's/ /\\ /g')\ UTC\" 

ifdef CAT
  BASECFLAGS += -DONE_FILE
endif

# Common source files.
SRCS = crypto.c kms.c endian.c output.c shared_globals.c helpers.c

HEADERS = config.h types.h rpc.h vlmcsd.h endian.h crypto.h kms.h network.h output.h shared_globals.h vlmcs.h helpers.h kmsdata.h
DEPS = $(patsubst %,../build/%,$(MULTI_SRCS:.c=.d))

# Source files for KMS server.
VLMCSD_SRCS = vlmcsd.c kmsdata.c $(SRCS)
# Object files for KMS server.
VLMCSD_OBJS = $(patsubst %,../build/%,$(VLMCSD_SRCS:.c=.o))

VLMCS_SRCS = vlmcs.c kmsdata-full.c $(SRCS)
VLMCS_OBJS = $(patsubst %,../build/%,$(VLMCS_SRCS:.c=.o))

MULTI_SRCS = vlmcsd.c vlmcs.c vlmcsdmulti.c kmsdata-full.c $(SRCS)
MULTI_OBJS = $(patsubst %,../build/%,$(SRCS:.c=.o)) ../build/kmsdata-full.o ../build/vlmcsd-m.o ../build/vlmcs-m.o ../build/vlmcsdmulti-m.o

DLL_SRCS = libkms.c vlmcs.c $(SRCS)
DLL_OBJS = $(patsubst %,../build/%,$(DLL_SRCS:.c=-l.o))
A_OBJS = $(patsubst %,../build/%,$(DLL_SRCS:.c=-a.o))

PDFDOCS = vlmcs.1.pdf vlmcsd.7.pdf vlmcsd.8.pdf vlmcsdmulti.1.pdf vlmcsd.ini.5.pdf vlmcsd-floppy.7.pdf
HTMLDOCS = $(PDFDOCS:.pdf=.html)
UNIXDOCS = $(PDFDOCS:.pdf=.unix.txt)
DOSDOCS = $(PDFDOCS:.pdf=.dos.txt)

ifneq ($(NO_DNS),1)

  VLMCS_SRCS += dns_srv.c
  MULTI_SRCS += dns_srv.c
  MULTI_OBJS += ../build/dns_srv.o

ifeq ($(DNS_PARSER),internal)
  VLMCS_SRCS += ns_parse.c ns_name.c
  MULTI_SRCS += ns_parse.c ns_name.c
  MULTI_OBJS += ../build/ns_parse.o ../build/ns_name.o
  BASECFLAGS += "-DDNS_PARSER_INTERNAL"
endif

endif

ifeq ($(MSRPC),1)
  VLMCSD_SRCS += msrpc-server.c
  VLMCS_SRCS += msrpc-client.c
  MULTI_SRCS += msrpc-server.c msrpc-client.c
  MULTI_OBJS += ../build/msrpc-server-m.o ../build/msrpc-client-m.o
  DLL_SRCS += msrpc-server.c
  BASECFLAGS += -DUSE_MSRPC -Wno-unknown-pragmas
  BASELDFLAGS += -lrpcrt4
else
  SRCS += network.c rpc.c  
endif

ifeq ($(GETIFADDRS),musl)
ifneq ($(NO_GETIFADDRS),1)
  BASECFLAGS += -DGETIFADDRS_MUSL
  VLMCSD_SRCS += getifaddrs-musl.c
  MULTI_SRCS += getifaddrs-musl.c
  VLMCS_SRCS += getifaddrs-musl.c
  DLL_SRCS += getifaddrs-musl.c
  MULTI_OBJS += ../build/getifaddrs-musl.o
endif
endif

# Android
#ifneq ($(NO_GETIFADDRS),1)
#  VLMCSD_SRCS += ifaddrs-android.c
#  MULTI_SRCS += ifaddrs-android.c
#  DLL_SRCS += ifaddrs-android.c
#  MULTI_OBJS += ../build/ifaddrs-android.o
#endif

# MinGW & Cygwin
# VLMCSD_SRCS += ntservice.c wintap.c
# MULTI_SRCS += ntservice.c wintap.c
# MULTI_OBJS += ../build/ntservice.o ../build/wintap.o

ifeq ($(CRYPTO), openssl_with_aes)
	BASECFLAGS += -D_CRYPTO_OPENSSL -D_USE_AES_FROM_OPENSSL
	BASELDFLAGS += -lcrypto
	SRCS += crypto_openssl.c
else ifeq ($(CRYPTO), openssl_with_aes_soft)
	BASECFLAGS += -D_CRYPTO_OPENSSL -D_USE_AES_FROM_OPENSSL -D_OPENSSL_SOFTWARE
	BASELDFLAGS += -lcrypto
	SRCS += crypto_openssl.c
else ifeq ($(CRYPTO), openssl)
	BASECFLAGS += -D_CRYPTO_OPENSSL
	BASELDFLAGS += -lcrypto
	SRCS += crypto_openssl.c
else ifeq ($(CRYPTO), polarssl)
	BASECFLAGS += -D_CRYPTO_POLARSSL
	BASELDFLAGS += -lpolarssl
else ifeq ($(CRYPTO), windows)
	BASECFLAGS += -D_CRYPTO_WINDOWS
	SRCS += crypto_windows.c
else
	BASECFLAGS += -D_CRYPTO_INTERNAL
	SRCS += crypto_internal.c
endif

ifneq ($(STRIP),0)
	BASELDFLAGS += $(STRIPFLAGS)
endif

ifeq ($(OPENSSL_HMAC),0)
	BASECFLAGS += -D_OPENSSL_NO_HMAC
endif

ifeq ($(DEPENDENCIES),2)
    BASECFLAGS += -MMD
endif

ifeq ($(VERBOSE),3)
    COMPILER := $(shell printf "%-40s" $(CC))
    ARCHIVER := $(shell printf "%-40s" $(notdir $(AR)))
endif

ifdef CAT
    LDCMD := CC/LD
else
    LDCMD := LD    
endif

-include $(MULTI_SRCS:.c=.d)

../build/%.o: %.c 
  ifeq ($(VERBOSE),1)
	+$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) -c $< -o $@
  ifeq ($(DEPENDENCIES),1)
	+$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) -MM -MF $*.d $< -MT $@
  endif
  else
	+@echo "$(COMPILER)	CC	$(notdir $@) <- $<"
	+@$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) -c $< -o $@
  ifeq ($(DEPENDENCIES),1)
	+@echo "$(COMPILER)	DEP	$*.d <- $<"
	+@$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) -MM -MF $*.d $< -MT $@
  endif
  endif

../build/%-m.o: %.c
  ifeq ($(VERBOSE),1)
	+$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) -o $@ -c $<
  ifeq ($(DEPENDENCIES),1)
	+$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) -MM -MF $*.d $< -MT $@
  endif
  else
	+@echo "$(COMPILER)	CC	$(notdir $@) <- $<"
	+@$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) -o $@ -c $<
  ifeq ($(DEPENDENCIES),1)
	+@echo "$(COMPILER)	DEP	$*.d <- $<"
	+@$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) -MM -MF $*.d $< -MT $@
  endif
  endif

../build/%-a.o: %.c
  ifeq ($(VERBOSE),1)
	+$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -o $@ -c $<
  ifeq ($(DEPENDENCIES),1)
	+$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -MM -MF $*.d $<
  endif
  else
	+@echo "$(COMPILER)	CC	$(notdir $@) <- $<"
	+@$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -o $@ -c $<
  ifeq ($(DEPENDENCIES),1)
	+@echo "$(COMPILER)	DEP	$*.d <- $<"
	+@$(CC) -xc $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -MM -MF $*.d $<
  endif
  endif

../build/%-l.o: %.c
  ifeq ($(VERBOSE),1)
	+$(CC) -xc $(PICFLAGS) $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -o $@ -c $<
  ifeq ($(DEPENDENCIES),1)
	+$(CC) -xc $(PICFLAGS) $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -MM -MF $*.d $<
  endif
  else
	+@echo "$(COMPILER)	CC	$(notdir $@) <- $<"
	+@$(CC) -xc $(PICFLAGS) $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -o $@ -c $<
  ifeq ($(DEPENDENCIES),1)
	+@echo "$(COMPILER)	DEP	$*.d <- $<"
	+@$(CC) -xc $(PICFLAGS) $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(PLATFORMFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -MM -MF $*.d $<
  endif
  endif


ifdef CAT
  BUILDCOMMAND = cat $^ | $(CC) -xc -o $@ -
  VLMCSD_PREREQUISITES = $(VLMCSD_SRCS)
  VLMCS_PREREQUISITES = $(VLMCS_SRCS)
  MULTI_PREREQUISITES = $(MULTI_SRCS)
  DLL_PREREQUISITES = $(DLL_SRCS)
  OBJ_PREREQUISITES = $(DLL_SRCS)
  A_PREREQUISITES = $(DLL_SRCS)
else
  BUILDCOMMAND = $(CC) -o $@ $^
  VLMCSD_PREREQUISITES = $(VLMCSD_OBJS)
  VLMCS_PREREQUISITES = $(VLMCS_OBJS)
  MULTI_PREREQUISITES = $(MULTI_OBJS)
  DLL_PREREQUISITES = $(DLL_OBJS)
  OBJ_PREREQUISITES = $(A_OBJS)
  A_PREREQUISITES = $(A_OBJS)
endif

ifeq ($(VERBOSE),1)
  BUILDCOMMANDPREFIX = +
else
  BUILDCOMMANDPREFIX = +@
endif

INFOCOMMAND = +@echo "$(COMPILER)	$(LDCMD)	$@ <- $(notdir $^)"
ARINFOCOMMAND = +@echo "$(ARCHIVER)	AR      	$@ <. $(notdir $^)"

VLMCS_COMMAND = $(BUILDCOMMANDPREFIX)$(BUILDCOMMAND) $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(BASELDFLAGS) $(LDFLAGS) $(CLIENTLDFLAGS)
MULTI_COMMAND = $(BUILDCOMMANDPREFIX)$(BUILDCOMMAND) $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(BASELDFLAGS) $(LDFLAGS) $(CLIENTLDFLAGS) $(SERVERLDFLAGS)
DLL_COMMAND = $(BUILDCOMMANDPREFIX)$(BUILDCOMMAND) $(PICFLAGS) $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(BASELDFLAGS) $(LDFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -shared -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC
OBJ_COMMAND = $(BUILDCOMMANDPREFIX)$(BUILDCOMMAND) $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(BASELDFLAGS) $(LDFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC
  

# Rules for KMS server.
$(REAL_PROGRAM_NAME): $(VLMCSD_PREREQUISITES)
  ifneq ($(VERBOSE),1)
	$(INFOCOMMAND)
  endif
	$(BUILDCOMMANDPREFIX)$(BUILDCOMMAND) $(PLATFORMFLAGS) $(BASECFLAGS) $(CFLAGS) $(BASELDFLAGS) $(LDFLAGS) $(SERVERLDFLAGS)

$(REAL_CLIENT_NAME): $(VLMCS_PREREQUISITES)
  ifneq ($(VERBOSE),1)
	$(INFOCOMMAND)
  endif
	$(VLMCS_COMMAND)

$(REAL_MULTI_NAME): $(MULTI_PREREQUISITES)
  ifneq ($(VERBOSE),1)
	$(INFOCOMMAND)
  endif
	$(MULTI_COMMAND)

$(REAL_DLL_NAME): $(DLL_PREREQUISITES)
  ifneq ($(VERBOSE),1)
	$(INFOCOMMAND)
  endif
	$(DLL_COMMAND)

ifndef CAT
$(OBJ_NAME):
	+@echo Cannot make $@ without CAT defined. Please create $(A_NAME)
else
$(OBJ_NAME): $(OBJ_PREREQUISITES)
  ifneq ($(VERBOSE),1)
	$(INFOCOMMAND)
  endif
	$(OBJ_COMMAND)
endif

ifdef CAT
$(REAL_A_NAME): $(OBJ_NAME)
else
$(REAL_A_NAME): BASECFLAGS += -fvisibility=hidden -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC
$(REAL_A_NAME): $(A_OBJS)
endif
  ifneq ($(VERBOSE),1)
	$(ARINFOCOMMAND)
  endif
	+@rm -f $@
	$(BUILDCOMMANDPREFIX)$(AR) rcs $@ $^

clean:
	rm -f $(REAL_PROGRAM_NAME) $(REAL_MULTI_NAME) $(REAL_DLL_NAME) $(REAL_CLIENT_NAME)  $(OBJ_NAME) $(REAL_A_NAME) ../bin/* ../build/* *.d

dnsclean:
	rm -f ../build/dns_srv.o


# shell command: realpath `pwd`/..
