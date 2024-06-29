BUILD_DIR ?= build/
.DEFAULT_GOAL := all

all: ${BUILD_DIR}bootloader.bin

STAGE1 := ${BUILD_DIR}stage1/stage1.bin
STAGE2 := ${BUILD_DIR}stage2/stage2.bin

${BUILD_DIR}bootloader.bin: ${BUILD_DIR} stage1 stage2
	cat ${STAGE1} ${STAGE2} > $@
	truncate $@ -s 1440KB

stage1: ${STAGE1}

${STAGE1}:
	$(MAKE) -C stage1 BUILD_DIR=$(abspath $(BUILD_DIR))/stage1/

stage2: ${STAGE2}

${STAGE2}:
	$(MAKE) -C stage2 BUILD_DIR=$(abspath $(BUILD_DIR))/stage2/

$(BUILD_DIR):
	mkdir $@

run: all
	qemu-system-x86_64 -hda $(BUILD_DIR)bootloader.bin # -d int

clean: 
	rm -rf $(BUILD_DIR)