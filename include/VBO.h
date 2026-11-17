//
// Created by avi on 24/10/26.
//

#ifndef OPENGL_VBO_H
#define OPENGL_VBO_H

#include <glad/glad.h>

class VBO // Represents an OpenGL buffer containing vertex data.
{
   public:
     GLuint ID; // OpenGL identifier used to access this buffer.
   VBO(GLfloat* vertices, GLsizeiptr size); // Upload vertex data into a newly created buffer.


   void Bind(); // Make this buffer the active vertex-data buffer.
   void Unbind(); // Clear the active vertex-data buffer binding.
   void Delete(); // Free the buffer's OpenGL resource.

};


#endif
