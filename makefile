CC ?= clang
CFLAGS += -Iinclude -std=gnu11 -Wall

SOURCE_DIR ?= src
BUILD_DIR ?= build
TEST_DIR ?= tests

main: mk_build_dir
	${CC} ${CFLAGS} -o ${BUILD_DIR}/main main.c

mk_build_dir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

clean:
	rm ${BUILD_DIR}/*.o

simple_stack: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/simple_stack.o ${SOURCE_DIR}/simple_stack.c

common:
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/common.o ${SOURCE_DIR}/common.c

stack: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/stack.o ${SOURCE_DIR}/stack.c

queue: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/queue.o ${SOURCE_DIR}/queue.c

hashmap: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/hashmap.o ${SOURCE_DIR}/hashmap.c

dynvalue: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/dynvalue.o ${SOURCE_DIR}/dynvalue.c

print_dynvalue: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/print_dynvalue.o ${SOURCE_DIR}/print_dynvalue.c

argparser: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/argparser.o ${SOURCE_DIR}/argparser.c


# ------ Tests -------
simple_stack_test: simple_stack common
	${CC} ${CFLAGS} -o ${BUILD_DIR}/simple_stack_test ${TEST_DIR}/simple_stack_test.c ${BUILD_DIR}/simple_stack.o ${BUILD_DIR}/common.o

stack_test: stack common simple_stack
	${CC} ${CFLAGS} -o ${BUILD_DIR}/stack_test ${TEST_DIR}/stack_test.c ${BUILD_DIR}/stack.o ${BUILD_DIR}/common.o ${BUILD_DIR}/simple_stack.o

queue_test: queue common simple_stack
	${CC} ${CFLAGS} -o ${BUILD_DIR}/queue_test ${TEST_DIR}/queue_test.c ${BUILD_DIR}/queue.o ${BUILD_DIR}/common.o ${BUILD_DIR}/simple_stack.o

hashmap_test: hashmap common simple_stack
	${CC} ${CFLAGS} -o ${BUILD_DIR}/hashmap_test ${TEST_DIR}/hashmap_test.c ${BUILD_DIR}/hashmap.o ${BUILD_DIR}/common.o ${BUILD_DIR}/simple_stack.o

dynvalue_test: dynvalue print_dynvalue
	${CC} ${CFLAGS} -o ${BUILD_DIR}/dynvalue_test ${TEST_DIR}/dynvalue_test.c ${BUILD_DIR}/dynvalue.o ${BUILD_DIR}/print_dynvalue.o  -lm

argparser_test: argparser queue hashmap
	${CC} ${CFLAGS} -o ${BUILD_DIR}/argparser_test ${TEST_DIR}/argparser_test.c ${BUILD_DIR}/argparser.o ${BUILD_DIR}/queue.o ${BUILD_DIR}/hashmap.o