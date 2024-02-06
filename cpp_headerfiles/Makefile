#$INCLUDES += -I/usr/local/include/opencv4
#INCLUDES = /usr/local/include/opencv4
INCLUDES += -I/opt/opencv_4.5.2/include/opencv4/
INCLUDES += -I/home/ubilinux/scp/hikv_camera/
INCLUDES += -I/opt/MVS/include/
CPP_FILES = main.cpp \
			hikv_camera/hikv_camera.cpp

FILE = openCV
CXX = g++
CSTD = c++11
CPPFLAGS += -Wall -Werror -Wpedantic -g -O0 -std=$(CSTD)

LDPATH += -L/usr/local/lib/
LDPATH += -L/opt/opencv_4.5.2/lib/
LDPATH += -L/opt/MVS/lib/64/
LDFLAGS += -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lMvCameraControl

OBJS:=$(CPP_FILES:.cpp=.o)

%.o: %.cpp 
	$(CXX) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

$(FILE).out: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDPATH) $^ -o $(FILE).out $(LDFLAGS)

.PHONY: build 
build: all

all: 
	make $(FILE).out	

run:
	make clean
	make all
	./$(FILE).out

clean:
	rm -f *.out *.o **/*.o