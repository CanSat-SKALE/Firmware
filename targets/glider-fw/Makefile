##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
ifeq ($(USE_OPT),)
  USE_OPT = -O2 -ggdb -fomit-frame-pointer -falign-functions=16
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT = 
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -fno-rtti
endif

# Enable this if you want the linker to remove unused code and data
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

# Linker extra options here.
ifeq ($(USE_LDOPT),)
  USE_LDOPT = 
endif

# Enable this if you want link time optimizations (LTO)
# don't use for debugging
ifeq ($(USE_LTO),)
  USE_LTO = no
endif

# If enabled, this option allows to compile the application in THUMB mode.
ifeq ($(USE_THUMB),)
  USE_THUMB = yes
endif

# Enable this if you want to see the full log while compiling.
ifeq ($(USE_VERBOSE_COMPILE),)
  USE_VERBOSE_COMPILE = no
endif

#
# Build global options
##############################################################################

##############################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
ifeq ($(USE_PROCESS_STACKSIZE),)
  USE_PROCESS_STACKSIZE = 0x400
endif

# Stack size to the allocated to the Cortex-M main/exceptions stack. This
# stack is used for processing interrupts and exceptions.
ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
  USE_EXCEPTIONS_STACKSIZE = 0x400
endif

# Enables the use of FPU on Cortex-M4 (no, hard).
ifeq ($(USE_FPU),)
  USE_FPU = hard
endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Define project name here
PROJECT = glider-dev-fw

PROJROOT = ../..

# Imported source files and paths
CHIBIOS = $(PROJROOT)/ChibiOS
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/startup_stm32f4xx.mk
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/hal/ports/STM32/STM32F4xx/platform.mk
include $(CHIBIOS)/os/hal/osal/rt/osal.mk
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/rt/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk
include $(CHIBIOS)/test/rt/test.mk
include $(CHIBIOS)/os/various/cpp_wrappers/chcpp.mk
include $(PROJROOT)/src/fatfs/fatfs.mk
include $(PROJROOT)/src/src.mk

# Define linker script file here
LDSCRIPT= STM32F405xG.ld

# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CSRC = $(PORTSRC) \
       $(KERNSRC) \
       $(TESTSRC) \
       $(HALSRC) \
       $(OSALSRC) \
       $(PLATFORMSRC) \
       $(STARTUPSRC) \
       $(BOARDSRC) \
       $(CHIBIOS)/os/hal/lib/streams/chprintf.c \
       $(CHIBIOS)/os/hal/lib/streams/memstreams.c \
       $(CHIBIOS)/os/various/shell.c \
       $(FATFSSRC) \
       $(PROJCSRC) \
       $(PROJROOT)/src/git_revision.c \
       board.c main.c

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC = $(CHCPPSRC) $(PROJCPPSRC)

# C sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACSRC =

# C++ sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACPPSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCPPSRC =

# List ASM source files here
ASMSRC = $(PORTASM) $(OSALASM)
# Note: Using custom crt0_v7m.s instead of $(STARTUPASM)
#       This might create problems if the original crt0_v7m.s is updated or
# 		further startup assembly sources are added to STARTUPASM.
ASMSRC += $(PROJASMSRC) crt0_v7m.s #$(STARTUPASM)

INCDIR = $(PORTINC) $(KERNINC) $(TESTINC) $(STARTUPINC) \
         $(HALINC) $(OSALINC) $(PLATFORMINC) $(BOARDINC) \
         $(FATFSINC) $(CHIBIOS)/os/various $(CHCPPINC) \
         $(CHIBIOS)/os/hal/lib/streams \
         $(PROJINC)

#
# Project, sources and paths
##############################################################################

##############################################################################
# Compiler settings
#

MCU  = cortex-m4

#TRGT = arm-elf-
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CPPC = $(TRGT)g++
# Enable loading with g++ only if you need C++ runtime support.
# NOTE: You can use C++ even without C++ support if you are careful. C++
#       runtime support makes code size explode.
# LD   = $(TRGT)gcc
LD   = $(TRGT)g++
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
AR   = $(TRGT)ar
OD   = $(TRGT)objdump
NM   = $(TRGT)nm
SZ   = $(TRGT)size
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# ARM-specific options here
AOPT =

# THUMB-specific options here
TOPT = -mthumb -DTHUMB

# Define C warning options here
CWARN = -Wall -Wextra -Wstrict-prototypes -Werror

# Define C++ warning options here
CPPWARN = -Wall -Wextra -std=c++11

#
# Compiler settings
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
UDEFS = -DDEBUG

# Define ASM defines here
UADEFS =

# List all user directories here
UINCDIR =

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS = -lm

#
# End of user defines
##############################################################################

GLOBAL_SRC_DEP =  $(PROJROOT)/src/src.mk

RULESPATH = $(PROJROOT)
include $(PROJROOT)/rules.mk
-include $(PROJROOT)/tools.mk

PRE_MAKE_ALL_RULE_HOOK:
	cd $(PROJROOT) && ./git_revision.sh

POST_MAKE_ALL_RULE_HOOK: tests

.PHONY: tests
tests:
	cd $(PROJROOT) && mkdir -p build && cd build && cmake .. && rm -f tests && make check

# Generates a ctags file containing the correct definition for the build
.PHONY: ctags
ctags:
	@echo "Generating ctags file..."
	@cat .dep/*.d | grep ":$$" | sed "s/://" | sort | uniq | xargs ctags --file-scope=no --extra=+q $(CSRC) $(CPPSRC)
