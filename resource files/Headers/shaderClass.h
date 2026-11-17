//
// Created by avi on 24/10/26.
//

#ifndef OPENGL_SHADERCLASS_H
#define OPENGL_SHADERCLASS_H

#include "../glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
};


#endif //OPENGL_SHADERCLASS_H
