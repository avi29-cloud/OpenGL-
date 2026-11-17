//
// Created by avi on 24/10/26.
//

#ifndef OPENGL_SHADERCLASS_H
#define OPENGL_SHADERCLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader // Compiles shader source files and manages the linked GPU program.
{
public:
    GLuint ID; // OpenGL identifier for the linked shader program.
    Shader(const char* vertexFile, const char* fragmentFile); // Build a program from vertex and fragment shader files.

    void Activate(); // Select this program for subsequent draw calls.
    void Delete(); // Release the linked program.
};


#endif
