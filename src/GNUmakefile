#
# compiler language: c
# target platform:   linux
################################################################################

.PHONY: clean

OBJ_NAME := ../build/libkms-static.o


PROGRAM_NAME=../bin/vlmcsd
CLIENT_NAME=../bin/vlmcs
DLL_NAME=../lib/libkms.so
A_NAME=../lib/libkms.a


# crypto library to use for standard algos, could save ~1-2kb ;)
# can be either 'openssl', 'polarssl' or anything other for internal impl
CRYPTO ?= internal

# use DNS_PARSER=internal if your OS doesn't supply the DNS parser routines
DNS_PARSER ?= OS


#FEATURES := full
FEATURES := minimum
VERBOSE ?= NO

################################################################################

CC ?= gcc

# show current platform:
#PLATFORM := $(shell LANG=en_US.UTF-8 $(CC) -v 2>&1 | grep '^Target: ' | cut -f 2 -d ' ')




BASECFLAGS = -DBUILD_TIME=$(shell date '+%s') -g -Os -fno-strict-aliasing -fomit-frame-pointer -ffunction-sections -fdata-sections
BASELDFLAGS = 
CLIENTLDFLAGS =
SERVERLDFLAGS =

ifndef SAFE_MODE
  BASECFLAGS += -fvisibility=hidden -pipe -fno-common -fno-exceptions -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fmerge-all-constants
  
  BASELDFLAGS += -Wl,-z,norelro
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

LIBRARY_CFLAGS = -DSIMPLE_SOCKETS -DNO_TIMEOUT -DNO_SIGHUP -DNO_CL_PIDS -DNO_LOG -DNO_RANDOM_EPID -DNO_INI_FILE -DNO_HELP -DNO_CUSTOM_INTERVALS -DNO_PID_FILE -DNO_USER_SWITCH -DNO_VERBOSE_LOG -DNO_VERSION_INFORMATION -DNO_PRIVATE_IP_DETECT -DNO_STRICT_MODES -DNO_CLIENT_LIST -DNO_TAP -UNO_SOCKETS -USIMPLE_RPC

ifeq ($(FEATURES), embedded)
  BASECFLAGS += -DNO_USER_SWITCH -DNO_CUSTOM_INTERVALS -DNO_PID_FILE -DNO_VERBOSE_LOG -DNO_VERSION_INFORMATION
else ifeq ($(FEATURES), autostart)
  BASECFLAGS +=  -DNO_VERSION_INFORMATION
else ifeq ($(FEATURES), minimum)

  BASECFLAGS += -DSIMPLE_RPC \
				-DSIMPLE_SOCKETS \
				-DNO_TIMEOUT \
				-DNO_SIGHUP \
				-DNO_CL_PIDS \
				-DNO_LOG \
				-DNO_RANDOM_EPID \
				-DNO_INI_FILE \
				-DNO_CUSTOM_INTERVALS \
				-DNO_PID_FILE \
				-DNO_USER_SWITCH \
				-DNO_VERBOSE_LOG \
				-DNO_VERSION_INFORMATION \
				-DNO_PRIVATE_IP_DETECT \
				-DSMALL_AES \
				-DNO_STRICT_MODES \
				-DNO_TAP \
				-DNO_CLIENT_LIST \
				-DUNSAFE_DATA_LOAD \
				-DNO_INTERNAL_DATA \
				-DNO_HELP \
				-U_PEDANTIC
				#-DNO_EXTERNAL_DATA \

else ifeq ($(FEATURES), most)
  BASECFLAGS += -DNO_SIGHUP -DNO_PID_FILE 
else ifeq ($(FEATURES), inetd)
  BASECFLAGS += -DNO_SIGHUP -DNO_SOCKETS -DNO_PID_FILE -DNO_VERSION_INFORMATION
else ifeq ($(FEATURES), fixedepids)
  BASECFLAGS += -DNO_SIGHUP -DNO_CL_PIDS -DNO_RANDOM_EPID -DNO_INI_FILE
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
  
  SERVERLDFLAGS += -lpthread
endif


# default
vlmcsd: $(PROGRAM_NAME)
	+@true

vlmcs: $(CLIENT_NAME)
	+@true

libkms: $(DLL_NAME)
	+@true

libkms-static: $(A_NAME)

# add vlmcsd version
BASECFLAGS += -DVERSION=\"private-version,\ $(shell date -u '+%Y-%m-%d %H:%M' | sed -e 's/ /\\ /g')\ UTC\" 

ifdef CAT
  BASECFLAGS += -DONE_FILE
endif

# Common source files.
SRCS = crypto.c \
	   kms.c \
	   endian.c \
	   output.c \
	   shared_globals.c \
	   helpers.c

HEADERS = config.h \
		  types.h \
		  rpc.h \
		  vlmcsd.h \
		  endian.h \
		  crypto.h \
		  kms.h \
		  network.h \
		  output.h \
		  shared_globals.h \
		  vlmcs.h \
		  helpers.h \
		  kmsdata.h

## what's this??
##DEPS = $(patsubst %,../build/%,$(MULTI_SRCS:.c=.d))

# Source files for KMS server.
VLMCSD_SRCS = vlmcsd.c kmsdata.c $(SRCS)

# Source files for KMS client.
VLMCS_SRCS = vlmcs.c kmsdata-full.c $(SRCS)
VLMCS_OBJS = $(patsubst %,../build/%,$(VLMCS_SRCS:.c=.o))

DLL_SRCS = libkms.c vlmcs.c $(SRCS)
DLL_OBJS = $(patsubst %,../build/%,$(DLL_SRCS:.c=-l.o))
A_OBJS = $(patsubst %,../build/%,$(DLL_SRCS:.c=-a.o))


ifneq ($(NO_DNS),1)

  VLMCS_SRCS += dns_srv.c

ifeq ($(DNS_PARSER),internal)
  VLMCS_SRCS += ns_parse.c ns_name.c
  BASECFLAGS += "-DDNS_PARSER_INTERNAL"
endif

endif

ifeq ($(MSRPC),1)
  VLMCSD_SRCS += msrpc-server.c
  VLMCS_SRCS += msrpc-client.c
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
  VLMCS_SRCS += getifaddrs-musl.c
  DLL_SRCS += getifaddrs-musl.c
endif
endif

# Android
#ifneq ($(NO_GETIFADDRS),1)
#  VLMCSD_SRCS += ifaddrs-android.c
#  DLL_SRCS += ifaddrs-android.c
#endif

# MinGW & Cygwin
# VLMCSD_SRCS += ntservice.c wintap.c

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
	SRCS += crypto_internal.c
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

## what's this??
##-include $(MULTI_SRCS:.c=.d)


# Object files
../build/%.o: %.c 
  ifeq ($(VERBOSE),1)
	+$(CC) -xc  $(BASECFLAGS) $(CFLAGS)  -c $< -o $@
  ifeq ($(DEPENDENCIES),1)
	+$(CC) -xc  $(BASECFLAGS) $(CFLAGS)  -MM -MF $*.d $< -MT $@
  endif
  else
	+@echo "$(COMPILER)	CC	$(notdir $@) <- $<"
	+@$(CC) -xc  $(BASECFLAGS) $(CFLAGS)  -c $< -o $@
  ifeq ($(DEPENDENCIES),1)
	+@echo "$(COMPILER)	DEP	$*.d <- $<"
	+@$(CC) -xc  $(BASECFLAGS) $(CFLAGS)  -MM -MF $*.d $< -MT $@
  endif
  endif

../build/%-a.o: %.c
  ifeq ($(VERBOSE),1)
	+$(CC) -xc  $(BASECFLAGS) $(CFLAGS)  $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -o $@ -c $<
  ifeq ($(DEPENDENCIES),1)
	+$(CC) -xc  $(BASECFLAGS) $(CFLAGS)  $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -MM -MF $*.d $<
  endif
  else
	+@echo "$(COMPILER)	CC	$(notdir $@) <- $<"
	+@$(CC) -xc  $(BASECFLAGS) $(CFLAGS)  $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -o $@ -c $<
  ifeq ($(DEPENDENCIES),1)
	+@echo "$(COMPILER)	DEP	$*.d <- $<"
	+@$(CC) -xc  $(BASECFLAGS) $(CFLAGS)  $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -MM -MF $*.d $<
  endif
  endif

../build/%-l.o: %.c
  ifeq ($(VERBOSE),1)
	+$(CC) -xc $(PICFLAGS)  $(BASECFLAGS) $(CFLAGS)  $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -o $@ -c $<
  ifeq ($(DEPENDENCIES),1)
	+$(CC) -xc $(PICFLAGS)  $(BASECFLAGS) $(CFLAGS)  $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -MM -MF $*.d $<
  endif
  else
	+@echo "$(COMPILER)	CC	$(notdir $@) <- $<"
	+@$(CC) -xc $(PICFLAGS)  $(BASECFLAGS) $(CFLAGS)  $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -o $@ -c $<
  ifeq ($(DEPENDENCIES),1)
	+@echo "$(COMPILER)	DEP	$*.d <- $<"
	+@$(CC) -xc $(PICFLAGS)  $(BASECFLAGS) $(CFLAGS)  $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC -MM -MF $*.d $<
  endif
  endif


ifdef CAT
  BUILDCOMMAND = cat $^ | $(CC) -xc -o $@ -
  VLMCSD_PREREQUISITES = $(VLMCSD_SRCS)
  VLMCS_PREREQUISITES = $(VLMCS_SRCS)
  DLL_PREREQUISITES = $(DLL_SRCS)
  OBJ_PREREQUISITES = $(DLL_SRCS)
  A_PREREQUISITES = $(DLL_SRCS)
else
  BUILDCOMMAND = $(CC) -o $@ $^
  # Object files for KMS server.
  VLMCSD_PREREQUISITES = $(patsubst %,../build/%,$(VLMCSD_SRCS:.c=.o))
  VLMCS_PREREQUISITES = $(VLMCS_OBJS)
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


VLMCS_COMMAND = $(BUILDCOMMANDPREFIX)$(BUILDCOMMAND)  $(BASECFLAGS) $(CFLAGS) $(BASELDFLAGS) $(CLIENTLDFLAGS)
DLL_COMMAND = $(BUILDCOMMANDPREFIX)$(BUILDCOMMAND) $(PICFLAGS)  $(BASECFLAGS) $(CFLAGS) $(BASELDFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -shared -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC
OBJ_COMMAND = $(BUILDCOMMANDPREFIX)$(BUILDCOMMAND)  $(BASECFLAGS) $(CFLAGS) $(BASELDFLAGS) $(SERVERLDFLAGS) -fvisibility=hidden -c -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC


# KMS server.
$(PROGRAM_NAME): $(VLMCSD_PREREQUISITES)
	@echo "build $(PROGRAM_NAME)"
	+@echo "$(COMPILER)	$(LDCMD)	$@ <- $(notdir $^)"
	+@$(BUILDCOMMAND) $(BASECFLAGS) $(CFLAGS) $(BASELDFLAGS) $(SERVERLDFLAGS)

# KMS client
$(CLIENT_NAME): $(VLMCS_PREREQUISITES)
  ifneq ($(VERBOSE),1)
	$(INFOCOMMAND)
  endif
	$(VLMCS_COMMAND)


# lib
$(DLL_NAME): $(DLL_PREREQUISITES)
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
$(A_NAME): $(OBJ_NAME)
else
$(A_NAME): BASECFLAGS += -fvisibility=hidden -DIS_LIBRARY=1 $(LIBRARY_CFLAGS) -UNO_SOCKETS -UUSE_MSRPC
$(A_NAME): $(A_OBJS)
endif
  ifneq ($(VERBOSE),1)
	$(ARINFOCOMMAND)
  endif
	+@rm -f $@
	$(BUILDCOMMANDPREFIX)$(AR) rcs $@ $^

clean:
	rm -f $(PROGRAM_NAME) $(DLL_NAME) $(CLIENT_NAME)  $(OBJ_NAME) $(A_NAME) ../bin/* ../build/* *.d

dnsclean:
	rm -f ../build/dns_srv.o


# shell command: realpath `pwd`/..
