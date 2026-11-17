//
// Created by avi on 25/10/26.
//

#ifndef OPENGL_VAO_H
#define OPENGL_VAO_H
#include<glad/glad.h>
# include "VBO.h"

class VAO
{
  public:
  GLuint ID;
  VAO();

  void LinkAttrib(VBO VBO,GLuint layout, GLuint numComponents, GLenum type,GLsizeiptr stride ,void* offset);
  void Bind();
  void Unbind();
  void Delete();
};

#endif //OPENGL_VAO_H
