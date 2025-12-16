ifeq ($(OS), Windows_NT)
	#WINDOWS USE THESE DEFINITIONS
	RM = del /Q
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
	TOOLCHAIN = $(ECO_TOOLCHAIN)$(SLASH)xpack-aarch64-none-elf-gcc-13.2.1-1.1$(SLASH)bin$(SLASH)
	TOOL = aarch64-none-elf-
else
	#LINUX USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = /
	SWALLOW_OUTPUT =
	TOOLCHAIN = $(ECO_TOOLCHAIN)$(SLASH)xpack-aarch64-none-elf-gcc-13.2.1-1.1$(SLASH)bin$(SLASH)
	TOOL = aarch64-none-elf-
endif

ifeq ($(TARGET), 1)
OUT_TARGET = lib902ABA722D34417BB714322CC761620F.a
ifeq ($(DEBUG), 1)
CONFIG_TARGET = StaticDebug
CCFLAGS_TARGET = -Wall -g -DECO_LIB
LDFLAGS_TARGET =
ARCH_TARGET = arm64-v8a
else
CONFIG_TARGET = StaticRelease
CCFLAGS_TARGET = -DECO_LIB
LDFLAGS_TARGET =
ARCH_TARGET = arm64-v8a
endif
else
OUT_TARGET = 902ABA722D34417BB714322CC761620F.so
ifeq ($(DEBUG), 1)
CONFIG_TARGET = DynamicDebug
CCFLAGS_TARGET = -Wall -fPIC -g -DECO_DLL
LDFLAGS_TARGET = -shared
ARCH_TARGET = arm64-v8a
else
CONFIG_TARGET = DynamicRelease
CCFLAGS_TARGET = -fPIC -DECO_DLL
LDFLAGS_TARGET = -shared
ARCH_TARGET = arm64-v8a
endif
endif

# include directories
INC = \
-I ..$(SLASH)..$(SLASH)..$(SLASH)HeaderFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.Core1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.Timer1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.InterfaceBus1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.MemoryManager1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.FileSystemManagement1$(SLASH)SharedFiles


# source files.
SRC = \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoTask1Lab.c \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoTaskScheduler1Lab.c \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoTaskScheduler1LabFactory.c

OBJ = $(SRC:.c=.o)

OUT = $(OUT_TARGET)
OUT_DIR = ..$(SLASH)..$(SLASH)..$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)$(CONFIG_TARGET)


# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = $(CCFLAGS_TARGET) -Wno-missing-braces -march=armv8-a+simd -mtune=cortex-a53 -mstrict-align -fno-tree-loop-vectorize -fno-tree-slp-vectorize -fno-builtin -DECO_OS -DECO_BCM283X -DECO_AARCH64 -DUGUID_UTILITY

# compiler
GNU = $(TOOLCHAIN)
CC = $(TOOL)gcc
AR = $(TOOL)gcc-ar

ifeq ($(TARGET), 1)
CMD_TARGET=$(GNU)$(AR) rcs
else
CMD_TARGET=$(GNU)$(CC) -o
endif

# library paths
LIBS = -lc -lm -lgcc

# compile flags
LDFLAGS = $(LDFLAGS_TARGET)

.SUFFIXES: .c

all: $(OUT)

.c.o:
	$(GNU)$(CC) $(INC) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
ifeq ($(OS), Windows_NT)
	if not exist "$(OUT_DIR)" mkdir "$(OUT_DIR)"
else
	mkdir -p $(OUT_DIR)
endif
	$(CMD_TARGET) $(OUT_DIR)$(SLASH)$(OUT) $(OBJ) $(LDFLAGS)
	$(RM) $(OBJ) $(SWALLOW_OUTPUT)


clean:
	$(RM) $(OBJ) $(OUT_DIR)$(SLASH)$(OUT)

