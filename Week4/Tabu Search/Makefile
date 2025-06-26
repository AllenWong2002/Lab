# 編譯器與參數
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# 目標執行檔
TARGET = main

# 原始碼與標頭檔
SRCS = main.cpp Alg.cpp OneMax.cpp Deception.cpp
OBJS = $(SRCS:.cpp=.o)

# 預設目標
all: $(TARGET)
	
# 連結目標
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 編譯每個 .cpp 為 .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清除編譯產物
clean:
	rm -f $(TARGET) $(OBJS)
