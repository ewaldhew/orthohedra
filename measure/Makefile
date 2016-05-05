CC = clang++
CFLAGS = -Wall -pedantic

all: 01_n_vertexrepr_color.out 02_n_nbhoodrepr_color.out 03_n_vertexrepr_complement.out \
	04_n_nbhoodrepr_complement.out 05_n_vertexrepr_intersection.out \
	06_n_nbhoodrepr_intersection.out

01_n_vertexrepr_color.out: 01_n_vertexrepr_color.cpp utils.h utils.cpp
	${CC} ${CFLAGS} -static 01_n_vertexrepr_color.cpp utils.cpp -L.. -lorthopoly -o 01_n_vertexrepr_color.out

02_n_nbhoodrepr_color.out: 02_n_nbhoodrepr_color.cpp utils.h utils.cpp
	${CC} ${CFLAGS} -static 02_n_nbhoodrepr_color.cpp utils.cpp -L.. -lorthopoly -o 02_n_nbhoodrepr_color.out

03_n_vertexrepr_complement.out: 03_n_vertexrepr_complement.cpp utils.h utils.cpp
	${CC} ${CFLAGS} -static 03_n_vertexrepr_complement.cpp utils.cpp -L.. -lorthopoly -o 03_n_vertexrepr_complement.out

04_n_nbhoodrepr_complement.out: 04_n_nbhoodrepr_complement.cpp utils.h utils.cpp
	${CC} ${CFLAGS} -static 04_n_nbhoodrepr_complement.cpp utils.cpp -L.. -lorthopoly -o 04_n_nbhoodrepr_complement.out

05_n_vertexrepr_intersection.out: 05_n_vertexrepr_intersection.cpp utils.h utils.cpp
	${CC} ${CFLAGS} -static 05_n_vertexrepr_intersection.cpp utils.cpp -L.. -lorthopoly -o 05_n_vertexrepr_intersection.out

06_n_nbhoodrepr_intersection.out: 06_n_nbhoodrepr_intersection.cpp utils.h utils.cpp
	${CC} ${CFLAGS} -static 06_n_nbhoodrepr_intersection.cpp utils.cpp -L.. -lorthopoly -o 06_n_nbhoodrepr_intersection.out
