CC        = g++
OBJ_FILES = main.o cell.o grid.o image.o
CFLAGS	  = -Wall -Wextra -pedantic -std=c++11
OPENCV_FLAGS = -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_imgcodecs
all: simulator

simulator:	$(OBJ_FILES)
		$(CC) $(OBJ_FILES) -o $@ $(CFLAGS) $(OPENCV_FLAGS)

main.o: main.cpp cell.hpp grid.hpp image.hpp
	$(CC) -o $@ -c $<  $(CFLAGS) $(OPENCV_FLAGS)

clean:
	rm -f *.o simulator 

.PHONY: clean

