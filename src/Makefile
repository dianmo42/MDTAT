# CC = gcc
# CFLAGS = -O2 -g -std=c99 -fopenmp
# LIBS = -lm 

CC = icx
CFLAGS = -O2 -g -std=c99 -qopenmp

PROGRAM = TAT.o
OBJECTS = main.o args.o input.o alloc_mem.o read_dump.o compute.o output.o

${PROGRAM} : ${OBJECTS}
	${CC} -o ${PROGRAM} ${OBJECTS} ${CFLAGS} ${LIBS}

${OBJECTS} : mdtat.h

.PHONY : clean
clean :
	-rm ${PROGRAM} ${OBJECTS}
