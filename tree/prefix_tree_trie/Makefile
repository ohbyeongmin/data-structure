CC=gcc
CFLAGS=-g -Wall
BINS=trieexample

all: $(BINS)

%: %.CC
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(BINS) *.dSYM