SRC=program.c
OBJ=program.o
PROG=program
CFLAGS=-g -lgmp

all: ${PROG}

${PROG}: ${OBJ}
	gcc -o ${PROG} ${OBJ} ${CFLAGS}

${OBJ}: ${SRC}
	gcc -c -o ${OBJ} ${SRC} ${CFLAGS}