CC        = g++
OBJ_FILES = main.o cell.o grid.o

all: simulator

simulator:	$(OBJ_FILES)
		$(CC) $(OBJ_FILES) -o $@ $(CFLAGS)

main.o: main.cpp grid.hpp cell.hpp
	$(CC) -o $@ -c $<  $(CFLAGS)

cell.o: cell.cpp cell.hpp
	$(CC) -o $@ -c $<  $(CFLAGS)

grid.o: grid.cpp grid.hpp
	$(CC) -o $@ -c $<  $(CFLAGS)

clean:
	rm -f *.o simulator 

.PHONY: clean
