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

.DEFAULT:
	+@(test -d bin || mkdir bin) & (test -d lib || mkdir lib) & (test -d build || mkdir build)
	+@$(MAKE) -j16 -C src $@

all:
	+@(test -d bin || mkdir bin) & (test -d lib || mkdir lib) & (test -d build || mkdir build)
	+@$(MAKE) -j16 -C src

clean:
	+@$(MAKE) -j16 -C src $@

