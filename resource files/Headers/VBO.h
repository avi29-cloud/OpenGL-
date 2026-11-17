//
// Created by avi on 24/10/26.
//

#ifndef OPENGL_VBO_H
#define OPENGL_VBO_H

#include "../glad/glad.h"

class VBO
{
    public:
      GLuint ID;
    VBO(GLfloat* vertices, GLsizeiptr size);


    void Bind();
    void Unbind();
    void Delete();

};


#endif //OPENGL_VBO_H
