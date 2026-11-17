//
// Created by avi on 25/10/26.
//
#include "VAO.h"

VAO::VAO()
{
  // Create an object that will retain vertex-buffer and attribute settings.
  glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO,GLuint layout, GLuint numComponents, GLenum type,GLsizeiptr stride ,void* offset)
{
  // Configure the requested attribute while this vertex buffer is bound.
  VBO.Bind();
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

  // Enable the attribute so the shader can read it during drawing.
  glEnableVertexAttribArray(layout );
  VBO.Unbind();
}

void VAO::Bind()
{
 // Activate the stored vertex-input configuration.
 glBindVertexArray(ID);
}

void VAO::Unbind()
{
 // Stop using this vertex-input configuration.
 glBindVertexArray(0);
}

void VAO::Delete()
{
 // Release the vertex array object from OpenGL.
 glDeleteVertexArrays(1, &ID);
}