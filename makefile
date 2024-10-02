CC ?= clang
CFLAGS += -Iinclude -std=gnu11 -Wall

SOURCE_DIR ?= src
BUILD_DIR ?= build

main: mk_build_dir
	${CC} ${CFLAGS} -o ${BUILD_DIR}/main ${SOURCE_DIR}/main.c

hashmap_test: hashmap common
	${CC} ${CFLAGS} -o ${BUILD_DIR}/hashmap_test ${SOURCE_DIR}/hashmap_test.c ${BUILD_DIR}/hashmap.o ${BUILD_DIR}/common.o

hashmap: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/hashmap.o ${SOURCE_DIR}/hashmap.c

dynvalue_test: dynvalue print_dynvalue
	${CC} ${CFLAGS} -o ${BUILD_DIR}/dynvalue_test ${SOURCE_DIR}/dynvalue_test.c ${BUILD_DIR}/dynvalue.o ${BUILD_DIR}/print_dynvalue.o  -lm

dynvalue: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/dynvalue.o ${SOURCE_DIR}/dynvalue.c

print_dynvalue: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/print_dynvalue.o ${SOURCE_DIR}/print_dynvalue.c

argparser_test: argparser queue hashmap
	${CC} ${CFLAGS} -o ${BUILD_DIR}/argparser_test ${SOURCE_DIR}/argparser_test.c ${BUILD_DIR}/argparser.o ${BUILD_DIR}/queue.o ${BUILD_DIR}/hashmap.o

argparser: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/argparser.o ${SOURCE_DIR}/argparser.c

queue_test: queue common
	${CC} ${CFLAGS} -o ${BUILD_DIR}/queue_test ${SOURCE_DIR}/queue_test.c ${BUILD_DIR}/queue.o ${BUILD_DIR}/common.o

queue: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/queue.o ${SOURCE_DIR}/queue.c

common:
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/common.o ${SOURCE_DIR}/common.c

mk_build_dir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi
