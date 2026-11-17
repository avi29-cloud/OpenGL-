//
// Created by avi on 25/10/26.
//

#ifndef OPENGL_EBO_H
#define OPENGL_EBO_H
#include <glad/glad.h>

class EBO
{
public :
    GLuint ID;
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};
#endif //OPENGL_EBO_H
