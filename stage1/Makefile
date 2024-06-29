BUILD_DIR ?= build/
ASM ?= nasm
.DEFAULT_GOAL := all

.PHONY: all clean
all: stage1

stage1: ${BUILD_DIR} ${BUILD_DIR}stage1.bin

${BUILD_DIR}%.bin: %.asm
	$(ASM) -f bin $< -o $@

$(BUILD_DIR):
	mkdir $@

clean: 
	rm -rf $(BUILD_DIR)