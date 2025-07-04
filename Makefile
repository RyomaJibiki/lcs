# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -I./libs
TARGET = server
SRCS = main.cpp lcs.cpp
OBJS = $(SRCS:.cpp=.o)
LIBS =

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
