//
// Created by avi on 25/10/26.
//

#ifndef OPENGL_VAO_H
#define OPENGL_VAO_H
#include <glad/glad.h>
#include "VBO.h"

class VAO // Holds vertex-buffer bindings and attribute layout configuration.
{
  public:
  GLuint ID; // OpenGL identifier for this vertex array.
  VAO(); // Create a vertex array object.

  void LinkAttrib(VBO& VBO,GLuint layout, GLuint numComponents, GLenum type,GLsizeiptr stride ,void* offset); // Describe one vertex attribute in the supplied buffer.
  void Bind(); // Make this vertex array's configuration active.
  void Unbind(); // Clear the active vertex-array binding.
  void Delete(); // Release the vertex array's OpenGL resource.
};

#endif
