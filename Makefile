CXXFLAGS = -O3	-g -Wall -fmessage-length=0

OBJS =		Maze.o MazeDebug.o main.o

LIBS =

TARGET =	maze

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
