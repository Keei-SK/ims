FLAGS= -std=c++11
LDFLAGS= -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_imgcodecs

all: evacuation

evacuation:
	g++ $(FLAGS) -o evacuation main.cpp Cell.cpp CA.cpp Image.cpp $(LDFLAGS)

run: evacuation
	./evacuation experiments/E112_full_with_alpha

clean:
	rm -rf evacuation *.o
