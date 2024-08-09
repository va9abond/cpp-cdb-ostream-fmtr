CC := clang++
CXXFLAGS := -pedantic-errors -Wall -Werror -g3 -O0 --std=c++20
# CXXFLAGS += -c


.PHONY: run
run: a.out
	./a.out

a.out: cst_ostream_fmtr.gch main.o
	$(CC) $(CXXFLAGS) main.o cst_ostream_fmtr.gch -o a.out

cst_ostream_fmtr.gch: cst_ostream_fmtr.hpp
	$(CC) $(CXXFLAGS) -c cst_ostream_fmtr.hpp -o cst_ostream_fmtr.gch

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp -o main.o

.PHONY: clean
clean:
	rm -rf *.o *.gch a.out

test: test.cpp
	$(CC) $(CXXFLAGS) test.cpp -o test
	./test
