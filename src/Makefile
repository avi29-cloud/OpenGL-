# Select the C++ compiler and the language and header-search settings.
CXX = g++
CXXFLAGS = -std=c++17 -O2 -I../include -DGLM_ENABLE_EXPERIMENTAL -DOPENGL_ASSET_DIR=\"..\"

# Link GLFW, OpenGL, and the Linux system libraries used by the application.
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# List project sources, including the GLAD and stb_image implementation units.
SRC = main.cpp Camera.cpp shaderClass.cpp VAO.cpp VBO.cpp EBO.cpp stb.cpp Texture.cpp glad.c
TARGET = Test

# Build the executable by default.
all: $(TARGET)

# Rebuild the executable when one of its listed sources changes.
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Mark utility targets as commands rather than file names.
.PHONY: test clean

# Build and launch the application.
test: $(TARGET)
	./$(TARGET)

# Remove the generated executable.
clean:
	rm -f $(TARGET)