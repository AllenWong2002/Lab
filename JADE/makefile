CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

OBJS = main.o Alg.o TestFunction.o

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Alg.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Alg.o: Alg.cpp Alg.h
	$(CXX) $(CXXFLAGS) -c Alg.cpp

TestFunction.o: TestFunction.cpp
	$(CXX) $(CXXFLAGS) -c TestFunction.cpp

clean:
	rm -f $(OBJS)