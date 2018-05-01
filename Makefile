CC = g++
CPPFLAGS = -std=c++11 -g -Wall

OBJS = main.o

main: $(OBJS)
	g++ -o main $(OBJS)

clean:
	rm -f main $(OBJS)
