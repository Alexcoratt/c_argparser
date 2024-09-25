CC ?= gcc
CFLAGS += -Iinclude -std=gnu11 -Wall

SOURCE_DIR ?= src
BUILD_DIR ?= build

main: mk_build_dir
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/main $(SOURCE_DIR)/main.c

hashmap_test: mk_build_dir
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/hashmap_test $(SOURCE_DIR)/hashmap_test.c $(SOURCE_DIR)/hashmap.c

mk_build_dir:
	if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
