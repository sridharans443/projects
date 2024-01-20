INCLUDES = /usr/local/include/opencv4
FILE = faceDetection
CXX = g++
CPPFLAGS = -I$(INCLUDES) -Wall -Werror -g -O0 -std=c++11
LDFLAGS = -L/opt/bin -L/opt/lib
LDLIBS = -lopencv_videoio -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_core -lopencv_objdetect

all: $(FILE).out

$(FILE).out: $(FILE).cpp
	$(CXX) $(CPPFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

run: all
	./$(FILE).out

clean:
	rm -f *.out
