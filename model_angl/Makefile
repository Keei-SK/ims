CC        = g++
OBJ_FILES = main.o cell.o

all: simulator

simulator:	$(OBJ_FILES)
		$(CC) $(OBJ_FILES) -o $@ $(CFLAGS)

main.o: main.cpp cell.hpp grid.hpp
	$(CC) -o $@ -c $<  $(CFLAGS)

cell.o: cell.cpp cell.hpp
	$(CC) -o $@ -c $<  $(CFLAGS)

grid.o: grid.cpp grid.hpp cell.hpp
	$(CC) -o $@ -c $<  $(CFLAGS)

clean:
	rm -f *.o simulator 

.PHONY: clean
