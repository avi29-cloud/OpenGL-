cmake_minimum_required(VERSION 3.16)

project(OpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(Test
    src/Camera.cpp
    src/EBO.cpp
    src/Texture.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/glad.c
    src/main.cpp
    src/shaderClass.cpp
    src/stb.cpp
)

target_include_directories(Test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_definitions(Test PRIVATE
    GLM_ENABLE_EXPERIMENTAL
    OPENGL_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(Test PRIVATE glfw OpenGL::GL glm::glm)
