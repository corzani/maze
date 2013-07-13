CXXFLAGS = -O3	-g -Wall -fmessage-length=0

OBJS =		Maze.o MazeDebug.o MazePng.o main.o

LIBS =		-lpng

TARGET =	maze

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
