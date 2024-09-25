CC ?= gcc
CFLAGS += -Iinclude -std=gnu11 -Wall

SOURCE_DIR ?= src
BUILD_DIR ?= build

main: mk_build_dir
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/main $(SOURCE_DIR)/main.c

mk_build_dir:
	if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
