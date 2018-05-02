CC = g++
CPPFLAGS = -std=c++11 -g -Wall

# https://stackoverflow.com/questions/1814270/gcc-g-option-to-place-all-object-files-into-separate-directory

SDIR = src
ODIR = obj
INC = 

_OBJS = main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cc
	$(CC) -c $(INC) -o $@ $< $(CPPFLAGS) 

main: $(OBJS)
	g++ -o main $(OBJS)

clean:
	rm -f $(ODIR)/*.o main
