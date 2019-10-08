SRC_DIR  = src
OBJ_DIR  = obj
DEPS_DIR = depends

GPP = /usr/bin/g++
GCC = /usr/bin/cc
AR = /usr/bin/ar

# paths, etc, used by main Makefile...

TOOLS_DIR := ${HOME}/Desktop/tools


PBJSON := ${TOOLS_DIR}/pbjson

HALF_PRECISION := ${TOOLS_DIR}/half-2.1.0

MY_LIBELF := ${TOOLS_DIR}/elftoolchain-0.7.1

STATIC_LIBELF := ${MY_LIBELF}/libelf/libelf.a

LIBELF_INCLUDES := -I${MY_LIBELF}/libelf -I${MY_LIBELF}/common

STATIC_BOOSTLIB := ${TOOLS_DIR}/lib/libboost_program_options.a

BOOST_INCLUDES := -I${TOOLS_DIR}/boost_1_71_0

STATIC_PROTOLIB := /usr/lib/x86_64-linux-gnu/libprotobuf.a


# 'core' cflags - common to all src compiles...
CORE_CFLAGS := -Iinclude -std=c++11 -Wall -Werror -Wno-unknown-pragmas -g

# cflags - include derived include files, protocol-buffer include files, json includes...
CFLAGS := -I/usr/include ${LIBELF_INCLUDES} ${BOOST_INCLUDES} -Iderived -I./proto ${CORE_CFLAGS} 

CPPFLAGS = $(CFLAGS)

# VFP code needs core flags, and rounding-math define...
VFP_CFLAGS := ${CORE_CFLAGS} -frounding-math
# VFP half-precision flags...
HALF_VFP_CFLAGS := $(CORE_CFLAGS) -I$(HALF_PRECISION)/include

LIBDIRS := -L/usr/lib/x86_64-linux-gnu -L./lib

LDFLAGS += -pthread -Wl,--no-as-needed
