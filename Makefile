all:naive gen_tests chain strassen compare

obj:
	mkdir -p obj

naive.o:
	gcc -Wall -g -c naive.c -o obj/naive.o

matrix.o:
	gcc -Wall -g -c matrix.c -o obj/matrix.o

mult.o:
	gcc -Wall -g -c mult.c -o obj/mult.o

gen_tests.o:
	gcc -Wall -g -c gen_tests.c -o obj/gen_tests.o

chain.o:
	gcc -Wall -g -c chain.c -o obj/chain.o

strassen.o:
	gcc -Wall -g -c strassen.c -o obj/strassen.o

main_chain.o:
	gcc -Wall -g -c main_chain.c -o obj/main_chain.o

main_strassen.o:
	gcc -Wall -g -c main_strassen.c -o obj/main_strassen.o

compare.o:
	gcc -Wall -g -c compare.c -o obj/compare.o

modulo.o:
	gcc -Wall -g -c modulo.c -o obj/modulo.o

chain:obj main_chain.o chain.o matrix.o mult.o
	gcc -Wall -g -o chain obj/main_chain.o obj/chain.o obj/matrix.o obj/mult.o

naive:obj matrix.o naive.o mult.o
	gcc -Wall -g -o naive obj/naive.o obj/matrix.o obj/mult.o

strassen:obj mult.o matrix.o strassen.o main_strassen.o
	gcc -Wall -g -o strassen obj/mult.o obj/matrix.o obj/strassen.o obj/main_strassen.o

compare:obj compare.o matrix.o
	gcc -Wall -g -o compare obj/compare.o obj/matrix.o

modulo:obj matrix.o modulo.o
	gcc -Wall -g -o modulo obj/modulo.o obj/matrix.o

gen_tests:obj matrix.o mult.o gen_tests.o
	gcc -Wall -g -o gen_tests obj/gen_tests.o obj/matrix.o obj/mult.o

clean:
	rm -rf obj
	rm -f strassen

