TARGET = Tutorial
OBJS = main.o \
gfx.o

CFLAGS =
CXXFLAGS = $(CFLAGS) -std=c++14 -fno-rtti
ASFLAGS = $(CFLAGS)

# PSP Stuff
BUILD_PRX = 1
PSP_FW_VERSION = 500
PSP_LARGE_MEMORY = 1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Hello World Application

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak