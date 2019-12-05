CC              = g++
CFLAGS         = -g -lm
OBJ_FILES      = main.o

all: simulator

run: experiment1

simulator:	$(OBJ_FILES)
		$(CC) $(OBJ_FILES) -o $@ $(CFLAGS)

main.o: main.cpp args.h
	$(CC) -o $@ -c $<  $(CFLAGS)

clean:
	rm -f *.o simulator experiment*

experiment1:
	./simulator -B 2.5 -t 1000 -l 1 -L 10 -c 500 -s 0.25 -S 0.95 -A 10 -k 14

.PHONY: clean
