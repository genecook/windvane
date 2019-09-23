SRC_DIR  = src
OBJ_DIR  = obj
DEPS_DIR = depends

GPP = /usr/bin/g++
GCC = /usr/bin/cc
AR = /usr/bin/ar

# paths, etc, used by main Makefile...

PBJSON := ${HOME}/Downloads/pbjson-master

HALF_PRECISION := ${HOME}/Downloads/half-1.11.0

MY_LIBELF := ${HOME}/Downloads/elftoolchain-0.7.1

STATIC_LIBELF := ${MY_LIBELF}/libelf/libelf.a

LIBELF_INCLUDES := -I${MY_LIBELF}/libelf -I${MY_LIBELF}/common

STATIC_BOOSTLIB := /usr/local/lib/libboost_program_options.a

PROTOLIBDIRS := -L/usr/local/lib

STATIC_PROTOLIB := /usr/local/lib/libprotobuf.a


# 'core' cflags - common to all src compiles...
CORE_CFLAGS := -Iinclude -std=c++11 -Wall -Werror -Wno-unknown-pragmas -O2

# cflags - include derived include files, protocol-buffer include files, json includes...
CFLAGS := ${LIBELF_INCLUDES} -Iderived -I./proto ${CORE_CFLAGS} -I${PBJSON}/src 

CPPFLAGS = $(CFLAGS)

# VFP code needs core flags, and rounding-math define...
VFP_CFLAGS := ${CORE_CFLAGS} -frounding-math
# VFP half-precision flags...
HALF_VFP_CFLAGS := $(CORE_CFLAGS) -I$(HALF_PRECISION)/include

LIBDIRS := -L/usr/lib/x86_64-linux-gnu -L./lib

