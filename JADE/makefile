CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

OBJS = main.o Alg.o Ackley.o

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Alg.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Alg.o: Alg.cpp Alg.h
	$(CXX) $(CXXFLAGS) -c Alg.cpp

Ackley.o: Ackley.cpp
	$(CXX) $(CXXFLAGS) -c Ackley.cpp

clean:
	rm -f $(OBJS)