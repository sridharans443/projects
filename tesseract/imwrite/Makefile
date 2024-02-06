#INCLUDES = /usr/local/include/opencv4
INCLUDES = /opt/opencv_4.5.2/include/opencv4/
FILE = testTimeDelay
CXX = g++					#-Werror 
CPPFLAGS = -I$(INCLUDES) -Wall -g -O0 -std=c++11
LDFLAGS = -L/opt/opencv_4.5.2/bin -L/opt/opencv_4.5.2/lib
LDLIBS = -lopencv_videoio -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_core

all: $(FILE).out

$(FILE).out: $(FILE).cpp
	$(CXX) $(CPPFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

run: all
	./$(FILE).out

clean:
	rm -f *.out
