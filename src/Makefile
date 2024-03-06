TARGET = TAT.o
OBJECTS = main.o open_file.o read_para.o alloc_mem.o save_conf.o \
			compute.o compute_msd.o compute_sisf.o output.o

CC = icc
CFLAGS = -qopenmp -mkl -O2 -std=c99

# CC = gcc
# CFLAGS = -fopenmp -lm -mkl

${TARGET}: ${OBJECTS}
	${CC} -o ${TARGET} ${CFLAGS} ${OBJECTS} ${LDFLAGS}

.PHONY:clean
clean:
	-rm -rf ${TARGET} ${OBJECTS}
