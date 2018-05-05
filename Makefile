# https://stackoverflow.com/questions/1814270/gcc-g-option-to-place-all-object-files-into-separate-directory

CC = g++
CPPFLAGS = -std=c++14 -g -Wall
INC = 

SDIR = src
ODIR = obj
BDIR = bin
MAIN = $(BDIR)/main
TEST = $(BDIR)/test

_COMMON_OBJS = peg.o code.o guess.o feedback.o mastermind.o autosolve.o

_OBJS = $(_COMMON_OBJS) main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cc
	@mkdir -p $(ODIR)
	$(CC) -c $(INC) -o $@ $< $(CPPFLAGS) 

main: $(OBJS)
	@mkdir -p $(BDIR)
	g++ -o $(MAIN) $(OBJS)

test: $(TEST)
	$(TEST)

_TEST_OBJS = $(_COMMON_OBJS) mastermind_tests.o
TEST_OBJS = $(patsubst %,$(ODIR)/%,$(_TEST_OBJS))

$(TEST): $(TEST_OBJS)
	@mkdir -p $(BDIR)
	g++ -o $(TEST) $(TEST_OBJS)

clean:
	rm -rf $(ODIR) $(BDIR)
