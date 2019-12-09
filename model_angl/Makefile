CC        = g++
OBJ_FILES = main.o cell.o grid.o image.o
CFLAGS	  = -Wall -Wextra -pedantic -std=c++11
OPENCV_FLAGS = -lopencv_highgui -lopencv_core -lopencv_imgproc -I/usr/local/opt/opencv@2/include -L/usr/local/opt/opencv@2/lib
all: simulator

simulator:	$(OBJ_FILES)
		$(CC) $(OBJ_FILES) -o $@ $(CFLAGS) $(OPENCV_FLAGS)
		rm -f *.o

main.o: main.cpp cell.hpp grid.hpp image.hpp
	$(CC) -o $@ -c $<  $(CFLAGS) $(OPENCV_FLAGS)

cell.o: cell.cpp cell.hpp
	$(CC) -o $@ -c $<  $(CFLAGS)

grid.o: grid.cpp grid.hpp
	$(CC) -o $@ -c $<  $(CFLAGS)

image.o: image.cpp image.hpp cell.hpp
	$(CC) -o $@ -c $<  $(CFLAGS) $(OPENCV_FLAGS)


clean:
	rm -f *.o simulator 

.PHONY: clean

