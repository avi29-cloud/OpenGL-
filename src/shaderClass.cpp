//
// Created by avi on 24/10/26.
//
#include <iostream>
#include "shaderClass.h"

GLint success; // Receives OpenGL's compile and link status values.
char shaderlog[512]; // Reused to capture shader compilation and program-link diagnostics.

std::string get_file_contents(const char* filename)
{
    // Read the complete shader file in binary mode to preserve its source bytes.
    std::ifstream in (filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        // Size the string from the file length, then return to the beginning to read it.
        in.seekg(0,std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    // Surface file-open failures to the caller instead of compiling empty source.
    throw (errno);
}
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    // Keep the source strings alive while OpenGL compiles their contents.
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create shader objects for the two programmable pipeline stages.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Pass null-terminated source pointers to the OpenGL shader compiler.
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    // Compile the vertex stage and report any compiler diagnostics.
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);


    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, shaderlog);
        std::cerr << "Vertex shader error:\n" << shaderlog << '\n';
    }


    // Compile the fragment stage and report any compiler diagnostics.
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, shaderlog);
        std::cerr << "Fragment shader error:\n" << shaderlog << '\n';
    }

    // Create a program and attach both compiled stages.
     ID =glCreateProgram();

    glAttachShader(ID,vertexShader);
    glAttachShader(ID,fragmentShader);

    // Link the stages into one executable program and report link failures.
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, shaderlog);
        std::cerr << "Shader link error:\n" << shaderlog << '\n';
    }


    // The linked program retains the shader code, so the temporary objects can be deleted.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
  // Use this linked program for subsequent rendering commands.
  glUseProgram(ID);
}

void Shader::Delete()
{
    // Release the linked program object.
    glDeleteProgram(ID);
}

