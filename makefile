CXX=g++
CFLAGS=-Wall -ansi -pedantic -std=c++11
EXEC=main

all: $(EXEC)

main : main.o lexer.o symbole.o Automate.o state.o
	$(CXX) -o $@ $^
	
%.o : %.cpp
	$(CXX) -c -g $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)