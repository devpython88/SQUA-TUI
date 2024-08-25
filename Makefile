CXXFLAGS = -O3 -std=c++17 -fconcepts
LDFLAGS = -lncurses

CXX = g++

SRCS = main.cpp squa.h
OBJS = $(SRCS:.cpp =.o)

TARGET = squa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run:
	./squa

build_library:
	g++ -c squa.h -o squa.o
	g++ -shared -o libsqua.so squa.o
	rm -f squa.o

install:
	cp ./squa.h ./squa_gfx.h /usr/include
