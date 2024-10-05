CC ?= clang
CFLAGS += -Iinclude -std=gnu11 -Wall

SOURCE_DIR ?= src
BUILD_DIR ?= build
TEST_DIR ?= tests

PROJECT_NAME ?= argreader

# basic targets
main: mk_build_dir
	${CC} ${CFLAGS} -o ${BUILD_DIR}/${PROJECT_NAME} main.c

mk_build_dir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

clean:
	rm ${BUILD_DIR}/*.o

# modules
simple_stack: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/simple_stack.o ${SOURCE_DIR}/simple_stack.c

common:
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/common.o ${SOURCE_DIR}/common.c

stack: simple_stack common
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/stack.o ${SOURCE_DIR}/stack.c

queue: simple_stack common
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/queue.o ${SOURCE_DIR}/queue.c

hashmap: simple_stack common
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/hashmap.o ${SOURCE_DIR}/hashmap.c

dynvalue: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/dynvalue.o ${SOURCE_DIR}/dynvalue.c

print_dynvalue: dynvalue
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/print_dynvalue.o ${SOURCE_DIR}/print_dynvalue.c

argparser: hashmap queue
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/argparser.o ${SOURCE_DIR}/argparser.c

# ------ Tests -------
simple_stack_test: simple_stack
	${CC} ${CFLAGS} -o ${BUILD_DIR}/simple_stack_test ${TEST_DIR}/simple_stack_test.c ${BUILD_DIR}/simple_stack.o ${BUILD_DIR}/common.o

stack_test: stack
	${CC} ${CFLAGS} -o ${BUILD_DIR}/stack_test ${TEST_DIR}/stack_test.c ${BUILD_DIR}/stack.o ${BUILD_DIR}/common.o ${BUILD_DIR}/simple_stack.o

queue_test: queue
	${CC} ${CFLAGS} -o ${BUILD_DIR}/queue_test ${TEST_DIR}/queue_test.c ${BUILD_DIR}/queue.o ${BUILD_DIR}/common.o ${BUILD_DIR}/simple_stack.o

hashmap_test: hashmap
	${CC} ${CFLAGS} -o ${BUILD_DIR}/hashmap_test ${TEST_DIR}/hashmap_test.c ${BUILD_DIR}/hashmap.o ${BUILD_DIR}/common.o ${BUILD_DIR}/simple_stack.o

dynvalue_test: print_dynvalue
	${CC} ${CFLAGS} -o ${BUILD_DIR}/dynvalue_test ${TEST_DIR}/dynvalue_test.c ${BUILD_DIR}/dynvalue.o ${BUILD_DIR}/print_dynvalue.o  -lm

argparser_test: argparser
	${CC} ${CFLAGS} -o ${BUILD_DIR}/argparser_test ${TEST_DIR}/argparser_test.c ${BUILD_DIR}/common.o ${BUILD_DIR}/argparser.o ${BUILD_DIR}/queue.o ${BUILD_DIR}/hashmap.o ${BUILD_DIR}/simple_stack.o