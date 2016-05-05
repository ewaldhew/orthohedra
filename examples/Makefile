CC = clang++
CFLAGS = -Wall -pedantic

all: 01.out 02.out

01.out: 01.cpp
	${CC} ${CFLAGS} -static 01.cpp -L.. -lorthopoly -o 01.out

02.out: 02.cpp
	${CC} ${CFLAGS} -static 02.cpp -L.. -lorthopoly -o 02.out
