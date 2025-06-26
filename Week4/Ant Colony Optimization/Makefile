# 編譯器
CXX = g++
# 編譯參數
CXXFLAGS = -std=c++17 -Wall -O2
# 執行檔名
TARGET = main
# 原始碼檔案
SRCS = main.cpp Alg.cpp
# 物件檔
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
