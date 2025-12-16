ifeq ($(OS), Windows_NT)
	#WINDOWS USE THESE DEFINITIONS
	RM = del /Q /F
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
else
	#LINUX USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = /
	SWALLOW_OUTPUT =
endif

INCLUDES = \
-I ..$(SLASH)..$(SLASH)..$(SLASH)HeaderFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.Mutex1Lab$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.Semaphore1Lab$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.TaskScheduler1Lab$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.MemoryManager1Lab$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.IPCC.Mailbox1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.VFB1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.Core1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.InterfaceBus1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.Timer1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.InterruptController1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.TaskScheduler1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.MemoryManager1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.FileSystemManagement1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.String1$(SLASH)SharedFiles

LIB = \
-L ..$(SLASH)..$(SLASH)..$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.Mutex1Lab$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.Semaphore1Lab$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.TaskScheduler1Lab$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.MemoryManager1Lab$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.IPCC.Mailbox1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.VFB1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.Timer1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.InterruptController1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.InterfaceBus1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.TaskScheduler1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.FileSystemManagement1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.MemoryManager1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.String1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)arm64-v8a$(SLASH)StaticRelease

Pi3-64: CFLAGS = -Wall -std=gnu89 -Wno-missing-braces -march=armv8-a+simd -mtune=cortex-a53 -mstrict-align -fno-tree-loop-vectorize -fno-tree-slp-vectorize -DECO_LIB -DECO_OS -DECO_AARCH64 -DECO_BCM283X -DUGUID_UTILITY $(INCLUDES)
Pi3-64: IMGFILE = kernel8.img
Pi3-64: ARMGNU  = $(ECO_TOOLCHAIN)$(SLASH)xpack-aarch64-none-elf-gcc-13.2.1-1.1$(SLASH)bin$(SLASH)
#Pi3-64: ARMGNU  = C:$(SLASH)Dev$(SLASH)toolchain$(SLASH)xpack-aarch64-none-elf-gcc-13.2.1-1.1$(SLASH)bin$(SLASH)
Pi3-64: LINKERFILE = startup.ld
Pi3-64: PISTART = ..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)entry.S


LDFLAGS = -nostartfiles -ffreestanding -fno-asynchronous-unwind-tables -fomit-frame-pointer

LIBFLAGS=-static $(LIB)  -l0000000000000000000000004D656D31 -lF10BC39A4F2143CF8A1E104650A2C302 -l902ABA722D34417BB714322CC761620F -l939B1DCDB6404F7D9C072291AF252188 -l00000000000000000000000042757331 -l81589BFED0B84B1194524BEE623E1838 -l8DB93F3DF5B947D4A67F7C100B569723 -l2F48BBCBE4884CC08ECFC45990017215 -l0741985B8FD0476C867CAE177CD26E7C  -lc -lm -lgcc

LINKERFLAGS=-Wl,-Map,kernel.map
ASMFLAGS=-nostartfiles -ffreestanding -fno-asynchronous-unwind-tables -fomit-frame-pointer -Wa,-a>list.txt"

# The directory in which source files are stored.
SOURCE = \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)MySimpleEcoOS.c


# The name of the assembler listing file to generate.
LIST = kernel.list

# The name of the map file to generate.
MAP = kernel.map

# The names of all object files that must be generated. Deduced from the
# assembly code files in source.
C_FILES := $(filter-out $(SOURCE), $(wildcard *.c))

# Rule to make everything.
Pi3-64: $(LIST)

# Rule to remake everything. Does not include clean.
all: Pi3-64

# Rule to make the image & listing files.
$(LIST) : kernel.elf
	$(ARMGNU)aarch64-none-elf-objdump -d kernel.elf > $(LIST)
	$(ARMGNU)aarch64-none-elf-objcopy kernel.elf -O binary $(IMGFILE)
	$(ARMGNU)aarch64-none-elf-nm -n kernel.elf > $(MAP)

OBJDIR := build
target = ${OBJDIR}/$(patsubst %.c,%.o,$(notdir ${1}))
obj.c :=
define obj
  $(call target,${1}) : ${1} |
  obj$(suffix ${1}) += $(call target,${1})
endef

define SOURCES
  $(foreach src,${1},$(eval $(call obj,${src})))
endef

$(eval $(call SOURCES,${C_FILES}))

main.c : ${obj.c}

 ${obj.c} : % :
	$(ARMGNU)aarch64-none-elf-gcc $(CFLAGS) $(ASMFLAGS) $(LDFLAGS) -c $^ -o $@
# Uncomment this if you want the assembler output of each object file
#	$(ARMGNU)aarch64-none-elf-gcc $(CFLAGS) $(LDFLAGS) -S $^ -o $(patsubst %.o,%.s,$(@))

kernel.elf : main.c
	$(ARMGNU)aarch64-none-elf-gcc $(CFLAGS) $(LDFLAGS) $(LINKERFLAGS) -Wl,-T,$(LINKERFILE) $(wildcard $(OBJDIR)/*.o)  -o $@ $(SOURCE) $(PISTART) $(LIBFLAGS)

# Control silent mode  .... we want silent in clean
.silent:clean

# cleanup temp files
clean:
	$(RM) $(MAP) $(SWALLOW_OUTPUT)
	$(RM) kernel.elf $(SWALLOW_OUTPUT)
	$(RM) $(LIST) $(SWALLOW_OUTPUT)
	$(RM) $(OBJDIR)$(SLASH)*.o $(SWALLOW_OUTPUT)
	$(RM) $(OBJDIR)$(SLASH)*.s $(SWALLOW_OUTPUT)
	echo CLEAN COMPLETED
