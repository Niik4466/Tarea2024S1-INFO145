CC=clang++
CFLAGS=-std=c++20 -Ofast -Wall -Wextra -Wno-unused-parameter -Wdouble-promotion
BINS=bin/prog
COM=out
OBJS= $(COM)/ArregloExplicito.o $(COM)/GapCoding.o $(COM)/Huffman.o $(COM)/Experimentacion.o

all: clean programa

programa: $(OBJS)
	$(CC) $(CFLAGS) -o $(BINS) src/main.cpp $(OBJS) -Iinclude

$(COM)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude

clean:
	@echo " [CLN] Cleaning"
	@rm -f $(BINS) $(COM)/*.o
