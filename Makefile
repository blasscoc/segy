
CXX=g++
CFLAGS=-I.


%.o: %.cpp 
	$(CXX) -c -o $@ $< $(CFLAGS) -I./include

ebcdic:	lib/ebcdic.o
	$(CXX) apps/print_ebcdic.cpp -o ./exe/ebcdic lib/ebcdic.o -I./include


print_binary_header: lib/binary_header.o
	$(CXX) apps/print_binary_header.cpp -o ./exe/print_binary_header lib/binary_header.o -I./include
