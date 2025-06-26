# 編譯器與參數
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# 目標執行檔
TARGET = main

# 原始碼
SRCS = main.cpp Alg.cpp OneMax.cpp
OBJS = $(SRCS:.cpp=.o)

# 預設目標：產生執行檔
all: $(TARGET)

# 連結物件檔生成執行檔
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 每個 .cpp 對應一個 .o（編譯規則）
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清除所有編譯產物
clean:
	rm -f $(TARGET) *.o