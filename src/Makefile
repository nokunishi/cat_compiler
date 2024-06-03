CFLAGS= -std=c++11

all: main

main: main.o asm.o token.o animal.o
	$(CXX) $(CFLAGS) main.o asm.o token.o animal.o -o main

main.o: main.cpp 
	$(CXX) $(CFLAGS) -c main.cpp

asm.o: asm.h asm.cpp
	$(CXX) $(CFLAGS) -c asm.cpp

token.o: token.h token.cpp
	$(CXX) $(CFLAGS) -c token.cpp

animal.o: animal.h animal.cpp
	$(CXX) $(CFLAGS) -c animal.cpp

clean:
	rm -f *.o ../out/* main