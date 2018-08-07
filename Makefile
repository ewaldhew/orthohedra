CC = g++
CFLAGS = -std=c++11 -Wall -pedantic -g -fPIC

OBJS = bin/main.o bin/test.o bin/space.o bin/repr.o bin/grid_repr.o bin/vertex_repr.o bin/nbhood_repr.o

all: orthopoly

orthopoly: bin ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o orthopoly

bin:
	mkdir bin

bin/main.o: src/main.cpp src/test/test.h
	${CC} ${CFLAGS} src/main.cpp -c -o bin/main.o

bin/test.o: src/test/test_grid_repr.cpp src/test/test_vertex_repr.cpp src/test/test_ndimtable.cpp \
 src/test/test_nbhood_repr.cpp src/test/test_trivial_polyhedron.cpp \
 src/test/test_float_trivial_polyhedron.cpp src/test/test_float_vertex_repr.cpp src/test/test_float_nbhood_repr.cpp \
 src/test/test.cpp src/test/test.h src/space.h src/grid_repr.h src/repr.h src/vertex_repr.h
	${CC} ${CFLAGS} src/test/test.cpp -c -o bin/test.o

bin/space.o: src/space.cpp src/space.h
	${CC} ${CFLAGS} src/space.cpp -c -o bin/space.o

bin/repr.o: src/repr.cpp src/repr.h src/space.h
	${CC} ${CFLAGS} src/repr.cpp -c -o bin/repr.o

bin/grid_repr.o: src/grid_repr.cpp src/grid_repr.h src/repr.h src/space.h \
 src/vertex_repr.h src/nbhood_repr.h
	${CC} ${CFLAGS} src/grid_repr.cpp -c -o bin/grid_repr.o

bin/vertex_repr.o: src/vertex_repr.cpp src/vertex_repr.h src/repr.h \
 src/space.h src/grid_repr.h src/nbhood_repr.h
	${CC} ${CFLAGS} src/vertex_repr.cpp -c -o bin/vertex_repr.o

bin/nbhood_repr.o: src/nbhood_repr.cpp src/nbhood_repr.h src/vertex_repr.h \
 src/repr.h src/space.h src/grid_repr.h
	${CC} ${CFLAGS} src/nbhood_repr.cpp -c -o bin/nbhood_repr.o

clean:
	rm -rf bin orthopoly html latex

staticlib: orthopoly
	ar rcs bin/liborthopoly.a ${OBJS}

dynamiclib: staticlib
	${CC} ${CFLAGS} -shared src/orthohedra.cpp -L. -Iinclude -l:bin/liborthopoly.a -o bin/liborthohedra.so
