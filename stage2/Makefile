BUILD_DIR ?= build/
ASM ?= nasm
CC ?= i686-elf-gcc
LD ?= i686-elf-ld
.DEFAULT_GOAL := all

SOURCE_C := $(wildcard *.c)
SOURCE_ASM := $(wildcard *.asm)
SOURCE := ${SOURCE_C} ${SOURCE_ASM}

OBJECTS_C := $(patsubst %.c, ${BUILD_DIR}c/%.o, \
			${SOURCE_C})
OBJECTS_ASM := $(patsubst %.asm, ${BUILD_DIR}asm/%.o, \
			${SOURCE_ASM})
OBJECTS := ${OBJECTS_C} ${OBJECTS_ASM}

C_FLAGS ?= -O3
# Mandatory flags
C_FLAGS := ${C_FLAGS} -m32 -ffreestanding -Wall \
		-Wextra -nostdlib -fno-PIC

.PHONY: all clean
all: stage2

stage2: ${BUILD_DIR}c/ ${BUILD_DIR}asm/ ${BUILD_DIR}stage2.bin

${BUILD_DIR}stage2.bin: ${OBJECTS}
	${LD} -m elf_i386 -T linker.ld -o $@ ${OBJECTS}

${BUILD_DIR}c/%.o: %.c
	$(CC) -c $< -o $@ ${C_FLAGS}

${BUILD_DIR}asm/%.o: %.asm
	$(ASM) -f elf32 $< -o $@

${BUILD_DIR}c/ ${BUILD_DIR}asm/: ${BUILD_DIR}
	mkdir $@

$(BUILD_DIR):
	mkdir $@

clean: 
	rm -rf $(BUILD_DIR)
