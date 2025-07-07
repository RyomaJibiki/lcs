# Makefile

# 使用するコンパイラ
CXX = g++
# コンパイル時のオプション
CXXFLAGS = -std=c++17 -O2 -Wall -I./libs
# 生成される実行可能ファイル名
TARGET = server
# コンパイル対象
SRCS = main.cpp lcs.cpp
# 拡張子.cppを .o に置き換えてオブジェクトファイルのリストを生成
OBJS = $(SRCS:.cpp=.o)
# リンクするライブラリ
LIBS =

# 引数無し→実行可能ファイルserverを生成
all: $(TARGET)

# $OBJS がなければ生成
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# オブジェクトファイルの生成
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# make clean でオブジェクトファイルと実行可能ファイルを削除
clean:
	rm -f $(OBJS) $(TARGET)
