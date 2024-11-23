CFLAGS = -std=c11 -Wall -Wextra -g -O2
CPPFLAGS = -I../include -DDEBUG
LDFLAGS = -lm  

all : sudoku 

sudoku: sudoku.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

sudoku.o: sudoku.c sudoku.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< 

clean: 
	@rm -f *.o sudoku 

help: 
	@echo "Usage: "

.PHONY: all clean help