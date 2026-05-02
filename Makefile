CXX = g++
CXXFLAGS = -std=c++17 -O2 -I.
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

SRC = main.cpp glad.c
TARGET = Test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

.PHONY: test clean

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)