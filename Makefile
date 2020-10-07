CC=g++
SRCDIR=Sources/
SRC=$(SRCDIR)main.cpp $(SRCDIR)fileworks.cpp $(SRCDIR)quicksort.cpp $(SRCDIR)testsuite.cpp
HEADERDIR=Headers/
TESTSUITE=TestSuite/
HEADERS=$(HEADERDIR)fileworks.hpp $(HEADERDIR)quicksort.hpp $(TESTSUITE)testsuite.hpp
PRODUCT=DerivedData/Build/Products/
CCFLAGS=-Wall -Wpedantic -O3 -Wextra -Wno-c++11-long-long

all: debug release

tests: debug
	cd $(PRODUCT)Debug/
	$(PRODUCT)Debug/ub-sort hamlet.txt sortbeg.txt sortright.txt
	

release: fileworks quicksort tester
	mkdir -p $(PRODUCT)Release
	$(CC) $(CCFLAGS) $(SRC) $(HEADERS)
	mv a.out $(PRODUCT)Release/ub-sort

debug: fileworks quicksort tester
	mkdir -p $(PRODUCT)Debug
	$(CC) -DDEBUG $(CCFLAGS) $(SRC) $(HEADERS)
	mv a.out $(PRODUCT)Debug/ub-sort

fileworks: $(HEADERDIR)fileworks.hpp $(SRCDIR)fileworks.cpp

quicksort: $(HEADERDIR)quicksort.hpp $(SRCDIR)quicksort.cpp

tester: $(TESTSUITE)testsuite.hpp $(SRCDIR)testsuite.cpp

clean:
	rm -rf *.o $(PRODUCT)*
