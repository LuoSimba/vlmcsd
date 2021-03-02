# Support gcc. Others may or may not work.
#
# Not Support: MinGW Cygwin Minix Solaris Darwin Hurd Android *BSD
#
# lib name:
# Cygwin: lib/cygkms.dll
# MinGW:  lib/libkms.dll
# Darwin: lib/libkms.dylib
#
.NOTPARALLEL:


# 只有 .DEFAULT all clean 三个才用到了 src 目录
.DEFAULT:
	+@(test -d bin || mkdir bin) & (test -d lib || mkdir lib) & (test -d build || mkdir build)
	+@$(MAKE) -j16 -C src $@

all:
	+@(test -d bin || mkdir bin) & (test -d lib || mkdir lib) & (test -d build || mkdir build)
	+@$(MAKE) -j16 -C src $@

clean:
	+@$(MAKE) -j16 -C src $@
	+@$(MAKE) -j16 -C man $@



# ========== DOCs ===========
alldocs:
	+@$(MAKE) -j16 -C man $@

dosdocs:
	+@$(MAKE) -j16 -C man $@

unixdocs:
	+@$(MAKE) -j16 -C man $@

htmldocs:
	+@$(MAKE) -j16 -C man $@

pdfdocs:
	+@$(MAKE) -j16 -C man $@

# ===========================



GNUmakefile:


