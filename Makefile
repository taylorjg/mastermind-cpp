# https://stackoverflow.com/questions/1814270/gcc-g-option-to-place-all-object-files-into-separate-directory

CC = g++
CPPFLAGS = -std=c++11 -g -Wall
INC = 

SDIR = src
ODIR = obj
BIN = bin
OUT = $(BIN)/main

_OBJS = peg.o mastermind.o main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cc
	@mkdir -p $(ODIR)
	$(CC) -c $(INC) -o $@ $< $(CPPFLAGS) 

$(OUT): $(OBJS)
	@mkdir -p $(BIN)
	g++ -o $(OUT) $(OBJS)

clean:
	rm -rf $(ODIR) $(BIN)

# g++ -std=c++11 src/mastermind_tests.cc -o bin/mastermind_tests obj/mastermind.o obj/peg.o
